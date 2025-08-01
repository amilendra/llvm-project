// DEFINE: %{entry_point} = za0_d_f64
// DEFINE: %{compile} = mlir-opt %s -test-lower-to-arm-sme -test-lower-to-llvm
// DEFINE: %{run} = %mcr_aarch64_cmd \
// DEFINE:  -march=aarch64 -mattr=+sve,+sme \
// DEFINE:  -e %{entry_point} -entry-point-result=i32 \
// DEFINE:  -shared-libs=%native_mlir_runner_utils,%native_mlir_c_runner_utils,%native_arm_sme_abi_shlib

// RUN: %{compile} | %{run} | FileCheck %s --check-prefix=CHECK-ZA0_D

// REDEFINE: %{entry_point} = load_store_two_za_s_tiles
// RUN: %{compile} | %{run} | FileCheck %s

// Integration tests demonstrating load/store to/from SME ZA tile.

// This test verifies a 64-bit element ZA with FP64 data is correctly
// loaded/stored to/from memory.
func.func @za0_d_f64() -> i32 {
  %c0 = arith.constant 0 : index
  %c0_f64 = arith.constant 0.0 : f64
  %c1_f64 = arith.constant 1.0 : f64
  %c1_index = arith.constant 1 : index

  // "svl" refers to the Streaming Vector Length and "svl_d" the number of
  // 64-bit elements in a vector of SVL bits.
  %svl_d = arm_sme.streaming_vl <double>

  // Allocate "mem1" and fill each "row" with row number.
  //
  // For example, assuming an SVL of 256-bits:
  //
  //   0.1, 0.1, 0.1, 0.1
  //   1.1, 1.1, 1.1, 1.1
  //   2.1, 2.1, 2.1, 2.1
  //   3.1, 3.1, 3.1, 3.1
  //
  %mem1 = memref.alloca(%svl_d, %svl_d) : memref<?x?xf64>
  %init_0 = arith.constant 0.1 : f64
  scf.for %i = %c0 to %svl_d step %c1_index iter_args(%val = %init_0) -> (f64) {
    %splat_val = vector.broadcast %val : f64 to vector<[2]xf64>
    vector.store %splat_val, %mem1[%i, %c0] : memref<?x?xf64>, vector<[2]xf64>
    %val_next = arith.addf %val, %c1_f64 : f64
    scf.yield %val_next : f64
  }

  // Dump "mem1". The smallest SVL is 128-bits so the tile will be at least
  // 2x2xi64.
  //
  // CHECK-ZA0_D:      ( 0.1, 0.1
  // CHECK-ZA0_D-NEXT: ( 1.1, 1.1
  scf.for %i = %c0 to %svl_d step %c1_index {
    %tileslice = vector.load %mem1[%i, %c0] : memref<?x?xf64>, vector<[2]xf64>
    vector.print %tileslice : vector<[2]xf64>
  }

  // Load ZA0.D from "mem1"
  %za0_d = vector.load %mem1[%c0, %c0] : memref<?x?xf64>, vector<[2]x[2]xf64>

  // Allocate "mem2" to store ZA0.D to
  %mem2 = memref.alloca(%svl_d, %svl_d) : memref<?x?xf64>

  // Zero "mem2"
  scf.for %i = %c0 to %svl_d step %c1_index {
    scf.for %j = %c0 to %svl_d step %c1_index {
      memref.store %c0_f64, %mem2[%i, %j] : memref<?x?xf64>
    }
  }

  // Verify "mem2" is zeroed by doing an add reduction with initial value of
  // zero
  %init_0_f64 = arith.constant 0.0 : f64
  %add_reduce = scf.for %vnum = %c0 to %svl_d step %c1_index iter_args(%iter = %init_0_f64) -> (f64) {
    %row = vector.load %mem2[%vnum, %c0] : memref<?x?xf64>, vector<[2]xf64>

    %inner_add_reduce = scf.for %offset = %c0 to %svl_d step %c1_index iter_args(%inner_iter = %init_0_f64) -> (f64) {
      %t = vector.extract %row[%offset] : f64 from vector<[2]xf64>
      %inner_add_reduce_next = arith.addf %inner_iter, %t : f64
      scf.yield %inner_add_reduce_next : f64
    }

    %add_reduce_next = arith.addf %iter, %inner_add_reduce : f64
    scf.yield %add_reduce_next : f64
  }

  // CHECK-ZA0_D: 0
  vector.print %add_reduce : f64

  // Dump zeroed "mem2". The smallest SVL is 128-bits so the tile will be at
  // least 2x2xi64.
  //
  // CHECK-ZA0_D-NEXT: ( 0, 0
  // CHECK-ZA0_D-NEXT: ( 0, 0
  scf.for %i = %c0 to  %svl_d  step %c1_index{
    %tileslice = vector.load %mem2[%i, %c0] : memref<?x?xf64>, vector<[2]xf64>
    vector.print %tileslice : vector<[2]xf64>
  }

  // Verify "mem1" != "mem2"
  %init_1 = arith.constant 1 : i64
  %mul_reduce_0 = scf.for %vnum = %c0 to %svl_d step %c1_index iter_args(%iter = %init_1) -> (i64) {
    %row_1 = vector.load %mem1[%vnum, %c0] : memref<?x?xf64>, vector<[2]xf64>
    %row_2 = vector.load %mem2[%vnum, %c0] : memref<?x?xf64>, vector<[2]xf64>
    %cmp = arith.cmpf one, %row_1, %row_2 : vector<[2]xf64>

    %inner_mul_reduce = scf.for %i = %c0 to %svl_d step %c1_index iter_args(%inner_iter = %init_1) -> (i64) {
      %t = vector.extract %cmp[%i] : i1 from vector<[2]xi1>
      %t_i64 = arith.extui %t : i1 to i64
      %inner_mul_reduce_next = arith.muli %inner_iter, %t_i64 : i64
      scf.yield %inner_mul_reduce_next : i64
    }

    %mul_reduce_next = arith.muli %iter, %inner_mul_reduce : i64
    scf.yield %mul_reduce_next : i64
  }

  // CHECK-ZA0_D: 1
  vector.print %mul_reduce_0 : i64

  // Store ZA0.D to "mem2"
  vector.store %za0_d, %mem2[%c0, %c0] : memref<?x?xf64>, vector<[2]x[2]xf64>

  // Verify "mem1" == "mem2"
  %mul_reduce_1 = scf.for %vnum = %c0 to %svl_d step %c1_index iter_args(%iter = %init_1) -> (i64) {
    %row_1 = vector.load %mem1[%vnum, %c0] : memref<?x?xf64>, vector<[2]xf64>
    %row_2 = vector.load %mem2[%vnum, %c0] : memref<?x?xf64>, vector<[2]xf64>
    %cmp = arith.cmpf oeq, %row_1, %row_2 : vector<[2]xf64>

    %inner_mul_reduce = scf.for %i = %c0 to %svl_d step %c1_index iter_args(%inner_iter = %init_1) -> (i64) {
      %t = vector.extract %cmp[%i] : i1 from vector<[2]xi1>
      %t_i64 = arith.extui %t : i1 to i64
      %inner_mul_reduce_next = arith.muli %inner_iter, %t_i64 : i64
      scf.yield %inner_mul_reduce_next : i64
    }

    %mul_reduce_next = arith.muli %iter, %inner_mul_reduce : i64
    scf.yield %mul_reduce_next : i64
  }

  // CHECK-ZA0_D-NEXT: 1
  vector.print %mul_reduce_1 : i64

  // Dump "mem2". The smallest SVL is 128-bits so the tile will be at least
  // 2x2xi64.
  //
  // CHECK-ZA0_D-NEXT: ( 0.1, 0.1
  // CHECK-ZA0_D-NEXT: ( 1.1, 1.1
  scf.for %i = %c0 to %svl_d step %c1_index{
    %tileslice = vector.load %mem2[%i, %c0] : memref<?x?xf64>, vector<[2]xf64>
    vector.print %tileslice : vector<[2]xf64>
  }

  %c0_i32 = arith.constant 0 : i32
  return %c0_i32 : i32
}

