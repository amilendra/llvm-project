// RUN: mlir-opt %s -split-input-file -verify-diagnostics

// Asking the dimension of a 0-D shape doesn't make sense.
func.func @dim_0_ranked(%arg : tensor<f32>, %arg1 : index) {
  tensor.dim %arg, %arg1 : tensor<f32> // expected-error {{'tensor.dim' op operand #0 must be non-0-ranked or unranked tensor, but got 'tensor<f32>'}}
  return
}

// -----

func.func @tensor.cast_mismatching_constants(%arg0: tensor<1xf32>) {
  // expected-error@+1 {{operand type 'tensor<1xf32>' and result type 'tensor<2xf32>' are cast incompatible}}
  %0 = tensor.cast %arg0 : tensor<1xf32> to tensor<2xf32>
  return
}

// -----

func.func @concat_empty() {
  // expected-error@+1 {{requires at least one input}}
  %0 = tensor.concat dim(0) : () -> tensor<1x2x3xf32>
  return
}

// -----

func.func @concat_rank_mismatch(%arg0: tensor<1xf32>, %arg1: tensor<1xf32>) {
  // expected-error@+1 {{rank of concatenated inputs must match result rank}}
  %0 = tensor.concat dim(0) %arg0, %arg1 : (tensor<1xf32>, tensor<1xf32>) -> tensor<2x1xf32>
  return
}

// -----

func.func @concat_dim_out_of_range(%arg0: tensor<3xf32>) {
  // expected-error@+1 {{concatenation dim must be less than the tensor rank}}
  %0 = tensor.concat dim(1) %arg0 : (tensor<3xf32>) -> tensor<3xf32>
  return
}

// -----

func.func @concat_element_type_mismatch(%arg0: tensor<3xf32>, %arg1: tensor<3xi32>) {
  // expected-error@+1 {{inputs and result element type must match}}
  %0 = tensor.concat dim(0) %arg0, %arg1 : (tensor<3xf32>, tensor<3xi32>) -> tensor<3xf32>
  return
}

// -----

func.func @concat_incompatible_input_types(%arg0: tensor<3x4xf32>, %arg1: tensor<4x5xf32>) {
  // expected-error@+1 {{static concatenation size mismatch along non-concatenated dimension 1}}
  %0 = tensor.concat dim(0) %arg0, %arg1 : (tensor<3x4xf32>, tensor<4x5xf32>) -> tensor<7x5xf32>
  return
}

// -----

func.func @concat_static_shape_mismatch(%arg0: tensor<3xf32>) {
  // expected-error@+1 {{result type 'tensor<7xf32>'does not match inferred shape 'tensor<6xf32>' static sizes}}
  %0 = tensor.concat dim(0) %arg0, %arg0 : (tensor<3xf32>, tensor<3xf32>) -> tensor<7xf32>
  return
}

// -----

func.func @extract_too_many_indices(%arg0: tensor<?xf32>) {
  // expected-error@+1 {{incorrect number of indices for extract_element}}
  %0 = tensor.extract %arg0[] : tensor<?xf32>
  return
}

// -----

func.func @insert_too_many_indices(%arg0: f32, %arg1: tensor<?xf32>) {
  // expected-error@+1 {{incorrect number of indices}}
  %0 = tensor.insert %arg0 into %arg1[] : tensor<?xf32>
  return
}

// -----

func.func @tensor.from_elements_wrong_result_type() {
  // expected-error@+2 {{'tensor.from_elements' invalid kind of type specified: expected builtin.tensor, but found 'tensor<*xi32>'}}
  %c0 = arith.constant 0 : i32
  %0 = tensor.from_elements %c0 : tensor<*xi32>
  return
}

// -----

func.func @tensor.from_elements_wrong_elements_count() {
  // expected-error@+2 {{number of operands and types do not match: got 1 operands and 2 types}}
  %c0 = arith.constant 0 : index
  %0 = tensor.from_elements %c0 : tensor<2xindex>
  return
}

// -----

