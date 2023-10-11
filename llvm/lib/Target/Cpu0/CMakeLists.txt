add_llvm_component_group(Cpu0)

set(LLVM_TARGET_DEFINITIONS Cpu0.td)

tablegen(LLVM Cpu0GenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(Cpu0CommonTableGen)

add_llvm_target(Cpu0CodeGen
  Cpu0TargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  Cpu0Desc
  Cpu0Info
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  Cpu0
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
