#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    namespace CRO {
        bool Toggle(u32 address, bool enabled) {
            u32 process;
            Handle handle;
            MemInfo mem;
            PageInfo page;
            bool out = false;

            if (R_SUCCEEDED(svcGetProcessId(&process, CUR_PROCESS_HANDLE))) {
                if (R_SUCCEEDED(svcOpenProcess(&handle, process))) {
                    if (R_SUCCEEDED(svcQueryMemory(&mem, &page, address))) {
                        if (enabled) {
                            if (!System::IsCitra()) {
                                if (mem.perm < 2)
                                    goto apply;

                                else goto skip;
                            }

                            else {
                                apply:
                                if (R_SUCCEEDED(svcControlProcessMemory(handle, mem.base_addr, 0, mem.size, MemOp(MEMOP_PROT), MemPerm(MEMPERM_READ | MEMPERM_EXECUTE | MEMPERM_WRITE))))
                                    out = true;
                            }
                        }

                        else {
                            if (!System::IsCitra()) {
                                if (mem.perm > 2)
                                    goto revert;

                                else goto skip;
                            }

                            else {
                                revert:
                                if (R_SUCCEEDED(svcControlProcessMemory(handle, mem.base_addr, 0, mem.size, MemOp(MEMOP_PROT), MEMPERM_READ)))
                                    out = true;
                            }
                        }
                    }

                    skip:
                    svcCloseHandle(handle);
                }
            }

            return out;
        }

        u32 Read32(u32 address) {
            u32 value;

            if (Toggle(address, true)) {
                value = *(u32*)address;
                Toggle(address, false);
                return value;
            }

            return 0;
        }

        vector<u32> Read32(u32 address, int length) {
            vector<u32> vals(length);

            if (Toggle(address, true)) {
                for (int i = 0; i < length; i++) {
                    vals[i] = *(u32*)address;
                    address += 0x4;
                }

                Toggle(address, false);
            }

            return vals;
        }

        bool Write32(u32 address, u32 value) {
            if (Toggle(address, true)) {
                *(u32*)address = value;
                Toggle(address, false);
                return true;
            }

            return false;
        }

        bool Write32(u32 address, u32 value, u32 &original) {
            if (Toggle(address, true)) {
                original = *(u32*)address;
                *(u32*)address = value;
                Toggle(address, false);
                return true;
            }

            return false;
        }

        bool Write32(u32 address, vector<u32> value) {
            if (Toggle(address, true)) {
                for (unsigned int i = 0; i < value.size(); i++)
                    *(u32*)(address + i * 4) = value[i];

                Toggle(address, false);
                return true;
            }

            return false;
        }
    }
}