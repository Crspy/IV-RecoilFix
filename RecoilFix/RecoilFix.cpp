#include "RecoilFix.h"

void ApplyRecoilFix()
{
    auto _pattern = hook::pattern("85 C0 74 09 80 B8 8D 32 00 00  00 75 0D E8");
    if (!_pattern.empty())
    {
        auto address = _pattern.get(0).get<unsigned char>(0);
        /*AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        printf("%x", (address + 0x400000 - (unsigned int)GetModuleHandleA(NULL)));
        */
        Patch::Set<unsigned char, true>((unsigned int)address, 0xEBu);
        Patch::Set<unsigned char, true>((unsigned int)address + 1, 40);
    }
    else if (GameVersion::Get() == eGameVersion::IV_1_0_4_0)
    {
        Patch::Set<unsigned char, false>(0xA9C760, 0xEBu);
        Patch::Set<unsigned char, false>(0xA9C760 + 1, 45);
    }
    else if (GameVersion::Get() == eGameVersion::IV_1_0_0_4)
    {
        Patch::Set<unsigned char, false>(0x98CB6E, 0xEBu);
        Patch::Set<unsigned char, false>(0x98CB6E + 1, 40);
    }
    else
    {
        MessageBoxA(NULL, "RecoilFix : Game version unknown", "Error", MB_OK);
    }
    //switch(GameVersion::Get())
    //{
    //    case eGameVersion::IV_1_0_4_0:
    //        Patch::SetUChar(0xA9C760, 0xEBu);// after "85 C0 74 09 80 B8 ED 29  00 00 00 75 12 E8 BE 86"
    //        Patch::SetUChar(0xA9C760 + 1, 45);
    //        break;
    //    case eGameVersion::IV_1_0_7_0:  // before "BF A8 03 00 00 00 74 04 B3 01 EB 02 32 DB"
    //        Patch::SetUChar(0x97978E, 0xEBu);// after "85 C0 74 09 80 B8 8D 32 00 00  00 75 0D E8 F0 97 AE"
    //        Patch::SetUChar(0x97978E + 1, 40);
    //        break;
    //    case eGameVersion::IV_1_0_8_0:
    //        Patch::SetUChar(0x9D1D7E, 0xEBu);// after "85 C0 74 09 80 B8 8D 32 00 00  00 75 0D E8 80"
    //        Patch::SetUChar(0x9D1D7E + 1, 40);
    //        break;
    //    case eGameVersion::EFLC_1_1_2_0:
    //        Patch::SetUChar(0x9A053E, 0xEBu);
    //        Patch::SetUChar(0x9A053E + 1, 40);
    //        break;
    //    case eGameVersion::EFLC_1_1_3_0:
    //        Patch::SetUChar(0x99C78E, 0xEBu);
    //        Patch::SetUChar(0x99C78E + 1, 40);
    //        break;
    //    case eGameVersion::UNKNOWN_VERSION:
    //        MessageBoxA(NULL, "RecoilFix : Game version unknown", "Error", MB_OK);
    //        break;
    //}
}


