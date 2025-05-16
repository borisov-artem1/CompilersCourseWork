; ModuleID = 'IfElseExample'
source_filename = "IfElseExample"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 2, ptr %x, align 4
  br label %next

next:                                             ; preds = %entry
  %value = load i32, ptr %x, align 4
  %cmp_equal = icmp eq i32 %value, 0
  br i1 %cmp_equal, label %then, label %next1

end:                                              ; preds = %next7, %then6, %then2, %then
  %value10 = load i32, ptr %x, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %value10)
  ret i32 %value10

then:                                             ; preds = %next
  store i32 1, ptr %x, align 4
  br label %end

next1:                                            ; preds = %next
  %value4 = load i32, ptr %x, align 4
  %cmp_equal5 = icmp eq i32 %value4, 1
  br i1 %cmp_equal5, label %then2, label %next3

then2:                                            ; preds = %next1
  store i32 2, ptr %x, align 4
  br label %end

next3:                                            ; preds = %next1
  %value8 = load i32, ptr %x, align 4
  %cmp_equal9 = icmp eq i32 %value8, 2
  br i1 %cmp_equal9, label %then6, label %next7

then6:                                            ; preds = %next3
  store i32 3, ptr %x, align 4
  br label %end

next7:                                            ; preds = %next3
  store i32 4, ptr %x, align 4
  br label %end
}

declare i32 @printf(ptr, ...)
