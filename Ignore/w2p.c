#include <windows.h>
#include <stdio.h>
#include "../inc/patch.h"

PROC g_proc_0000846A, g_proc_004739F5, g_proc_00006C21, g_proc_00006CB3, 
     g_proc_00473A63, g_proc_00473A35, g_proc_0046D062, g_proc_0042CB3B,
     g_proc_0046D119;

char g_ignorelist[1024][16];

const char IGNORE_CMD[] = "/ignore ";
const char UNIGNORE_CMD[] = "/unignore ";
const char SQUELCH_CMD[] = "/squelch ";
const char UNSQUELCH_CMD[] = "/unsquelch ";
const char IGNORELIST_PATH[] = ".\\plugin\\ignorelist.txt";

void save_ignorelist()
{
    FILE *fp = fopen(IGNORELIST_PATH, "w");
    if (fp)
    {
        for (int i = 0; i < sizeof(g_ignorelist) / sizeof(g_ignorelist[0]); i++)
        {
            if (g_ignorelist[i][0])
                fprintf(fp, "%s\n", g_ignorelist[i]);
        }

        fclose(fp);
    }
}

void load_ignorelist()
{
    FILE *fp = fopen(IGNORELIST_PATH, "r");
    if (fp)
    {
        int i = 0;

        while (i < sizeof(g_ignorelist) / sizeof(g_ignorelist[0]) && 
               fgets(g_ignorelist[i], sizeof(g_ignorelist[i]), fp))
        {
            g_ignorelist[i][strcspn(g_ignorelist[i], "\r\n")] = 0;
            i++;
        }

        fclose(fp);
    }
}

BOOL is_ignored(char *nickname)
{
    if (!nickname)
        return FALSE;

    for (int i = 0; i < sizeof(g_ignorelist) / sizeof(g_ignorelist[0]); i++)
    {
        if (g_ignorelist[i][0] && _strcmpi(nickname, g_ignorelist[i]) == 0)
            return TRUE;
    }
    
    return FALSE;
}

void handle_ignore(char *nickname)
{
    nickname[strcspn(nickname, " ")] = 0;
    
    if (strlen(nickname) >= 16 || is_ignored(nickname))
        return;
    
    for (int i = 0; i < sizeof(g_ignorelist) / sizeof(g_ignorelist[0]); i++)
    {
        if (!g_ignorelist[i][0])
        {
            strncpy(g_ignorelist[i], nickname, sizeof(g_ignorelist[0]));
            g_ignorelist[i][sizeof(g_ignorelist[0]) - 1] = 0; /* strncpy fix */
            save_ignorelist();
            return;
        }
    }
}

void handle_unignore(char *nickname)
{
    nickname[strcspn(nickname, " ")] = 0;
    
    for (int i = 0; i < sizeof(g_ignorelist) / sizeof(g_ignorelist[0]); i++)
    {
        if (g_ignorelist[i][0] && _strcmpi(nickname, g_ignorelist[i]) == 0)
        {
            g_ignorelist[i][0] = 0;
            save_ignorelist();
            return;
        }
    }
}

void parse_command(char *text)
{
    if (text)
    {
        if (_strnicmp(text, IGNORE_CMD, strlen(IGNORE_CMD)) == 0)
            handle_ignore(text + strlen(IGNORE_CMD));
        
        if (_strnicmp(text, SQUELCH_CMD, strlen(SQUELCH_CMD)) == 0)
            handle_ignore(text + strlen(SQUELCH_CMD));
        
        if (_strnicmp(text, UNIGNORE_CMD, strlen(UNIGNORE_CMD)) == 0)
            handle_unignore(text + strlen(UNIGNORE_CMD));
        
        if (_strnicmp(text, UNSQUELCH_CMD, strlen(UNSQUELCH_CMD)) == 0)
            handle_unignore(text + strlen(UNSQUELCH_CMD));
    }
}

int __stdcall read_text(char *text)
{
    parse_command(text);
    return ((int (__stdcall *)(char *))g_proc_004739F5)(text);
}

void __fastcall read_bnet_text(char *text, int a)
{
    parse_command(text);
    ((void (__fastcall *)(char *, int))g_proc_0000846A)(text, a);
}

BOOL __fastcall private_bnet_mes_ignored(char *nickname)
{
    if (is_ignored(nickname))
        return TRUE;

    return ((BOOL (__fastcall *)(char *))g_proc_00006C21)(nickname);
}

BOOL __fastcall public_bnet_mes_ignored(char *nickname)
{
    if (is_ignored(nickname))
        return TRUE;

    return ((BOOL (__fastcall *)(char *))g_proc_00006CB3)(nickname);
}

