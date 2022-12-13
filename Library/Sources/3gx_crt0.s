    .cpu mpcore
    .section ".crt0"
    .global _start, __service_ptr
    .align 4
    .arm

_start:
    b startup

__service_ptr:
    .word 0

startup:
    mov     r4, lr
    ldr     r0, =__bss_start__
    ldr     r1, =__bss_end__
    sub     r1, r1, r0
    bl      ClearMem
    ldr     R0, [SP]
    bl      __entrypoint
    mov     pc, r4

ClearMem:
    mov     r2, #3      @ Round down to nearest word boundary
    add     r1, r1, r2  @ Shouldn't be needed
    bics    r1, r1, r2  @ Clear 2 LSB (and set Z)
    bxeq    lr          @ Quit if copy size is 0
    mov     r2, #0

ClrLoop:
    stmia   r0!, {r2}
    subs    r1, r1, #4
    bne     ClrLoop
    bx      lr