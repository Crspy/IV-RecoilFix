#pragma once
#include "injector.hpp"

class Patch {
private:
    static unsigned int base_address;

public:
    inline static unsigned int GetGlobalAddress(unsigned int address) {
    return base_address - 0x400000 + address;
    }
    inline static void Nop(int address, size_t size, bool vp = true) {
        injector::MakeNOP(GetGlobalAddress(address), size, vp);
    }

    inline static void RedirectCall(int address, void *func, bool vp = true) {
        injector::MakeCALL(GetGlobalAddress(address), func, vp);
    }

    inline static void RedirectJump(int address, void *func, bool vp = true) {
        injector::MakeJMP(GetGlobalAddress(address), func, vp);
    }

    inline static void SetChar(int address, char value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static void SetUChar(int address, unsigned char value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static void SetShort(int address, short value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static void SetUShort(int address, unsigned short value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static void SetInt(int address, int value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static void SetUInt(int address, unsigned int value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static void SetFloat(int address, float value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static void SetPointer(int address, void *value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    inline static char GetChar(int address, bool vp = true) {
        return injector::ReadMemory<char>(GetGlobalAddress(address), vp);
    }

    inline static unsigned char GetUChar(int address, bool vp = true) {
        return injector::ReadMemory<unsigned char>(GetGlobalAddress(address), vp);
    }

    inline static short GetShort(int address, bool vp = true) {
        return injector::ReadMemory<short>(GetGlobalAddress(address), vp);
    }

    inline static unsigned short GetUShort(int address, bool vp = true) {
        return injector::ReadMemory<unsigned short>(GetGlobalAddress(address), vp);
    }

    inline static int GetInt(int address, bool vp = true) {
        return injector::ReadMemory<int>(GetGlobalAddress(address), vp);
    }

    inline static unsigned int GetUInt(int address, bool vp = true) {
        return injector::ReadMemory<unsigned int>(GetGlobalAddress(address), vp);
    }

    inline static float GetFloat(int address, bool vp = true) {
        return injector::ReadMemory<float>(GetGlobalAddress(address), vp);
    }

    inline static void *GetPointer(int address, bool vp = true) {
        return injector::ReadMemory<void *>(GetGlobalAddress(address), vp);
    }

    template <typename T>
    static void Set(int address, T value, bool vp = true) {
        injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    template <typename T>
    static T Get(int address, bool vp = true) {
        return injector::ReadMemory<T>(GetGlobalAddress(address), vp);
    }

    template <typename T>
    static T TranslateCallOffset(int address) {
        if (GetUChar(address) == 0xE8) {
            auto offset = GetInt(address + 1);
            offset += (GetGlobalAddress(address) + 5);
            return reinterpret_cast<T>(offset);
        }
        return nullptr;
    }

    template <typename T>
    static T TranslateJumpOffset(int address) {
        if (GetUChar(address) == 0xE9) {
            auto offset = GetInt(address + 1);
            offset += (GetGlobalAddress(address) + 5);
            return reinterpret_cast<T>(offset);
        }
        return nullptr;
    }

    inline static void ReplaceFunction(int address, void *func, bool vp = true) {
        RedirectJump(address, func, vp);
    }

    inline static void ReplaceFunctionCall(int address, void *func, bool vp = true) {
        RedirectCall(address, func, vp);
    }
};

enum eGameVersion
{
    UNKNOWN_VERSION,
    IV_1_0_4_0,
    IV_1_0_7_0,
    IV_1_0_8_0,
    EFLC_1_1_2_0,
    EFLC_1_1_3_0
};

class GameVersion
{
    static eGameVersion m_nGameVersion;

public:
    static eGameVersion Get()
    {
        return m_nGameVersion;
    }

};