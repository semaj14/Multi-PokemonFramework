#include "3ds.h"

#include <algorithm>
#include <cmath>
#include <cfloat>

#include "CTRPluginFrameworkImpl/ActionReplay/ARHandler.hpp"
#include "CTRPluginFramework/System/Controller.hpp"
#include "CTRPluginFramework/System/Process.hpp"
#include "CTRPluginFramework/System/Touch.hpp"
#include "CTRPluginFramework/System/Vector.hpp"
#include "CTRPluginFramework/Utils/Utils.hpp"

#include "Framework/CRO.hpp"

#define debug 0
#if debug
#define Notify(str, ...) OSD::Notify(Utils::Format(str, ##__VA_ARGS__))
#else
#define Notify(str, ...)
#endif

extern "C"
void AR__ExecuteRoutine(u32 **args, const u32 *routine);

namespace CTRPluginFramework {
    using Register = ARHandler::Register;

    static u32 arStack[1000] ALIGN(8);
    u32 ARHandler::Offset[2] = {0};
    Register ARHandler::Data[2];
    u32 ARHandler::Storage[2] = {0};
    u32 ARHandler::ActiveOffset = 0;
    u32 ARHandler::ActiveData = 0;
    u32 ARHandler::ActiveStorage = 0;
    bool ARHandler::ExitCodeImmediately = false;
    static bool ToggleFloat = false;
    static ARCodeContext *g_context;

    bool ActionReplay_IsValidAddress(u32 address, bool write) {
        if (!Process::CheckAddress(address, (int)write + 1)) {
            Notify("Unreachable: %08X", address);
            return false;
        }

        return true;
    }

    #define CheckAddress(addr, write) ActionReplay_IsValidAddress(addr, write)

    void ARHandler::Execute(ARCodeContext &ctx) {
        g_context = &ctx;
        Offset[0] = 0;
        Offset[1] = 0;
        Data[0].Clear();
        Data[1].Clear();
        Storage[0] = ctx.storage[0];
        Storage[1] = ctx.storage[1];
        ActiveStorage = ActiveData = ActiveOffset = 0;
        ExitCodeImmediately = false;
        ToggleFloat = false;
        _Execute(ctx.codes);
        ctx.storage[0] = Storage[0];
        ctx.storage[1] = Storage[1];
    }

    struct Game {
        u32 id;
    };

    static const vector<Game> game = {
        {0x55D00}, {0x55E00}, {0x11C400}, {0x11C500}, {0x164800}, {0x175E00}, {0x1B5000}, {0x1B5100}
    };

    template <typename T>
    bool Write(u32 address, T value) {
        u32 titleID = Process::GetTitleID();
        static vector<u32> limits = {0x8044000, 0x8163000};

        if (titleID == game[2].id || titleID == game[3].id)
            limits[1] += 0x3000;

        else if (titleID == game[4].id || titleID == game[5].id || titleID == game[6].id || titleID == game[7].id) {
            limits = {0x8009000, 0x8103000};

            if (titleID == game[6].id || titleID == game[7].id)
                limits[1] += 0x5000;
        }

        if ((titleID == game[0].id || titleID == game[1].id || titleID == game[2].id || titleID == game[3].id || titleID == game[4].id || titleID == game[5].id || titleID == game[6].id || titleID == game[7].id) && (address >= limits[0] && address < limits[1])) {
            if (CRO::Toggle(address, true)) {
                *(T*)address = value;
                CRO::Toggle(address, false);
                return (true);
            }
        }

        else {
            if (CheckAddress(address, true)) {
                *(T*)address = value;
                return (true);
            }
        }

        return false;
    }

    bool Write32(u32 address, u32 value) {
        if (Write<vu32>(address, value))
            return true;

        return false;
    }

    bool Write16(u32 address, u16 value) {
        if (Write<vu16>(address, value))
            return true;

        return false;
    }

    bool Write8(u32 address, u8 value) {
        if (Write<vu8>(address, value))
            return true;

        return false;
    }

