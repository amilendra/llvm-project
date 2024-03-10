add_llvm_component_group(Cpu0)

set(LLVM_TARGET_DEFINITIONS Cpu0.td)

tablegen(LLVM Cpu0GenSubtargetInfo.inc -gen-subtarget)
# Cpu0GenRegisterInfo.inc comes from Cpu0RegisterInfo.td
tablegen(LLVM Cpu0GenRegisterInfo.inc -gen-register-info)

# Cpu0CommonTableGen must be defined
add_public_tablegen_target(Cpu0CommonTableGen)

add_llvm_target(Cpu0CodeGen
  Cpu0TargetMachine.cpp

  ADD_TO_COMPONENT
  Cpu0
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
