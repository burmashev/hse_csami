#include <stdio.h>
#include <sys/stat.h>

// https://pubs.opengroup.org/onlinepubs/009695399/basedefs/sys/stat.h.html

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) {
        return buf;
    }
    char term_perms[9];
    char * start = buf; 
    size_t sticky = 0;
    // owners
    if (perms & S_IREAD) { // read 
        term_perms[0] = 'r';
    } else {
        term_perms[0] = '-';
    }
    if (perms & S_IWRITE) { // write
        term_perms[1] = 'w';
    } else {
        term_perms[1] = '-';
    }
    if (perms & S_IXUSR) { // execute
        term_perms[2] = 'x';
    } else {
        term_perms[2] = '-';
    }
    // groups
    if (perms & S_IRGRP) { // read
        term_perms[3] = 'r';
    } else {
        term_perms[3] = '-';
    }
    if (perms & S_IWGRP) { // write
        term_perms[4] = 'w';
    } else {
        term_perms[4] = '-';
    }
    if (perms & S_IXGRP) { // execute
        term_perms[5] = 'x';
    } else {
        term_perms[5] = '-';
    }
    // other users
    if (perms & S_IROTH) { // read
        term_perms[6] = 'r';
    } else {
        term_perms[6] = '-';
    }
    if (perms & S_IWOTH) { // write 
        ++sticky;
        term_perms[7] = 'w';
    } else {
        term_perms[7] = '-';
    }
    if (perms & S_IXOTH) { // execute
        ++sticky;
        term_perms[8] = 'x';
    } else {
        term_perms[8] = '-';
    }
    // SUID, if SUID and execute for groups or other users
    if (perms & S_ISUID) {
        if ((perms & S_IXGRP) || (perms & S_IXOTH)) {
            term_perms[2] = 's';
        }
    }
    // SGID, if SGID and execute for other users
    if ((perms & S_ISGID) && (perms & S_IXOTH))
        term_perms[5] = 's';
    // Sticky, if sticky and w and x for other users
    if ((perms & S_ISVTX) && sticky == 2) {
        term_perms[8] = 't';
    }
    if (size > 10) {
        size = 10;
    }
    for (size_t i = 0; i != size - 1; ++i) {
        *(buf++) = term_perms[i];
    };
    *buf = '\0';
    return start;
}