    template <typename T>
    bool Read(u32 address, T &value) {
        u32 titleID = Process::GetTitleID();
        static vector<u32> limits = {0x8044000, 0x8163000};

        if (titleID == game[2].id || titleID == game[3].id)
            limits[1] += 0x3000;

        else if (titleID == game[4].id || titleID == game[5].id || titleID == game[6].id || titleID == game[7].id) {
            limits = {0x8009000, 0x8103000};

            if (titleID == game[6].id || titleID == game[7].id)
                limits[1] += 0x5000;
        }

        if ((titleID == game[0].id || titleID == game[1].id || titleID == game[2].id || titleID == game[3].id || titleID == game[4].id || titleID == game[5].id || titleID == game[6].id || titleID == game[7].id) && (address >= limits[0] && address < limits[1])) {
            if (CRO::Toggle(address, true)) {
                value = *(T*)address;
                CRO::Toggle(address, false);
                return (true);
            }
        }

        else {
            if (CheckAddress(address, true)) {
                value = *(T*)address;
                return (true);
            }
        }

        return false;
    }

    bool Read32(u32 address, u32 &value) {
        if (Read<u32>(address, value))
            return true;

        return false;
    }

    bool Read16(u32 address, u16 &value) {
        if (Read<u16>(address, value))
            return true;

        return false;
    }

    bool Read8(u32 address, u8 &value) {
        if (Read<u8>(address, value))
            return true;

        return false;
    }

    static bool Memcpy(u32 address, u8 *pattern, u32 size) {
        u32 titleID = Process::GetTitleID();
        static vector<u32> limits = {0x8044000, 0x8163000};

        if (titleID == game[2].id || titleID == game[3].id)
            limits[1] += 0x3000;

        else if (titleID == game[4].id || titleID == game[5].id || titleID == game[6].id || titleID == game[7].id) {
            limits = {0x8009000, 0x8103000};

            if (titleID == game[6].id || titleID == game[7].id)
                limits[1] += 0x5000;
        }

        if ((titleID == game[0].id || titleID == game[1].id || titleID == game[2].id || titleID == game[3].id || titleID == game[4].id || titleID == game[5].id || titleID == game[6].id || titleID == game[7].id) && (address >= limits[0] && address < limits[1])) {
            if (CRO::Toggle(address, true)) {
                while (size--)
                    *(vu8*)address++ = *pattern++;

                CRO::Toggle(address, false);
                return (true);
            }
        }

        else {
            if (CheckAddress((u32)pattern, false) && CheckAddress(address, true)) {
                while (size--)
                    *(vu8*)address++ = *pattern++;

                return (true);
            }
        }

        return false;
    }

    bool AlmostEqualRelative(float A, float B, float maxRelDiff = FLT_EPSILON);
    #define IsValid(val) (!std::isnan(val) && !std::isinf(val))
    #define FP_EQ(x, y) (IsValid(x) && AlmostEqualRelative(x, y))

    #define Cond32(operator, flcmp) \
    if (conditionalMode == CondMode::ImmAgainstData) { \
        if (currentData.isVFP) { \
            float imm = *(float*)(code.Right); \
            \
            if (flcmp(imm, currentData.vfp)) \
                continue; \
        } \
        \
        else if (code.Right operator currentData.value) \
            continue; \
    } \
    \
    else if (conditionalMode == CondMode::ImmAgainstStorage) { \
        if (code.Right operator Storage[ActiveStorage]) \
            continue; \
    } \
    \
    else if (conditionalMode == CondMode::DataAgainstVal) { \
        if (currentData.isVFP) { \
            if (flcmp(currentData.vfp, vfpval)) \
                continue; \
        } \
        \
        else if (currentData.value operator value) \
            continue; \
    } \
    \
    else if (conditionalMode == CondMode::DataAgainstStorage) { \
        if (currentData.isVFP) { \
            value = Storage[ActiveStorage]; \
            if (flcmp(currentData.vfp, vfpval)) \
                continue; \
        } \
        \
        else if (currentData.value operator Storage[ActiveStorage]) \
            continue; \
    } \
    \
    else if (code.Right operator value) \
        continue;

    #define Cond16(operator) \
    if (conditionalMode == CondMode::ImmAgainstData) { \
        if ((code.Right & 0xFFFF) operator ((currentData.value & 0xFFFF) & mask)) \
            continue; \
    } \
    \
    else if (conditionalMode == CondMode::ImmAgainstStorage) { \
        if ((code.Right & 0xFFFF) operator ((Storage[ActiveStorage] & 0xFFFF) & mask)) \
            continue; \
    } \
    \
    else if (conditionalMode == CondMode::DataAgainstVal) { \
        if ((currentData.value & 0xFFFF) operator value16) \
            continue; \
    } \
    \
    else if (conditionalMode == CondMode::DataAgainstStorage) { \
        if ((currentData.value & 0xFFFF) operator (Storage[ActiveStorage] & 0xFFFF)) \
            continue; \
    } \
    \
    else if ((code.Right & 0xFFFF) operator value16) \
        continue;

