; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@colour = dso_local local_unnamed_addr global i32 0, align 4
@grad = dso_local local_unnamed_addr global i32 0, align 4

; Function Attrs: mustprogress nofree norecurse nosync nounwind optsize sspstrong willreturn memory(read, argmem: none, inaccessiblemem: none) uwtable
define dso_local range(i32 -16776961, -65535) i32 @main_colour() local_unnamed_addr #0 {
  %1 = load i32, ptr @colour, align 4, !tbaa !5
  %2 = srem i32 %1, 3
  %3 = icmp eq i32 %2, 1
  %4 = select i1 %3, i32 -16711936, i32 -65536
  %5 = icmp eq i32 %2, 0
  %6 = select i1 %5, i32 -16776961, i32 %4
  ret i32 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind optsize sspstrong willreturn memory(none) uwtable
define dso_local range(i32 0, -2147483648) i32 @get_abs(i32 noundef %0) local_unnamed_addr #1 {
  %2 = tail call i32 @llvm.abs.i32(i32 %0, i1 true)
  ret i32 %2
}

; Function Attrs: nounwind optsize sspstrong uwtable
define dso_local void @draw_line(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #2 {
  %5 = sub nsw i32 255, %1
  %6 = sub nsw i32 255, %3
  %7 = load i32, ptr @colour, align 4, !tbaa !5
  %8 = srem i32 %7, 3
  %9 = icmp eq i32 %8, 1
  %10 = select i1 %9, i32 -16711936, i32 -65536
  %11 = icmp eq i32 %8, 0
  %12 = select i1 %11, i32 -16776961, i32 %10
  %13 = load i32, ptr @grad, align 4, !tbaa !5
  %14 = add nsw i32 %13, -1
  store i32 %14, ptr @grad, align 4, !tbaa !5
  %15 = add nsw i32 %12, %14
  %16 = sub nsw i32 %0, %2
  %17 = tail call range(i32 0, -2147483648) i32 @llvm.abs.i32(i32 %16, i1 true)
  %18 = sub nsw i32 %5, %6
  %19 = tail call range(i32 0, -2147483648) i32 @llvm.abs.i32(i32 %18, i1 true)
  %20 = icmp samesign ult i32 %17, %19
  br i1 %20, label %21, label %36

21:                                               ; preds = %4
  %22 = icmp sgt i32 %3, %1
  %23 = select i1 %22, i32 -1, i32 1
  %24 = icmp eq i32 %3, %1
  br i1 %24, label %51, label %25

25:                                               ; preds = %21
  %26 = sub nsw i32 %2, %0
  %27 = sub nsw i32 %6, %5
  br label %28

28:                                               ; preds = %25, %28
  %29 = phi i32 [ %5, %25 ], [ %34, %28 ]
  %30 = sub nsw i32 %29, %5
  %31 = mul nsw i32 %30, %26
  %32 = sdiv i32 %31, %27
  %33 = add nsw i32 %32, %0
  tail call void @simPutPixel(i32 noundef %33, i32 noundef %29, i32 noundef %15) #6
  %34 = add nsw i32 %29, %23
  %35 = icmp eq i32 %34, %6
  br i1 %35, label %51, label %28, !llvm.loop !9

36:                                               ; preds = %4
  %37 = icmp sgt i32 %0, %2
  %38 = select i1 %37, i32 -1, i32 1
  %39 = icmp eq i32 %0, %2
  br i1 %39, label %51, label %40

40:                                               ; preds = %36
  %41 = sub nsw i32 %6, %5
  %42 = sub nsw i32 %2, %0
  br label %43

43:                                               ; preds = %40, %43
  %44 = phi i32 [ %0, %40 ], [ %49, %43 ]
  %45 = sub nsw i32 %44, %0
  %46 = mul nsw i32 %45, %41
  %47 = sdiv i32 %46, %42
  %48 = add nsw i32 %47, %5
  tail call void @simPutPixel(i32 noundef %44, i32 noundef %48, i32 noundef %15) #6
  %49 = add nsw i32 %44, %38
  %50 = icmp eq i32 %49, %2
  br i1 %50, label %51, label %43, !llvm.loop !11

51:                                               ; preds = %43, %28, %36, %21
  ret void
}

; Function Attrs: optsize
declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #3

