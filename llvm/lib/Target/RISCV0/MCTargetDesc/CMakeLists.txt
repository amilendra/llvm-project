add_llvm_component_library(LLVMRISCV0Desc
  RISCV0AsmBackend.cpp
  RISCV0ELFObjectWriter.cpp
  RISCV0MCAsmInfo.cpp
  RISCV0MCTargetDesc.cpp
  RISCV0MCCodeEmitter.cpp

  LINK_COMPONENTS
  MC
  RISCV0Info
  Support
  TargetParser

  ADD_TO_COMPONENT
  RISCV0
)
