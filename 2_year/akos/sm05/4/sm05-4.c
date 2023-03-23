#include <unistd.h>

enum { BUF_SIZE = 4096 };

struct FileWriteState
{
    int fd;
    unsigned char *buf;
    int bufsize;
    int used_buf;
};

static unsigned char buffer[BUF_SIZE];

static struct FileWriteState state = {
    .fd = 1,
    .buf = buffer,
    .bufsize = BUF_SIZE,
    .used_buf = 0,
    };

struct FileWriteState *stout = &state;

void flush(struct FileWriteState *out) {
    write(out->fd, out->buf, out->used_buf);
}

void writechar(int c, struct FileWriteState *out) {
    if (out->bufsize == out->used_buf) {
        flush(out);
        out->used_buf = 0;
    }
    out->buf[out->used_buf] = c;
    out->used_buf += 1;
}