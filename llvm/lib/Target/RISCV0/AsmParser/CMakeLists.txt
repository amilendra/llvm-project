add_llvm_component_library(LLVMRISCV0AsmParser
  RISCV0AsmParser.cpp

  LINK_COMPONENTS
  MC
  MCParser
  RISCV0Desc
  RISCV0Info
  Support
  TargetParser

  ADD_TO_COMPONENT
  RISCV0
)
