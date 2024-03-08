
#include <windows.h>


#ifndef _LAMB_
#define _LAMB_

#define SCRW 640
#define SCRH 480



#define THUMB_W 128
#define THUMB_H 128




//////////////////////



#define sTYPE 0x45505954 // "TYPE"
#define sVER_ 0x20524556 // "VER "
#define sDESC 0x43534544 // "DESC"
#define sOWNR 0x524E574F // "OWNR"
#define sERA_ 0x20415245 // "ERA "
#define sERAX 0x54415245 // "ERAX"
#define sDIM_ 0x204D4944 // "DIM "
#define sUDTA 0x41544455 // "UDTA"
#define sUNIT 0x54494E55 // "UNIT"
#define sUGRD 0x44524755 // "UGRD"

#define sSIDE 0x45444953 // "SIDE"
#define sSGLD 0x444C4753 // "SGLD"
#define sSLBR 0x52424C53 // "SLBR"
#define sSOIL 0x4C494F53 // "SOIL"
#define sAIPL 0x4C504941 // "AIPL"

#define sMTXM 0x4D58544D // "MTXM"
#define sSQM_ 0x204D5153 // "SQM "
#define sOILM 0x4D4C494F // "OILM"
#define sREGM 0x4D474552 // "REGM"

#define sSIGN 0x4E474953 // "SIGN"
#define sALOW 0x574F4C41 // "ALOW"

#define FOREST     0
#define WINTER     1
#define WASTELAND  2
#define SWAMP      3



extern "C" { 
    typedef struct pudsect {
        DWORD Reserved;
        DWORD name;
        DWORD size;
        LPVOID data;
    }PUDSECT;
}

extern "C" { 
    typedef struct hmibmp {
        BITMAPFILEHEADER* pFile;
        BITMAPINFOHEADER* pInfo;
        RGBQUAD*          pPal;
        BYTE*             pBits;
        int               width;
        int               height;
        int               bpp;
        int               linew;
        int               usage;
        int               size;
    }HMIBMP;
}

extern "C" { 
    typedef struct pudunit{
    WORD x;
    WORD y;
    BYTE type;
    BYTE owner;
    WORD ai;     // 0-passive 1-active or (gold or oil)/2500
    }PUDUNIT;
}


extern "C" { 
    typedef struct wc2displayinfo{
    BYTE* backbuffer;
    int   bbwidth;
    int   bbheight;
    BYTE* backbuffer2;
    int   bb2x;
    int   bb2y;
    int   menux;
    int   menuy;
    int   vpTileW;
    int   vpTileH;
    int   vpPixW;
    int   vpPixH;
    }WC2DISPLAYINFO;
}

//PUDfile.inc
extern "C" typedef LPVOID  (__stdcall *pfnpudload )(CHAR* path);
extern "C" typedef int     (__stdcall *pfnpudsave )(LPVOID hpud,CHAR* path);

//PUDpud.inc
extern "C" typedef int     (__stdcall *pfnsectcnt )(LPVOID hpud);
extern "C" typedef void    (__stdcall *pfndestroy )(LPVOID hpud);
extern "C" typedef LPVOID  (__stdcall *pfndelsect )(LPVOID hpud,LPVOID hsect);
extern "C" typedef PUDSECT*(__stdcall *pfnfindsect)(LPVOID hpud,DWORD sectname);
extern "C" typedef int     (__stdcall *pfnupdsect )(LPVOID hpud,LPVOID hsect,LPVOID lpnew,int nbytes);
extern "C" typedef PUDSECT*(__stdcall *pfngetsect )(LPVOID hpud,int nsect);
extern "C" typedef int     (__stdcall *pfnsectndx )(LPVOID hpud,DWORD sectname);
extern "C" typedef LPVOID  (__stdcall *pfnsectset )(LPVOID hpud,LPVOID hsect,int nsect);
extern "C" typedef BOOL    (__stdcall *pfnsectcre )(LPVOID hpud,DWORD sectname,LPVOID lpnew,int nbytes);
extern "C" typedef LPVOID  (__stdcall *pfnrealloc )(PUDSECT* hSect,int nbytes);

//PUDunit.inc
extern "C" typedef int     (__stdcall *pfnunitsize)(int utype);
extern "C" typedef int     (__stdcall *pfnuniticof)(int utype);
extern "C" typedef int     (__stdcall *pfnlistget )(int list,int ndx);
extern "C" typedef int     (__stdcall *pfnlistnext)(int list,int utype);
extern "C" typedef int     (__stdcall *pfnlistprev)(int list,int utype);
extern "C" typedef LPVOID  (__stdcall *pfnlistname)(int list);

//PUDtile.inc
extern "C" typedef void    (__stdcall *pfnrndrmap )(LPVOID hbmp,LPVOID mtxm,int mapw);
extern "C" typedef void    (__stdcall *pfnrndrtile)(LPVOID hbmp,int tile,int x,int y);
extern "C" typedef LPVOID  (__stdcall *pfngettile )(int tile);
extern "C" typedef void    (__stdcall *pfntileset )(LPVOID tileset);
extern "C" typedef void    (__stdcall *pfnblack   )(HDC dc,int x,int y,int w,int h);

