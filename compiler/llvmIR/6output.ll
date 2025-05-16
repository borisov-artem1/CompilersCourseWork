; ModuleID = 'WhileExample'
source_filename = "WhileExample"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %n = alloca i32, align 4
  store i32 0, ptr %n, align 4
  br label %while

while:                                            ; preds = %do, %entry
  %value = load i32, ptr %n, align 4
  %cmp_smaller = icmp slt i32 %value, 5
  br i1 %cmp_smaller, label %do, label %end

do:                                               ; preds = %while
  %value1 = load i32, ptr %n, align 4
  %addtmp = add i32 %value1, 1
  store i32 %addtmp, ptr %n, align 4
  br label %while

end:                                              ; preds = %while
  %value2 = load i32, ptr %n, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %value2)
  ret i32 %value2
}

declare i32 @printf(ptr, ...)
