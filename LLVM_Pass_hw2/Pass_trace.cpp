#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct TrassOfUsesPass : public PassInfoMixin<TrassOfUsesPass> {

  bool isFuncLogger(StringRef name) {
    return name == "traceLogger";
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    for (auto &F : M) {

      if (isFuncLogger(F.getName()) || F.isDeclaration()) {
        continue;
      }
      

      // Prepare builder for IR modification
      LLVMContext &Ctx = F.getContext();
      IRBuilder<> builder(Ctx);
      Type *retType = Type::getVoidTy(Ctx);
      Type *int8PtrTy = PointerType::get(Type::getInt8Ty(Ctx), 0);

      // Prepare traceLogger function
      Type* traceParamTypes[] = {int8PtrTy, int8PtrTy};
      FunctionType *traceLoggerType =
          FunctionType::get(retType, traceParamTypes, false);
      FunctionCallee traceLogger =
          M.getOrInsertFunction("traceLogger", traceLoggerType);
      
      for (auto &B : F) {
        for (auto &I : B) {
          if (isa<PHINode>(&I)) {
            continue;
          }
          builder.SetInsertPoint(&I);
          Value *user = builder.CreateGlobalString(I.getOpcodeName());
          for (auto &U : I.operands()) {
            if (auto* op = dyn_cast<Instruction>(U)) {
              Value *operand = builder.CreateGlobalString(op->getOpcodeName());
              builder.CreateCall(traceLogger, {user, operand});
            }
          }
        }
      }
      outs() << "\n";
      bool verif = verifyFunction(F, &outs());
      outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
    }
    outs() << "\n";
    return PreservedAnalyses::none();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, auto, auto) {
      MPM.addPass(TrassOfUsesPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
