add_llvm_component_group(OR1K)

set(LLVM_TARGET_DEFINITIONS OR1K.td)
tablegen(LLVM OR1KGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM OR1KGenInstrInfo.inc    -gen-instr-info)

add_public_tablegen_target(OR1KCommonTableGen)

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
