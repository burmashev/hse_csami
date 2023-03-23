#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_ipv4_subnet(const char* mask, const char* subnet_address, const char* address) {
	in_addr_t msk = inet_addr(mask);
	in_addr_t subadr = inet_addr(subnet_address);
	in_addr_t adr= inet_addr(address);
	in_addr_t new_one = msk & adr;
	if (subadr == new_one) {
		return true;
	} else {
		return false;
	}
}
