; ModuleID = 'hello'
source_filename = "hello"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %result = alloca i32, align 4
  %n = alloca i32, align 4
  store i32 10, ptr %a, align 4
  store i32 3, ptr %b, align 4
  store i32 5, ptr %c, align 4
  %value = load i32, ptr %a, align 4
  %value1 = load i32, ptr %b, align 4
  %multmp = mul i32 %value, %value1
  %value2 = load i32, ptr %c, align 4
  %addtmp = add i32 %value2, 1
  %modtmp = srem i32 %multmp, %addtmp
  store i32 %modtmp, ptr %result, align 4
  %value3 = load i32, ptr %result, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %value3)
  ret i32 %value3
}

declare i32 @printf(ptr, ...)
