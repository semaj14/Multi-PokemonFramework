#include <Headers.hpp>

#define THREADVARS_MAGIC  0x21545624 // !TV$
#define REG32(x) *(vu32*)(x | (1u << 31))
#define GPU_PSC0_CNT REG32(0x1040001C)
#define GPU_PSC1_CNT REG32(0x1040002C)
#define GPU_TRANSFER_CNT REG32(0x10400C18)
#define GPU_CMDLIST_CNT REG32(0x104018F0)

namespace CTRPluginFramework {
    bool OSDImpl::DrawSaveIcon = false;
    bool OSDImpl::MessColors = false;
    u32 OSDImpl::WaitingForScreenshot = 0;
    u32 OSDImpl::FramesToPlay = 0;
    Hook OSDImpl::OSDHook;
    Screen OSDImpl::TopScreen;
    Screen OSDImpl::BottomScreen;
    RecursiveLock OSDImpl::ReClock;
    FloatingButton OSDImpl::FloatingBtn(IntRect(0, 0, 40, 40), Icon::DrawRocket);
    vector<OSDImpl::OSDMessage*> OSDImpl::Notifications;
    vector<OSDCallback> OSDImpl::Callbacks;
    vector<OSDCallback> OSDImpl::CallbacksTrashBin;
    void *OSDImpl::previousFBAddr[2][2][2] = {0};

    bool OSDImpl::IsFramePaused = false;
    bool OSDImpl::NeedToPauseFrame = false;
    bool OSDImpl::WritesToPrevFB = false;
    LightEvent OSDImpl::OnNewFrameEvent;
    LightEvent OSDImpl::OnFramePaused;
    LightEvent OSDImpl::OnFrameResume;
    Task OSDImpl::DrawNotifTask1(OSDImpl::DrawNotif_TaskFunc, nullptr, Task::AppCores);
    Task OSDImpl::DrawNotifTask2(OSDImpl::DrawNotif_TaskFunc, nullptr, Task::AppCores);

    static const Time g_second = Seconds(1.f);
    void InstallOSD(void);

    void OSDImpl::_Initialize(void) {
        RecursiveLock_Init(&ReClock);

        // Init frame event
        LightEvent_Init(&OnNewFrameEvent, RESET_STICKY);
        LightEvent_Init(&OnFramePaused, RESET_STICKY);
        LightEvent_Init(&OnFrameResume, RESET_STICKY);
        IsFramePaused = false;

        const u64 titlesNeedWritePrevFB[] = {
            0x0004000000101200ULL, // Puyo Puyo Tetris
            0x0004000000197500ULL, // Puyo Puyo Chronicle
            0x0004000000056600ULL, // Puyo Puyo!! 20th Anniversary
        };

        u64 titleID = Process::GetTitleID();

        for (u32 i = 0; i < sizeof(titlesNeedWritePrevFB) / sizeof(u64); i++) {
            if (titleID == titlesNeedWritePrevFB[i]) {
                WritesToPrevFB = true;
                break;
            }
        }

        InstallOSD();
    }

    #define XEND 390

    OSDImpl::OSDMessage::OSDMessage(const string &str, const Color &fg, const Color &bg) {
        text = str;
        width = Renderer::LinuxFontSize(text.c_str());
        drawn = false;
        foreground = fg;
        background = bg;
        time = Clock();
    }

    void OSDImpl::Update(void) {
        if (Preferences::IsEnabled(Preferences::UseFloatingBtn)) {
            FloatingBtn.Update(Touch::IsDown(), IntVector(Touch::GetPosition()));

            if (FloatingBtn())
                PluginMenuImpl::ForceOpen();
        }

        if (TryLock())
            return;

        if (Notifications.size() && Notifications.front()->drawn)
            Notifications.erase(remove_if (Notifications.begin(), Notifications.end(),
                [](OSDMessage *message) {
                    bool remove = message->drawn && message->time.HasTimePassed(Seconds(5.f));

                    if (remove)
                        delete message;

                    return remove;
                }), Notifications.end());

        Unlock();
    }

    bool OSDImpl::Draw(void) {
        if (Notifications.empty())
            return false;

        int posX;
        int posY = min((u32)15, (u32)Notifications.size());
        posY = 230 - (15 * posY);
        int count = 0;

        for (OSDMessage *message : Notifications) {
            posX = XEND - message->width;
            Renderer::DrawString(message->text.c_str(), posX, posY, message->foreground, message->background);
            posY += 5;

            if (!message->drawn)
                message->time.Restart();

            message->drawn = true;
            count++;

            if (count >= 15)
                break;
        }

        return (true);
    }

