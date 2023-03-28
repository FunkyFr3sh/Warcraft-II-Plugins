#include <windows.h>
#include <stdio.h>
#include "../inc/patch.h"


#define W2_HWND *((HWND*)0x004CE7B8)
#define W2_MY_PLAYER_ID *((int*)0x004A70AC)

PROC g_proc_00475A0F, g_proc_004781CA, g_proc_00478EDD, g_proc_00475A7A, 
     g_proc_00473A63, g_proc_00420F36, g_proc_0046D912;

const char SOUNDS_PATH[] = ".\\plugin\\Sounds\\";

void play_sound(char *sound)
{
    char path[MAX_PATH] = {0};
    _snprintf(path, sizeof(path), "%s%s.wav", SOUNDS_PATH, sound);

    if (GetFileAttributes(path) == INVALID_FILE_ATTRIBUTES)
    {
        if (GetForegroundWindow() != W2_HWND)
            _snprintf(path, sizeof(path), "%s%sNoFocus.wav", SOUNDS_PATH, sound);
        else
            _snprintf(path, sizeof(path), "%s%sFocus.wav", SOUNDS_PATH, sound);
    }

    PlaySoundA(path, NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC);
}

int join_game(int a)
{
    play_sound("JoinGame");
    return ((int (*)(int))g_proc_00475A0F)(a);
}

void start_game(int a, int b)
{
    play_sound("StartGame");
    ((void (*)(int, int))g_proc_004781CA)(a, b);
}

void leave_game(int a, int b)
{
    play_sound("LeaveGame");
    ((void (*)(int, int))g_proc_00478EDD)(a, b);
}

int message(int player_id)
{
    if (player_id != W2_MY_PLAYER_ID)
        play_sound("Message");
    
    return ((int (*)(int))g_proc_00475A7A)(player_id);
}

void private_message(int a, int b)
{
    play_sound("PrivateMessage");
    ((void (*)(int, int))g_proc_00473A63)(a, b);
}

void game_end(int a)
{
    play_sound("GameEnd");
    ((void (*)(int))g_proc_00420F36)(a);
}

void kicked(int a)
{
    play_sound("Kicked");
    ((void (*)(int))g_proc_0046D912)(a);
}

void __declspec(dllexport) w2p_init()
{
    g_proc_00475A0F = patch_call((void *)0x00475A0F, (void *)join_game);
    g_proc_004781CA = patch_call((void *)0x004781CA, (void *)start_game);
    g_proc_00478EDD = patch_call((void *)0x00478EDD, (void *)leave_game);
    g_proc_00475A7A = patch_call((void *)0x00475A7A, (void *)message);
    g_proc_00473A63 = patch_call((void *)0x00473A63, (void *)private_message);
    g_proc_00420F36 = patch_call((void *)0x00420F36, (void *)game_end);
    g_proc_0046D912 = patch_call((void *)0x0046D912, (void *)kicked);
}