func.func @tensor.generate(%m : index)
    -> tensor<?x3x?xf32> {
  // expected-error @+1 {{must have as many index operands as dynamic extents in the result type}}
  %tnsr = tensor.generate %m {
    ^bb0(%i : index, %j : index, %k : index):
      %elem = arith.constant 8.0 : f32
      tensor.yield %elem : f32
  } : tensor<?x3x?xf32>
  return %tnsr : tensor<?x3x?xf32>
}

// -----

func.func @tensor.generate(%m : index, %n : index)
    -> tensor<?x3x?xf32> {
  // expected-error @+1 {{must have one body argument per input dimension}}
  %tnsr = tensor.generate %m, %n {
    ^bb0(%i : index, %j : index):
      %elem = arith.constant 8.0 : f32
      tensor.yield %elem : f32
  } : tensor<?x3x?xf32>
  return %tnsr : tensor<?x3x?xf32>
}

// -----

func.func @tensor.generate(%m : index, %n : index)
    -> tensor<?x3x?xf32> {
  // expected-error @+1 {{all body arguments must be index}}
  %tnsr = tensor.generate %m, %n {
    ^bb0(%i : index, %j : index, %k : i64):
      %elem = arith.constant 8.0 : f32
      tensor.yield %elem : f32
  } : tensor<?x3x?xf32>
  return %tnsr : tensor<?x3x?xf32>
}

// -----

func.func @tensor.generate(%m : index, %n : index)
    -> tensor<?x3x?xf32> {
  // expected-error @+4 {{'func.return' op expects parent op 'func.func'}}
  %tnsr = tensor.generate %m, %n {
    ^bb0(%i : index, %j : index, %k : index):
      %elem = arith.constant 8.0 : f32
      func.return %elem : f32
  } : tensor<?x3x?xf32>
  return %tnsr : tensor<?x3x?xf32>
}

// -----

func.func @tensor.generate(%m : index, %n : index)
    -> tensor<?x3x?xf32> {
  // expected-error @+1 {{body must be terminated with a `yield` operation of the tensor element type}}
  %tnsr = tensor.generate %m, %n {
    ^bb0(%i : index, %j : index, %k : index):
      %elem = arith.constant 8 : i32
      tensor.yield %elem : i32
  } : tensor<?x3x?xf32>
  return %tnsr : tensor<?x3x?xf32>
}

// -----

func.func @tensor.reshape_element_type_mismatch(
       %buf: tensor<*xf32>, %shape: tensor<1xi32>) {
  // expected-error @+1 {{element types of source and destination tensor types should be the same}}
  tensor.reshape %buf(%shape) : (tensor<*xf32>, tensor<1xi32>) -> tensor<?xi32>
}

// -----

func.func @tensor.reshape_dst_ranked_shape_unranked(
       %buf: tensor<*xf32>, %shape: tensor<?xi32>) {
  // expected-error @+1 {{cannot use shape operand with dynamic length to reshape to statically-ranked tensor type}}
  tensor.reshape %buf(%shape) : (tensor<*xf32>, tensor<?xi32>) -> tensor<?xf32>
}

// -----

func.func @tensor.reshape_dst_shape_rank_mismatch(
       %buf: tensor<*xf32>, %shape: tensor<1xi32>) {
  // expected-error @+1 {{length of shape operand differs from the result's tensor rank}}
  tensor.reshape %buf(%shape)
    : (tensor<*xf32>, tensor<1xi32>) -> tensor<?x?xf32>
}

// -----

func.func @tensor.reshape_num_elements_mismatch(
       %buf: tensor<1xf32>, %shape: tensor<1xi32>) {
  // expected-error @+1 {{source and destination tensor should have the same number of elements}}
  tensor.reshape %buf(%shape)
    : (tensor<1xf32>, tensor<1xi32>) -> tensor<10xf32>
}

// -----

func.func @extract_slice_wrong_result_rank(%t: tensor<?xf32>, %idx : index) {
  // expected-error @+1 {{expected rank to be smaller or equal to the other rank.}}
  %0 = tensor.extract_slice %t[0][4][1] : tensor<?xf32> to tensor<?x?xf32>
  return
}