    bool ARHandler::_Execute(const ARCodeVector &codes) {
        enum CondMode {
            ImmAgainstVal,
            DataAgainstVal,
            ImmAgainstData,
            ImmAgainstStorage,
            DataAgainstStorage
        };

        union {
            u32 value = 0;
            float vfpval;
        };

        u16 value16 = 0;
        u16 mask;
        bool waitForEndLoop = false;
        bool waitForExitCode = false;
        CondMode conditionalMode = ImmAgainstVal;
        int conditionCount = 0;
        int loopCount = 0;
        int loopIteration = 0;
        ARCodeVector loopCodes;

        for (const ARCode &code : codes) {
            Register &currentData = Data[ActiveData];

            // If we must exit
            if (ExitCodeImmediately)
                return true;

            // If we have a full terminator
            if (code.Type == 0xD2 && code.Right == 0) {
                // If we have blocks waiting to be ended
                if (waitForExitCode) {
                    conditionCount = 0;
                    waitForExitCode = false;
                }

                // If we have loops waiting to be launched
                if (waitForEndLoop) {
                    loopCount = 0;
                    waitForEndLoop = false;

                    // Execute loops
                    while (loopIteration-- && !_Execute(loopCodes));

                    // Clear codes
                    loopCodes.clear();
                }

                // Clear registers and continue
                Offset[ActiveOffset] = 0;
                currentData.Clear();
                continue;
            }

            // If we're waiting for the end of a block
            if (waitForExitCode) {
                if (code.Type == 0xD0 && code.Right == 0) {
                    --conditionCount;

                    if (conditionCount == 0)
                        waitForExitCode = false;
                }

                // Check for embricked conditions
                if (code.Type >= 0x30 && code.Type <= 0xA0)
                    ++conditionCount;

                continue;
            }

            // If we're waiting for an execute loop code
            if (waitForEndLoop) {
                if (code.Type == 0xD1) {
                    loopCount--;

                    if (loopCount == 0) {
                        waitForEndLoop = false;
                        // Execute loop
                        while (loopIteration-- && !_Execute(loopCodes));

                        // Clear codes
                        loopCodes.clear();
                        continue;
                    }
                }

                loopCount += (code.Type >= 0xC0 && code.Type <= 0xC2);
                loopCodes.push_back(code);
                continue;
            }

            // Execute code
            switch (code.Type) {
                case 0x00:
                    ExitCodeImmediately = !Write32(code.Left + Offset[ActiveOffset], code.Right);
                    break;
                case 0x10:
                    ExitCodeImmediately = !Write16(code.Left + Offset[ActiveOffset], code.Right);
                    break;
                case 0x20:
                    ExitCodeImmediately = !Write8(code.Left + Offset[ActiveOffset], code.Right);
                    break;

                case 0x30: {
                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read32(code.Left + Offset[ActiveOffset], value)))) {
                        Cond32(>, std::isgreater);
                    }

                    conditionCount++;
                    waitForExitCode = true;
                    break;
                }

