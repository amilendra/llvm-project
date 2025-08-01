; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py UTC_ARGS: --version 4
; RUN: llc -global-isel=0 -mtriple=amdgcn -mcpu=gfx1250 < %s | FileCheck -check-prefix=GCN %s
; RUN: llc -global-isel=1 -mtriple=amdgcn -mcpu=gfx1250 < %s | FileCheck -check-prefix=GCN %s

declare <2 x half> @llvm.amdgcn.cvt.sr.pk.f16.f32(float, float, i32) #0

define amdgpu_ps float @cvt_sr_pk_f16_f32_vvv(float %src0, float %src1, i32 %src2) #1 {
; GCN-LABEL: cvt_sr_pk_f16_f32_vvv:
; GCN:       ; %bb.0:
; GCN-NEXT:    v_cvt_sr_pk_f16_f32 v0, v0, v1, v2
; GCN-NEXT:    ; return to shader part epilog
  %cvt = call <2 x half> @llvm.amdgcn.cvt.sr.pk.f16.f32(float %src0, float %src1, i32 %src2) #0
  %ret = bitcast <2 x half> %cvt to float
  ret float %ret
}

define amdgpu_ps float @cvt_sr_pk_f16_f32_sss(float inreg %src0, float inreg %src1, i32 inreg %src2) #1 {
; GCN-LABEL: cvt_sr_pk_f16_f32_sss:
; GCN:       ; %bb.0:
; GCN-NEXT:    v_mov_b32_e32 v0, s2
; GCN-NEXT:    s_delay_alu instid0(VALU_DEP_1)
; GCN-NEXT:    v_cvt_sr_pk_f16_f32 v0, s0, s1, v0
; GCN-NEXT:    ; return to shader part epilog
  %cvt = call <2 x half> @llvm.amdgcn.cvt.sr.pk.f16.f32(float %src0, float %src1, i32 %src2) #0
  %ret = bitcast <2 x half> %cvt to float
  ret float %ret
}

define amdgpu_ps float @cvt_sr_pk_f16_f32_vvi(float %src0, float %src1) #1 {
; GCN-LABEL: cvt_sr_pk_f16_f32_vvi:
; GCN:       ; %bb.0:
; GCN-NEXT:    v_cvt_sr_pk_f16_f32 v0, v0, v1, 0x10002
; GCN-NEXT:    ; return to shader part epilog
  %cvt = call <2 x half> @llvm.amdgcn.cvt.sr.pk.f16.f32(float %src0, float %src1, i32 65538) #0
  %ret = bitcast <2 x half> %cvt to float
  ret float %ret
}

define amdgpu_ps float @cvt_sr_pk_f16_f32_vvi_mods(float %src0, float %src1) #1 {
; GCN-LABEL: cvt_sr_pk_f16_f32_vvi_mods:
; GCN:       ; %bb.0:
; GCN-NEXT:    v_cvt_sr_pk_f16_f32 v0, -v0, |v1|, 1
; GCN-NEXT:    ; return to shader part epilog
  %s0 = fneg float %src0
  %s1 = call float @llvm.fabs.f32(float %src1) #0
  %cvt = call <2 x half> @llvm.amdgcn.cvt.sr.pk.f16.f32(float %s0, float %s1, i32 1) #0
  %ret = bitcast <2 x half> %cvt to float
  ret float %ret
}

define amdgpu_ps float @cvt_sr_pk_f16_f32_ssi(float inreg %src0, float inreg %src1) #1 {
; GCN-LABEL: cvt_sr_pk_f16_f32_ssi:
; GCN:       ; %bb.0:
; GCN-NEXT:    v_cvt_sr_pk_f16_f32 v0, s0, s1, 1
; GCN-NEXT:    ; return to shader part epilog
  %cvt = call <2 x half> @llvm.amdgcn.cvt.sr.pk.f16.f32(float %src0, float %src1, i32 1) #0
  %ret = bitcast <2 x half> %cvt to float
  ret float %ret
}

declare float @llvm.fabs.f32(float) #0

attributes #0 = { nounwind readnone }
attributes #1 = { nounwind }