// -----

func.func @extract_slice_wrong_result_rank(%t: tensor<?xf32>, %idx : index) {
  // expected-error @+1 {{expected element type to be 'f32'}}
  %0 = tensor.extract_slice %t[0][4][1] : tensor<?xf32> to tensor<4xi8>
  return
}


// -----

func.func @extract_slice_size_and_output_dim_mismatch_static_size(%t: tensor<16xf32>) {
  // expected-error @+1 {{expected type to be 'tensor<4xf32>' or a rank-reduced version. (size mismatch)}}
  %0 = tensor.extract_slice %t[0][4][1]
    : tensor<16xf32> to tensor<6xf32>
  return
}

// -----

func.func @extract_slice_size_and_output_dim_mismatch_dynamic_size(%t: tensor<?xf32>, %idx : index) {
  // expected-error @+2 {{expected type to be 'tensor<?xf32>' or a rank-reduced version. (size mismatch)}}
  %c4 = arith.constant 4 : index
  %0 = tensor.extract_slice %t[0][%c4][1] : tensor<?xf32> to tensor<4xi8>
  return
}

// -----

func.func @extract_slice_wrong_static_type(%t: tensor<8x16x4xf32>, %idx : index) {
  // expected-error @+1 {{expected type to be 'tensor<?x4x4xf32>' or a rank-reduced version. (size mismatch)}}
  %0 = tensor.extract_slice %t[0, 0, 0][%idx, 4, 4][1, 1, 1]
    : tensor<8x16x4xf32> to tensor<4x4x4xf32>
  return
}

// -----

func.func @extract_slice_wrong_dynamic_type(%t: tensor<8x16x4xf32>, %idx : index) {
  // expected-error @+1 {{expected type to be 'tensor<4x4x4xf32>' or a rank-reduced version. (size mismatch)}}
  %0 = tensor.extract_slice %t[0, 2, 0][4, 4, 4][1, 1, 1]
    : tensor<8x16x4xf32> to tensor<?x4x4xf32>
  return
}

// -----

func.func @illegal_num_offsets(%arg0 : tensor<?x?x?xf32>, %arg1 : index, %arg2 : index) {
  // expected-error@+1 {{expected 3 offset values}}
  %0 = tensor.extract_slice %arg0[0, 0] [%arg1, %arg2] [1, 1] : tensor<?x?x?xf32> to tensor<?x?x?xf32>
  return
}

// -----

func.func @extract_slice_offset_out_of_bounds(%arg0: tensor<10xf32>) {
  // expected-error@+1 {{offset 0 is out-of-bounds: 10 >= 10}}
  %0 = tensor.extract_slice %arg0 [10][1][1] : tensor<10xf32> to tensor<1xf32>
  return
}

// -----

func.func @extract_slice_runs_out_of_bounds(%arg0: tensor<9xf32>) {
  // expected-error@+1 {{slice along dimension 0 runs out-of-bounds: 9 >= 9}}
  %0 = tensor.extract_slice %arg0 [3][4][2] : tensor<9xf32> to tensor<4xf32>
  return
}

// -----

func.func @insert_slice_wrong_result_rank(%t1: tensor<?xf32>, %t2: tensor<?x?xf32>, %idx : index) {
  // expected-error @+1 {{expected rank to be smaller or equal to the other rank.}}
  %0 = tensor.insert_slice %t2 into %t1[0][4][1] : tensor<?x?xf32> into tensor<?xf32>

  return
}

// -----

func.func @insert_slice_wrong_result_rank(%t1: tensor<4xi8>, %t2: tensor<?xf32>, %idx : index) {
  // expected-error @+1 {{expected element type to be 'f32'}}
  %0 = tensor.insert_slice %t1 into %t2[0][4][1] : tensor<4xi8> into tensor<?xf32>

  return
}

// -----