// This test loads two 32-bit element ZA tiles from memory and stores them back
// to memory in reverse order. This verifies the memref indices for the vector
// load and store are correctly preserved since the second tile is offset from
// the first tile.
func.func @load_store_two_za_s_tiles() -> i32 {
  %c0 = arith.constant 0 : index
  %c0_i32 = arith.constant 0 : i32
  %c1_i32 = arith.constant 1 : i32
  %c2_i32 = arith.constant 2 : i32
  %c1_index = arith.constant 1 : index
  %c2_index = arith.constant 2 : index

  // "svl" refers to the Streaming Vector Length and "svl_s" can mean either:
  // * the number of 32-bit elements in a vector of SVL bits.
  // * the number of tile slices (1d vectors) in a 32-bit element tile.
  %svl_s = arm_sme.streaming_vl <word>

  // Allocate memory for two 32-bit element tiles.
  %svl_s_x_2 = arith.muli %svl_s, %c2_index : index
  %mem1 = memref.alloca(%svl_s_x_2, %svl_s) : memref<?x?xi32>

  // Fill memory that tile 1 will be loaded from with '1' and '2' for tile 2.
  //
  // For example, assuming an SVL of 128-bits and two 4x4xi32 tiles:
  //
  // tile 1
  //
  //   1, 1, 1, 1
  //   1, 1, 1, 1
  //   1, 1, 1, 1
  //   1, 1, 1, 1
  //
  // tile 2
  //
  //   2, 2, 2, 2
  //   2, 2, 2, 2
  //   2, 2, 2, 2
  //   2, 2, 2, 2
  //
  scf.for %i = %c0 to %svl_s_x_2 step %c1_index {
    %isFirstTile = arith.cmpi ult, %i, %svl_s : index
    %val = scf.if %isFirstTile -> i32 {
      scf.yield %c1_i32 : i32
    } else {
      scf.yield %c2_i32 : i32
    }
    %splat_val = vector.broadcast %val : i32 to vector<[4]xi32>
    vector.store %splat_val, %mem1[%i, %c0] : memref<?x?xi32>, vector<[4]xi32>
  }

  // Dump "mem1". The smallest SVL is 128-bits so each tile will be at least
  // 4x4xi32.
  //
  // CHECK:      ( 1, 1, 1, 1
  // CHECK-NEXT: ( 1, 1, 1, 1
  // CHECK-NEXT: ( 1, 1, 1, 1
  // CHECK-NEXT: ( 1, 1, 1, 1
  // CHECK:      ( 2, 2, 2, 2
  // CHECK-NEXT: ( 2, 2, 2, 2
  // CHECK-NEXT: ( 2, 2, 2, 2
  // CHECK-NEXT: ( 2, 2, 2, 2
  scf.for %i = %c0 to %svl_s_x_2 step %c1_index {
    %tileslice = vector.load %mem1[%i, %c0] : memref<?x?xi32>, vector<[4]xi32>
    vector.print %tileslice : vector<[4]xi32>
  }

  // Load tile 1 from memory
  %za0_s = vector.load %mem1[%c0, %c0] : memref<?x?xi32>, vector<[4]x[4]xi32>

  // Load tile 2 from memory
  %za1_s = vector.load %mem1[%svl_s, %c0] : memref<?x?xi32>, vector<[4]x[4]xi32>

  // Allocate new memory to store tiles to
  %mem2 = memref.alloca(%svl_s_x_2, %svl_s)  : memref<?x?xi32>

  // Zero new memory
  scf.for %i = %c0 to %svl_s_x_2 step %c1_index {
    memref.store %c0_i32, %mem2[%i, %c0] : memref<?x?xi32>
  }

  // Stores tiles back to (new) memory in reverse order

  // Store tile 2 to memory
  vector.store %za1_s, %mem2[%c0, %c0] : memref<?x?xi32>, vector<[4]x[4]xi32>

  // Store tile 1 to memory
  vector.store %za0_s, %mem2[%svl_s, %c0] : memref<?x?xi32>, vector<[4]x[4]xi32>

  // Dump "mem2" and check the tiles were stored in reverse order. The smallest
  // SVL is 128-bits so the tiles will be at least 4x4xi32.
  //
  // CHECK:      TILE BEGIN
  // CHECK-NEXT: ( 2, 2, 2, 2
  // CHECK-NEXT: ( 2, 2, 2, 2
  // CHECK-NEXT: ( 2, 2, 2, 2
  // CHECK-NEXT: ( 2, 2, 2, 2
  // CHECK:      TILE END
  // CHECK-NEXT: TILE BEGIN
  // CHECK-NEXT: ( 1, 1, 1, 1
  // CHECK-NEXT: ( 1, 1, 1, 1
  // CHECK-NEXT: ( 1, 1, 1, 1
  // CHECK-NEXT: ( 1, 1, 1, 1
  // CHECK:      TILE END
  vector.print str "TILE BEGIN\n"
  scf.for %i = %c0 to %svl_s_x_2 step %c1_index {
    %av = vector.load %mem2[%i, %c0] : memref<?x?xi32>, vector<[4]xi32>
    vector.print %av : vector<[4]xi32>

    %tileSizeMinusStep = arith.subi %svl_s, %c1_index : index
    %isNextTile = arith.cmpi eq, %i, %svl_s : index
    scf.if %isNextTile {
      vector.print str "TILE END\n"
      vector.print str "TILE BEGIN\n"
    }
  }
  vector.print str "TILE END\n"

  return %c0_i32 : i32
}

