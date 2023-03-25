#include <windows.h>
#include "patch.h"

PROC g_proc_00420E00;

void set_low_lat()
{
    /* Original function call that was replaced by the patch */
    ((void (*)(void))g_proc_00420E00)();
    
    /* Set latency to low (0) */
    ((void (*)(int))0x00477CC0)(0);
}

void __declspec(dllexport) w2p_init()
{
    /* Automatically set low latency on game start to enable the WarLat patch */
    g_proc_00420E00 = patch_call((void *)0x00420E00, (void *)set_low_lat);
    
    /* Original WarLat patch copied from war2loader */
    PATCH_SET((void *)0x0047862E, "\x90\x90\x49\x90\x90\x90\x90");
}