    s32 OSDImpl::DrawNotif_TaskFunc(void *arg) {
        Renderer::SetTarget(TOP);

        DrawNotifArgs *args = reinterpret_cast<DrawNotifArgs*>(arg);
        OSDIter messIter = args->begin;
        OSDIter endIter = args->end;
        int posY = args->posY;

        for (; messIter != endIter; ++messIter) {
            OSDMessage *message = *messIter;
            int posX = XEND - message->width;
            Renderer::DrawString(message->text.c_str(), posX, posY, message->foreground, message->background);
            posY += 5;

            if (!message->drawn)
                message->time.Restart();

            message->drawn = true;
        }

        return 0;
    }

    u32 GetBPP(GSPFormat format);

    u32 OSDImpl::MainCallback(u32 isBottom, int nextBank, void *leftFb, void *rightFb, int stride, int format, int swap) {
        if (leftFb)
            CallbackCommon(isBottom, leftFb, rightFb, stride, format, swap);

        if (ProcessImpl::Status == Running)
            return HookContext::GetCurrent().OriginalFunction<u32>(isBottom, nextBank, leftFb, rightFb, stride, format, swap);

        return 0;
    }

    u32 OSDImpl::MainCallback2(u32 r0, u32 *params, u32 isBottom, u32 arg) {
        // It appears that sometimes that ptr is nullptr ???
        if (params) {
            // u32 isBottom = params[0];
            void *leftFb = (void*)params[1];
            // void *addrB = params[2]; possible, not confirmed
            u32 stride = params[3];
            u32 format = params[4] & 0xF;

            if (leftFb)
                CallbackCommon(isBottom, leftFb, nullptr, stride, format, 0);
        }

        if (ProcessImpl::Status == Running)
            return HookContext::GetCurrent().OriginalFunction<u32>(r0, params, isBottom, arg);

        return 0;
    }

    Result OSDImpl::OnTopScreenFrame(void) {
        if (FramesToPlay)
            --FramesToPlay;

        // If frame has to be paused
        PauseFrame();

        if (DrawSaveIcon)
            Icon::DrawSave(10, 10);

        OSDImpl::Update();
        LightEvent_Pulse(&OnNewFrameEvent);
        return 0;
    }

    Result OSDImpl::OnBottomScreenFrame(void) {
        // Floating button
        if (Preferences::IsEnabled(Preferences::UseFloatingBtn))
            FloatingBtn.Draw();

        // Touch cursor and / or position
        if (Touch::IsDown()) {
            IntVector touchPos(Touch::GetPosition());

            if (Preferences::IsEnabled(Preferences::DrawTouchCursor)) {
                int posX = touchPos.x - 2;
                int posY = touchPos.y - 1;
                Icon::DrawHandCursor(posX, posY);
            }

            if (Preferences::IsEnabled(Preferences::DrawTouchPosition)) {
                string &&str = Utils::Format("Touch.x: %d  Touch.y: %d", touchPos.x, touchPos.y);
                int posY = 20;
                Renderer::DrawString(str.c_str(), 10, posY, Color::White, Color::Black);
            }
        }

        return 0;
    }

    static u32 GetBuffer(u32 addr) {
        FwkSettings &settings = FwkSettings::Get();
        u32 ret;

        if (settings.CachedDrawMode || SystemImpl::IsCitra)
            ret = addr;

        else {
            u32 newAddr = PA_FROM_VA(addr);
            ret = (newAddr & (1 << 31)) ? newAddr : 0;
        }

        if (addr < 0x01000000 || addr > 0x40000000)
            return 0;

        else return ret;
    }