//hmibmp.inc
extern "C" typedef HMIBMP* (__stdcall *pfnmakebmp )(int w,int h,int bpp);
extern "C" typedef void    (__stdcall *pfnfreebmp )(HMIBMP* bmp);
extern "C" typedef int     (__stdcall *pfnzerobmp )(HMIBMP* bmp);
extern "C" typedef void    (__stdcall *pfnsavebmp )(CHAR* path,HMIBMP* bmp);
extern "C" typedef void    (__stdcall *pfnsavejpg )(CHAR* path,HMIBMP* bmp,int quality);
extern "C" typedef void    (__stdcall *pfnperfbmp )(HMIBMP* bmp);
extern "C" typedef void    (__stdcall *pfncopyimg )(HMIBMP* src,int scrx,int srcy,int srcw,int scrh,HMIBMP* dst,int dstx,int dsty,int transp);
extern "C" typedef int     (__stdcall *pfncopyfull)(HMIBMP* dstbmp,HMIBMP* srcbmp,int transp);
extern "C" typedef void    (__stdcall *pfndispimg )(HDC destDC,int x,int y,int w,int h,HMIBMP* bmp,int dx,int dy,int dw,int dh);
extern "C" typedef void    (__stdcall *pfnsetpal  )(HMIBMP* bmp,LPVOID palette);
extern "C" typedef void    (__stdcall *pfndrawrect)(HMIBMP* bmp,int x,int y,int w,int h,int color);
extern "C" typedef HMIBMP* (__stdcall *pfnsizebmp )(HMIBMP* bmp,int w,int h);
extern "C" typedef HMIBMP* (__stdcall *pfnscalebmp)(HMIBMP* bmp,int scale);
extern "C" typedef void    (__stdcall *pfnsetpixel)(HMIBMP* bmp,int x,int y,int pval);
extern "C" typedef void    (__stdcall *pfnpastestr)(HMIBMP* bmp,int x,int y,CHAR* lpsz,int color);
extern "C" typedef void    (__stdcall *pfnwc2tpast)(HMIBMP* bmp,int x,int y);

//PUDgrp.inc
extern "C" typedef LPVOID  (__stdcall *pfngrpinit )(LPVOID grplubase);
extern "C" typedef void    (__stdcall *pfndrawgrp )(int grp,int nframe,LPVOID daddr,int dwidth,int owner,int centre,int mirror);
extern "C" typedef void    (__stdcall *pfndrawbtn )(LPVOID bmp, int xpos, int ypos, int icon, int state);

extern "C" typedef WC2DISPLAYINFO* (__stdcall *pfngdinfo  )();


extern pfnpudload      PUDload;
extern pfnpudsave      PUDsave;

extern pfnsectcnt      PUDsection_count;
extern pfndestroy      PUDdestroy;
extern pfndelsect      PUDdelete_section;
extern pfnfindsect     PUDfind_section;
extern pfnupdsect      PUDupdate_section;
extern pfngetsect      PUDget_section;
extern pfnsectndx      PUDsection_index;
extern pfnsectset      PUDsection_set_index;
extern pfnsectcre      PUDcreate_section;
extern pfnrealloc      PUDsection_realloc;

extern pfnunitsize     PUDunitSize;
extern pfnuniticof     PUDunitIconFrame;
extern pfnlistget      PUDlistGet;
extern pfnlistnext     PUDlistNext;
extern pfnlistprev     PUDlistPrev;
extern pfnlistname     PUDlistName;

extern pfnrndrmap      PUDrenderMap;
extern pfnrndrtile     PUDrenderTile;
extern pfngettile      PUDgetTile;
extern pfntileset      PUDtileset;
extern pfnblack        PUDblack;

extern pfnmakebmp      make_bitmap;
extern pfnfreebmp      free_bitmap;
extern pfnzerobmp      zero_bitmap;
extern pfnsavebmp      save_bitmap;
extern pfnsavejpg      save_jpeg;
extern pfnperfbmp      perforate_bitmap;
extern pfncopyimg      copy_image;
extern pfncopyfull     copy_full_image;
extern pfndispimg      display_image;
extern pfnsetpal       set_palette;
extern pfndrawrect     draw_rect;
extern pfnsizebmp      size_bitmap;
extern pfnscalebmp     scale_bitmap;
extern pfnsetpixel     set_pixel;
extern pfnpastestr     paste_string;
extern pfnwc2tpast     wc2_trans_paste;
extern pfngdinfo       getDisplayInfo;


///////////////////////////

extern HMIBMP* PUDthumbnail(CHAR* pudpath);
extern BOOL in_lobby();
extern void paste_cursor(HMIBMP* hbm, int dx, int dy);
extern BOOL safe_set_pixel(HMIBMP* hbm, int x, int y, int pval);

#define MAP_NAME  (CHAR*)0x004ABB0C
#define MAP_PATH  (CHAR*)0x004ABFA4
#define MAP_LOBBY (CHAR*)0x004D3C9D
#define GAME_MODE (CHAR*)0x004AE430

extern DWORD tilecolors[];
extern int playercolors[];


#endif
