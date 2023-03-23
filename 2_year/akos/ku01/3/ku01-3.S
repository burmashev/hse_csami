.global mul2
mul2:
    push %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    movl (%eax), %ecx
    shl $1, %ecx
    jo stop
    movl %ecx, (%eax)
stop:
    movl %ebp, %esp
    pop %ebp
    ret