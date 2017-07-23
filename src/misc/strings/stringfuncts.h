#pragma once
#include <stddef.h>
#include <stdint.h>

size_t strlen(char* str);

void reverse(char* str);

void itoa(int num, int base, char* buffer);
