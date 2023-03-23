#include <unistd.h>

enum { BUF_SIZE = 4096 };

ssize_t copy_file(int in_fd, int out_fd) {
    ssize_t result;
    ssize_t ans = 0;
    char buf[BUF_SIZE];
    while ((result = read(in_fd, buf, BUF_SIZE)) > 0) {
        ssize_t copied;
        ssize_t shift = 0;
        while (result > 0 && ((copied = write(out_fd, buf + shift, result)) > 0)) {
            result -= copied;
            ans += copied;
            shift += copied;
        }
    }
    if (result != 0) {й
        return 1;
    }
    return ans;
};