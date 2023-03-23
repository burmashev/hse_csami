.global dot_product

.data
zero: 
    .float 0 

.text
dot_product:
    pushl %ebp
    movl %esp, %ebp
    movss zero, %xmm0 /* answer */ 
    movl 8(%ebp), %eax /* n */
    testl %eax, %eax
    jz stop
    movl 12(%ebp), %ecx /* x */ 
    movl 16(%ebp), %edx /* y */
loop:
    movss -4(%ecx, %eax, 4), %xmm1
    movss -4(%edx, %eax, 4), %xmm2
    mulss %xmm1, %xmm2
    addss %xmm2, %xmm0 
    decl %eax 
    testl %eax, %eax 
    jnz loop
stop: 
    movl 20(%ebp), %eax /* result */ 
    movss %xmm0, (%eax)  
    movl %ebp, %esp 
    popl %ebp
    ret
    