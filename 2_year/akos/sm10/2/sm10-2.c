#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    struct stat buf;
    unsigned long long files_size = 0;
    for (int i = 1; i != argc; ++i) {
        if (lstat(argv[i], &buf) == 0) { // exists
            if (S_ISREG(buf.st_mode)) { // regular
                if (buf.st_nlink == 1) { // only 1 link
                    files_size += buf.st_size;
                }
            }
        }
    }
    printf("%llu", files_size);
}