    void OSDImpl::CallbackCommon(u32 isBottom, void *addr, void *addrB, int stride, int format, int swap) {
        if (SystemImpl::Status())
            return;

        // Screen shot first
        if (Screenshot::OSDCallback(isBottom, addr, addrB, stride, format))
            return;

        // Convert to actual addresses and check validity
        if (WritesToPrevFB) {
            previousFBAddr[isBottom][swap ? 1 : 0][0] = addr;
            previousFBAddr[isBottom][swap ? 1 : 0][1] = addrB;
            addr = previousFBAddr[isBottom][swap ? 0 : 1][0];
            addrB = previousFBAddr[isBottom][swap ? 0 : 1][1];
        }

        addr = (void*)GetBuffer((u32)addr);

        if (!isBottom)
            addrB = (void*)GetBuffer((u32)addrB);

        if (!addr)
            return;

        if (!isBottom) {
            ScreenImpl::Top->Acquire((u32)addr, (u32)addrB, stride, format & 0b111);
            Renderer::SetTarget(TOP);
            Result res = OnTopScreenFrame();

            // No osd when game is paused
            if (ProcessImpl::IsPaused || res)
                return;
        }

        else {
            ScreenImpl::Bottom->Acquire((u32)addr, (u32)addrB, stride, format & 0b111);
            Renderer::SetTarget(BOTTOM);
            OnBottomScreenFrame();
        }

        DrawNotifArgs args[2]; ///< Careful with the scope of that var
        Lock();
        FwkSettings &settings = FwkSettings::Get();

        if (settings.CachedDrawMode) {
            svcInvalidateProcessDataCache(CUR_PROCESS_HANDLE, reinterpret_cast<u32>(addr), isBottom ? stride * 320 : stride * 400);

            if (!isBottom && addrB && addrB != addr)
                svcInvalidateProcessDataCache(CUR_PROCESS_HANDLE, reinterpret_cast<u32>(addrB), stride * 400);
        }

        if (Notifications.size()) {
            int nbOfMessage = min((u32)15, (u32)Notifications.size());
            int posY = 230 - 15 * nbOfMessage;

            args[0].begin = Notifications.begin();
            args[0].end = next(Notifications.begin(), nbOfMessage / 2);
            args[0].posY = posY;
            args[1].begin = args[0].end;
            args[1].end = next(Notifications.begin(), nbOfMessage);
            args[1].posY = posY + 15 * (nbOfMessage / 2);

            DrawNotifTask1.Start((void*)&args[0]);
            DrawNotifTask2.Start((void*)&args[1]);
        }

        // Remove callbacks in the trash bin
        if (CallbacksTrashBin.size()) {
            Callbacks.erase(remove_if (Callbacks.begin(), Callbacks.end(),
                [](OSDCallback cb) {
                    auto &trashbin = CallbacksTrashBin;
                    auto foundIter = find(trashbin.begin(), trashbin.end(), cb);
                    return foundIter != trashbin.end();
                }), Callbacks.end());

            CallbacksTrashBin.clear();
        }

        // We need to ensure that notifications are handled before running callbacks
        DrawNotifTask1.Wait();
        DrawNotifTask2.Wait();

        // Call OSD Callbacks
        if (Callbacks.size()) {
            Screen screen;
            screen.IsTop = !isBottom;
            screen.Is3DEnabled = isBottom ? false : ScreenImpl::Top->Is3DEnabled();
            screen.LeftFramebuffer = (u32)addr;
            screen.RightFramebuffer = (u32)addrB;
            screen.Stride = stride;
            screen.BytesPerPixel = GetBPP((GSPFormat)format);
            screen.Format = (GSPFormat)format;

            for (size_t i = 0; i < Callbacks.size(); i++) {
                if (Callbacks[i])
                    Callbacks[i](screen);
            }
        }

        Unlock();

        if (settings.CachedDrawMode) {
            svcFlushProcessDataCache(CUR_PROCESS_HANDLE, reinterpret_cast<u32>(addr), isBottom ? stride * 320 : stride * 400);

            if (!isBottom && addrB && addrB != addr)
                svcFlushProcessDataCache(CUR_PROCESS_HANDLE, reinterpret_cast<u32>(addrB), stride * 400);
        }
    }

    void OSDImpl::UpdateScreens(void) {
        ScreenImpl *screen = ScreenImpl::Top;

        // Top screen
        TopScreen.IsTop = true;
        TopScreen.Is3DEnabled = screen->Is3DEnabled();
        TopScreen.LeftFramebuffer = (u32)screen->GetLeftFrameBuffer(false);
        TopScreen.RightFramebuffer = (u32)screen->GetRightFrameBuffer(false);
        TopScreen.Stride = (u32)screen->GetStride();
        TopScreen.BytesPerPixel = screen->GetBytesPerPixel();
        TopScreen.Format = screen->GetFormat();

        screen = ScreenImpl::Bottom;

        // Bottom screen
        BottomScreen.IsTop = false;
        BottomScreen.Is3DEnabled = screen->Is3DEnabled();
        BottomScreen.LeftFramebuffer = (u32)screen->GetLeftFrameBuffer(false);
        BottomScreen.RightFramebuffer = (u32)screen->GetRightFrameBuffer(false);
        BottomScreen.Stride = (u32)screen->GetStride();
        BottomScreen.BytesPerPixel = screen->GetBytesPerPixel();
        BottomScreen.Format = screen->GetFormat();
    }