func.func @insert_slice_wrong_static_type(%t1: tensor<4x4x4xf32>, %t2: tensor<8x16x4xf32>, %idx : index) {
  // expected-error @+1 {{expected type to be 'tensor<?x4x4xf32>' or a rank-reduced version. (size mismatch)}}
  %0 = tensor.insert_slice %t1 into %t2[0, 0, 0][%idx, 4, 4][1, 1, 1]
    : tensor<4x4x4xf32> into tensor<8x16x4xf32>

  return
}

// -----

func.func @insert_slice_wrong_dynamic_type(%t1: tensor<?x4x4xf32>, %t2: tensor<8x16x4xf32>, %idx : index) {
  // expected-error @+1 {{expected type to be 'tensor<4x4x4xf32>' or a rank-reduced version. (size mismatch)}}
  %0 = tensor.insert_slice %t1 into %t2[0, 2, 0][4, 4, 4][1, 1, 1]
    : tensor<?x4x4xf32> into tensor<8x16x4xf32>

  return
}

// -----

func.func @insert_slice_offset_out_of_bounds(%arg0: tensor<1xf32>, %arg1: tensor<10xf32>) {
  // expected-error@+1 {{offset 0 is out-of-bounds: 10 >= 10}}
  %0 = tensor.insert_slice %arg0 into %arg1 [10][1][1] : tensor<1xf32> into tensor<10xf32>
  return
}

// -----

func.func @insert_slice_runs_out_of_bounds(%arg0: tensor<4xf32>, %arg1: tensor<9xf32>) {
  // expected-error@+1 {{slice along dimension 0 runs out-of-bounds: 9 >= 9}}
  %0 = tensor.insert_slice %arg0 into %arg1 [3][4][2] : tensor<4xf32> into tensor<9xf32>
  return
}

// -----

func.func @illegal_expanding_reshape_static_tensor
    (%arg0: tensor<2x3x20xf32>) -> tensor<2x3x2x4x5xf32> {
  // expected-error @+1 {{expected dimension 2 of collapsed type to be static value of 40}}
  %0 = tensor.expand_shape %arg0 [[0], [1], [2, 3, 4]] output_shape [2, 3, 2, 4, 5]
      : tensor<2x3x20xf32> into tensor<2x3x2x4x5xf32>
  return %0 : tensor<2x3x2x4x5xf32>
}

// -----

func.func @illegal_collapsing_reshape_static_tensor
    (%arg0: tensor<2x3x2x4x5xf32>) -> tensor<2x3x20xf32> {
  // expected-error @+1 {{expected dimension 2 of collapsed type to be static value of 40}}
  %0 = tensor.collapse_shape %arg0 [[0], [1], [2, 3, 4]]
      : tensor<2x3x2x4x5xf32> into tensor<2x3x20xf32>
  return %0 : tensor<2x3x20xf32>
}

// -----

func.func @illegal_expanding_reshape_mixed_tensor(%arg0 : tensor<?x?xf32>, %sz0: index)
    -> tensor<?x4x5xf32> {
  // expected-error @+1 {{expected dimension 1 of collapsed type to be static value of 5}}
  %0 = tensor.expand_shape %arg0 [[0, 1], [2]] output_shape [%sz0, 4, 5]
      : tensor<?x?xf32> into tensor<?x4x5xf32>
  return %0 : tensor<?x4x5xf32>
}

// -----

func.func @illegal_expanding_reshape_mixed_tensor_2(%arg0 : tensor<?x?xf32>, %sz0: index)
    -> tensor<?x4x5xf32> {
  // expected-error @+1 {{expected dimension 1 of collapsed type to be static value of 20}}
  %0 = tensor.expand_shape %arg0 [[0], [1, 2]] output_shape [%sz0, 4, 5]
      : tensor<?x?xf32> into tensor<?x4x5xf32>
  return %0 : tensor<?x4x5xf32>
}

// -----

