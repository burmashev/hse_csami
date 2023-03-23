#include <stdio.h>
#include <stdint.h>
#include <time.h>

enum { SECONDS = 60 * 60 * 24 };

int main(void) {
    time_t cur_time = time(NULL);
    int32_t day;
    while (scanf("%d", &day) == 1) {
        time_t new_day;
        if (__builtin_mul_overflow(SECONDS, day, &day)) {
            printf("%s\n", "OVERFLOW");
            continue;
        }
        if (__builtin_add_overflow(day, cur_time, &new_day)) {
            printf("%s\n", "OVERFLOW");
            continue;
        }
        struct tm * time_info = localtime(&new_day);
        time_info->tm_year += 1900;
        time_info->tm_mon += 1;
        printf("%04d-%02d-%02d\n", time_info->tm_year, time_info->tm_mon, time_info->tm_mday);
    }
}
