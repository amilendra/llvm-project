add_llvm_component_library(LLVMOR1KDesc
  OR1KMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  OR1KInfo
  Support

  ADD_TO_COMPONENT
  OR1K
  )
