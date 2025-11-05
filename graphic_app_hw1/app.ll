; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@grad = dso_local local_unnamed_addr global i32 0, align 4

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local range(i32 0, -2147483648) i32 @get_abs(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @llvm.abs.i32(i32 %0, i1 true)
  ret i32 %2
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @draw_line(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #1 {
  %5 = sub nsw i32 255, %1
  %6 = sub nsw i32 255, %3
  %7 = load i32, ptr @grad, align 4, !tbaa !5
  %8 = add nsw i32 %7, -1
  store i32 %8, ptr @grad, align 4, !tbaa !5
  %9 = add i32 %7, -65537
  %10 = sub nsw i32 %0, %2
  %11 = tail call range(i32 0, -2147483648) i32 @llvm.abs.i32(i32 %10, i1 true)
  %12 = sub nsw i32 %5, %6
  %13 = tail call range(i32 0, -2147483648) i32 @llvm.abs.i32(i32 %12, i1 true)
  %14 = icmp samesign ult i32 %11, %13
  br i1 %14, label %15, label %30

15:                                               ; preds = %4
  %16 = icmp sgt i32 %3, %1
  %17 = select i1 %16, i32 -1, i32 1
  %18 = icmp eq i32 %3, %1
  br i1 %18, label %45, label %19

19:                                               ; preds = %15
  %20 = sub nsw i32 %2, %0
  %21 = sub nsw i32 %6, %5
  br label %22

22:                                               ; preds = %19, %22
  %23 = phi i32 [ %5, %19 ], [ %28, %22 ]
  %24 = sub nsw i32 %23, %5
  %25 = mul nsw i32 %24, %20
  %26 = sdiv i32 %25, %21
  %27 = add nsw i32 %26, %0
  tail call void @simPutPixel(i32 noundef %27, i32 noundef %23, i32 noundef %9) #5
  %28 = add nsw i32 %23, %17
  %29 = icmp eq i32 %28, %6
  br i1 %29, label %45, label %22, !llvm.loop !9

30:                                               ; preds = %4
  %31 = icmp sgt i32 %0, %2
  %32 = select i1 %31, i32 -1, i32 1
  %33 = icmp eq i32 %0, %2
  br i1 %33, label %45, label %34

34:                                               ; preds = %30
  %35 = sub nsw i32 %6, %5
  %36 = sub nsw i32 %2, %0
  br label %37

37:                                               ; preds = %34, %37
  %38 = phi i32 [ %0, %34 ], [ %43, %37 ]
  %39 = sub nsw i32 %38, %0
  %40 = mul nsw i32 %39, %35
  %41 = sdiv i32 %40, %36
  %42 = add nsw i32 %41, %5
  tail call void @simPutPixel(i32 noundef %38, i32 noundef %42, i32 noundef %9) #5
  %43 = add nsw i32 %38, %32
  %44 = icmp eq i32 %43, %2
  br i1 %44, label %45, label %37, !llvm.loop !12

45:                                               ; preds = %37, %22, %30, %15
  ret void
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local noundef i32 @turn_x(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #0 {
  %5 = add i32 %1, %0
  %6 = sub i32 %5, %3
  ret i32 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local noundef i32 @turn_y(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #0 {
  %5 = sub i32 %1, %0
  %6 = add i32 %5, %2
  ret i32 %6
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @draw_pythagoras_tree(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #1 {
  br label %6

6:                                                ; preds = %13, %5
  %7 = phi i32 [ %0, %5 ], [ %28, %13 ]
  %8 = phi i32 [ %1, %5 ], [ %34, %13 ]
  %9 = phi i32 [ %2, %5 ], [ %19, %13 ]
  %10 = phi i32 [ %3, %5 ], [ %21, %13 ]
  %11 = phi i32 [ %4, %5 ], [ %35, %13 ]
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %36, label %13

13:                                               ; preds = %6
  %14 = add i32 %8, %7
  %15 = sub i32 %14, %10
  %16 = sub i32 %8, %7
  %17 = add i32 %16, %9
  %18 = sub i32 %17, %8
  %19 = add i32 %18, %15
  %20 = sub i32 %17, %15
  %21 = add i32 %20, %7
  tail call void @draw_line(i32 noundef %7, i32 noundef %8, i32 noundef %9, i32 noundef %10)
  tail call void @draw_line(i32 noundef %7, i32 noundef %8, i32 noundef %15, i32 noundef %17)
  tail call void @draw_line(i32 noundef %19, i32 noundef %21, i32 noundef %9, i32 noundef %10)
  tail call void @draw_line(i32 noundef %15, i32 noundef %17, i32 noundef %19, i32 noundef %21)
  %22 = mul nsw i32 %19, 3
  %23 = add nsw i32 %22, %15
  %24 = sub nsw i32 %21, %17
  %25 = mul nsw i32 %24, 7
  %26 = sdiv i32 %25, -4
  %27 = add i32 %23, %26
  %28 = sdiv i32 %27, 4
  %29 = mul nsw i32 %21, 3
  %30 = add nsw i32 %29, %17
  %31 = mul nsw i32 %18, 7
  %32 = sdiv i32 %31, 4
  %33 = add nsw i32 %30, %32
  %34 = sdiv i32 %33, 4
  tail call void @draw_line(i32 noundef %15, i32 noundef %17, i32 noundef %28, i32 noundef %34)
  tail call void @draw_line(i32 noundef %19, i32 noundef %21, i32 noundef %28, i32 noundef %34)
  %35 = add nsw i32 %11, -1
  tail call void @draw_pythagoras_tree(i32 noundef %15, i32 noundef %17, i32 noundef %28, i32 noundef %34, i32 noundef %35)
  br label %6

36:                                               ; preds = %6
  ret void
}

; Function Attrs: noreturn nounwind sspstrong uwtable
define dso_local void @app() local_unnamed_addr #3 {
  br label %2

1:                                                ; preds = %14, %11
  br label %2, !llvm.loop !13

2:                                                ; preds = %1, %0
  %3 = phi i32 [ 0, %0 ], [ %5, %1 ]
  %4 = phi i32 [ 1, %0 ], [ %12, %1 ]
  %5 = add nsw i32 %4, %3
  switch i32 %5, label %11 [
    i32 14, label %6
    i32 0, label %6
  ]

6:                                                ; preds = %2, %2
  %7 = icmp eq i32 %5, 0
  %8 = sub nsw i32 0, %4
  br i1 %7, label %9, label %11

9:                                                ; preds = %6
  %10 = tail call i32 (...) @simRand() #5
  store i32 %10, ptr @grad, align 4, !tbaa !5
  br label %11

11:                                               ; preds = %2, %6, %9
  %12 = phi i32 [ %8, %9 ], [ %8, %6 ], [ %4, %2 ]
  %13 = icmp sgt i32 %5, 0
  br i1 %13, label %14, label %1

14:                                               ; preds = %11, %14
  %15 = phi i32 [ %16, %14 ], [ 0, %11 ]
  tail call void @draw_pythagoras_tree(i32 noundef 256, i32 noundef 51, i32 noundef 298, i32 noundef 51, i32 noundef %15)
  tail call void (...) @simFlush() #5
  %16 = add nuw nsw i32 %15, 1
  %17 = icmp eq i32 %16, %5
  br i1 %17, label %1, label %14, !llvm.loop !14
}

declare i32 @simRand(...) local_unnamed_addr #2

declare void @simFlush(...) local_unnamed_addr #2

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.abs.i32(i32, i1 immarg) #4

attributes #0 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #5 = { nounwind }

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
!9 = distinct !{!9, !10, !11}
!10 = !{!"llvm.loop.mustprogress"}
!11 = !{!"llvm.loop.unroll.disable"}
!12 = distinct !{!12, !10, !11}
!13 = distinct !{!13, !11}
!14 = distinct !{!14, !10, !11}
