add_llvm_component_group(RISCV0)

set(LLVM_TARGET_DEFINITIONS RISCV0.td)

tablegen(LLVM RISCV0GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RISCV0GenInstrInfo.inc -gen-instr-info)

add_public_tablegen_target(RISCV0CommonTableGen)

add_llvm_target(RISCV0CodeGen
  RISCV0TargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  RISCV0Info
  SelectionDAG
  Support
  Target
  TargetParser
  GlobalISel

  ADD_TO_COMPONENT
  RISCV0
  )

# add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)

# add_llvm_target(RISCV0CodeGen
#   RISCV0TargetMachine.cpp
#   )

# add_subdirectory(TargetInfo)
