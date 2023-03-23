.global print_tb
	.equ SYS_exit, 1
	.equ SYS_write, 4
	.equ SYS_read, 3
	.equ STDIN_FILENO, 0
	.equ STDOUT_FILENO, 1

.data
print_tb_:
	.ascii "print_tb\n"
print_tb_end:

foo_:
	.ascii "foo\n"
foo_end:

bar_:
	.ascii "bar\n"
bar_end:

main_:
	.ascii "main\n"
main_end:

.text
myprint:
	push %ebp
   	mov %esp, %ebp
	push %edx
	mov $SYS_write, %eax
	mov $STDOUT_FILENO, %ebx
	mov 8(%ebp), %ecx
	mov 12(%ebp), %edx
	int $0x80
	pop %edx
	mov %ebp, %esp
	pop %ebp
	ret

print_tb:
	push %ebp
	mov %esp, %ebp
	mov %ebp, %edx
loop:
	mov 4(%edx), %eax
	mov %eax, %ecx
	sub $4, %ecx
	mov (%ecx), %ecx
	add %eax, %ecx

	cmp $print_tb, %ecx
	jz is_print_tb

	cmp $foo, %ecx
	jz is_foo

	cmp $bar, %ecx
	jz is_bar

	jmp stop
is_print_tb:	
	push $print_tb_end-print_tb_
	push $print_tb_
	call myprint
	movl (%edx), %edx
	jmp loop
is_foo:
	push $foo_end-foo_
	push $foo_	
	call myprint
	movl (%edx), %edx
	jmp loop
is_bar:
	push $bar_end-bar_
	push $bar_
	call myprint
	movl (%edx), %edx
	jmp loop
stop:
	push $main_end-main_
	push $main_
	call myprint
	
	mov %ebp, %esp
	pop %ebp
	ret
	
