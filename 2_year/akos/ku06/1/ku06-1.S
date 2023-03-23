text:
     .global run_on_stack

data:

run_on_stack:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx

    push %esp
    mov %edx, %esp 
    push %ecx 
    call *%eax

    mov %ebp, %esp
    pop %ebp
    ret