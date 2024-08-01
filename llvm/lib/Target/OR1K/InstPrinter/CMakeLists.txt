add_llvm_component_library(LLVMOR1KInstPrinter
  OR1KInstPrinter.cpp

  LINK_COMPONENTS
  MC
  Support
  OR1KInfo

  ADD_TO_COMPONENT
  OR1K
)