func.func @expand_shape_illegal_output_shape(%arg0: tensor<2xf32>) {
  // expected-error @+1 {{expected number of static shape dims to be equal to the output rank (3) but found 2 inputs instead}}
  %0 = tensor.expand_shape %arg0 [[0, 1, 2]] output_shape [1, 2] : tensor<2xf32> into tensor<1x1x2xf32>
  return
}


// -----

func.func @illegal_collapsing_reshape_mixed_tensor(%arg0 : tensor<?x4x5xf32>) -> tensor<?x?xf32> {
  // expected-error @+1 {{expected dimension 1 of collapsed type to be static value of 5}}
  %0 = tensor.collapse_shape %arg0 [[0, 1], [2]]
      : tensor<?x4x5xf32> into tensor<?x?xf32>
  return %0 : tensor<?x?xf32>
}

// -----

func.func @illegal_collapsing_reshape_mixed_tensor_2(%arg0 : tensor<?x4x5xf32>)
    -> tensor<?x?xf32> {
  // expected-error @+1 {{expected dimension 1 of collapsed type to be static value of 20}}
  %0 = tensor.collapse_shape %arg0 [[0], [1, 2]]
      : tensor<?x4x5xf32> into tensor<?x?xf32>
  return %0 : tensor<?x?xf32>
}

// -----

func.func @rank(%0: f32) {
  // expected-error@+1 {{'tensor.rank' op operand #0 must be tensor of any type values}}
  "tensor.rank"(%0): (f32)->index
  return
}

// -----

func.func @illegal_num_offsets(%arg0 : tensor<?x?xf32>, %arg1 : tensor<?x?x?xf32>,
    %arg2 : index, %arg3 : index) {
  // expected-error@+1 {{expected 3 offset values}}
  %0 = tensor.insert_slice %arg0 into %arg1[0, 0] [%arg2, %arg3] [1, 1] : tensor<?x?xf32> into tensor<?x?x?xf32>
  return
}

// -----


func.func @pad_result_type(%arg0: tensor<?x2x3x4xi32>, %arg1: index, %arg2: i32) -> tensor<?x?x?x8xf32> {
  // expected-error @+1 {{specified type 'tensor<?x?x?x8xf32>' does not match the inferred type 'tensor<?x?x?x9xi32>}}
  %0 = tensor.pad %arg0 low[1, %arg1, 2, 2] high[1, 2, %arg1, 3] {
  ^bb0(%arg3: index, %arg4: index):
    tensor.yield %arg2 : i32
  } : tensor<?x2x3x4xi32> to tensor<?x?x?x8xf32>
  return %0 : tensor<?x?x?x8xf32>
}

// -----

func.func @pad_number_of_block_args(%arg0: tensor<?x4xi32>, %arg1: i32) -> tensor<?x9xi32> {
  // expected-error @+1 {{expected the block to have 2 arguments}}
  %0 = tensor.pad %arg0 low[1, 2] high[2, 3] {
  ^bb0(%arg2: index, %arg3: index, %arg4: index):
    tensor.yield %arg1 : i32
  } : tensor<?x4xi32> to tensor<?x9xi32>
  return %0 : tensor<?x9xi32>
}

// -----

func.func @pad_block_args(%arg0: tensor<?x4xi32>, %arg1: i32) -> tensor<?x9xi32> {
  // expected-error @+1 {{op expected block argument 1 to be an index}}
  %0 = tensor.pad %arg0 low[1, 2] high[2, 3] {
  ^bb0(%arg2: i32, %arg3: i32):
    tensor.yield %arg1 : i32
  } : tensor<?x4xi32> to tensor<?x9xi32>
  return %0 : tensor<?x9xi32>
}

// -----

func.func @pad_yield_type(%arg0: tensor<?x4xi32>, %arg1: i8) -> tensor<?x9xi32> {
  // expected-error @+1 {{op expected yield type to match shape element type}}
  %0 = tensor.pad %arg0 low[1, 2] high[2, 3] {
  ^bb0(%arg2: index, %arg3: index):
    tensor.yield %arg1 : i8
  } : tensor<?x4xi32> to tensor<?x9xi32>
  return %0 : tensor<?x9xi32>
}

