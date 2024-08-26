add_llvm_component_library(LLVMOR1KAsmParser
  OR1KAsmParser.cpp

  LINK_COMPONENTS
  OR1KDesc
  OR1KInfo
  MC
  MCParser
  Support

  ADD_TO_COMPONENT
  OR1K
  )
