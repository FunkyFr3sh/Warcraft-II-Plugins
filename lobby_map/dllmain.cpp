                                                         //
     /////////////////////////////////////////////////////
    //         Lobby Map Plugin for Warcraft II        //
   /////////////////////////////////////////////////////
  //                                    Lambchops 2018
  
#include <windows.h>
#include "lamb.h"

int g_thumb_x = 452;
int g_thumb_y = 106;
BOOL display_map_on = FALSE;
int Htxos,Htyos;
int Hscrw;
BYTE* Hlpscr;


void get_scr_info(){
    WC2DISPLAYINFO* di = getDisplayInfo();
    Htxos=di->bb2x;
    Htyos=di->bb2y;
    Hscrw=di->bbwidth;
    Hlpscr=di->backbuffer2;
}

void wc2bmPaste(HMIBMP* hbm,int px, int py){
    BYTE* pix   = hbm->pBits;
    BYTE* lpscr = Hlpscr+(py*Hscrw)+px;
       
    for(int y=0;y<hbm->height;y++){
        CopyMemory(lpscr,pix,hbm->width);
        pix+=hbm->linew;
        lpscr+=Hscrw;
    }
}

#define MAP_NAME (CHAR*)0x004ABB0C
#define MAP_PATH (CHAR*)0x004ABFA4

CHAR* filename(CHAR* path){
    CHAR* ret=path;
    while ((CHAR)*path!=0){
        if ((CHAR)*path==0x5C) ret=path+1;
        path++;
    }
    return ret;
}

BOOL check_dl(){
    // is the map name the same in the full path?
    // = download is finished 
    if(CompareString(   LOCALE_SYSTEM_DEFAULT,
                        NORM_IGNORECASE,
                        filename(MAP_PATH),
                        -1,
                        MAP_NAME,
                        -1    )==2){return TRUE;}    
    return FALSE;
}


HMIBMP* thumb;
HMIBMP* thumb2;
int tdatsize;

DWORD CALLBACK ThumbThread(LPVOID lpParam){ 
    while(TRUE){
        Sleep(200);
        if(display_map_on){
            if(!in_lobby()){
                display_map_on=FALSE;
            }
        }else{ 
            if(in_lobby()){
                if(check_dl()){
                    get_scr_info();
                    free_bitmap(thumb);
                    thumb = PUDthumbnail(MAP_PATH);
                    tdatsize = thumb->linew*thumb->height;
                    display_map_on = TRUE;
                }
            }          
        }
    }
}


