.global sort_by_abs
.global comparator

comparator: # (int* a, int* b)
	push %ebp
	mov %esp, %ebp

	xor %eax, %eax
	xor %ecx, %ecx
	movl 8(%ebp), %edx 
	movw (%edx), %ax # a
	xor %edx, %edx
	movl 12(%ebp), %edx
	movw (%edx), %cx # b

	testw %ax, %ax # a < 0?
	jnl pos_a
	negw %ax
pos_a:
	testw %cx, %cx # b < 0?
	jnl pos_b
	negw %cx
pos_b:
	cmp %ecx, %eax 
	jl lower # a < b?
	jg upper # a > b?
	je eq # a == b?
lower:
	movl $-1, %eax
	jmp comp_stop
upper:
	movl $1, %eax
	jmp comp_stop
eq:
	movl $0, %eax
	jmp comp_stop
	
comp_stop:
	movl %ebp, %esp
	pop %ebp
	ret

sort_by_abs:
	push %ebp
	movl %esp, %ebp
	movl $comparator, %eax
	push %eax
	movl $2, %eax
	push %eax
	push 12(%ebp)
	push 8(%ebp)
	call qsort
	movl %ebp, %esp
	pop %ebp
	ret
