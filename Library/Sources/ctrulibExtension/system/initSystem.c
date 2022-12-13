#include <sys/iosupport.h>
#include <sys/time.h>
#include <string.h>
#include <3ds.h>

void (*__system_retAddr)(void);

void __system_initSyscalls(void);
void __system_allocateHeaps(void);
void __system_initArgv(void);
void __appInit(void);

Result __sync_init(void);

void __libctru_init(void) {
    return;
    __system_allocateHeaps();
}