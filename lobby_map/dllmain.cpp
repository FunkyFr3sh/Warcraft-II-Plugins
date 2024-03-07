                                                         //
     /////////////////////////////////////////////////////
    //         Lobby Map Plugin for Warcraft II        //
   /////////////////////////////////////////////////////
  //                                    Lambchops 2018
  
#include <windows.h>
#include "lamb.h"
#define THUMB_X 452
#define THUMB_Y 106

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
            paste_cursor(thumb2,THUMB_X+Htxos,THUMB_Y+Htyos);                      
            wc2bmPaste(thumb2,THUMB_X,THUMB_Y);
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






