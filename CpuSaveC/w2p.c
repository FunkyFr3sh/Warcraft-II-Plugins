#include <windows.h>
#include "../inc/patch.h"


BOOL WINAPI fake_PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    static int count;
    
    BOOL result = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
    
    if (!result && ++count == 200)
    {
        Sleep(15);
        count = 0;
    }
    
    return result;
}

void w2p_init()
{
    HMODULE storm_dll = GetModuleHandleA("storm.dll");
    
    if (storm_dll && memcmp((char *)storm_dll + 0x00010000, "\xC2\x8B\x54\x24\x2C\xD1\xF8\x8D", 8) == 0)
    {
        PATCH_SET((char*)storm_dll + 0x0001F5DB, "\x90\xBD");
        patch_setdword((DWORD*)((DWORD)storm_dll + 0x0001F5DB + 2), (DWORD)fake_PeekMessageA);
        
        patch_call_nop((char*)storm_dll + 0x00010DC3, (char*)fake_PeekMessageA);
    }
}
