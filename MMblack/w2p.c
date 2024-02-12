#include <windows.h>
#include "../inc/patch.h"
#include "../inc/ini.h"


#define W2_PALETTE ((unsigned int*)0x004ae844)

PROC g_proc_0041FBEF;

void init_colors(int a)
{
    if (W2_PALETTE[228] == 0x003C2828) /* make sure we're using the original palette (skip if black2pink patch detected) */
    {
        BYTE paletteIndex = ini_get_int("MMblack", "PaletteIndex", 253, ".\\plugin\\MMblack.ini"); /* Pink (253) */
        patch_setbyte((char *)0x004A48B1, paletteIndex); /* black player index */
    }
    
    ((void (*)(int))g_proc_0041FBEF)(a);
}

void __declspec(dllexport) w2p_init()
{
    g_proc_0041FBEF = patch_call((void *)0x0041FBEF, (void *)init_colors);
}
