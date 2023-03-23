.text      
.global  myhypot

myhypot:
        pushl   %ebp
        movl    %esp, %ebp
        movsd   8(%ebp), %xmm0
        movsd   16(%ebp), %xmm1
        movl    24(%ebp), %eax
        mulsd   %xmm0, %xmm0
        mulsd   %xmm1, %xmm1
        addsd   %xmm0, %xmm1
        sqrtsd  %xmm1, %xmm2
        movsd   %xmm2, (%eax)
        movl %ebp, %esp 
        popl    %ebp
        ret