                case 0x40: {
                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read32(code.Left + Offset[ActiveOffset], value)))) {
                        Cond32(<, std::isless);
                    }

                    conditionCount++;
                    waitForExitCode = true;
                    break;
                }

                case 0x50: {
                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read32(code.Left + Offset[ActiveOffset], value)))) {
                        Cond32(==, FP_EQ);
                    }

                    ++conditionCount;
                    waitForExitCode = true;
                    break;
                }

                case 0x60: {
                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read32(code.Left + Offset[ActiveOffset], value)))) {
                        Cond32(!=, !FP_EQ);
                    }

                    conditionCount++;
                    waitForExitCode = true;
                    break;
                }

                case 0x70: {
                    mask = ~(code.Right >> 16);

                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read16(code.Left + Offset[ActiveOffset], value16)))) {
                        value16 &= mask;
                        Cond16(>);
                    }

                    conditionCount++;
                    waitForExitCode = true;
                    break;
                }

                case 0x80: {
                    mask = ~(code.Right >> 16);

                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read16(code.Left + Offset[ActiveOffset], value16)))) {
                        value16 &= mask;
                        Cond16(<);
                    }

                    conditionCount++;
                    waitForExitCode = true;
                    break;
                }

                case 0x90: {
                    mask = ~(code.Right >> 16);

                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read16(code.Left + Offset[ActiveOffset], value16)))) {
                        value16 &= mask;
                        Cond16(==);
                    }

                    conditionCount++;
                    waitForExitCode = true;
                    break;
                }

                case 0xA0: {
                    mask = ~(code.Right >> 16);

                    if (conditionalMode == CondMode::ImmAgainstData || !((ExitCodeImmediately = !Read16(code.Left + Offset[ActiveOffset], value16)))) {
                        value16 &= mask;
                        Cond16(!=);
                    }

                    conditionCount++;
                    waitForExitCode = true;
                    break;
                }

                case 0xB0:
                    ExitCodeImmediately = !Read32(code.Left + Offset[ActiveOffset], Offset[ActiveOffset]);
                    break;

                case 0xD3: {
                    u32 target = code.Left & 1;
                    Offset[target] = code.Right;
                    break;
                }

                case 0xDC:
                    Offset[ActiveOffset] += code.Right;
                    break;
                case 0xC0:
                    loopIteration = code.Right;
                    loopCount++;
                    waitForEndLoop = true;
                    break;
                case 0xC1:
                    loopIteration = Data[0].value;
                    loopCount++;
                    waitForEndLoop = true;
                    break;
                case 0xC2:
                    loopIteration = Data[1].value;
                    loopCount++;
                    waitForEndLoop = true;
                    break;

                case 0xD0: {
                    if (code.Right == 1)
                        return true;

                    break;
                }

                case 0xD2: {
                    if (code.Right) {
                        ExitCodeImmediately = true;
                        return true;
                    }

                    conditionCount = 0;
                    Offset[ActiveOffset] = 0;
                    currentData.Clear();
                    loopCodes.clear();
                    break;
                }

                case 0xD4: {
                    value = code.Right;
                    u32 mode = code.Left & 3;
                    Register &dest = mode == 0 ? currentData : Data[mode -1];

                    if (mode) {
                        Register &src = Data[!(mode - 1)];

                        if (dest.isVFP)
                            vfpval += src.vfp;

                        else value += src.value;
                    }

                    if (dest.isVFP)
                        dest.vfp += vfpval;

                    else dest.value += value;

                    break;
                }

                case 0xD5: {
                    if (!code.Left)
                        currentData.value = code.Right;

                    else Data[(code.Left - 1) & 1].value = code.Right;

                    break;
                }

                case 0xD6: {
                    u32 v = code.Left == 0 ? currentData.value : Data[(code.Left - 1) & 1].value;
                    ExitCodeImmediately = !Write32(code.Right + Offset[ActiveOffset], v);
                    Offset[ActiveOffset] += 4;
                    break;
                }

                case 0xD7: {
                    value16 = code.Left == 0 ? currentData.value : Data[(code.Left - 1) & 1].value;
                    ExitCodeImmediately = !Write16(code.Right + Offset[ActiveOffset], value16);
                    Offset[ActiveOffset] += 2;
                    break;
                }

                case 0xD8: {
                    u8 value8 = code.Left == 0 ? currentData.value : Data[(code.Left - 1) & 1].value;
                    ExitCodeImmediately = !Write8(code.Right + Offset[ActiveOffset], value8);
                    Offset[ActiveOffset]++;
                    break;
                }

                case 0xD9: {
                    Register &data = code.Left == 0 ? currentData : Data[(code.Left - 1) & 1];
                    ExitCodeImmediately = !Read32(code.Right + Offset[ActiveOffset], data.value);
                    break;
                }

                case 0xDA: {
                    Register &data = code.Left == 0 ? currentData : Data[(code.Left - 1) & 1];
                    ExitCodeImmediately = !Read16(code.Right + Offset[ActiveOffset], value16);
                    data.value = value16;
                    break;
                }

                case 0xDB: {
                    u8 value8 = 0;
                    Register &data = code.Left == 0 ? currentData : Data[(code.Left - 1) & 1];
                    ExitCodeImmediately = !Read8(code.Right + Offset[ActiveOffset], value8);
                    data.value = value8;
                    break;
                }

                case 0xDD: {
                    if (!Controller::IsKeysDown(code.Right)) {
                        waitForExitCode = true;
                        conditionCount++;
                    }

                    break;
                }

                case 0xDE: {
                    #define IsInRange(val, min, max) (min <= val && val <= max)
                    UIntVector  touchPos = Touch::GetPosition();
                    u32 min = code.Right >> 16;
                    u32 max = code.Right & 0xFFFF;
                    bool isInRange = code.Left == 0 ? IsInRange(touchPos.x, min, max) : IsInRange(touchPos.y, min, max);

                    if (!Touch::IsDown() || !isInRange) {
                        waitForExitCode = true;
                        conditionCount++;
                    }

                    break;
                }

                case 0xDF: {
                    u16 operation = code.Right >> 16;
                    u16 parameter = code.Right & 0xFFFF;

                    if (code.Left == 0x00FFFFFE) {
                        currentData.isVFP = code.Right & 1;

                        if (code.Right & 0x10) {
                            if (currentData.isVFP) {
                                const float fvalue = static_cast<float>(currentData.value);
                                currentData.vfp = fvalue;
                            }

                            else {
                                const u32 ivalue = static_cast<u32>(currentData.vfp);
                                currentData.value = ivalue;
                            }
                        }

                        break;
                    }

                    if (code.Left == 0x00FFFFFF) {
                        conditionalMode = static_cast<CondMode>(parameter & 7);
                        break;
                    }

                    switch (operation) {
                        case 0x0: {
                            if (code.Left == 0)
                                ActiveOffset = parameter;

                            else if (code.Left == 1)
                                ActiveData = parameter;

                            else if (code.Left == 2)
                                ActiveStorage = parameter;

                            break;
                        }

                        case 0x1: {
                            if (code.Left == 0)
                                Offset[!parameter] = Offset[parameter];

                            else if (code.Left == 1)
                                Data[!parameter].value = Data[parameter].value;

                            else if (code.Left == 2)
                                Data[parameter].value = Storage[parameter];

                            break;
                        }

                        case 0x2: {
                            if (code.Left == 0)
                                Data[parameter].value = Offset[parameter];

                            else if (code.Left == 1)
                                Offset[parameter] = Data[parameter].value;

                            else if (code.Left == 2)
                                Storage[parameter] = Data[parameter].value;

                            break;
                        }

                        default: break;
                    }

                    break;
                }

                case 0xE0: {
                    u8 *data = (u8*)code.Data.data();

                    if (data == nullptr || code.Data.size() == 0 || !code.Right || code.Right > code.Data.size() * 4)
                        continue;

                    ExitCodeImmediately = !Memcpy(code.Left + Offset[ActiveOffset], data, code.Right);
                    break;
                }

                case 0xF0: {
                    switch (code.Left) {
                        case 1: {
                            ToggleFloat = code.Right & 1;
                            break;
                        }

                        case 0xF00000: {
                            u32 *args[] = {&Offset[0], &Offset[1], &Data[0].value, &Data[1].value, &Storage[0], &Storage[1], (u32*)0x01E81000, arStack};
                            u32 *data = (u32*)code.Data.data();

                            if (data == nullptr)
                                break;

                            // Execute routine
                            AR__ExecuteRoutine(args, data);
                            break;
                        }

                        default: break;
                    }

                    break;
                }

                case 0xF1: {
                    if (!ToggleFloat) {
                        if (Read32(code.Left + Offset[ActiveOffset], value))
                            ExitCodeImmediately = !Write32(code.Left + Offset[ActiveOffset], value + code.Right);
                    }

                    else {
                        value = code.Right;
                        float val = vfpval;

                        if (Read32(code.Left + Offset[ActiveOffset], value)) {
                            vfpval += val;
                            ExitCodeImmediately = !Write32(code.Left + Offset[ActiveOffset], value);
                        }
                    }

                    break;
                }

                case 0xF2: {
                    if (!ToggleFloat) {
                        if (Read32(code.Left + Offset[ActiveOffset], value))
                            ExitCodeImmediately = !Write32(code.Left + Offset[ActiveOffset], value * code.Right);
                    }

                    else {
                        value = code.Right;
                        float val = vfpval;

                        if (Read32(code.Left + Offset[ActiveOffset], value)) {
                            vfpval *= val;
                            ExitCodeImmediately = !Write32(code.Left + Offset[ActiveOffset], value);
                        }
                    }

                    break;
                }

                case 0xF3: {
                    if (!ToggleFloat && code.Right) {
                        if (Read32(code.Left + Offset[ActiveOffset], value))
                            ExitCodeImmediately = !Write32(code.Left + Offset[ActiveOffset], value / code.Right);
                    }

                    else if (code.Right) {
                        value = code.Right;
                        float val = vfpval;

                        if (Read32(code.Left + Offset[ActiveOffset], value)) {
                            vfpval += val;
                            ExitCodeImmediately = !Write32(code.Left + Offset[ActiveOffset], value);
                        }
                    }

                    break;
                }

                case 0xF4: {
                    value = code.Right;

                    if (currentData.isVFP)
                        currentData.vfp *= vfpval;

                    else currentData.value *= value;

                    break;
                }

                case 0xF5: {
                    value = code.Right;

                    if (code.Right != 0) {
                        if (currentData.isVFP)
                            currentData.vfp /= vfpval;

                        else currentData.value /= value;
                    }

                    break;
                }

                case 0xF6:
                    currentData.value &= code.Right;
                    break;
                case 0xF7:
                    currentData.value |= code.Right;
                    break;
                case 0xF8:
                    currentData.value ^= code.Right;
                    break;
                case 0xF9:
                    currentData.value = ~currentData.value;
                    break;
                case 0xFA:
                    currentData.value <<= code.Right;
                    break;
                case 0xFB:
                    currentData.value >>= code.Right;
                    break;

                case 0xFC: {
                    if (Offset[0] && Offset[1])
                        ExitCodeImmediately = !Process::CopyMemory((void*)Offset[0], (void*)Offset[1], code.Right);

                    break;
                }

                case 0xFD: {
                    HookVector *hooks = g_context->hooks;

                    // Check for disable mode (FD1)
                    if (code.Left >> 20 == 1) {
                        if (hooks != nullptr) {
                            int index = 0;

                            for (Hook &hook : *hooks) {
                                if (hook.GetContext().targetAddress == code.Right) {
                                    hook.Disable();
                                    hooks->erase(hooks->begin() + index);
                                    break;
                                }

                                ++index;
                            }
                        }

                        break;
                    }

                    // Add a new hook
                    if (hooks == nullptr)
                        g_context->hooks = hooks = new HookVector;

                    Hook hook;
                    u32 flags = (code.Left & 0x10) != 0x10 ? USE_LR_TO_RETURN : 0;
                    flags |= (code.Left & 1) != 1 ? EXECUTE_OI_BEFORE_CB : 0;
                    hook.Initialize(Offset[ActiveOffset], (u32)code.Data.data());
                    hook.SetFlags(flags);

                    if (hook.Enable() == HookResult::Success)
                        hooks->push_back(hook);

                    break;
                }

                case 0xFE: {
                    const std::vector<u32> &pattern = code.Data;
                    u32 regionSize = 0;
                    u32 start = Offset[ActiveOffset];
                    PageInfo pInfo = {0};
                    MemInfo mInfo = {0};

                    if (!pattern.empty() && code.Right && Process::CheckRegion(start, regionSize)) {
                        u32 address = 0;

                        if (R_SUCCEEDED(svcQueryMemory(&mInfo, &pInfo, start))) {
                            u32 size = std::min((u32)code.Right, mInfo.size - (start - mInfo.base_addr));
                            address = Utils::Search<u32>(start, size, pattern);
                        }

                        // If pattern isn't found
                        if (!address) {
                            waitForExitCode = true;
                            conditionCount++;
                            break;
                        }

                        // Pattern found, update offset
                        Offset[ActiveOffset] = address;
                    }

                    break;
                }

                case 0xFF: {
                    u32 min = code.Left;
                    u32 max = code.Right;

                    if (!currentData.isVFP)
                        currentData.value = Utils::Random(min, max);

                    else currentData.vfp = (float)Utils::Random(min, max);

                    break;
                }

                default: break;
            }
        }

        return false;
    }
}