add_llvm_component_library(LLVMOR1KDisassembler
  OR1KDisassembler.cpp

  LINK_COMPONENTS
  OR1KInfo
  CodeGenTypes
  MCDisassembler
  Support

  ADD_TO_COMPONENT
  OR1K
)
