add_llvm_component_library(LLVMOR1KDesc
  OR1KAsmBackend.cpp
  OR1KBaseInfo.cpp
  OR1KELFObjectWriter.cpp
  OR1KInstPrinter.cpp
  OR1KMCAsmInfo.cpp
  OR1KMCCodeEmitter.cpp
  OR1KMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  OR1KInfo
  Support

  ADD_TO_COMPONENT
  OR1K
)
