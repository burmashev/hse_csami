.text      
.global  discrim

four:
        .float 4.0
one:
        .float -1.0

discrim:
        ////////////
        pushl   %ebp
        movl    %esp, %ebp
        ////////////
        movss 8(%ebp), %xmm0
        movss 12(%ebp), %xmm1
        movss 16(%ebp), %xmm2
        ///////////
        mulss %xmm1, %xmm1 /* b^2 */
        mulss %xmm0, %xmm2
        mulss four, %xmm2 
        mulss one, %xmm2
        addss %xmm2, %xmm1
        movl 20(%ebp), %eax
        movss %xmm1, (%eax)
        ////////////
        movl %ebp, %esp 
        popl %ebp
        ret
        ///////////