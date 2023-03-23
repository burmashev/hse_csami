.global обработка
# (%ebx) -> struct S* next
# 4(%ebx) -> m1[0]
# 4+12*4(%ebx) -> m2[0]
# ESI -> i
# EDI -> j
# (p->m1[i] + p->m2[j]) / 2
#
обработка:
	push %ebp
 	mov %esp, %ebp
 	push %ebx
	xor %edx, %edx # sum
loop:
	test %ebx, %ebx
	jz stop
	mov 4(%ebx, %esi, 4), %eax # m1[i]
	mov 4+12*4(%ebx, %edi, 4), %ecx # m2[j]
	add %eax, %ecx # ecx = m1[i] + m2[j]
	mov %ecx, %eax
	shr $31, %ecx
	add %ecx, %eax
	sar %eax # eax = m1[i] + m2[j] / 2
	add %eax, %edx
	mov (%ebx), %ebx # next element
	jmp loop
stop:
	pop %ebx
	mov %ebp, %esp
 	pop %ebp
 	pop %eax
 	push %edx
 	push %eax
	ret