extern "C" __declspec (dllexport) void w2p_init(){
    g_thumb_x = GetPrivateProfileIntA("lobby_map", "x", 452, ".\\plugin\\lobby_map.ini");
    g_thumb_y = GetPrivateProfileIntA("lobby_map", "y", 106, ".\\plugin\\lobby_map.ini");

    tilecolors[0] = GetPrivateProfileIntA("colors", "tile0", 0x00, ".\\plugin\\lobby_map.ini");
    tilecolors[1] = GetPrivateProfileIntA("colors", "tile1", 0xB7, ".\\plugin\\lobby_map.ini");
    tilecolors[2] = GetPrivateProfileIntA("colors", "tile2", 0xB5, ".\\plugin\\lobby_map.ini");
    tilecolors[3] = GetPrivateProfileIntA("colors", "tile3", 0xAA, ".\\plugin\\lobby_map.ini");
    tilecolors[4] = GetPrivateProfileIntA("colors", "tile4", 0x46, ".\\plugin\\lobby_map.ini");
    tilecolors[5] = GetPrivateProfileIntA("colors", "tile5", 0x97, ".\\plugin\\lobby_map.ini");
    tilecolors[6] = GetPrivateProfileIntA("colors", "tile6", 0x96, ".\\plugin\\lobby_map.ini");
    tilecolors[7] = GetPrivateProfileIntA("colors", "tile7", 0x92, ".\\plugin\\lobby_map.ini");
    tilecolors[8] = GetPrivateProfileIntA("colors", "tile8", 0x3B, ".\\plugin\\lobby_map.ini");
    tilecolors[9] = GetPrivateProfileIntA("colors", "tile9", 0x6E, ".\\plugin\\lobby_map.ini");
    tilecolors[10] = GetPrivateProfileIntA("colors", "tile10", 0x6F, ".\\plugin\\lobby_map.ini");
    tilecolors[11] = GetPrivateProfileIntA("colors", "tile11", 0x7E, ".\\plugin\\lobby_map.ini");
    tilecolors[12] = GetPrivateProfileIntA("colors", "tile12", 0x7F, ".\\plugin\\lobby_map.ini");
    tilecolors[13] = GetPrivateProfileIntA("colors", "tile13", 0xB6, ".\\plugin\\lobby_map.ini");
    tilecolors[14] = GetPrivateProfileIntA("colors", "tile14", 0xB6, ".\\plugin\\lobby_map.ini");
    tilecolors[15] = GetPrivateProfileIntA("colors", "tile15", 0x88, ".\\plugin\\lobby_map.ini");
    tilecolors[16] = GetPrivateProfileIntA("colors", "tile16", 0x72, ".\\plugin\\lobby_map.ini");
    tilecolors[17] = GetPrivateProfileIntA("colors", "tile17", 0xAA, ".\\plugin\\lobby_map.ini");
    tilecolors[18] = GetPrivateProfileIntA("colors", "tile18", 0x97, ".\\plugin\\lobby_map.ini");
    tilecolors[19] = GetPrivateProfileIntA("colors", "tile19", 0x91, ".\\plugin\\lobby_map.ini");
    tilecolors[20] = GetPrivateProfileIntA("colors", "tile20", 0x6E, ".\\plugin\\lobby_map.ini");
    tilecolors[21] = GetPrivateProfileIntA("colors", "tile21", 0x6F, ".\\plugin\\lobby_map.ini");

    playercolors[0] = GetPrivateProfileIntA("colors", "player0", 0xA8, ".\\plugin\\lobby_map.ini");
    playercolors[1] = GetPrivateProfileIntA("colors", "player1", 0xD4, ".\\plugin\\lobby_map.ini");
    playercolors[2] = GetPrivateProfileIntA("colors", "player2", 0xD8, ".\\plugin\\lobby_map.ini");
    playercolors[3] = GetPrivateProfileIntA("colors", "player3", 0xDD, ".\\plugin\\lobby_map.ini");
    playercolors[4] = GetPrivateProfileIntA("colors", "player4", 0xE0, ".\\plugin\\lobby_map.ini");
    playercolors[5] = GetPrivateProfileIntA("colors", "player5", 0xEA, ".\\plugin\\lobby_map.ini");
    playercolors[6] = GetPrivateProfileIntA("colors", "player6", 0xE8, ".\\plugin\\lobby_map.ini");
    playercolors[7] = GetPrivateProfileIntA("colors", "player7", 0xFB, ".\\plugin\\lobby_map.ini");

    DWORD dw=0;
    
    CreateThread( NULL,
                  0,
                  ThumbThread,
                  &dw,
                  0,
                  NULL             );  
}

extern "C" __declspec (dllexport) void screen_update(DWORD location){   
    if(in_lobby()){                                                       
        if(display_map_on){
            //get_scr_info();
            thumb2=make_bitmap(thumb->width,thumb->height,8);
            CopyMemory(thumb2->pBits,thumb->pBits,tdatsize);
            paste_cursor(thumb2, g_thumb_x +Htxos, g_thumb_y +Htyos);
            wc2bmPaste(thumb2,g_thumb_x,g_thumb_y);
            //wc2bmPaste(thumb2,Htxos+THUMB_X,Htyos+THUMB_Y);
            free_bitmap(thumb2);
        }
    }
}

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        thumb = make_bitmap(32, 32, 8);
        break;
    }
    }
    return TRUE;
}






