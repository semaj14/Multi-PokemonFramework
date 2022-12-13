.arm
.balign 4

.macro SVC_BEGIN name
    .section .text.\name, "ax", %progbits
    .global \name
    .type \name, %function
    .align 2
    .cfi_startproc
\name:
.endm

.macro SVC_END
    .cfi_endproc
.endm

SVC_BEGIN svcCustomBackdoor
    svc 0x80
    bx lr
SVC_END

SVC_BEGIN svcConvertVAToPA
    svc 0x90
    bx lr
SVC_END

SVC_BEGIN svcFlushDataCacheRange
    svc 0x91
    bx lr
SVC_END

SVC_BEGIN svcFlushEntireDataCache
    svc 0x92
    bx lr
SVC_END

SVC_BEGIN svcInvalidateInstructionCacheRange
    svc 0x93
    bx lr
SVC_END

SVC_BEGIN svcInvalidateEntireInstructionCache
    svc 0x94
    bx lr
SVC_END

SVC_BEGIN svcMapProcessMemoryEx
    str r4, [sp, #-4]!
    ldr r4, [sp, #4]
    svc 0xA0
    ldr r4, [sp], #4
    bx lr
SVC_END

SVC_BEGIN svcUnmapProcessMemoryEx
    svc 0xA1
    bx lr
SVC_END

SVC_BEGIN svcControlMemoryEx
    push {r0, r4, r5}
    ldr  r0, [sp, #0xC]
    ldr  r4, [sp, #0xC+0x4]
    ldr  r5, [sp, #0xC+0x8]
    svc  0xA2
    pop  {r2, r4, r5}
    str  r1, [r2]
    bx   lr
SVC_END

SVC_BEGIN svcControlMemoryUnsafe
    str r4, [sp, #-4]!
    ldr r4, [sp, #4]
    svc 0xA3
    ldr r4, [sp], #4
    bx lr
SVC_END

SVC_BEGIN svcFreeMemory
    svc  0xA3
    bx   lr
SVC_END

SVC_BEGIN svcControlService
    svc 0xB0
    bx lr
SVC_END

SVC_BEGIN svcCopyHandle
    str r0, [sp, #-4]!
    svc 0xB1
    ldr r2, [sp], #4
    str r1, [r2]
    bx lr
SVC_END

SVC_BEGIN svcTranslateHandle
    str r0, [sp, #-4]!
    svc 0xB2
    ldr r2, [sp], #4
    str r1, [r2]
    bx lr
SVC_END

SVC_BEGIN svcControlProcess
    svc 0xB3
    bx lr
SVC_END