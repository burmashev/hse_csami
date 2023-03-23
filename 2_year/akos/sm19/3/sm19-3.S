.global stack_add

stack_add:

  pop %eax

  pop %ecx
  pop %edx

  add %ecx, %edx

  push %edx

  push %eax
