#include <windows.h>
#include "../inc/patch.h"
#include "../inc/ini.h"


void __declspec(dllexport) w2p_init()
{
    /* Scroll 1 cell at a time rather than 2 cells */
    PATCH_SET((char *)0x0043DEE9 + 1, "\x01");
    PATCH_SET((char *)0x0043DEF4 + 1, "\x01");
    PATCH_SET((char *)0x0043DF03 + 1, "\x01");
    PATCH_SET((char *)0x0043DF0E + 1, "\x01");

    /* Reduce delay between each "Scroll Tick" from 20ms to 10ms */
    PATCH_SET((char *)0x0043DE8E + 2, "\x0A"); /* Mouse scroll */
    PATCH_SET((char *)0x0043DC90 + 2, "\x0A"); /* Keyboard scroll */
}
