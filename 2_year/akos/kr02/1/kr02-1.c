#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

// нашел тут: (вроде можно гуглить и использовать код из открытых источников)
// https://ru.stackoverflow.com/questions/496634/Изменить-порядок-бит-в-массиве-byte

void tinyconv(uint8_t bytes[], size_t size) {
	size_t i = 0;
	for (i = 0; i < size; ++i) {
		bytes[i] = (bytes[i] * 0x0202020202 & 0x010884422010) % 1023; 
	}
}
