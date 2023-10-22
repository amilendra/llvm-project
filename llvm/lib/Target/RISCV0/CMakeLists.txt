add_llvm_component_group(RISCV0)

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
