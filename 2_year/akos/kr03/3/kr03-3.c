#include <inttypes.h>
#include <stdio.h>

void print_parent_arg() {
    uint32_t num;
    asm ("mov (%%ebp), %%eax\n\t"
         "mov 8(%%eax), %%eax\n\t"
         "mov %%eax, %0\n\t"
         :"=m"(num)
         : 
         : "eax"
         );

    printf("%" PRIx32 "\n", num);
}

void calling_fun(int xyzzy) { 
	++xyzzy;
	print_parent_arg(); 
}

int main() {
	calling_fun(31);
}




/*
#include <inttypes.h>
#include <stdio.h>

void print_parent_arg() {
	uint32_t a;
	asm (
		"movl (%%ebp), %%eax\n\t"
		"mov 8(%%eax), %%eax"
		: "=a"(a)
		: 
		:
		);
	printf("%" PRIx32 "\n", a);
};
*/