#include <windows.h>
#include "../inc/patch.h"
#include "../inc/ini.h"


void __declspec(dllexport) w2p_init()
{
    BYTE paletteIndex = ini_get_int("MMblack", "PaletteIndex", 253, ".\\plugin\\MMblack.ini");

    /* Changes the mini map color for the black player */
    patch_setbyte((char *)0x004A48B1, paletteIndex); /* Pink */
}
