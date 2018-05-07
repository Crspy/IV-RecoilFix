#pragma once
#include "injector.hpp"

class Patch {
private:
    static unsigned int m_nBaseAddress;

public:
    inline static unsigned int GetGlobalAddress(unsigned int address) {
    return m_nBaseAddress - 0x400000 + address;
    }

    template<bool IsGlobalAddress>
    inline static void Nop(int address, size_t size, bool vp = true) {
        if (IsGlobalAddress)
            injector::MakeNOP(address, size, vp);
        else
            injector::MakeNOP(GetGlobalAddress(address), size, vp);
    }

    template<bool IsGlobalAddress>
    inline static void RedirectCall(int address, void *func, bool vp = true) {
        if (IsGlobalAddress)
            injector::MakeCALL(address, func, vp);
        else
            injector::MakeCALL(GetGlobalAddress(address), func, vp);
    }

    template<bool IsGlobalAddress>
    inline static void RedirectJump(int address, void *func, bool vp = true) {
        if (IsGlobalAddress)
            injector::MakeJMP(address, func, vp);
        else
            injector::MakeJMP(GetGlobalAddress(address), func, vp);
    }

    template<bool IsGlobalAddress>
    inline static void SetPointer(int address, void *value, bool vp = true) {
        if (IsGlobalAddress)
            injector::WriteMemory(address, value, vp);
        else
            injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    template<bool IsGlobalAddress>
    inline static void *GetPointer(int address, bool vp = true) {
        if (IsGlobalAddress)
            return injector::ReadMemory<void *>(address, vp);
        else
            return injector::ReadMemory<void *>(GetGlobalAddress(address), vp);
    }

    template <typename T, bool IsGlobalAddress>
    static void Set(int address, T value, bool vp = true) {
        if (IsGlobalAddress)
            injector::WriteMemory(address, value, vp);
        else
            injector::WriteMemory(GetGlobalAddress(address), value, vp);
    }

    template <typename T, bool IsGlobalAddress>
    static T Get(int address, bool vp = true) {
        if (IsGlobalAddress)
            return injector::ReadMemory<T>(address, vp);
        else
            return injector::ReadMemory<T>(GetGlobalAddress(address), vp);
    }

    template <typename T, bool IsGlobalAddress>
    static T TranslateCallOffset(int address) {
        if (GetUChar(address) == 0xE8) {
            auto offset = GetInt(address + 1);
            if (IsGlobalAddress)
                offset += (address + 5);
            else
                offset += (GetGlobalAddress(address) + 5);
            return reinterpret_cast<T>(offset);
        }
        return nullptr;
    }

    template <typename T, bool IsGlobalAddress>
    static T TranslateJumpOffset(int address) {
        if (GetUChar(address) == 0xE9) {
            auto offset = GetInt(address + 1);
            if (IsGlobalAddress)
                offset += (address + 5);
            else
                offset += (GetGlobalAddress(address) + 5);
            return reinterpret_cast<T>(offset);
        }
        return nullptr;
    }

    template<bool IsGlobalAddress>
    inline static void ReplaceFunction(int address, void *func, bool vp = true) {
        if (IsGlobalAddress)
            RedirectJump<true>(address, func, vp);
        else
            RedirectJump<false>(address, func, vp);
    }

    template<bool IsGlobalAddress>
    inline static void ReplaceFunctionCall(int address, void *func, bool vp = true) {
        if (IsGlobalAddress)
            RedirectCall<true>(address, func, vp);
        else
            RedirectCall<false>(address, func, vp);
    }
};

enum eGameVersion
{
    UNKNOWN_VERSION,
    IV_1_0_4_0,
    IV_1_0_0_4,
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