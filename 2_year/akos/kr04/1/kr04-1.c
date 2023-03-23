#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 1) {
        return 1;
    }
    int rows = strtol(argv[2], NULL, 10);
    int cols = strtol(argv[3], NULL, 10);
    size_t file_len = rows * cols * sizeof(double);
    if (ftruncate(fd, file_len) == -1) {
        return 1;
    }
    void *addr = mmap(NULL, file_len, PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        return 1;
    }
    double (*matrix)[cols] = addr;
    for (int i = 0; i != rows; ++i) {
        for (int j = 0; j != cols; ++j) {
            double di = (double)i;
            double dj = (double)j;
            double el = 2 * sin(di)+ 4 * cos(dj/2);
            matrix[i][j] = el;
        }
    }
    munmap(addr, file_len);
    close(fd);
    return 0;
}