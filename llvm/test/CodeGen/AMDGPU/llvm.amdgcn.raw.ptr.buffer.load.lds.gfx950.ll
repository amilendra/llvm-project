; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -global-isel=0 -mtriple=amdgcn -mcpu=gfx950 < %s | FileCheck -check-prefixes=GFX950,GFX950-SDAG %s
; RUN: llc -global-isel=1 -mtriple=amdgcn -mcpu=gfx950 < %s | FileCheck -check-prefixes=GFX950,GFX950-GISEL %s
; RUN: not --crash llc -global-isel=0 -mtriple=amdgcn -mcpu=gfx942 -filetype=null < %s 2>&1 | FileCheck -check-prefix=ERR-SDAG %s
; RUN: not llc -global-isel=1 -mtriple=amdgcn -mcpu=gfx942 -filetype=null < %s 2>&1 | FileCheck -check-prefix=ERR-GISEL %s

; FIXME: Not a great error
; ERR-SDAG: LLVM ERROR: Do not know how to expand this operator's operand!
; ERR-GISEL: LLVM ERROR: cannot select: G_INTRINSIC_W_SIDE_EFFECTS intrinsic(@llvm.amdgcn.raw.ptr.buffer.load.lds),

declare void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) nocapture, i32 %size, i32 %voffset, i32 %soffset, i32 %offset, i32 %aux)

;---------------------------------------------------------------------y
; dwordx3
;---------------------------------------------------------------------

define amdgpu_ps float @buffer_load_lds_dwordx3(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds) {
; GFX950-LABEL: buffer_load_lds_dwordx3:
; GFX950:       ; %bb.0: ; %main_body
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dword off, s[0:3], 0 lds
; GFX950-NEXT:    buffer_load_dword off, s[0:3], 0 offset:4 sc0 lds
; GFX950-NEXT:    buffer_load_dword off, s[0:3], 0 offset:8 nt lds
; GFX950-NEXT:    v_mov_b32_e32 v0, s4
; GFX950-NEXT:    s_waitcnt vmcnt(0)
; GFX950-NEXT:    ds_read_b32 v0, v0
; GFX950-NEXT:    s_waitcnt lgkmcnt(0)
; GFX950-NEXT:    ; return to shader part epilog
main_body:
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 4, i32 0, i32 0, i32 0, i32 0)
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 4, i32 0, i32 0, i32 4, i32 1)
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 4, i32 0, i32 0, i32 8, i32 2)
  %res = load float, ptr addrspace(3) %lds
  ret float %res
}

define amdgpu_ps void @buffer_load_lds_dwordx3_imm_voffset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds) {
; GFX950-LABEL: buffer_load_lds_dwordx3_imm_voffset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    v_mov_b32_e32 v0, 0x800
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx3 v0, s[0:3], 0 offen lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 12, i32 2048, i32 0, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx3_v_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 %voffset) {
; GFX950-LABEL: buffer_load_lds_dwordx3_v_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx3 v0, s[0:3], 0 offen lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 12, i32 %voffset, i32 0, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx3_s_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 inreg %soffset) {
; GFX950-LABEL: buffer_load_lds_dwordx3_s_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx3 off, s[0:3], s5 lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 12, i32 0, i32 %soffset, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx3_vs_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 %voffset, i32 inreg %soffset) {
; GFX950-LABEL: buffer_load_lds_dwordx3_vs_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx3 v0, s[0:3], s5 offen lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 12, i32 %voffset, i32 %soffset, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx3_vs_imm_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 %voffset, i32 inreg %soffset) {
; GFX950-LABEL: buffer_load_lds_dwordx3_vs_imm_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx3 v0, s[0:3], s5 offen offset:2048 lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 12, i32 %voffset, i32 %soffset, i32 2048, i32 0)
  ret void
}

;---------------------------------------------------------------------y
; dwordx4
;---------------------------------------------------------------------

define amdgpu_ps float @buffer_load_lds_dwordx4(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds) {
; GFX950-LABEL: buffer_load_lds_dwordx4:
; GFX950:       ; %bb.0: ; %main_body
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dword off, s[0:3], 0 lds
; GFX950-NEXT:    buffer_load_dword off, s[0:3], 0 offset:4 sc0 lds
; GFX950-NEXT:    buffer_load_dword off, s[0:3], 0 offset:8 nt lds
; GFX950-NEXT:    v_mov_b32_e32 v0, s4
; GFX950-NEXT:    s_waitcnt vmcnt(0)
; GFX950-NEXT:    ds_read_b32 v0, v0
; GFX950-NEXT:    s_waitcnt lgkmcnt(0)
; GFX950-NEXT:    ; return to shader part epilog
main_body:
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 4, i32 0, i32 0, i32 0, i32 0)
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 4, i32 0, i32 0, i32 4, i32 1)
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 4, i32 0, i32 0, i32 8, i32 2)
  %res = load float, ptr addrspace(3) %lds
  ret float %res
}

define amdgpu_ps void @buffer_load_lds_dwordx4_imm_voffset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds) {
; GFX950-LABEL: buffer_load_lds_dwordx4_imm_voffset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    v_mov_b32_e32 v0, 0x800
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx4 v0, s[0:3], 0 offen lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 16, i32 2048, i32 0, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx4_v_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 %voffset) {
; GFX950-LABEL: buffer_load_lds_dwordx4_v_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx4 v0, s[0:3], 0 offen lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 16, i32 %voffset, i32 0, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx4_s_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 inreg %soffset) {
; GFX950-LABEL: buffer_load_lds_dwordx4_s_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx4 off, s[0:3], s5 lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 16, i32 0, i32 %soffset, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx4_vs_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 %voffset, i32 inreg %soffset) {
; GFX950-LABEL: buffer_load_lds_dwordx4_vs_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx4 v0, s[0:3], s5 offen lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 16, i32 %voffset, i32 %soffset, i32 0, i32 0)
  ret void
}

define amdgpu_ps void @buffer_load_lds_dwordx4_vs_imm_offset(ptr addrspace(8) inreg %rsrc, ptr addrspace(3) inreg %lds, i32 %voffset, i32 inreg %soffset) {
; GFX950-LABEL: buffer_load_lds_dwordx4_vs_imm_offset:
; GFX950:       ; %bb.0:
; GFX950-NEXT:    s_mov_b32 m0, s4
; GFX950-NEXT:    s_nop 0
; GFX950-NEXT:    buffer_load_dwordx4 v0, s[0:3], s5 offen offset:2048 lds
; GFX950-NEXT:    s_endpgm
  call void @llvm.amdgcn.raw.ptr.buffer.load.lds(ptr addrspace(8) %rsrc, ptr addrspace(3) %lds, i32 16, i32 %voffset, i32 %soffset, i32 2048, i32 0)
  ret void
}
;; NOTE: These prefixes are unused and the list is autogenerated. Do not add tests below this line:
; GFX950-GISEL: {{.*}}
; GFX950-SDAG: {{.*}}
