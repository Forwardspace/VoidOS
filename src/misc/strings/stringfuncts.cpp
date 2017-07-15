#include "stringfuncts.h"

//Get the length of a char* str
size_t strlen(char* str) {
	size_t len = 0;	
	while (str[len]) {
		len++;
	}
}
