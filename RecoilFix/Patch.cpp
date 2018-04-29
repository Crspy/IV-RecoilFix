#include "Patch.h"

unsigned int Patch::base_address = []() {
    return reinterpret_cast<unsigned int>(GetModuleHandleA(NULL));
}();

eGameVersion GameVersion::m_nGameVersion = []() {
    switch (Patch::GetUInt(0x401230 + 2))
    {
    case 0xC200050D:
        return eGameVersion::IV_1_0_4_0;
    case 0xC2001A99:
        return eGameVersion::IV_1_0_7_0;
    case 0xC068006A:
        return eGameVersion::IV_1_0_8_0;
    case 0x3068006A:
        return eGameVersion::EFLC_1_1_2_0;
    case 0xC2001A6B:
        return eGameVersion::EFLC_1_1_3_0;
    default:
        return eGameVersion::UNKNOWN_VERSION;
    }
}();