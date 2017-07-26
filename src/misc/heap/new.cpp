#include "alloc.h"

void *operator new(size_t size) {
    return heap::malloc(size);
}
 
void *operator new[](size_t size) {
    return heap::malloc(size);
}
 
void operator delete(void *p) {
    heap::free(p);
}
 
void operator delete[](void *p) {
    heap::free(p);
}