    static const u32 g_OSDPattern[] = {
        0xE1833000, // ORR R3, R3, R0
        0xE2044CFF, // AND R4, R4, #0xFF00
        0xE3C33CFF, // BIC R3, R3, #0xFF00
        0xE1833004, // ORR R3, R3, R4
        0xE1824F93, // STREX R4, R3, [R2] // 0x14

        0xE8830E60, // STMIA R3, {R5, R6, R9 - R11}
        0xEE078F9A, // MCR p15, 0, R8, c7, c10, 4
        0xE3A03001, // MOV R3, #1
        0xE7902104, // LDR R2, [R0, R4, LSL#2] // 0x10

        0xEE076F9A, // MCR p15, 0, R6, c7, c10, 4
        0xE3A02001, // MOV R2, #1
        0xE7901104, // LDR R1, [R0, R4, LSL#2]
        0xE1911F9F, // LDREX R1, [R1]
        0xE3C110FF, // BIC R1, R1, #0xFF // 0x14

        0xE3A00000, // MOV R0, #0
        0xEE070F9A, // MCR P15, 0, R0, c7, c10, 4
        0xE3A00001, // MOV R0, #1
        0xE7951104, // LDR R1, [R5, R4, LSL#2] // 0x10

        0xE3A00000, // MOV R0, #0
        0xEE070F9A, // MCR P15, 0, R0, c7, c10, 4
        0xE2850001, // ADD R0, R5, #1
        0xEA000004, // B #16 // 0x10
    };

    static u8 *memsearch(u8 *startPos, const void *pattern, u32 size, u32 patternSize) {
        const u8 *patternc = (const u8*)pattern;
        u32 table[256];

        // Pre-processing
        for (u32 i = 0; i < 256; i++)
            table[i] = patternSize;

        for (u32 i = 0; i < patternSize - 1; i++)
            table[patternc[i]] = patternSize - i - 1;

        u32 j = 0;

        // Searching
        while (j <= size - patternSize) {
            u8 c = startPos[j + patternSize - 1];

            if (patternc[patternSize - 1] == c && memcmp(pattern, startPos + j, patternSize - 1) == 0)
                return startPos + j;

            j += table[c];
        }

        return nullptr;
    }

    static u32 SearchStmfd(u32 start, u32 size, u32 stmfd) {
        if (!start || !size || !stmfd)
            return (0);

        u32 result = 0;
        u32 *end = (u32*)(start - size);

        for (u32 *addr = (u32*)start; addr > end; addr--) {
            if (*addr == stmfd) {
                result = (u32)addr;
                break;
            }
        }

        return result;
    }

    static u32 SearchOSD(u32 pattern) {
        u8 *address = nullptr;

        if (pattern == 0) {
            address = memsearch((u8*)0x100000, g_OSDPattern, Process::GetTextSize(), 0x14);

            if (address == nullptr)
                address = memsearch((u8*)0x100000, &g_OSDPattern[5], Process::GetTextSize(), 0x10);
        }

        else if (pattern == 3)
            address = memsearch((u8*)0x100000, &g_OSDPattern[9], Process::GetTextSize(), 0x14);

        else if (pattern == 4)
            address = memsearch((u8*)0x100000, &g_OSDPattern[14], Process::GetTextSize(), 0x10);

        else if (pattern == 5)
            address = memsearch((u8*)0x100000, &g_OSDPattern[18], Process::GetTextSize(), 0x10);

        return (u32)address;
    }

    void InstallOSD(void) {
        const u32 stmfd1 = 0xE92D5FF0; // STMFD SP!, {R4-R12, LR}
        const u32 stmfd2 = 0xE92D47F0; // STMFD SP!, {R4-R10, LR}
        const u32 stmfd3 = 0xE92D4070; // STMFD SP!, {R4-R6, LR}

        u32 found = SearchOSD(0);
        u32 found2 = 0;
        found = SearchStmfd(found, 0x400, stmfd1);

        if (!found) {
            found = SearchOSD(3);
            found = SearchStmfd(found, 0x400, stmfd2);

            if (!found) {
                found2 = SearchOSD(4);
                found2 = SearchStmfd(found2, 0x400, stmfd3);

                if (!found2)
                    return;

                OSDImpl::OSDHook.InitializeForMitm(found2, u32(OSDImpl::MainCallback2)).Enable();
                return;
            }
        }

        OSDImpl::OSDHook.InitializeForMitm(found, u32(OSDImpl::MainCallback)).Enable();
    }

    using CTRPFLock = CTRPluginFramework::Lock;
    using namespace CTRPluginFrameworkImpl::Services;

