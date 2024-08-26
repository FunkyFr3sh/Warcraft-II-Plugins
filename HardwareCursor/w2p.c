#include <windows.h>
#include <stdio.h>
#include "../inc/patch.h"
#include "../inc/ini.h"


#define FILE_EXISTS(a) (GetFileAttributes(a) != INVALID_FILE_ATTRIBUTES)

#define W2_HWND *((HWND*)0x004CE7B8)
#define W2_CURSOR_ID *((unsigned char*)0x004AE098)
#define W2_GAME_WIDTH  *((unsigned short*)0x004D4A90)
#define W2_GAME_HEIGHT *((unsigned short*)0x004D4A92)
#define W2_CURSOR_VISIBLE *((unsigned char*)0x004D48A8)

#define IDT_TIMER_RESIZE 541282672

BOOL(WINAPI* real_GetClientRect)(HWND, LPRECT) = GetClientRect;
HMODULE g_module;
WNDPROC g_wndproc;
HCURSOR g_cursors[256];
float g_cursor_size;
PROC g_proc_0048AAD7, g_proc_00417F28, g_proc_00418026, g_proc_00489705,
    g_proc_0048975B, g_proc_004897FA, g_proc_0048983F, g_proc_00489910;

void load_cursors(float scale);

LRESULT CALLBACK fake_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SETCURSOR:
    {
        if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
            return TRUE;
        }

        break;
    }
    case WM_WINDOWPOSCHANGED:
    {
        WINDOWPOS* pos = (WINDOWPOS*)lParam;
        
        if (!(pos->flags & SWP_NOSIZE))
        {
            SetTimer(W2_HWND, IDT_TIMER_RESIZE, 1000, (TIMERPROC)NULL);
        }
        
        break;
    }
    case WM_SIZE:
    {
        if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED)
        {
            SetTimer(W2_HWND, IDT_TIMER_RESIZE, 1000, (TIMERPROC)NULL);
        }
        
        break;
    }
    case WM_TIMER:
    {
        switch (wParam)
        {
        case IDT_TIMER_RESIZE:
        {
            KillTimer(W2_HWND, IDT_TIMER_RESIZE);

            if (FindWindowEx(HWND_DESKTOP, NULL, "SDlgDialog", NULL))
                return 0;
            
            RECT rc;
            if (g_cursor_size == 0.0f && real_GetClientRect(W2_HWND, &rc) && rc.right > 0 && rc.bottom > 0)
            {
                float scale_w = (float)rc.right / W2_GAME_WIDTH;
                float scale_h = (float)rc.bottom / W2_GAME_HEIGHT;
                float scale = scale_w > scale_h ? scale_h : scale_w;

                load_cursors(scale);
            }

            return 0;
        }
        }
        
        break;
    }
    }

    return CallWindowProcA(g_wndproc, hwnd, uMsg, wParam, lParam);
}

void show_cusor()
{
    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
    ((void (*)())g_proc_00489705)();
}

void hide_cusor()
{
    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
    ((void (*)())g_proc_0048975B)();
}

void toggle_cursor1()
{
    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
    ((void (*)())g_proc_004897FA)();
}

void toggle_cursor2()
{
    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
    ((void (*)())g_proc_0048983F)();
}

void toggle_cursor3()
{
    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
    ((void (*)())g_proc_00489910)();
}

void draw_cursor(int a, int b, int c, int d)
{
    //((void (*)(int,int,int,int))0x0048AA20)(a, b, c, d);
}

void change_cursor(int a)
{
    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
    ((void (*)(int))g_proc_00417F28)(a);
}

void change_cursor2(int a)
{
    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
    ((void (*)(int))g_proc_00418026)(a);
}

void extract_resource(int id, char* file_path)
{
    HRSRC loc = FindResourceA(g_module, MAKEINTRESOURCE(id), RT_RCDATA);
    if (loc)
    {
        HGLOBAL res = LoadResource(g_module, loc);
        DWORD size = SizeofResource(g_module, loc);
        if (res && size > 0)
        {
            void* data = LockResource(res);
            if (data)
            {
                FILE* fp = fopen(file_path, "wb");
                if (fp)
                {
                    fwrite(data, 1, size, fp);
                    fclose(fp);
                }
            }
        }
    }
}

BOOL get_cursor_size(HCURSOR cur, SIZE* size)
{
    BOOL result = FALSE;

    if (cur)
    {
        ICONINFO info = {0};
        if (GetIconInfo(cur, &info))
        {
            BOOL monochrome = info.hbmColor == NULL;
            BITMAP bmp = {0};
            if (GetObjectA(info.hbmMask, sizeof(BITMAP), &bmp))
            {
                size->cx = bmp.bmWidth;
                size->cy = abs(bmp.bmHeight) / (monochrome ? 2 : 1);

                result = TRUE;
            }

            DeleteObject(info.hbmColor);
            DeleteObject(info.hbmMask);
        }
    }

    return result;
}

