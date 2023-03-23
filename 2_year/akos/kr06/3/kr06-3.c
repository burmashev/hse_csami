#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

enum { BUF = 4096 };

int main(int argc, char * argv[]) {
    if (argc < 3) {
        return 1;
    }
    DIR * dp = opendir(argv[1]);
    struct dirent * ep;
    char * prefix = argv[2];
    size_t prefix_size = strlen(prefix);
    if (dp) {
        while ((ep = readdir(dp))) {
            struct stat buf;
            char file_prefix[prefix_size + 1];
            char cur_file_path[BUF];
            char * cur_file_name = ep->d_name;
            snprintf(cur_file_path, sizeof(cur_file_path), "%s/%s", argv[1], cur_file_name); // path/file_name
            if (stat(cur_file_path, &buf) == 0) { // exists 
                if (S_ISREG(buf.st_mode)) { // regular
                    int cur_file = open(cur_file_path, O_RDONLY);
                    if (cur_file == -1) {
                        closedir(dp);
                        return 1;
                    }
                    if (read(cur_file, file_prefix, prefix_size) == prefix_size) {
                        file_prefix[prefix_size] = '\0';
                        if (!strcmp(file_prefix, prefix)) { // file_prefix == prefix
                            printf("%s\n", cur_file_name);
                        }
                    }
                    close(cur_file);
                }
            }
        }
    } else {
        return 1;
    }
    closedir(dp);
    return 0;
};
