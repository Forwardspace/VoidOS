#include "stringfuncts.h"

//Get the length of a char* str
size_t strlen(char* str) {
	size_t len = 0;	
	while (str[len]) {
		len++;
	}
	
	return len;
}

void reverse(char* str) {
	for(int i = 0; i < strlen(str) / 2; i++) {
		char temp = str[i];
		str[i] = str[strlen(str) - i - 1];
		str[strlen(str) - i - 1] = temp;
	}
}

void itoa(int num, int base, char* buffer) {
	//TODO: CHANGE TO ALLOCATION
   	int idx = 0;
   	while (num != 0) {
		int digit = num % base;
		char c = (digit <= 9) ? '0' + digit : 'A' + digit - 9;
		buffer[idx++] = c;
	  	num /= base;
  }

	reverse(buffer);
}

//Optimized strcmp implementation
int strcmp(char* s1, char* s2) {
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}