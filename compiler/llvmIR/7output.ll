; ModuleID = 'ForTest'
source_filename = "ForTest"

@0 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1

define float @main() {
entry:
  %i = alloca i32, align 4
  %sum = alloca i32, align 4
  %k = alloca float, align 4
  store i32 0, ptr %sum, align 4
  store float 0x40019999A0000000, ptr %k, align 4
  %i1 = alloca i32, align 4
  store i32 1, ptr %i1, align 4
  br label %loop.cond

loop.cond:                                        ; preds = %loop.body, %entry
  %i.load = load i32, ptr %i1, align 4
  %loopcond = icmp sle i32 %i.load, 5
  br i1 %loopcond, label %loop.body, label %loop.end

loop.body:                                        ; preds = %loop.cond
  %value = load i32, ptr %sum, align 4
  %value2 = load i32, ptr %i1, align 4
  %addtmp = add i32 %value, %value2
  store i32 %addtmp, ptr %sum, align 4
  %value3 = load float, ptr %k, align 4
  %fmultmp = fmul float %value3, 2.000000e+00
  store float %fmultmp, ptr %k, align 4
  %nextval = add i32 %i.load, 1
  store i32 %nextval, ptr %i1, align 4
  br label %loop.cond

loop.end:                                         ; preds = %loop.cond
  %value4 = load float, ptr %k, align 4
  %0 = fpext float %value4 to double
  %1 = call i32 (ptr, ...) @printf(ptr @0, double %0)
  ret float %value4
}

declare i32 @printf(ptr, ...)
