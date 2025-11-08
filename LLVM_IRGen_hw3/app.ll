; ModuleID = 'app.c'
source_filename = "app.c"

@grad = global i32 0

declare void @simPutPixel(i32, i32, i32)

declare i32 @simRand()

declare void @simFlush()

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.abs.i32(i32, i1 immarg) #0

define void @draw_line(i32 %0, i32 %1, i32 %2, i32 %3) {
  %5 = sub nsw i32 255, %1
  %6 = sub nsw i32 255, %3
  %7 = load i32, ptr @grad, align 4
  %8 = add nsw i32 %7, -1
  store i32 %8, ptr @grad, align 4
  %9 = add i32 %7, -65537
  %10 = sub nsw i32 %0, %2
  %11 = tail call i32 @llvm.abs.i32(i32 %10, i1 true)
  %12 = sub nsw i32 %5, %6
  %13 = tail call i32 @llvm.abs.i32(i32 %12, i1 true)
  %14 = icmp ult i32 %11, %13
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

22:                                               ; preds = %22, %19
  %23 = phi i32 [ %5, %19 ], [ %28, %22 ]
  %24 = sub nsw i32 %23, %5
  %25 = mul nsw i32 %24, %20
  %26 = sdiv i32 %25, %21
  %27 = add nsw i32 %26, %0
  tail call void @simPutPixel(i32 %27, i32 %23, i32 %9)
  %28 = add nsw i32 %23, %17
  %29 = icmp eq i32 %28, %6
  br i1 %29, label %45, label %22

30:                                               ; preds = %4
  %31 = icmp sgt i32 %0, %2
  %32 = select i1 %31, i32 -1, i32 1
  %33 = icmp eq i32 %0, %2
  br i1 %33, label %45, label %34

34:                                               ; preds = %30
  %35 = sub nsw i32 %6, %5
  %36 = sub nsw i32 %2, %0
  br label %37

37:                                               ; preds = %37, %34
  %38 = phi i32 [ %0, %34 ], [ %43, %37 ]
  %39 = sub nsw i32 %38, %0
  %40 = mul nsw i32 %39, %35
  %41 = sdiv i32 %40, %36
  %42 = add nsw i32 %41, %5
  tail call void @simPutPixel(i32 %38, i32 %42, i32 %9)
  %43 = add nsw i32 %38, %32
  %44 = icmp eq i32 %43, %2
  br i1 %44, label %45, label %37

45:                                               ; preds = %37, %30, %22, %15
  ret void
}

define void @draw_pythagoras_tree(i32 %0, i32 %1, i32 %2, i32 %3, i32 %4) {
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
  tail call void @draw_line(i32 %7, i32 %8, i32 %9, i32 %10)
  tail call void @draw_line(i32 %7, i32 %8, i32 %15, i32 %17)
  tail call void @draw_line(i32 %19, i32 %21, i32 %9, i32 %10)
  tail call void @draw_line(i32 %15, i32 %17, i32 %19, i32 %21)
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
  tail call void @draw_line(i32 %15, i32 %17, i32 %28, i32 %34)
  tail call void @draw_line(i32 %19, i32 %21, i32 %28, i32 %34)
  %35 = add nsw i32 %11, -1
  tail call void @draw_pythagoras_tree(i32 %15, i32 %17, i32 %28, i32 %34, i32 %35)
  br label %6

36:                                               ; preds = %6
  ret void
}

define void @app() {
  br label %2

1:                                                ; preds = %14, %11
  br label %2

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
  %10 = tail call i32 @simRand()
  store i32 %10, ptr @grad, align 4
  br label %11

11:                                               ; preds = %9, %6, %2
  %12 = phi i32 [ %8, %9 ], [ %8, %6 ], [ %4, %2 ]
  %13 = icmp sgt i32 %5, 0
  br i1 %13, label %14, label %1

14:                                               ; preds = %14, %11
  %15 = phi i32 [ %16, %14 ], [ 0, %11 ]
  tail call void @draw_pythagoras_tree(i32 256, i32 51, i32 298, i32 51, i32 %15)
  tail call void @simFlush()
  %16 = add nuw nsw i32 %15, 1
  %17 = icmp eq i32 %16, %5
  br i1 %17, label %1, label %14
}

attributes #0 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
