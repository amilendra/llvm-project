add_llvm_component_group(H2BLB)

set(LLVM_TARGET_DEFINITIONS H2BLB.td)

tablegen(LLVM H2BLBGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(H2BLBCommonTableGen)

add_llvm_target(H2BLBCodeGen
  H2BLBRegisterInfo.cpp
  H2BLBISelLowering.cpp
  H2BLBTargetMachine.cpp
  H2BLBSubtarget.cpp

  LINK_COMPONENTS
  H2BLBDesc
  H2BLBInfo

  CodeGen
  Core
  MC
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  H2BLB
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
