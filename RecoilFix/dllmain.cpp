// dllmain.cpp : Defines the entry point for the DLL application.
#include "RecoilFix.h"

static unsigned int* off_EC4DA8 = (unsigned int*)0xEC4DA8;

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        ApplyRecoilFix();
        //Patch::Nop(0xBA01F9,0x5);
        //Patch::SetUInt(0x150C4B0, off_EC4DA8[1]);
    }

    //{
    //    AllocConsole();
    //    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    //    printf("%x", GameVersion::Get());
    //    Sleep(1000000);
    //}
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}