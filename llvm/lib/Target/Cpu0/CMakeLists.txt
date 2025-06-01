add_llvm_component_group(Cpu0)

add_llvm_target(Cpu0CodeGen
  Cpu0TargetMachine.cpp

  LINK_COMPONENTS
  AsmPrinter
  MC
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  Cpu0
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
