#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd < 1) {
        return 1;
    }
    int rows = strtol(argv[2], NULL, 10);
    int cols = strtol(argv[3], NULL, 10);
    size_t file_len = rows * cols * sizeof(int);
    if (ftruncate(fd, file_len) == -1) {
        close(fd);
        return 1;
    }
    void *addr = mmap(NULL, file_len, PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        close(fd);
        return 1;
    }
    int (*matrix)[cols] = addr;
    int i = 0, j = 0;
    int right_stop = cols - 1;
    int left_stop = 0;
    int down_stop = rows - 1;
    int up_stop = 1;
    char move_to = 'R'; // R - right, L - left, D - down, U - up 
    int number = 1;
    while (number <= rows * cols) {
        if (move_to == 'R') {
            while (j <= right_stop) {
                matrix[i][j++] = number++;
            }
            move_to = 'D';
            ++i;
            --j;
            --right_stop;
        }
        if (move_to == 'D') {
            while (i <= down_stop) {
                matrix[i++][j] = number++;
            }
            move_to = 'L';
            --i;
            --j;
            --down_stop;
        }
        if (number > rows * cols) {
            break;
        }
        if (move_to == 'L') {
            while (j >= left_stop) {
                matrix[i][j--] = number++;
            }
            move_to = 'U';
            --i;
            ++j;
            ++left_stop;
        }
        if (move_to == 'U') {
            while (i >= up_stop) {
                matrix[i--][j] = number++;
            }
            move_to = 'R';
            ++i;
            ++j;
            ++up_stop;
        }
    }
    munmap(addr, file_len);
    close(fd);
    return 0;
}