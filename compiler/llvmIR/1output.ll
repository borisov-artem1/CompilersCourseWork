; ModuleID = 'Test'
source_filename = "Test"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 42, ptr %x, align 4
  %value = load i32, ptr %x, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %value)
  ret i32 %value
}

declare i32 @printf(ptr, ...)
