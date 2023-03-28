#include <windows.h>
#include "../inc/patch.h"
#include "../inc/ini.h"


void __declspec(dllexport) w2p_init()
{
    BYTE delay = ini_get_int("Scroll", "Delay", 10, ".\\plugin\\SmoothScroll.ini");
    BYTE amount = ini_get_int("Scroll", "Amount", 1, ".\\plugin\\SmoothScroll.ini");

    /* Scroll x cells at a time rather than the default 2 cells */
    patch_setbyte((char *)0x0043DEE9 + 1, amount);
    patch_setbyte((char *)0x0043DEF4 + 1, amount);
    patch_setbyte((char *)0x0043DF03 + 1, amount);
    patch_setbyte((char *)0x0043DF0E + 1, amount);

    /* Reduce delay between each "Scroll Tick" from 20ms to x ms */
    patch_setbyte((char *)0x0043DE8E + 2, delay); /* Mouse scroll */
    patch_setbyte((char *)0x0043DC90 + 2, delay); /* Keyboard scroll */
}
