#include <types.h>
#include <malloc.h>
#include <unistd.h>

extern u8 *fake_heap_end;
extern u8 *fake_heap_start;

u8 *getHeapStart(void) {
    return fake_heap_start;
}

u8 *getHeapEnd(void) {
    return (u8*)sbrk(0);
}

u8 *getHeapLimit(void) {
    return fake_heap_end;
}

// Returns the amount of used memory in bytes
int getMemUsed(void) {
    struct mallinfo mi = mallinfo();
    return mi.uordblks;
}

// Returns the amount of free memory in bytes
int getMemFree(void) {
    struct mallinfo mi = mallinfo();
    return mi.fordblks + (getHeapLimit() - getHeapEnd());
}