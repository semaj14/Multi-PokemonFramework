#include <Headers.hpp>

#define PA_PTR(addr) (void*)((u32)(addr) | 1 << 31)
#define REG32(addr) (*(vu32*)(PA_PTR(addr)))

extern "C" {
    u32 g_gspEventThreadPriority;
    void LoadCROHooked(void);
    void OnLoadCro(void);
    void abort(void);
    void initSystem(void);
    void initLib(void);
    Result __sync_init(void);
    void __system_initSyscalls(void);
    s32 PLGLDR__FetchEvent(void);
    void PLGLDR__Reply(s32 event);
    void hidInitFake();
    void hidExitFake();
    void hidSetSharedMem(vu32 *sharedMem);
    extern u32 __ctru_heap;
    extern u32 __ctru_heap_size;
}

using CTRPluginFramework::Hook;
using namespace CTRPluginFrameworkImpl::Services;

namespace CTRPluginFramework {
    static u8 keepThreadStack[0x1000] ALIGN(8);
    FS_Archive _sdmcArchive;
    Handle g_continueGameEvent = 0;
    Handle g_keepThreadHandle;
    Handle g_keepEvent = 0;
    Handle g_resumeEvent = 0;
    bool g_keepRunning = true;
    void ThreadInit(void *arg);
    void ThreadExit(void);
    void InstallOSD(void);
    void InitializeRandomEngine(void);
    static ThreadEx g_mainThread(ThreadInit, 0x4000, 0x19, -1);
    int main(void);
}

namespace Kernel {
    void Initialize(void);
}

static Hook g_onLoadCroHook;
static Hook g_onSharedMemMapHook;
static LightLock g_onLoadCroLock;

void abort(void) {
    if (CTRPluginFramework::System::OnAbort)
        CTRPluginFramework::System::OnAbort();

    CTRPluginFramework::Color c(255, 69, 0);
    CTRPluginFramework::ScreenImpl::Top->Flash(c);
    CTRPluginFramework::ScreenImpl::Bottom->Flash(c);
    CTRPluginFramework::ThreadExit();

    while (true);
}

static void ExecuteLoopOnEvent(void) {
    using CTRPluginFramework::PluginMenuExecuteLoop;
    PluginMenuExecuteLoop::ExecuteAR();
    PluginMenuExecuteLoop::ExecuteBuiltin();
}

void OnLoadCro(void) {
    LightLock_Lock(&g_onLoadCroLock);
    ExecuteLoopOnEvent();
    LightLock_Unlock(&g_onLoadCroLock);
}

Result OnSharedMemMap(Handle handle, void *sharedMem, MemPerm myPerm, MemPerm otherPerm) {
    Result res = svcMapMemoryBlock(handle, (u32)sharedMem, myPerm, otherPerm);

    if (R_SUCCEEDED(res) && sharedMem && CTRPluginFramework::FwkSettings::Get().UseGameHidMemory) {
        u64 firstSysTick = reinterpret_cast<vu64*>(sharedMem)[0];
        u32 arrayIndex = reinterpret_cast<vu32*>(sharedMem)[4];
        u32 sharedMemTouchScreen = (u32)sharedMem + 0xA8;
        u64 firstSysTickTS = reinterpret_cast<vu64*>(sharedMemTouchScreen)[0];
        u32 arrayIndexTS = reinterpret_cast<vu32*>(sharedMemTouchScreen)[4];
        u64 currSysTick = svcGetSystemTick();

        if (llabs(currSysTick - firstSysTick) < 1000000000ULL && llabs(currSysTick - firstSysTickTS) < 1000000000ULL && arrayIndex < 8 && arrayIndexTS < 8)
            hidSetSharedMem((vu32*)sharedMem);
    }

    return res;
}

#ifdef _MSC_VER
#define WEAK_SYMBOL
#else
#define WEAK_SYMBOL __attribute__((weak))
#endif

namespace CTRPluginFramework {
    void WEAK_SYMBOL PatchProcess(FwkSettings &settings) {}
    void WEAK_SYMBOL EarlyCallback(u32 *savedInstructions);
    void WEAK_SYMBOL OnProcessExit(void) {}
    void WEAK_SYMBOL OnPluginToSwap(void) {}
    void WEAK_SYMBOL OnPluginFromSwap(void) {}

    namespace Heap {
        extern u8 *__ctrpf_heap;
        extern u32 __ctrpf_heap_size;
    }

