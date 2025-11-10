#include "include/extIR.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define GEP2_32(Arg) builder.CreateConstGEP2_32(regFileType, regFile, 0, Arg)
#define LOAD_REG(Arg) builder.CreateLoad(int32Type, GEP2_32(Arg))
#define GEN_IMM(Arg) builder.getInt32(Arg)

void ExtIR::buildIR(Binary &Bin) {
  module = new Module("top", context);
  IRBuilder<> builder(context);
  voidType = Type::getVoidTy(context);
  int32Type = Type::getInt32Ty(context);

  ArrayType *regFileType = ArrayType::get(int32Type, CPU::StackSize);
  module->getOrInsertGlobal("regFile", regFileType);
  regFile = module->getNamedGlobal("regFile");
  
  module->getOrInsertGlobal("sp", int32Type);
  sp = module->getNamedGlobal("sp");

  // declare void @main()
  FunctionType *funcType = FunctionType::get(voidType, false);
  mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);
  // Funcions types
  FunctionType *voidFuncType = FunctionType::get(voidType, false);
  Type *int32x4Types[] = {int32Type, int32Type, int32Type, int32Type};
  FunctionType *int32x4FuncType =
      FunctionType::get(voidType, int32x4Types, false);

  // Functions
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  FunctionCallee Callee##_Name =                                               \
      module->getOrInsertFunction("do_" #_Name, int32x4FuncType);
#include "include/ISA.h"
#undef _ISA

  std::unordered_map<uint32_t, BasicBlock *> BBMap;
  for (auto &BB : Bin.BBName2PC) {
    BBMap[BB.second] = BasicBlock::Create(context, BB.first, mainFunc);
  }

  uint32_t PC = 0;
  builder.SetInsertPoint(BBMap[0]);
  for (Instr &I : Bin.Instrs) {
    Value *arg1 = builder.getInt32(I.R1);
    Value *arg2 = builder.getInt32(I.R2Imm);
    Value *arg3 = builder.getInt32(I.R3Imm);
    Value *arg4 = builder.getInt32(I.R4Imm);
    Value *args[] = {arg1, arg2, arg3, arg4};
    switch (I.Op) {
    default:
      break;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    builder.CreateCall(Callee##_Name, args);                                   \
    break;
#include "include/ISA.h"
#undef _ISA
    }
    PC++;
    auto BB = BBMap.find(PC);

    switch (I.Op) {
    default:
      if (BB != BBMap.end()) {
        builder.CreateBr(BB->second);
      }
      break;
    case Instr::BR_COND:
      builder.CreateCondBr(
          builder.CreateTrunc(LOAD_REG(I.R1), builder.getInt1Ty()),
          BBMap[I.R3Imm], BBMap[I.R4Imm]);
      break;
    case Instr::BR:
      builder.CreateBr(BBMap[I.R3Imm]);
      break;
    case Instr::EXIT:
      builder.CreateRetVoid();
      break;
    case Instr::BR_EQi:
      builder.CreateCondBr(
          builder.CreateICmpEQ(LOAD_REG(I.R1), GEN_IMM(I.R2Imm)),
          BBMap[I.R3Imm], BBMap[I.R4Imm]);
      break;
    case Instr::BR_EQ:
      builder.CreateCondBr(
          builder.CreateICmpEQ(LOAD_REG(I.R1), LOAD_REG(I.R2Imm)),
          BBMap[I.R3Imm], BBMap[I.R4Imm]);
      break;
    }
    if (BB != BBMap.end()) {
      builder.SetInsertPoint(BB->second);
    }
  }
}

void ExtIR::dumpIR() {
  outs() << "\n[LLVM IR]:\n";
  module->print(outs(), nullptr);
  outs() << "\n";
}
bool ExtIR::verifyIR() {
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
  return verif;
}

void ExtIR::executeIR(CPU &Cpu) {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  if (fnName == "do_" #_Name)                                                  \
    return reinterpret_cast<void *>(CPU::do_##_Name);
#include "include/ISA.h"
#undef _ISA
    return nullptr;
  });

  ee->addGlobalMapping(regFile, (void *)Cpu.RegFile);
  ee->addGlobalMapping(sp, (void *)Cpu.SP);
  ee->finalizeObject();

  simInit();
  CPU::setCPU(&Cpu);
  // Cpu.DumpInstrs = true;

  ArrayRef<GenericValue> noargs;
  outs() << "\n#[Running code]\n";
  ee->runFunction(mainFunc, noargs);
  outs() << "#[Code was run]\n";

  simExit();
}