    namespace {
        Mutex FrameLockingMutex;
        bool IsForced = false;
        bool HasGameResumed = false;
        Task CheckFrameResumedTask([](void *arg) -> s32 {
            while (!HasGameResumed) {
                Sleep(Milliseconds(32)); ///< Wait for 2 frames

                if (!HasGameResumed)
                    GSP::TriggerPSCEvents();
            }

            return 0;
        });
    }

    void OSDImpl::Lock(void) {
        RecursiveLock_Lock(&ReClock);
    }

    bool OSDImpl::TryLock(void) {
        return (RecursiveLock_TryLock(&ReClock));
    }

    void OSDImpl::Unlock(void) {
        RecursiveLock_Unlock(&ReClock);
    }

    enum {
        CLEARED_STICKY = -2,
        CLEARED_ONESHOT = -1,
        SIGNALED_ONESHOT = 0,
        SIGNALED_STICKY = 1
    };

    static inline int LightEvent_TryReset(LightEvent &event) {
        __dmb();

        do {
            if (__ldrex(&event.state)) {
                __clrex();
                return 0;
            }
        }

        while (__strex(&event.state, CLEARED_ONESHOT));

        __dmb();
        return 1;
    }

    // Return false when event was signaled, true on timeout
    static bool LightEvent__WaitTimeOut(LightEvent &event, const Time timeout) {
        s64 timeOutNs = timeout.AsMicroseconds() * 1000;
        Result toRes = 0x09401BFE;
        Result res = 0;

        for (; res != toRes; ) {
            if (event.state == CLEARED_STICKY) {
                res = syncArbitrateAddressWithTimeout(&event.state, ARBITRATION_WAIT_IF_LESS_THAN_TIMEOUT, 0, timeOutNs);
                return res == toRes;
            }

            if (event.state != CLEARED_ONESHOT) {
                if (event.state == SIGNALED_STICKY)
                    return false;

                if (event.state == SIGNALED_ONESHOT && LightEvent_TryReset(event))
                    return false;
            }

            res = syncArbitrateAddressWithTimeout(&event.state, ARBITRATION_WAIT_IF_LESS_THAN_TIMEOUT, 0, timeOutNs);
        }

        return res == toRes;
    }

    int OSDImpl::PauseFrame(void) {
        HasGameResumed = true;
        // Check if we need to pause frame
        if (WaitingForScreenshot || FramesToPlay || !ProcessImpl::IsPaused || !NeedToPauseFrame)
            return 0;

        // Check frame buffers validity before pausing
        if (ScreenImpl::CheckGspFrameBuffersInfo())
            return 0;

        {
            CTRPFLock lock(FrameLockingMutex);

            if (IsForced || !NeedToPauseFrame)
                return 0;

            // Lock game threads except this one
            ProcessImpl::LockGameThreads();
            IsFramePaused = true;
        }

        // Wake up threads waiting for frame to be paused
        LightEvent_Signal(&OnFramePaused);

        // Wait until the frame is ready to continue
        LightEvent_Wait(&OnFrameResume);
        LightEvent_Clear(&OnFrameResume);

        IsFramePaused = false;
        return 1;
    }

    void OSDImpl::WaitFramePaused(void) {
        if (IsFramePaused)
            return;

        bool isAsync = ProcessImpl::Status & NoImage;

        if (!isAsync) {
            IsForced = false;
            NeedToPauseFrame = true;

            while ((IsForced = LightEvent__WaitTimeOut(OnFramePaused, Milliseconds(50))) && ScreenImpl::CheckGspFrameBuffersInfo());

            LightEvent_Clear(&OnFramePaused);
            CTRPFLock lock(FrameLockingMutex);

            // Lock game threads
            if (!IsFramePaused) {
                ProcessImpl::LockGameThreads();
                IsForced = true;
            }
        }

        IsFramePaused = true;

        // Wake up gsp event thread
        GSP::ResumeInterruptReceiver();
    }

    void OSDImpl::ResumeFrame(const u32 nbFrames) {
        if (!IsFramePaused)
            return;

        HasGameResumed = false;
        bool isAsync = ProcessImpl::Status & NoImage;
        GSP::PauseInterruptReceiver();

        if (isAsync)
            return;

        FramesToPlay = nbFrames;

        // Unlock game threads
        ProcessImpl::UnlockGameThreads();

        // Async job to ensure frame is resumed
        CheckFrameResumedTask.Start();

        // Wake up game's thread
        LightEvent_Signal(&OnFrameResume);

        if (nbFrames) {
            // Wait until all our frames are rendered and the process is paused again
            LightEvent_Wait(&OnFramePaused);
            LightEvent_Clear(&OnFramePaused);
        }

        else IsForced = NeedToPauseFrame = false;
    }
}