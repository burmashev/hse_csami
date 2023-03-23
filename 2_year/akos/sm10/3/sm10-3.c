#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

enum { BUF = 4096 };

int main(int argc, char* argv[]) {
    unsigned long long files_size = 0;
    DIR * dp = opendir(argv[1]);
    struct dirent * ep;
    if (dp) {
        while ((ep = readdir(dp))) {
            struct stat buf;
            char cur_file_path[BUF];
            char * cur_file_name = ep->d_name;
            snprintf(cur_file_path, sizeof(cur_file_path), "%s/%s", argv[1], cur_file_name); // path/file_name
            if (stat(cur_file_path, &buf) == 0) { // exists 
                if  (S_ISREG(buf.st_mode)) { // regular
                    if (buf.st_uid == getuid()) { // the owner is getuid()
                        if (cur_file_name[0] >= 'A' && cur_file_name[0] <= 'Z') { // [A..Z]
                            files_size += buf.st_size;
                        }
                    }
                }
            }
        }
    } else { // incorrect path 
        printf("%llu", files_size);
        return 1;
    }
    closedir(dp);
    printf("%llu", files_size);
    return 0;

}