int public_mes_lobby(int a, char *message, int c)
{
    if (message)
    {
        char nickname[20] = { 0 };
        strncpy(nickname, message, sizeof(nickname)); 
        nickname[sizeof(nickname) - 1] = 0; /* strncpy fix */
        char *end = strstr(nickname, ": ");

        if (!end)
            end = strrchr(nickname, ':');
        
        if (end)
        {
            *end = 0;
            
            if (is_ignored(nickname))
                return -1;
        }
    }

    return ((int (*)(int, char *, int))g_proc_0046D062)(a, message, c);
}

int public_multi_line_mes_lobby(int a, char *message, int c)
{
    if (message)
    {
        char nickname[20] = { 0 };
        strncpy(nickname, message, sizeof(nickname)); 
        nickname[sizeof(nickname) - 1] = 0; /* strncpy fix */
        char *end = strstr(nickname, ": ");

        if (!end)
            end = strrchr(nickname, ':');
        
        if (end)
        {
            *end = 0;
            
            if (is_ignored(nickname))
                return -1;
        }
    }

    return ((int (*)(int, char *, int))g_proc_0046D119)(a, message, c);
}

void private_mes_lobby(int a, char *nickname)
{
    if (is_ignored(nickname))
        return;

    ((void (*)(int, char *))g_proc_00473A63)(a, nickname);
}

void private_mes_ingame(char *nickname, int b)
{
    if (is_ignored(nickname))
        return;

    ((void (*)(char *, int))g_proc_00473A35)(nickname, b);
}

void public_mes_ingame(char *message, int a, int b)
{
    if (message)
    {
        char nickname[20] = { 0 };
        strncpy(nickname, message, sizeof(nickname));
        nickname[sizeof(nickname) - 1] = 0; /* strncpy fix */
        char *end = strstr(nickname, ": ");

        if (!end)
            end = strrchr(nickname, ':');
        
        if (end)
        {
            *end = 0;
            
            if (is_ignored(nickname))
                return;
        }
    }

    ((void (*)(char *, int, int))g_proc_0042CB3B)(message, a, b);
}

int format_private_mes(char *buf, char *format, char *nickname, char *message)
{
    if (is_ignored(nickname) && buf)
    {
        strncpy(buf, nickname, 16);
        buf[16 - 1] = 0; /* strncpy fix */
        return 0;
    }

    return wsprintfA(buf, format, nickname, message);
}

HMODULE WINAPI fake_LoadLibraryA(LPCSTR lpLibFileName)
{
    HMODULE hmod = LoadLibraryA(lpLibFileName);
    
    if (hmod && memcmp((char *)hmod + 0x00010000, "\x00\x68\x5E\x01\x00\x00", 6) == 0)
    {
        g_proc_0000846A = patch_call((char *)hmod + 0x0000846A, (void *)read_bnet_text);
        g_proc_00006C21 = patch_call((char *)hmod + 0x00006C21, (void *)private_bnet_mes_ignored);
        g_proc_00006CB3 = patch_call((char *)hmod + 0x00006CB3, (void *)public_bnet_mes_ignored);
        
        patch_clear((char *)hmod + 0x00017C3C, 0x90, (char *)hmod + 0x00017C42);
        patch_call((char *)hmod + 0x00017C3C, (void *)format_private_mes);
    } /* battle.snp */
    
    return hmod;
}

void __declspec(dllexport) w2p_init()
{
    g_proc_004739F5 = patch_call((void *)0x004739F5, (void *)read_text);
    g_proc_00473A63 = patch_call((void *)0x00473A63, (void *)private_mes_lobby);
    g_proc_00473A35 = patch_call((void *)0x00473A35, (void *)private_mes_ingame);
    g_proc_0046D062 = patch_call((void *)0x0046D062, (void *)public_mes_lobby);
    g_proc_0042CB3B = patch_call((void *)0x0042CB3B, (void *)public_mes_ingame);
    g_proc_0046D119 = patch_call((void *)0x0046D119, (void *)public_multi_line_mes_lobby);
    
    
    HMODULE storm_dll = GetModuleHandleA("storm.dll");
    
    if (storm_dll && memcmp((char *)storm_dll + 0x00010000, "\xC2\x8B\x54\x24\x2C\xD1\xF8\x8D", 8) == 0)
    {
        patch_clear((char *)storm_dll + 0x00023138, 0x90, (char *)storm_dll + 0x0002313E);
        patch_call((char *)storm_dll + 0x00023138, (void *)fake_LoadLibraryA);
    }

    load_ignorelist();
}
