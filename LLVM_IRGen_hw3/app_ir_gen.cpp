#include "../graphic_app_hw1/sim.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

#include <functional>

#ifdef GET_LL
#include <cstdio>
#endif

using namespace llvm;

int main() {
  #ifdef GET_LL
  freopen("app.ll", "w", stdout);
  #endif
  LLVMContext context;
  // ; ModuleID = 'app.c'
  // source_filename = "app.c"
  Module *module = new Module("app.c", context);
  IRBuilder<> builder(context);

  auto createBB = [&](auto *func) {
    return BasicBlock::Create(context, "", func);
  };

  auto setEntry = [&](auto& func) {
    auto *bb = createBB(func);
    builder.SetInsertPoint(bb);
    return bb;
  };

  // phi i32 [ %0, %1 ], [ %2, %3 ]
  auto linkPhi2 = [](PHINode *phi, auto* val0, auto* val1, auto* val2, auto* val3) {
    phi->addIncoming(val0, val1);
    phi->addIncoming(val2, val3);
  };

  Type *int32Ty = Type::getInt32Ty(context);
  Type *voidType = Type::getVoidTy(context);
  Type *arrParamTypes1[] = {int32Ty};
  Type *arrParamTypes3[] = {int32Ty, int32Ty, int32Ty};
  Type *arrParamTypes4[] = {int32Ty, int32Ty, int32Ty, int32Ty};
  Type *arrParamTypes5[] = {int32Ty, int32Ty, int32Ty, int32Ty, int32Ty};

  // @grad = dso_local local_unnamed_addr global i32 0, align 4
  GlobalVariable *grad = new GlobalVariable(*module, int32Ty, false, GlobalValue::ExternalLinkage,
                                            builder.getInt32(0), "grad");

  // declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2
  FunctionType *simPutPixelType =
      FunctionType::get(voidType, arrParamTypes3, false);
  FunctionCallee simPutPixelFunc =
      module->getOrInsertFunction("simPutPixel", simPutPixelType);

  // declare i32 @simRand(...) local_unnamed_addr #2
  FunctionType *simRandType = FunctionType::get(int32Ty, false);
  FunctionCallee simRandFunc =
        module->getOrInsertFunction("simRand", simRandType);

  // declare void @simFlush(...) local_unnamed_addr #2
    FunctionType *simFlushType = FunctionType::get(voidType, false);
    FunctionCallee simFlushFunc =
        module->getOrInsertFunction("simFlush", simFlushType);
        

  // ; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
  // declare i32 @llvm.abs.i32(i32, i1 immarg) #4
  Function *absFunc = Intrinsic::getOrInsertDeclaration(module, Intrinsic::abs, {int32Ty});

  // define dso_local range(i32 0, -2147483648) i32 @get_abs(i32 noundef %0) local_unnamed_addr #0 {
  FunctionType *get_absType = FunctionType::get(int32Ty, arrParamTypes1, false);
  Function *get_absFunc = 
      Function::Create(get_absType, Function::ExternalLinkage, "get_abs", module);
  {
  setEntry(get_absFunc);
  //   %2 = tail call i32 @llvm.abs.i32(i32 %0, i1 true)
  CallInst *val2 = builder.CreateCall(absFunc, {get_absFunc->getArg(0), builder.getTrue()});
  val2->setTailCall();
  //   ret i32 %2
  builder.CreateRet(val2); 
  }

  // define dso_local void @draw_line(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #1 {
  FunctionType *draw_lineType = FunctionType::get(voidType, arrParamTypes4, false);
  Function *draw_lineFunc = 
      Function::Create(draw_lineType, Function::ExternalLinkage, "draw_line", module);
  {
  setEntry(draw_lineFunc);
  BasicBlock *BB15 = createBB(draw_lineFunc);
  BasicBlock *BB19 = createBB(draw_lineFunc);
  BasicBlock *BB22 = createBB(draw_lineFunc);
  BasicBlock *BB30 = createBB(draw_lineFunc);
  BasicBlock *BB34 = createBB(draw_lineFunc);
  BasicBlock *BB37 = createBB(draw_lineFunc);
  BasicBlock *BB45 = createBB(draw_lineFunc);
  
  Value * val0 = draw_lineFunc->getArg(0), *val1 = draw_lineFunc->getArg(1), 
  *val2 = draw_lineFunc->getArg(2), *val3 = draw_lineFunc->getArg(3);
  // %5 = sub nsw i32 255, %1
  Value *val5 = builder.CreateSub(builder.getInt32(255), val1, "", false, true);
  // %6 = sub nsw i32 255, %3
  Value *val6 = builder.CreateSub(builder.getInt32(255), val3, "", false, true);
  // %7 = load i32, ptr @grad, align 4, !tbaa !5
  Value *val7 = builder.CreateLoad(int32Ty, grad);
  // %8 = add nsw i32 %7, -1
  Value *val8 = builder.CreateAdd(val7, builder.getInt32(-1), "", false, true);
  // store i32 %8, ptr @grad, align 4, !tbaa !5
  builder.CreateStore(val8, grad);
  //   %9 = add i32 %7, -65537
  Value *val9 = builder.CreateAdd(val7, builder.getInt32(-65537), "", false, false);
  //   %10 = sub nsw i32 %0, %2
  Value *val10 = builder.CreateSub(val0, val2, "", false, true);
  //   %11 = tail call range(i32 0, -2147483648) i32 @llvm.abs.i32(i32 %10, i1 true)
  CallInst *val11 = builder.CreateCall(absFunc, {val10, builder.getTrue()});
  val11->setTailCall();
  //   %12 = sub nsw i32 %5, %6
  Value *val12 = builder.CreateSub(val5, val6, "", false, true);
  //   %13 = tail call range(i32 0, -2147483648) i32 @llvm.abs.i32(i32 %12, i1 true)
  CallInst *val13 = builder.CreateCall(absFunc, {val12, builder.getTrue()});
  val13->setTailCall();
  //   %14 = icmp samesign ult i32 %11, %13 // samesign?
  Value *val14 = builder.CreateICmpULT(val11, val13);
  //   br i1 %14, label %15, label %30
  builder.CreateCondBr(val14, BB15, BB30);

  // 15:                                               ; preds = %4
  builder.SetInsertPoint(BB15);
  //   %16 = icmp sgt i32 %3, %1
  Value *val16 = builder.CreateICmpSGT(val3, val1);
  //   %17 = select i1 %16, i32 -1, i32 1
  Value *val17 = builder.CreateSelect(val16, builder.getInt32(-1), builder.getInt32(1));
  //   %18 = icmp eq i32 %3, %1
  Value *val18 = builder.CreateICmpEQ(val3, val1);
  //   br i1 %18, label %45, label %19
  builder.CreateCondBr(val18, BB45, BB19);

  // 19:                                               ; preds = %15
  builder.SetInsertPoint(BB19);
  //   %20 = sub nsw i32 %2, %0
  Value *val20 = builder.CreateSub(val2, val0, "", false, true);
  //   %21 = sub nsw i32 %6, %5
  Value *val21 = builder.CreateSub(val6, val5, "", false, true);
  //   br label %22
  builder.CreateBr(BB22);

  // 22:                                               ; preds = %19, %22
  builder.SetInsertPoint(BB22);
  //   %23 = phi i32 [ %5, %19 ], [ %28, %22 ]
  PHINode *val23 = builder.CreatePHI(int32Ty, 2);
  //   %24 = sub nsw i32 %23, %5
  Value *val24 = builder.CreateSub(val23, val5, "", false, true);
  //   %25 = mul nsw i32 %24, %20
  Value *val25 = builder.CreateMul(val24, val20, "", false, true);
  //   %26 = sdiv i32 %25, %21
  Value *val26 = builder.CreateSDiv(val25, val21);
  //   %27 = add nsw i32 %26, %0
  Value *val27 = builder.CreateAdd(val26, val0, "", false, true);
  //   tail call void @simPutPixel(i32 noundef %27, i32 noundef %23, i32 noundef %9) #5
  builder.CreateCall(simPutPixelFunc, {val27, val23, val9})->setTailCall();
  //   %28 = add nsw i32 %23, %17
  Value *val28 = builder.CreateAdd(val23, val17, "", false, true);
  //   %29 = icmp eq i32 %28, %6
  Value *val29 = builder.CreateICmpEQ(val28, val6);
  //   br i1 %29, label %45, label %22, !llvm.loop !9
  builder.CreateCondBr(val29, BB45, BB22);

  // 30:                                               ; preds = %4
  builder.SetInsertPoint(BB30);
  //   %31 = icmp sgt i32 %0, %2
  Value *val31 = builder.CreateICmpSGT(val0, val2);
  //   %32 = select i1 %31, i32 -1, i32 1
  Value *val32 = builder.CreateSelect(val31, builder.getInt32(-1), builder.getInt32(1));
  //   %33 = icmp eq i32 %0, %2
  Value *val33 = builder.CreateICmpEQ(val0, val2);
  //   br i1 %33, label %45, label %34
  builder.CreateCondBr(val33, BB45, BB34);

  // 34:                                               ; preds = %30
  builder.SetInsertPoint(BB34);
  //   %35 = sub nsw i32 %6, %5
  Value *val35 = builder.CreateSub(val6, val5, "", false, true);
  //   %36 = sub nsw i32 %2, %0
  Value *val36 = builder.CreateSub(val2, val0, "", false, true);
  //   br label %37
  builder.CreateBr(BB37);

  // 37:                                               ; preds = %34, %37
  builder.SetInsertPoint(BB37);
  //   %38 = phi i32 [ %0, %34 ], [ %43, %37 ]
  PHINode *val38 = builder.CreatePHI(int32Ty, 2);
  //   %39 = sub nsw i32 %38, %0
  Value *val39 = builder.CreateSub(val38, val0, "", false, true);
  //   %40 = mul nsw i32 %39, %35
  Value *val40 = builder.CreateMul(val39, val35, "", false, true);
  //   %41 = sdiv i32 %40, %36
  Value *val41 = builder.CreateSDiv(val40, val36);
  //   %42 = add nsw i32 %41, %5
  Value *val42 = builder.CreateAdd(val41, val5, "", false, true);
  //   tail call void @simPutPixel(i32 noundef %38, i32 noundef %42, i32 noundef %9) #5
  builder.CreateCall(simPutPixelFunc, {val38, val42, val9})->setTailCall();
  //   %43 = add nsw i32 %38, %32
  Value *val43 = builder.CreateAdd(val38, val32, "", false, true);
  //   %44 = icmp eq i32 %43, %2
  Value *val44 = builder.CreateICmpEQ(val43, val2);
  //   br i1 %44, label %45, label %37, !llvm.loop !12
  builder.CreateCondBr(val44, BB45, BB37);

  // 45:                                               ; preds = %37, %22, %30, %15
  builder.SetInsertPoint(BB45);
  //   ret void
  builder.CreateRetVoid();

  // Link PHI nodes
  //   %23 = phi i32 [ %5, %19 ], [ %28, %22 ]
  linkPhi2(val23, val5, BB19, val28, BB22);
  //   %38 = phi i32 [ %0, %34 ], [ %43, %37 ]
  val38->addIncoming(val0, BB34);
  val38->addIncoming(val43, BB37);
  }

  // ; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
  // define dso_local noundef i32 @turn_x(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #0 
  FunctionType *turn_xType = FunctionType::get(int32Ty, arrParamTypes4, false);
  Function *turn_xFunc = Function::Create(turn_xType, Function::ExternalLinkage, "turn_x", module);
  {
  setEntry(turn_xFunc);
  Value *val0 = turn_xFunc->getArg(0);
  Value *val1 = turn_xFunc->getArg(1);
  Value *val2 = turn_xFunc->getArg(2);
  Value *val3 = turn_xFunc->getArg(3);
  //   %5 = add i32 %1, %0
  Value *val5 = builder.CreateAdd(val1, val0);
  //   %6 = sub i32 %5, %3
  Value *val6 = builder.CreateSub(val5, val3);
  //   ret i32 %6
  builder.CreateRet(val6);
  }

  // ; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
  // define dso_local noundef i32 @turn_y(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #0 {
  FunctionType *turn_yType = FunctionType::get(int32Ty, arrParamTypes4, false);
  Function *turn_yFunc = Function::Create(turn_yType, Function::ExternalLinkage, "turn_y", module);
  {
  setEntry(turn_yFunc);
  Value *val0 = turn_yFunc->getArg(0);
  Value *val1 = turn_yFunc->getArg(1);
  Value *val2 = turn_yFunc->getArg(2);
  Value *val3 = turn_yFunc->getArg(3);
  //   %5 = add i32 %1, %0
  Value *val5 = builder.CreateSub(val1, val0);
  //   %6 = sub i32 %5, %2
  Value *val6 = builder.CreateAdd(val5, val2);
  //   ret i32 %6
  builder.CreateRet(val6);
  }

  // ; Function Attrs: nounwind sspstrong uwtable
  // define dso_local void @draw_pythagoras_tree(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #1 {
  FunctionType *dptType = FunctionType::get(voidType, arrParamTypes5, false);
  Function *dptFunc = Function::Create(dptType, Function::ExternalLinkage, "draw_pythagoras_tree", module);
  {
    // setEntry(dptFunc);
    BasicBlock *BB5 = createBB(dptFunc);
    builder.SetInsertPoint(BB5);
    BasicBlock *BB6 = createBB(dptFunc);
    BasicBlock *BB13 = createBB(dptFunc);
    BasicBlock *BB36 = createBB(dptFunc);

    Value *val0 = dptFunc->getArg(0);
    Value *val1 = dptFunc->getArg(1);
    Value *val2 = dptFunc->getArg(2);
    Value *val3 = dptFunc->getArg(3);
    Value *val4 = dptFunc->getArg(4);
  //   br label %6
  builder.CreateBr(BB6);

  // 6:                                                ; preds = %13, %5
  builder.SetInsertPoint(BB6);
  //   %7 = phi i32 [ %0, %5 ], [ %28, %13 ]
  PHINode *val7 = builder.CreatePHI(int32Ty, 2);
  //   %8 = phi i32 [ %1, %5 ], [ %34, %13 ]
  PHINode *val8 = builder.CreatePHI(int32Ty, 2);
  //   %9 = phi i32 [ %2, %5 ], [ %19, %13 ]
  PHINode *val9 = builder.CreatePHI(int32Ty, 2);
  //   %10 = phi i32 [ %3, %5 ], [ %21, %13 ]
  PHINode *val10 = builder.CreatePHI(int32Ty, 2);
  //   %11 = phi i32 [ %4, %5 ], [ %35, %13 ]
  PHINode *val11 = builder.CreatePHI(int32Ty, 2);
  //   %12 = icmp eq i32 %11, 0
  Value *val12 = builder.CreateICmpEQ(val11, builder.getInt32(0));
  //   br i1 %12, label %36, label %13
  builder.CreateCondBr(val12, BB36, BB13);

  // 13:                                               ; preds = %6
  builder.SetInsertPoint(BB13);
  //   %14 = add i32 %8, %7
  Value *val14 = builder.CreateAdd(val8, val7);
  //   %15 = sub i32 %14, %10
  Value *val15 = builder.CreateSub(val14, val10);
  //   %16 = sub i32 %8, %7
  Value *val16 = builder.CreateSub(val8, val7);
  //   %17 = add i32 %16, %9
  Value *val17 = builder.CreateAdd(val16, val9);
  //   %18 = sub i32 %17, %8
  Value *val18 = builder.CreateSub(val17, val8);
  //   %19 = add i32 %18, %15
  Value *val19 = builder.CreateAdd(val18, val15);
  //   %20 = sub i32 %17, %15
  Value *val20 = builder.CreateSub(val17, val15);
  //   %21 = add i32 %20, %7
  Value *val21 = builder.CreateAdd(val20, val7);
  //   tail call void @draw_line(i32 noundef %7, i32 noundef %8, i32 noundef %9, i32 noundef %10)
  builder.CreateCall(draw_lineFunc, {val7, val8, val9, val10})->setTailCall();
  //   tail call void @draw_line(i32 noundef %7, i32 noundef %8, i32 noundef %15, i32 noundef %17)
  builder.CreateCall(draw_lineFunc, {val7, val8, val15, val17})->setTailCall();
  //   tail call void @draw_line(i32 noundef %19, i32 noundef %21, i32 noundef %9, i32 noundef %10)
  builder.CreateCall(draw_lineFunc, {val19, val21, val9, val10})->setTailCall();
  //   tail call void @draw_line(i32 noundef %15, i32 noundef %17, i32 noundef %19, i32 noundef %21)
  builder.CreateCall(draw_lineFunc, {val15, val17, val19, val21})->setTailCall();
  //   %22 = mul nsw i32 %19, 3
  Value *val22 = builder.CreateMul(val19, builder.getInt32(3), "", false, true);
  //   %23 = add nsw i32 %22, %15
  Value *val23 = builder.CreateAdd(val22, val15, "", false, true);
  //   %24 = sub nsw i32 %21, %17
  Value *val24 = builder.CreateSub(val21, val17, "", false, true);
  //   %25 = mul nsw i32 %24, 7
  Value *val25 = builder.CreateMul(val24, builder.getInt32(7), "", false, true);
  //   %26 = sdiv i32 %25, -4
  Value *val26 = builder.CreateSDiv(val25, builder.getInt32(-4));
  //   %27 = add i32 %23, %26
  Value *val27 = builder.CreateAdd(val23, val26);
  //   %28 = sdiv i32 %27, 4
  Value *val28 = builder.CreateSDiv(val27, builder.getInt32(4));
  //   %29 = mul nsw i32 %21, 3
  Value *val29 = builder.CreateMul(val21, builder.getInt32(3), "", false, true);
  //   %30 = add nsw i32 %29, %17
  Value *val30 = builder.CreateAdd(val29, val17, "", false, true);
  //   %31 = mul nsw i32 %18, 7
  Value *val31 = builder.CreateMul(val18, builder.getInt32(7), "", false, true);
  //   %32 = sdiv i32 %31, 4
  Value *val32 = builder.CreateSDiv(val31, builder.getInt32(4));
  //   %33 = add nsw i32 %30, %32
  Value *val33 = builder.CreateAdd(val30, val32, "", false, true);
  //   %34 = sdiv i32 %33, 4
  Value *val34 = builder.CreateSDiv(val33, builder.getInt32(4));
  //   tail call void @draw_line(i32 noundef %15, i32 noundef %17, i32 noundef %28, i32 noundef %34)
  builder.CreateCall(draw_lineFunc, {val15, val17, val28, val34})->setTailCall();
  //   tail call void @draw_line(i32 noundef %19, i32 noundef %21, i32 noundef %28, i32 noundef %34)
  builder.CreateCall(draw_lineFunc, {val19, val21, val28, val34})->setTailCall();
  //   %35 = add nsw i32 %11, -1
  Value *val35 = builder.CreateAdd(val11, builder.getInt32(-1), "", false, true);
  //   tail call void @draw_pythagoras_tree(i32 noundef %15, i32 noundef %17, i32 noundef %28, i32 noundef %34, i32 noundef %35)
  builder.CreateCall(dptFunc, {val15, val17, val28, val34, val35})->setTailCall();
  //   br label %6
  builder.CreateBr(BB6);

  // 36:                                               ; preds = %6
  builder.SetInsertPoint(BB36);
  //   ret void
  builder.CreateRetVoid();

  // Link PHI nodes
  //   %7 = phi i32 [ %0, %5 ], [ %28, %13 ]
  linkPhi2(val7, val0, BB5, val28, BB13);
  //   %8 = phi i32 [ %1, %5 ], [ %34, %13 ]
  linkPhi2(val8, val1, BB5, val34, BB13);
  //   %9 = phi i32 [ %2, %5 ], [ %19, %13 ]
  linkPhi2(val9, val2, BB5, val19, BB13);
  //   %10 = phi i32 [ %3, %5 ], [ %21, %13 ]
  linkPhi2(val10, val3, BB5, val21, BB13);
  //   %11 = phi i32 [ %4, %5 ], [ %35, %13 ]
  linkPhi2(val11, val4, BB5, val35, BB13);
  }

  // define dso_local void @app() local_unnamed_addr #3 {
  FunctionType *appFuncType = FunctionType::get(voidType, false);
  Function *appFunc =
      Function::Create(appFuncType, Function::ExternalLinkage, "app", module);
  {
  // setEntry(appFunc);
  BasicBlock *BB0 = createBB(appFunc);
  builder.SetInsertPoint(BB0);
  BasicBlock *BB1 = createBB(appFunc);
  BasicBlock *BB2 = createBB(appFunc);
  BasicBlock *BB6 = createBB(appFunc);
  BasicBlock *BB9 = createBB(appFunc);
  BasicBlock *BB11 = createBB(appFunc);
  BasicBlock *BB14 = createBB(appFunc);
  //   br label %2
  builder.CreateBr(BB2);

  // 1:                                                ; preds = %14, %11
  builder.SetInsertPoint(BB1);
  //   br label %2, !llvm.loop !13
  builder.CreateBr(BB2);

  // 2:                                                ; preds = %1, %0
  builder.SetInsertPoint(BB2);
  //   %3 = phi i32 [ 0, %0 ], [ %5, %1 ]
  PHINode *val3 = builder.CreatePHI(int32Ty, 2);
  //   %4 = phi i32 [ 1, %0 ], [ %12, %1 ]
  PHINode *val4 = builder.CreatePHI(int32Ty, 2);
  //   %5 = add nsw i32 %4, %3
  Value *val5 = builder.CreateAdd(val4, val3, "", false, true);
  //   switch i32 %5, label %11 [
  //     i32 14, label %6
  //     i32 0, label %6
  //   ]
  SwitchInst *sw = builder.CreateSwitch(val5, BB11, 2);
  sw->addCase(builder.getInt32(14), BB6);
  sw->addCase(builder.getInt32(0), BB6);


  // 6:                                                ; preds = %2, %2
  builder.SetInsertPoint(BB6);
  //   %7 = icmp eq i32 %5, 0
  Value *val7 = builder.CreateICmpEQ(val5, builder.getInt32(0));
  //   %8 = sub nsw i32 0, %4
  Value *val8 = builder.CreateSub(builder.getInt32(0), val4, "", false, true);
  //   br i1 %7, label %9, label %11
  builder.CreateCondBr(val7, BB9, BB11);

  // 9:                                                ; preds = %6
  builder.SetInsertPoint(BB9);
  //   %10 = tail call i32 (...) @simRand() #5
  CallInst *val10 = builder.CreateCall(simRandFunc);
  val10->setTailCall();
  //   store i32 %10, ptr @grad, align 4, !tbaa !5
  builder.CreateStore(val10, grad);
  //   br label %11
  builder.CreateBr(BB11);

  // 11:                                               ; preds = %2, %6, %9
  builder.SetInsertPoint(BB11);
  //   %12 = phi i32 [ %8, %9 ], [ %8, %6 ], [ %4, %2 ]
  PHINode *val12 = builder.CreatePHI(int32Ty, 3);
  //   %13 = icmp sgt i32 %5, 0
  Value *val13 = builder.CreateICmpSGT(val5, builder.getInt32(0));
  //   br i1 %13, label %14, label %1
  builder.CreateCondBr(val13, BB14, BB1);

  // 14:                                               ; preds = %11, %14
  builder.SetInsertPoint(BB14);
  //   %15 = phi i32 [ %16, %14 ], [ 0, %11 ]
  PHINode *val15 = builder.CreatePHI(int32Ty, 2);
  //   tail call void @draw_pythagoras_tree(i32 noundef 256, i32 noundef 51, i32 noundef 298, i32 noundef 51, i32 noundef %15)
  builder.CreateCall(dptFunc, {builder.getInt32(256), builder.getInt32(51), 
                               builder.getInt32(298), builder.getInt32(51), val15})->setTailCall();
  //   tail call void (...) @simFlush() #5
  builder.CreateCall(simFlushFunc)->setTailCall();
  //   %16 = add nuw nsw i32 %15, 1
  Value *val16 = builder.CreateAdd(val15, builder.getInt32(1), "", true, true);
  //   %17 = icmp eq i32 %16, %5
  Value *val17 = builder.CreateICmpEQ(val16, val5);
  //   br i1 %17, label %1, label %14, !llvm.loop !14
  builder.CreateCondBr(val17, BB1, BB14);

  // Link PHI nodes
  //   %3 = phi i32 [ 0, %0 ], [ %5, %1 ]
  linkPhi2(val3, builder.getInt32(0), BB0, val5, BB1);
  //   %4 = phi i32 [ 1, %0 ], [ %12, %1 ]
  linkPhi2(val4, builder.getInt32(1), BB0, val12, BB1);
  //   %12 = phi i32 [ %8, %9 ], [ %8, %6 ], [ %4, %2 ]
  linkPhi2(val12, val8, BB9, val8, BB6);
  val12->addIncoming(val4, BB2);
  //   %15 = phi i32 [ %16, %14 ], [ 0, %11 ]
  linkPhi2(val15, val16, BB14, builder.getInt32(0), BB11);
  }

  // Dump LLVM IR
  module->print(outs(), nullptr);\

  #ifdef GET_LL
  return 0;
  #endif

  outs() << "\n";
  bool verif = verifyFunction(*appFunc, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
    if (fnName == "simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
    }
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    if (fnName == "simRand") {
      return reinterpret_cast<void *>(simRand);
    }
    return nullptr;
  });
  ee->finalizeObject();

  simInit();

  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(appFunc, noargs);
  outs() << "[EE] Result: " << v.IntVal << "\n";

  simExit();
  return EXIT_SUCCESS;
}
