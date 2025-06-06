; RUN: llc < %s -mtriple=bpfel -mcpu=v1 | FileCheck %s

define i32 @test0(i32 %X) {
  %tmp.1 = add i32 %X, 1
  ret i32 %tmp.1
; CHECK-LABEL: test0:
; CHECK: r0 += 1
}

; CHECK-LABEL: store_imm:
; CHECK: *(u32 *)(r1 + 0) = r{{[03]}}
; CHECK: *(u32 *)(r2 + 4) = r{{[03]}}
define i32 @store_imm(ptr %a, ptr %b) {
entry:
  store i32 0, ptr %a, align 4
  %0 = getelementptr inbounds i32, ptr %b, i32 1
  store i32 0, ptr %0, align 4
  ret i32 0
}

@G = external global i8
define zeroext i8 @loadG() {
  %tmp = load i8, ptr @G
  ret i8 %tmp
; CHECK-LABEL: loadG:
; CHECK: r1 =
; CHECK: r0 = *(u8 *)(r1 + 0)
}