; Function Attrs: mustprogress nofree norecurse nosync nounwind optsize sspstrong willreturn memory(none) uwtable
define dso_local noundef i32 @turn_x(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #1 {
  %5 = add i32 %1, %0
  %6 = sub i32 %5, %3
  ret i32 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind optsize sspstrong willreturn memory(none) uwtable
define dso_local noundef i32 @turn_y(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #1 {
  %5 = sub i32 %1, %0
  %6 = add i32 %5, %2
  ret i32 %6
}

; Function Attrs: nounwind optsize sspstrong uwtable
define dso_local void @draw_pythagoras_tree(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #2 {
  %6 = icmp eq i32 %4, 0
  br i1 %6, label %36, label %7

7:                                                ; preds = %5, %7
  %8 = phi i32 [ %34, %7 ], [ %4, %5 ]
  %9 = phi i32 [ %20, %7 ], [ %3, %5 ]
  %10 = phi i32 [ %18, %7 ], [ %2, %5 ]
  %11 = phi i32 [ %33, %7 ], [ %1, %5 ]
  %12 = phi i32 [ %27, %7 ], [ %0, %5 ]
  %13 = add i32 %11, %12
  %14 = sub i32 %13, %9
  %15 = sub i32 %11, %12
  %16 = add i32 %15, %10
  %17 = sub i32 %16, %11
  %18 = add i32 %17, %14
  %19 = sub i32 %16, %14
  %20 = add i32 %19, %12
  tail call void @draw_line(i32 noundef %12, i32 noundef %11, i32 noundef %10, i32 noundef %9) #7
  tail call void @draw_line(i32 noundef %12, i32 noundef %11, i32 noundef %14, i32 noundef %16) #7
  tail call void @draw_line(i32 noundef %18, i32 noundef %20, i32 noundef %10, i32 noundef %9) #7
  tail call void @draw_line(i32 noundef %14, i32 noundef %16, i32 noundef %18, i32 noundef %20) #7
  %21 = mul nsw i32 %18, 3
  %22 = add nsw i32 %21, %14
  %23 = sub nsw i32 %20, %16
  %24 = mul nsw i32 %23, 7
  %25 = sdiv i32 %24, -4
  %26 = add i32 %22, %25
  %27 = sdiv i32 %26, 4
  %28 = mul nsw i32 %20, 3
  %29 = add nsw i32 %28, %16
  %30 = mul nsw i32 %17, 7
  %31 = sdiv i32 %30, 4
  %32 = add nsw i32 %29, %31
  %33 = sdiv i32 %32, 4
  tail call void @draw_line(i32 noundef %14, i32 noundef %16, i32 noundef %27, i32 noundef %33) #7
  tail call void @draw_line(i32 noundef %18, i32 noundef %20, i32 noundef %27, i32 noundef %33) #7
  %34 = add nsw i32 %8, -1
  tail call void @draw_pythagoras_tree(i32 noundef %14, i32 noundef %16, i32 noundef %27, i32 noundef %33, i32 noundef %34) #7
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %36, label %7

36:                                               ; preds = %7, %5
  ret void
}

; Function Attrs: noreturn nounwind optsize sspstrong uwtable
define dso_local void @app() local_unnamed_addr #4 {
  br label %1

1:                                                ; preds = %17, %0
  %2 = phi i32 [ 0, %0 ], [ %4, %17 ]
  %3 = phi i32 [ 1, %0 ], [ %15, %17 ]
  %4 = add nsw i32 %3, %2
  switch i32 %4, label %14 [
    i32 14, label %5
    i32 0, label %5
  ]

5:                                                ; preds = %1, %1
  %6 = icmp eq i32 %4, 0
  %7 = sub nsw i32 0, %3
  br i1 %6, label %10, label %8

8:                                                ; preds = %5
  %9 = load i32, ptr @colour, align 4, !tbaa !5
  br label %12

10:                                               ; preds = %5
  %11 = tail call i32 (...) @simRand() #6
  store i32 %11, ptr @colour, align 4, !tbaa !5
  br label %12

12:                                               ; preds = %8, %10
  %13 = phi i32 [ %9, %8 ], [ %11, %10 ]
  store i32 %13, ptr @grad, align 4, !tbaa !5
  br label %14

14:                                               ; preds = %1, %12
  %15 = phi i32 [ %7, %12 ], [ %3, %1 ]
  %16 = icmp sgt i32 %4, 0
  br i1 %16, label %18, label %17

17:                                               ; preds = %18, %14
  br label %1

18:                                               ; preds = %14, %18
  %19 = phi i32 [ %20, %18 ], [ 0, %14 ]
  tail call void @draw_pythagoras_tree(i32 noundef 256, i32 noundef 51, i32 noundef 298, i32 noundef 51, i32 noundef %19) #7
  tail call void (...) @simFlush() #6
  %20 = add nuw nsw i32 %19, 1
  %21 = icmp eq i32 %20, %4
  br i1 %21, label %17, label %18, !llvm.loop !12
}

; Function Attrs: optsize
declare i32 @simRand(...) local_unnamed_addr #3

; Function Attrs: optsize
declare void @simFlush(...) local_unnamed_addr #3

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.abs.i32(i32, i1 immarg) #5

attributes #0 = { mustprogress nofree norecurse nosync nounwind optsize sspstrong willreturn memory(read, argmem: none, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree norecurse nosync nounwind optsize sspstrong willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind optsize sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { optsize "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind optsize sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #6 = { nounwind optsize }
attributes #7 = { optsize }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 20.1.8"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = distinct !{!12, !10}
