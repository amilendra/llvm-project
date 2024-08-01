add_llvm_component_group(OR1K)

set(LLVM_TARGET_DEFINITIONS OR1K.td)

tablegen(LLVM OR1KGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM OR1KGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM OR1KGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM OR1KGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM OR1KGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM OR1KGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM OR1KGenCallingConv.inc -gen-callingconv)
tablegen(LLVM OR1KGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM OR1KGenDisassemblerTables.inc -gen-disassembler)

add_public_tablegen_target(OR1KCommonTableGen)

add_llvm_target(OR1KCodeGen
  OR1KDelaySlotFiller.cpp
  OR1KISelDAGToDAG.cpp
  OR1KISelLowering.cpp
  OR1KInstrInfo.cpp
  OR1KFrameLowering.cpp
  OR1KMachineFunctionInfo.cpp
  OR1KRegisterInfo.cpp
  OR1KSubtarget.cpp
  OR1KTargetMachine.cpp
  OR1KAsmPrinter.cpp
  OR1KMCInstLower.cpp

  LINK_COMPONENTS
  OR1KDesc
  OR1KInfo
  OR1KInstPrinter
  Analysis
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  MC
  SelectionDAG
  Support
  Target
  TargetParser
  TransformUtils

  ADD_TO_COMPONENT
  OR1K
)

add_subdirectory(InstPrinter)
add_subdirectory(Disassembler)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
add_subdirectory(AsmParser)
