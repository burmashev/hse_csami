.globl myexp

.data
one:    
        .double 1

.text
myexp:
        pushl %ebp
        movl %esp, %ebp
        movsd 8(%ebp), %xmm0 /* x */
        movsd one, %xmm1 /* S_{i-1} */
        movsd one, %xmm2 /* S_{i} */
        movsd one, %xmm3 /* x^(i) */
        movsd one, %xmm4 /* (i)! */
        movsd one, %xmm5 /* i */
        movsd one, %xmm7 /* 1 for loop */
loop:
        movsd %xmm2, %xmm1 /* S_{i-1} = S_{i} */
        mulsd %xmm0, %xmm3 /* x^i = x^{i-1}*x */
        mulsd %xmm5, %xmm4 /* i! = (i-1)!*i */
        movsd %xmm3, %xmm6 /* %xmm6 as a temp rg */ 
        divsd %xmm4, %xmm6 /* %xmm6 = x^(i)/(i)! */
        addsd %xmm6, %xmm2 /* S_i += x^(i)/(i)! */
        addsd %xmm7, %xmm5 /* ++i */
        comisd %xmm1, %xmm2 /* S_{i-1} == S_{i} */
        jnz loop
        movl 16(%ebp), %eax
        movsd %xmm2, (%eax)   
        movl %ebp, %esp 
        popl %ebp
        ret