    static void InitFS(void) {
        // Init sdmcArchive
        FS_Path sdmcPath = {PATH_EMPTY, 1, (u8*)""};
        FSUSER_OpenArchive(&_sdmcArchive, ARCHIVE_SDMC, sdmcPath);

        // Set current working directory
        if (FwkSettings::Header->isDefaultPlugin) {
            string path = "/luma/plugins/ActionReplay";

            if (!Directory::IsExists(path))
                Directory::Create(path);

            path += Utils::Format("/%016llX", Process::GetTitleID());

            if (!Directory::IsExists(path))
                Directory::Create(path);

            Directory::ChangeWorkingDirectory(path + "/");
        }

        else {
            char path[255] = {0};
            PLGLDR__GetPluginPath(path);

            for (u32 i = 254; i > 0; --i) {
                if (path[i] != '/')
                    continue;

                path[i] = 0;
                break;
            }

            Directory::ChangeWorkingDirectory(path);
        }
    }

    static void InitHeap(void) {
        u32 size = 0x100000;
        Heap::__ctrpf_heap_size = size;
        Heap::__ctrpf_heap = static_cast<u8*>(::operator new(size));
    }

    void KeepThreadMain(void *arg UNUSED) {
        __sync_init();
        __system_initSyscalls();
        initLib();
        srvInit();
        acInit();
        amInit();
        fsInit();
        hidInitFake();
        cfguInit();
        plgLdrInit();

        Kernel::Initialize();
        SystemImpl::Initialize();
        InitializeRandomEngine();
        ProcessImpl::Initialize();
        ScreenImpl::Initialize();

        FwkSettings &settings = FwkSettings::Get();
        settings.ThreadPriority = 0x30;
        settings.AllowActionReplay = true;
        settings.AllowSearchEngine = true;
        settings.WaitTimeToBoot = Seconds(5.f);
        FwkSettings::SetThemeDefault();

        Scheduler::Initialize();
        OSDImpl::_Initialize();

        const vector<u32> LoadCroPattern = {
            0xE92D5FFF, 0xE28D4038, 0xE89407E0, 0xE28D4054,
            0xE8944800, 0xEE1D4F70, 0xE59FC058, 0xE3A00000,
            0xE5A4C080, 0xE284C028, 0xE584500C, 0xE584A020
        };

        u32 loadCroAddress = Utils::Search<u32>(0x00100000, Process::GetTextSize(), LoadCroPattern);

        if (loadCroAddress) {
            LightLock_Init(&g_onLoadCroLock);
            g_onLoadCroHook.Initialize(loadCroAddress, (u32)LoadCROHooked);
            g_onLoadCroHook.Enable();
        }

        u32 svcMapMemoryBlockAddr = 0x00100000 - 4;

        do {
            svcMapMemoryBlockAddr = Utils::Search<u32>(svcMapMemoryBlockAddr + 4, Process::GetTextSize(), {0xEF00001F});

            if (svcMapMemoryBlockAddr) {
                for (int i = 0; i > -10; i--) {
                    if (reinterpret_cast<u32*>(svcMapMemoryBlockAddr)[i] == 0xE3A03201) {
                        g_onSharedMemMapHook.Initialize(svcMapMemoryBlockAddr, (u32)OnSharedMemMap);
                        g_onSharedMemMapHook.SetFlags(USE_LR_TO_RETURN);
                        g_onSharedMemMapHook.Enable();
                        svcMapMemoryBlockAddr = 0;
                        break;
                    }
                }
            }
        }

        while (svcMapMemoryBlockAddr);

        InitFS();
        InitHeap();

        // Patch process before it starts & let the dev init some settings
        PatchProcess(settings);

        // Init hid properly depending on the settings
        if (settings.UseGameHidMemory) {
            // Check the svcMapMemoryBlock hook was installed properly
            if (!g_onSharedMemMapHook.IsEnabled())
                abort();
        }

        else {
            hidExitFake();
            hidInit();
        }

        Preferences::LoadSettings();
        svcSignalEvent(g_continueGameEvent);

        // Check threads priorities
        settings.ThreadPriority = min(settings.ThreadPriority, (u32)0x3E);

        if (GSP::Initialize()) {
            ScreenImpl::Top->Flash((Color&)Color::Yellow);
            abort();
        }

        // Wait for the required time
        Sleep(settings.WaitTimeToBoot);
        svcCreateEvent(&g_keepEvent, RESET_ONESHOT);

        // Create plugin's main thread
        g_mainThread.Start(nullptr);

        // Reduce priority
        while (R_FAILED(svcSetThreadPriority(g_keepThreadHandle, settings.ThreadPriority - 1)));

        // Wait until Main Thread finished all it's initializing
        svcWaitSynchronization(g_keepEvent, U64_MAX);
        svcCloseHandle(g_keepEvent);
        Handle memLayoutChanged;
        svcControlProcess(CUR_PROCESS_HANDLE, PROCESSOP_GET_ON_MEMORY_CHANGE_EVENT, (u32)&memLayoutChanged, 0);

        while (true) {
            if (svcWaitSynchronization(memLayoutChanged, 100000000ULL) == 0x09401BFE) {
                s32 event = PLGLDR__FetchEvent();

                if (event == PLG_SLEEP_ENTRY) {
                    SystemImpl::AptStatus |= BIT(6);
                    PLGLDR__Reply(event);
                }

                else if (event == PLG_SLEEP_EXIT) {
                    SystemImpl::WakeUpFromSleep();
                    PLGLDR__Reply(event);
                }

                else if (event == PLG_ABOUT_TO_SWAP) {
                    OnPluginToSwap();

                    // Un-map hook memory
                    HookManager::Lock();
                    HookManager::PrepareToUnmapMemory();
                    svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x01E80000, 0x2000);

                    // Reply and wait
                    PLGLDR__Reply(event);

                    // Re-map hook memory
                    svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x1E80000, CUR_PROCESS_HANDLE, __ctru_heap + __ctru_heap_size, 0x2000);
                    HookManager::RecoverFromUnmapMemory();
                    HookManager::Unlock();
                    OnPluginFromSwap();
                }

                else if (event == PLG_ABOUT_TO_EXIT) {
                    OnProcessExit();
                    ProcessImpl::SignalExit();
                    SystemImpl::AptStatus |= BIT(3);
                    Scheduler::Exit();
                    PluginMenuImpl::ForceExit();

                    if (settings.UseGameHidMemory)
                        hidExitFake();

                    else hidExit();

                    cfguExit();
                    fsExit();
                    amExit();
                    acExit();
                    srvExit();

                    // Un-map hook wrapper memory
                    HookManager::Lock();
                    HookManager::PrepareToUnmapMemory();
                    svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x01E80000, 0x2000);

                    // This function do not return and exit the thread
                    PLGLDR__Reply(event);
                }

