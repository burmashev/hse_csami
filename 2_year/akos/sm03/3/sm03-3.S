.global обработка
# EBX -> struct S* next
# ESI -> i
# EDI -> j
# (p->m1[i] + p->m2[j]) / 2
обработка:
	push %ebp
	mov %esp, %ebp
	push %ebx
	xor %edx, %edx #ans
loop:
	testl %ebx, %ebx
	jz stop
	movl 4(%ebx, %esi, 4), %eax
	movl 52(%ebx, %edi, 4), %ecx
	addl %ecx, %eax
	movl %eax, %ecx
	shrl $31, %ecx
	addl %ecx, %eax
	sarl %eax
	addl %eax, %edx
	mov (%ebx), %ebx
	jmp loop
stop:
	pop %ebx
	movl %ebp, %esp
	pop %ebp
	pop %eax
	push %ecx
	push %eax
	ret


.text
    .global get_ans
get_ans:
    push %ebp
    mov %esp, %ebp
    push %ebx
    push %esi
    push %edi

    mov 8(%ebp), %ebx
    mov 12(%ebp), %esi
    mov 16(%ebp), %edi

    call обработка
    pop %eax

    pop %edi
    pop %esi
    pop %ebx
    mov %ebp, %esp
    pop %ebp
    ret
