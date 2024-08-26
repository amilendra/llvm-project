add_llvm_component_group(OR1K)

set(LLVM_TARGET_DEFINITIONS OR1K.td)

tablegen(LLVM OR1KGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM OR1KGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM OR1KGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM OR1KGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM OR1KGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM OR1KGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM OR1KGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM OR1KGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(OR1KCommonTableGen)

add_llvm_target(OR1KCodeGen
  OR1KAsmPrinter.cpp
  OR1KFrameLowering.cpp
  OR1KInstrInfo.cpp
  OR1KISelDAGToDAG.cpp
  OR1KISelLowering.cpp
  OR1KMCInstLower.cpp
  OR1KRegisterInfo.cpp
  OR1KSubtarget.cpp
  OR1KTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  GlobalISel
  MC
  OR1KDesc
  OR1KInfo
  SelectionDAG
  Support
  Target
  TargetParser
  TransformUtils

  ADD_TO_COMPONENT
  OR1K
)

add_subdirectory(AsmParser)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