                continue;
            }

            ProcessImpl::UpdateMemRegions();
        }

        svcCloseHandle(g_keepEvent);
        svcExitThread();
    }

    void Initialize(void) {
        Font::Initialize();
        const char *cheatsPath = "/cheats";

        if (!Directory::IsExists(cheatsPath))
            Directory::Create(cheatsPath);

        // Set AR file path
        Preferences::CheatsFile = "cheats.txt";

        // Default: cheats.txt in cwd
        if (!File::Exists(Preferences::CheatsFile))
            Preferences::CheatsFile = Utils::Format("/cheats/%016llX.txt", Process::GetTitleID());

        const char *ssPath = "/Screenshots";

        if (!Directory::IsExists(ssPath))
            Directory::Create(ssPath);

        // Set default screenshot path
        Screenshot::Path = ssPath;
        Screenshot::Path.append("/");

        // Set default screenshot prefix
        Screenshot::Prefix = "[";
        Process::GetName(Screenshot::Prefix);
        Screenshot::Prefix += Utils::Format(" - %08X] - Screenshot", (u32)Process::GetTitleID());
        Screenshot::Initialize();
    }

    // Main thread's start
    void ThreadInit(void *arg) {
        Initialize();

        // Wake up init thread
        svcSignalEvent(g_keepEvent);

        // Reduce thread priority
        svcSetThreadPriority(threadGetHandle(threadGetCurrent()), FwkSettings::Get().ThreadPriority);

        // Update memory layout
        ProcessImpl::UpdateMemRegions();

        // Start plugin
        main();
        ThreadExit();
    }

    void ThreadExit(void) {
        // In which thread are we?
        if (reinterpret_cast<u32>(((CThread_tag*)threadGetCurrent())->stacktop) < 0x07000000) {
            // Remove the OSD Hook
            OSDImpl::OSDHook.Disable();

            // Release process in case it's currently paused
            ProcessImpl::IsPaused = min((u32)ProcessImpl::IsPaused, (u32)1);
            ProcessImpl::Play(true);

            // Exit services
            gspExit();

            // Exit loop in keep thread
            g_keepRunning = false;
            svcSignalEvent(g_keepEvent);
            threadExit(1);
            return;
        }

        if (g_mainThread.GetStatus() == ThreadEx::RUNNING) {
            ProcessImpl::Play(true);
            PluginMenuImpl::ForceExit();
            g_mainThread.Join(false);
        }

        // We aborted in a very early stage, so just release the game and exit
        else svcSignalEvent(g_continueGameEvent);

        svcExitThread();
    }

    extern "C"
    int __entrypoint(int arg) {
        // Call early callback, with pointer to the 2 saved instructions
        if (EarlyCallback)
            EarlyCallback((u32*)arg);

        ProcessImpl::MainThreadTls = (u32)getThreadLocalStorage();
        ProcessImpl::EnableExceptionHandlers();
        SystemImpl::CheckCitra();
        svcCreateEvent(&g_continueGameEvent, RESET_ONESHOT);
        svcCreateThread(&g_keepThreadHandle, KeepThreadMain, arg, (u32*)&keepThreadStack[0x1000], 0x1A, 0);
        svcWaitSynchronization(g_continueGameEvent, U64_MAX);
        svcCloseHandle(g_continueGameEvent);
        return 0;
    }
}