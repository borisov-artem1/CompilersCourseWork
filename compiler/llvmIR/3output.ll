; ModuleID = 'hello'
source_filename = "hello"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %arr = alloca [3 x i32], align 4
  %n = alloca i32, align 4
  %k = alloca i32, align 4
  %arr_element_ptr = getelementptr [3 x i32], ptr %arr, i32 0, i32 0
  store i32 1, ptr %arr_element_ptr, align 4
  %arr_element_ptr1 = getelementptr [3 x i32], ptr %arr, i32 0, i32 1
  store i32 2, ptr %arr_element_ptr1, align 4
  %arr_element_ptr2 = getelementptr [3 x i32], ptr %arr, i32 0, i32 2
  store i32 3, ptr %arr_element_ptr2, align 4
  store i32 2, ptr %k, align 4
  %arr_element_ptr3 = getelementptr [3 x i32], ptr %arr, i32 0, i32 0
  %value = load i32, ptr %arr_element_ptr3, align 4
  %arr_element_ptr4 = getelementptr [3 x i32], ptr %arr, i32 0, i32 1
  %value5 = load i32, ptr %arr_element_ptr4, align 4
  %arr_element_ptr6 = getelementptr [3 x i32], ptr %arr, i32 0, i32 2
  %value7 = load i32, ptr %arr_element_ptr6, align 4
  %multmp = mul i32 %value5, %value7
  %value8 = load i32, ptr %k, align 4
  %addtmp = add i32 %value8, 1
  %divtmp = sdiv i32 %multmp, %addtmp
  %addtmp9 = add i32 %value, %divtmp
  store i32 %addtmp9, ptr %n, align 4
  %value10 = load i32, ptr %n, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %value10)
  ret i32 %value10
}

declare i32 @printf(ptr, ...)
