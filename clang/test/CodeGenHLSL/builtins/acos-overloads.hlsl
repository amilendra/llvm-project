// RUN: %clang_cc1 -std=hlsl202x -finclude-default-header -x hlsl -triple \
// RUN:   spirv-unknown-vulkan-compute %s -emit-llvm -disable-llvm-passes \
// RUN:   -o - | FileCheck %s --check-prefixes=CHECK

// CHECK-LABEL: test_acos_double
// CHECK: call reassoc nnan ninf nsz arcp afn float @llvm.acos.f32
float test_acos_double ( double p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_double2
// CHECK: call reassoc nnan ninf nsz arcp afn <2 x float> @llvm.acos.v2f32
float2 test_acos_double2 ( double2 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_double3
// CHECK: call reassoc nnan ninf nsz arcp afn <3 x float> @llvm.acos.v3f32
float3 test_acos_double3 ( double3 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_double4
// CHECK: call reassoc nnan ninf nsz arcp afn <4 x float> @llvm.acos.v4f32
float4 test_acos_double4 ( double4 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int
// CHECK: call reassoc nnan ninf nsz arcp afn float @llvm.acos.f32
float test_acos_int ( int p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int2
// CHECK: call reassoc nnan ninf nsz arcp afn <2 x float> @llvm.acos.v2f32
float2 test_acos_int2 ( int2 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int3
// CHECK: call reassoc nnan ninf nsz arcp afn <3 x float> @llvm.acos.v3f32
float3 test_acos_int3 ( int3 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int4
// CHECK: call reassoc nnan ninf nsz arcp afn <4 x float> @llvm.acos.v4f32
float4 test_acos_int4 ( int4 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint
// CHECK: call reassoc nnan ninf nsz arcp afn float @llvm.acos.f32
float test_acos_uint ( uint p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint2
// CHECK: call reassoc nnan ninf nsz arcp afn <2 x float> @llvm.acos.v2f32
float2 test_acos_uint2 ( uint2 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint3
// CHECK: call reassoc nnan ninf nsz arcp afn <3 x float> @llvm.acos.v3f32
float3 test_acos_uint3 ( uint3 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint4
// CHECK: call reassoc nnan ninf nsz arcp afn <4 x float> @llvm.acos.v4f32
float4 test_acos_uint4 ( uint4 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int64_t
// CHECK: call reassoc nnan ninf nsz arcp afn float @llvm.acos.f32
float test_acos_int64_t ( int64_t p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int64_t2
// CHECK: call reassoc nnan ninf nsz arcp afn <2 x float> @llvm.acos.v2f32
float2 test_acos_int64_t2 ( int64_t2 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int64_t3
// CHECK: call reassoc nnan ninf nsz arcp afn <3 x float> @llvm.acos.v3f32
float3 test_acos_int64_t3 ( int64_t3 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_int64_t4
// CHECK: call reassoc nnan ninf nsz arcp afn <4 x float> @llvm.acos.v4f32
float4 test_acos_int64_t4 ( int64_t4 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint64_t
// CHECK: call reassoc nnan ninf nsz arcp afn float @llvm.acos.f32
float test_acos_uint64_t ( uint64_t p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint64_t2
// CHECK: call reassoc nnan ninf nsz arcp afn <2 x float> @llvm.acos.v2f32
float2 test_acos_uint64_t2 ( uint64_t2 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint64_t3
// CHECK: call reassoc nnan ninf nsz arcp afn <3 x float> @llvm.acos.v3f32
float3 test_acos_uint64_t3 ( uint64_t3 p0 ) {
  return acos ( p0 );
}

// CHECK-LABEL: test_acos_uint64_t4
// CHECK: call reassoc nnan ninf nsz arcp afn <4 x float> @llvm.acos.v4f32
float4 test_acos_uint64_t4 ( uint64_t4 p0 ) {
  return acos ( p0 );
}
