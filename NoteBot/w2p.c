#include <windows.h>
#include "../inc/patch.h"

PROC g_proc_00473A63;

const char HOLEPUNCH_MESSAGE[] = 
    "<From: note> HolePunch Enabled: If someone can't join, tell them to install the new War2Combat";
    
const char NOTE_MESSAGE[] = 
    "<From: note> Your port ";

void check_notebot_message(int a, const char *message)
{
    if (message && strncmp(message, NOTE_MESSAGE, strlen(NOTE_MESSAGE)) == 0)
    {
        if (GetFileAttributes(".\\wsock32.dll") != INVALID_FILE_ATTRIBUTES)
        {
            ((void (*)(int, const char *))g_proc_00473A63)(a, HOLEPUNCH_MESSAGE);
            return;
        }
    }

    ((void (*)(int, const char *))g_proc_00473A63)(a, message);
}

void __declspec(dllexport) w2p_init()
{
    g_proc_00473A63 = patch_call((void *)0x00473A63, (void *)check_notebot_message);
}
