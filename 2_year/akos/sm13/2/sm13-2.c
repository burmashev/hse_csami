#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    FILE * fd = fopen(argv[1], "r");
    if (fd == NULL) {
        return 1;
    }
    time_t cur_time;
    time_t prev_time;
    time_t dif;
    struct tm time;
    time.tm_isdst = -1; // DST < 0
    if (fscanf(fd, "%04d/%02d/%02d %02d:%02d:%02d", &time.tm_year, &time.tm_mon, 
            &time.tm_mday, &time.tm_hour, 
            &time.tm_min, &time.tm_sec) != 6) {
        return 0;
    }
    time.tm_year -= 1900;
    time.tm_mon -=1;
    prev_time = mktime(&time); // first time
    if (prev_time == -1) {
        return 1;
    }
    while (fscanf(fd, "%04d/%02d/%02d %02d:%02d:%02d", &time.tm_year,  &time.tm_mon, 
            &time.tm_mday, &time.tm_hour, 
            &time.tm_min, &time.tm_sec) == 6) {
        time.tm_isdst = -1;
        time.tm_year -= 1900;
        time.tm_mon -=1;
        cur_time = mktime(&time);
        if (cur_time == -1) {
            return 1;
        }
        dif = cur_time - prev_time;
        printf("%ld\n", dif);
        prev_time = cur_time;
    }
    fclose(fd);
    return 0;
}