// -----

func.func @invalid_splat(%v : f32) {
  // expected-error@+1 {{invalid kind of type specified: expected builtin.tensor, but found 'memref<8xf32>'}}
  tensor.splat %v : memref<8xf32>
  return
}

// -----

// expected-note@+1 {{prior use here}}
func.func @invalid_splat(%v : f32) {
  // expected-error@+1 {{expects different type than prior uses: 'i32' vs 'f32'}}
  %w = tensor.splat %v : tensor<1xi32>
  return
}

// -----

func.func @invalid_splat(%v: f32, %m: index) {
  // expected-error@+1 {{incorrect number of dynamic sizes, has 1, expected 2}}
  %w = tensor.splat %v[%m] : tensor<?x8x?xf32>
  return
}

// -----

func.func @gather_empty_dims(
    %source : tensor<4x5x6xf32>, %indices: tensor<1x2x3xindex>) {
  // expected-error@+1 {{gather_dims must be non-empty}}
  %out = tensor.gather %source[%indices] gather_dims([]):
    (tensor<4x5x6xf32>, tensor<1x2x3xindex>) -> tensor<1x2xf32>
  return
}

// -----

func.func @gather_coordinate_rank_overflow(
    %source : tensor<4x5x6xf32>, %indices: tensor<1x2x3xindex>) {
  // expected-error@+1 {{gather_dims overflow source rank}}
  %out = tensor.gather %source[%indices] gather_dims([0, 1, 2, 3]):
    (tensor<4x5x6xf32>, tensor<1x2x3xindex>) -> tensor<1x2xf32>
  return
}

// -----

func.func @gather_coordinate_rank_mismatch0(
    %source: tensor<4x5x6xf32>, %indices: tensor<index>) {
  // expected-error@+1 {{gather_dims length must match the size of last dimension of indices}}
  %out = tensor.gather %source[%indices] gather_dims([0, 1, 2]):
    (tensor<4x5x6xf32>, tensor<index>) -> tensor<1x2xf32>
}

// -----

func.func @gather_coordinate_rank_mismatch1(
    %source: tensor<4x5x6xf32>, %indices: tensor<1x2x2xindex>) {
  // expected-error@+1 {{gather_dims length must match the size of last dimension of indices}}
  %out = tensor.gather %source[%indices] gather_dims([0, 1, 2]):
    (tensor<4x5x6xf32>, tensor<1x2x2xindex>) -> tensor<1x2xf32>
}

// -----

func.func @gather_coordinate_negative(
    %source : tensor<4x5x6xf32>, %indices: tensor<1x2x1xindex>) {
  // expected-error@+1 {{gather_dims value must be non-negative}}
  %out = tensor.gather %source[%indices] gather_dims([-1]):
    (tensor<4x5x6xf32>, tensor<1x2x1xindex>) -> tensor<1x2x1xf32>
  return
}

// -----

func.func @gather_coordinate_overflow(
    %source : tensor<4x5x6xf32>, %indices: tensor<1x2x1xindex>) {
  // expected-error@+1 {{gather_dims value must be smaller than source rank}}
  %out = tensor.gather %source[%indices] gather_dims([42]):
    (tensor<4x5x6xf32>, tensor<1x2x1xindex>) -> tensor<1x2x1xf32>
  return
}

// -----

func.func @gather_coordinate_increase(
    %source : tensor<4x5x6xf32>, %indices: tensor<1x2x2xindex>) {
  // expected-error@+1 {{gather_dims values must be strictly increasing}}
  %out = tensor.gather %source[%indices] gather_dims([1, 0]):
    (tensor<4x5x6xf32>, tensor<1x2x2xindex>) -> tensor<1x2x1x1xf32>
  return
}

// -----

