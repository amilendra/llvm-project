add_llvm_component_group(Cpu0)

set(LLVM_TARGET_DEFINITIONS Cpu0Other.td)

# Generate Cpu0GenRegisterInfo.inc and Cpu0GenInstrInfo.inc which included by
#  your hand code C++ files.
# Cpu0GenRegisterInfo.inc came from Cpu0RegisterInfo.td, Cpu0GenInstrInfo.inc
#  came from Cpu0InstrInfo.td.

llvm_tablegen(Cpu0GenRegisterInfo.inc -gen-register-info)
llvm_tablegen(Cpu0GenInstrInfo.inc -gen-instr-info)
llvm_tablegen(Cpu0GenCodeEmitter.inc -gen-emitter)
llvm_tablegen(Cpu0GenMCCodeEmitter.inc -gen-emitter)

llvm_tablegen(Cpu0GenAsmWriter.inc -gen-asm-writer)
llvm_tablegen(Cpu0GenDAGISel.inc -gen-dag-isel)
llvm_tablegen(Cpu0GenCallingConv.inc -gen-callingconv)
llvm_tablegen(Cpu0GenSubtargetInfo.inc -gen-subtarget)
llvm_tablegen(Cpu0GenMCPseudoLowering.inc -gen-pseudo-lowering)

# Cpu0CommonTableGen must be defined
add_public_tablegen_target(Cpu0CommonTableGen)

add_llvm_target(Cpu0CodeGen
  Cpu0AnalyzeImmediate.cpp
  Cpu0AsmPrinter.cpp
  Cpu0MCInstLower.cpp
  Cpu0DelaySlotFiller.cpp
  Cpu0DelUselessJMP.cpp
  Cpu0FrameLowering.cpp
  Cpu0LongBranch.cpp
  Cpu0InstrInfo.cpp
  Cpu0ISelLowering.cpp
  Cpu0MachineFunction.cpp
  Cpu0RegisterInfo.cpp
  Cpu0SEFrameLowering.cpp
  Cpu0SEInstrInfo.cpp
  Cpu0SEISelLowering.cpp
  Cpu0SERegisterInfo.cpp
  Cpu0Subtarget.cpp
  Cpu0TargetObjectFile.cpp
  Cpu0ISelDAGToDAG.cpp
  Cpu0SEISelDAGToDAG.cpp
  Cpu0TargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  MC
  Cpu0Desc
  Cpu0Info
  Cpu0AsmPrinter
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  Cpu0
  )

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
