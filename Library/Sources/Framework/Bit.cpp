#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    namespace Bit {
        bool Read8(u32 address, u8 &value, bool rightSide) {
            // Checks if address is valid or not
            if (!Process::CheckAddress(address))
                return false;

            // Right side of the byte
            if (rightSide) {
                value = *(u8*)(address) & 0xF;
                return true;
            }

            // Left side of the byte
            value = (*(u8*)(address) >> 4) & 0xF;
            return true;
        }

        bool Read8(vector<u32> address, vector<u32> &value, vector<bool> rightSide) {
            bool out = false;

            // Checks if address is valid or not
            for (unsigned int i = 0; i < address.size(); i++) {
                if (!Process::CheckAddress(address[i]))
                    out=  false;

                // Right side of the byte
                if (rightSide[i]) {
                    value[i] = *(u8*)(address[i]) & 0xF;
                    out = true;
                }

                // Left side of the byte
                value[i] = (*(u8*)(address[i]) >> 4) & 0xF;
            }

            return out;
        }

        bool Write8(u32 address, u8 value, bool rightSide) {
            // Checks if address is valid or not
            if (!Process::CheckAddress(address))
                return false;

            // Clears 4-bit first then write 4-bit to the right side of the byte
            if (rightSide) {
                *(u8*)address &= ~0xF;
                *(u8*)address |= (value & 0xF);
                return true;
            }

            // Clears 4-bit first then write 4-bit to the left side of the byte
            *(u8*)address &= ~(0xF << 4);
            *(u8*)address |= ((value & 0xF) << 4);
            return true;
        }

        bool Write8(vector<u32> address, vector<u8> value, vector<bool> rightSide) {
            bool out = false;

            for (unsigned int i = 0; i < address.size(); i++) {
                // Checks if address is valid or not
                if (!Process::CheckAddress(address[i]))
                    out = false;

                // Clears 4-bit first then write 4-bit to the right side of the byte
                if (rightSide[i]) {
                    *(u8*)address[i] &= ~0xF;
                    *(u8*)address[i] |= (value[i] & 0xF);
                    out = true;
                }

                // Clears 4-bit first then write 4-bit to the left side of the byte
                *(u8*)address[i] &= ~(0xF << 4);
                *(u8*)address[i] |= ((value[i] & 0xF) << 4);
            }

            return out;
        }
    }
}