func.func @gather_wrong_result_type(
    %source : tensor<4x5x6xf32>, %indices: tensor<1x2x2xindex>) {
  // expected-error@+1 {{result type mismatch: expected 'tensor<1x2x1x5x1xf32>' or its rank-reduced variant 'tensor<1x2x5xf32>' (got: 'tensor<1x2x1xf32>')}}
  %out = tensor.gather %source[%indices] gather_dims([0, 2]):
    (tensor<4x5x6xf32>, tensor<1x2x2xindex>) -> tensor<1x2x1xf32>
  return
}

// -----

func.func @scatter_empty_dims(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x3xindex>) {
  // expected-error@+1 {{scatter_dims must be non-empty}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x3xindex>) -> tensor<1x2xf32>
  return
}

// -----

func.func @scatter_coordinate_rank_overflow(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x3xindex>) {
  // expected-error@+1 {{scatter_dims overflow dest rank}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([0, 1, 2, 3]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x3xindex>) -> tensor<1x2xf32>
  return
}

// -----

func.func @scatter_coordinate_rank_mismatch0(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<index>) {
  // expected-error@+1 {{scatter_dims length must match the size of last dimension of indices}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([0, 1, 2]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<index>) -> tensor<1x2xf32>
  return
}

// -----

func.func @scatter_coordinate_rank_mismatch1(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x2xindex>) {
  // expected-error@+1 {{scatter_dims length must match the size of last dimension of indices}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([0, 1, 2]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x2xindex>) -> tensor<1x2xf32>
  return
}

// -----

func.func @scatter_coordinate_negative(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x1xindex>) {
  // expected-error@+1 {{scatter_dims value must be non-negative}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([-1]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x1xindex>) -> tensor<1x2x1xf32>
  return
}

// -----

func.func @scatter_coordinate_overflow(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x1xindex>) {
  // expected-error@+1 {{scatter_dims value must be smaller than dest rank}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([42]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x1xindex>) -> tensor<1x2x1xf32>
  return
}

// -----

func.func @scatter_coordinate_increase(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x2xindex>) {
  // expected-error@+1 {{scatter_dims values must be strictly increasing}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([1, 0]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x2xindex>) -> tensor<1x2x1x1xf32>
  return
}

// -----

func.func @scatter_missing_unique(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x2xindex>) {
  // expected-error@+1 {{requires 'unique' attribute to be set}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([0, 2]):
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x2xindex>) -> tensor<1x2x1xf32>
  return
}

// -----

func.func @scatter_wrong_result_type(
    %source : tensor<f32>,
    %dest : tensor<4x5x6xf32>, %indices: tensor<1x2x2xindex>) {
  // expected-error@+1 {{source type mismatch: expected 'tensor<1x2x1x5x1xf32>' or its rank-reduced variant 'tensor<1x2x5xf32>' (got: 'tensor<f32>')}}
  %out = tensor.scatter %source into %dest[%indices] scatter_dims([0, 2]) unique:
    (tensor<f32>, tensor<4x5x6xf32>, tensor<1x2x2xindex>) -> tensor<1x2x1xf32>
  return
}

// -----

func.func @empty_wrong_number_of_operands(%sz : index) {
  // expected-error@+1 {{incorrect number of dynamic sizes, has 1, expected 2}}
  %out = tensor.empty(%sz) : tensor<2x?x?x5xf32>
  return
}

// -----

func.func @bitcast_index_0(%arg0 : tensor<?xi64>) -> tensor<?xindex> {
  // expected-error @+1 {{'tensor.bitcast' op result #0 must be tensor of signless integer or unsigned integer or signed integer or floating-point values, but got 'tensor<?xindex>'}}
  %0 = tensor.bitcast %arg0 : tensor<?xi64> to tensor<?xindex>
  return %0 : tensor<?xindex>
}

// -----

func.func @bitcast_index_1(%arg0 : tensor<?xindex>) -> tensor<?xi64> {
  // expected-error @+1 {{'tensor.bitcast' op operand #0 must be tensor of signless integer or unsigned integer or signed integer or floating-point values, but got 'tensor<?xindex>'}}
  %0 = tensor.bitcast %arg0 : tensor<?xindex> to tensor<?xi64>
  return %0 : tensor<?xi64>
}
