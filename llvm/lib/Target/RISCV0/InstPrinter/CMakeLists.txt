add_llvm_component_library(LLVMRISCV0AsmPrinter
  RISCV0InstPrinter.cpp

  LINK_COMPONENTS
  MC
  Support
  RISCV0Info

  ADD_TO_COMPONENT
  RISCV0
)
