; ModuleID = 'hello'
source_filename = "hello"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %n = alloca i32, align 4
  %m = alloca i32, align 4
  %l = alloca i32, align 4
  %k = alloca i32, align 4
  store i32 -10, ptr %l, align 4
  store i32 1025, ptr %n, align 4
  %value = load i32, ptr %l, align 4
  %value1 = load i32, ptr %l, align 4
  %addtmp = add i32 %value, %value1
  %value2 = load i32, ptr %n, align 4
  %addtmp3 = add i32 %addtmp, %value2
  store i32 %addtmp3, ptr %m, align 4
  %value4 = load i32, ptr %m, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %value4)
  ret i32 %value4
}

declare i32 @printf(ptr, ...)
