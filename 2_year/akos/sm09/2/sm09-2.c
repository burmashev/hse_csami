#include <sys/syscall.h>

void _start() {
    const char * buf = "hello world\n";
    asm volatile ( 
        "int $0x80" 
        : /* No output */
        : "a"(4), "b"(1), "c"(buf), "d"(12)
        );
    asm volatile ( 
        "int $0x80" 
        : /* No output */
        : "a"(1), "b"(0)
        );
}
