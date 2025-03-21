;RUN: llc < %s -mtriple=r600 -mcpu=redwood | FileCheck %s

; This test is for a bug in
; DAGCombiner::reduceBuildVecConvertToConvertBuildVec() where
; the wrong type was being passed to
; TargetLowering::getOperationAction() when checking the legality of
; ISD::UINT_TO_FP and ISD::SINT_TO_FP opcodes.


; CHECK: {{^}}sint:
; CHECK: INT_TO_FLT * T{{[0-9]+\.[XYZW], T[0-9]+\.[XYZW]}}

define amdgpu_kernel void @sint(ptr addrspace(1) %out, ptr addrspace(1) %in) {
entry:
  %ptr = getelementptr i32, ptr addrspace(1) %in, i32 1
  %sint = load i32, ptr addrspace(1) %in
  %conv = sitofp i32 %sint to float
  %0 = insertelement <4 x float> poison, float %conv, i32 0
  %splat = shufflevector <4 x float> %0, <4 x float> poison, <4 x i32> zeroinitializer
  store <4 x float> %splat, ptr addrspace(1) %out
  ret void
}

;CHECK: {{^}}uint:
;CHECK: UINT_TO_FLT * T{{[0-9]+\.[XYZW], T[0-9]+\.[XYZW]}}

define amdgpu_kernel void @uint(ptr addrspace(1) %out, ptr addrspace(1) %in) {
entry:
  %ptr = getelementptr i32, ptr addrspace(1) %in, i32 1
  %uint = load i32, ptr addrspace(1) %in
  %conv = uitofp i32 %uint to float
  %0 = insertelement <4 x float> poison, float %conv, i32 0
  %splat = shufflevector <4 x float> %0, <4 x float> poison, <4 x i32> zeroinitializer
  store <4 x float> %splat, ptr addrspace(1) %out
  ret void
}
