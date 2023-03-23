#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   	if (argc < 2) {
   		return 0;
   	}
   	struct stat buf;
   	for (int i = 1; i != argc; ++i) {
   		if (stat(argv[i], &buf) == -1) {
   			if (lstat(argv[i], &buf) != -1) {
   				printf("%s %s\n", argv[i], "(broken symlink)");
   				continue;
   			}
   			printf("%s %s\n", argv[i], "(missing)");
   			continue;
   		}
   		//printf("%s %s\n", argv[i], "(broken symlink)");
   		//printf("%s %s\n", argv[i], "(missing)");
   		printf("%s\n", argv[i]);

   	}
    return 0;

}