void load_cursors(float scale)
{
    if (scale < 1.0f && scale != 0.0f)
        scale = 1.0f;

    SetCursor(NULL);

    char cursor_path[MAX_PATH] = { 0 };

    for (int i = 0; i < 22; i++)
    {
        _snprintf(cursor_path, sizeof(cursor_path), ".\\plugin\\Cursors\\cursor%d.ani", i);

        if (!FILE_EXISTS(cursor_path))
            extract_resource(i + 1000, cursor_path);

        HCURSOR cur = (HCURSOR)LoadImageA(NULL, cursor_path, IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
        SIZE size = { 0, 0 };

        if (cur)
        {
            get_cursor_size(cur, &size);
            DestroyCursor(cur);
        }

        cur = 
            (HCURSOR)LoadImageA(
                NULL, cursor_path, IMAGE_CURSOR, (UINT)(size.cx * scale), (UINT)(size.cy * scale), LR_LOADFROMFILE);

        if (cur)
        {
            if (g_cursors[i])
                DestroyCursor(g_cursors[i]);

            g_cursors[i] = cur;
        }
    }

    SetCursor(W2_CURSOR_VISIBLE ? g_cursors[W2_CURSOR_ID] : NULL);
}

void __declspec(dllexport) w2p_init()
{
    /* setup cursors */
    CreateDirectoryA(".\\plugin\\Cursors", NULL);
    
    real_GetClientRect = (void*)GetProcAddress(LoadLibraryA("user32.dll"), "GetClientRect");

    g_cursor_size = ini_get_float("Cursor", "Size", 0.0f, ".\\plugin\\HardwareCursor.ini");
    
    load_cursors(g_cursor_size > 1.0f ? g_cursor_size : 0.0f);
    
    RECT rc;
    if (g_cursor_size == 0.0f && real_GetClientRect(W2_HWND, &rc) && rc.right > 0 && rc.bottom > 0)
    {
        float scale_w = (float)rc.right / W2_GAME_WIDTH;
        float scale_h = (float)rc.bottom / W2_GAME_HEIGHT;
        float scale = scale_w > scale_h ? scale_h : scale_w;
        
        load_cursors(scale);
    }

    ShowCursor(TRUE);

    /* hook wndproc */
    g_wndproc = (WNDPROC)SetWindowLongA(W2_HWND, GWL_WNDPROC, (LONG)fake_wndproc);

    /* hook show/hide cursor */
    g_proc_00489705 = patch_call((void*)0x00489705, (void*)show_cusor);
    g_proc_0048975B = patch_call((void*)0x0048975B, (void*)hide_cusor);
    g_proc_004897FA = patch_call((void*)0x004897FA, (void*)toggle_cursor1);
    g_proc_0048983F = patch_call((void*)0x0048983F, (void*)toggle_cursor2);
    g_proc_00489910 = patch_call((void*)0x00489910, (void*)toggle_cursor3);

    /* hook change cursor */
    g_proc_00417F28 = patch_call((void*)0x00417F28, (void*)change_cursor);
    g_proc_00418026 = patch_call((void*)0x00418026, (void*)change_cursor2);

    /* hook cursor drawing */
    patch_setdword((void*)0x00428931, (DWORD)draw_cursor);
    patch_setdword((void*)0x004D48B8, (DWORD)draw_cursor);

    /* remove ShowCursor calls */
    patch_clear((void*)0x0045EA9F, 0x90, (void*)0x0045EAA7);
    patch_clear((void*)0x0045EAD2, 0x90, (void*)0x0045EADA);
    patch_clear((void*)0x0045EE6F, 0x90, (void*)0x0045EE77);
    patch_clear((void*)0x0045EE86, 0x90, (void*)0x0045EE8E);
    patch_clear((void*)0x0045F07C, 0x90, (void*)0x0045F07D);
    patch_clear((void*)0x0045F083, 0x90, (void*)0x0045F089);
    patch_clear((void*)0x0045EE86, 0x90, (void*)0x0045EE8E);
    patch_clear((void*)0x00469BFA, 0x90, (void*)0x00469C01);
    patch_clear((void*)0x00469DC0, 0x90, (void*)0x00469DC8);

    HMODULE storm_dll = GetModuleHandleA("storm.dll");

    if (storm_dll && memcmp((char*)storm_dll + 0x00010000, "\xC2\x8B\x54\x24\x2C\xD1\xF8\x8D", 8) == 0)
    {
        /* remove ShowCursor calls */
        patch_clear((char*)storm_dll + 0x0000F182, 0x90, (char*)storm_dll + 0x0000F184);
        patch_clear((char*)storm_dll + 0x0000F185, 0x90, (char*)storm_dll + 0x0000F18F);
        patch_clear((char*)storm_dll + 0x0000F2F4, 0x90, (char*)storm_dll + 0x0000F2FC);
        patch_clear((char*)storm_dll + 0x00011660, 0x90, (char*)storm_dll + 0x00011664);
        patch_clear((char*)storm_dll + 0x00012AF7, 0x90, (char*)storm_dll + 0x00012AF9);
        patch_clear((char*)storm_dll + 0x00012AFA, 0x90, (char*)storm_dll + 0x00012B00);
        patch_clear((char*)storm_dll + 0x00012B59, 0x90, (char*)storm_dll + 0x00012B5D);
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        g_module = hinstDLL;
    }
    return TRUE;
}
