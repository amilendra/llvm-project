# add_llvm_library(LLVMRISCV0Info
#   RISCV0TargetInfo.cpp
#   )

add_llvm_component_library(LLVMRISCV0Info
  RISCV0TargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  RISCV0
)
  