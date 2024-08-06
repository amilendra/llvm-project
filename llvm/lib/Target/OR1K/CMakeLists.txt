add_llvm_component_group(OR1K)

add_llvm_target(OR1KCodeGen
  OR1KTargetMachine.cpp

  LINK_COMPONENTS
  MC
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  OR1K
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
