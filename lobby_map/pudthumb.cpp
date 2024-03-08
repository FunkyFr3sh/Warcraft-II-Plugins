#include <windows.h>
#include "lamb.h"

BOOL file_exists(char* path){
    // does the file exist and can we read it?
    HANDLE fn = CreateFile(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
    if(fn==INVALID_HANDLE_VALUE){
        return FALSE;
    }else{
        CloseHandle(fn);
        return TRUE;
    }
}


int playercolors[] = {       0xA8,         // red
                             0xD4,         // blue
                             0xD8,         // teal
                             0xDD,         // purp
                             0xE0,         // oj
                             0xEA,         // black
                             0xE8,         // white
                             0xFB       }; // yellow

// this just gives 3-letter names to some color values
// you can add more if you want

#define LTW 0xD4
#define DKW 0xD5
#define LTM 0xAA
#define DKM 0xA9
#define LTG 0x98
#define DKG 0x96
#define TRE 0x90
#define ROC 0x7D
#define OWL 0x7E
#define HWL 0x7F

#define TRE_GRA 0x93
#define ROC_MUD 0x7E
#define MUD_WAT 0xAC

#define GOLD 0xFB
#define OIL  0x00

DWORD tilecolors[] = { 0,
                       0xB7,
                       0xB5,
                       LTM,
                       0x46,
                       0x97,
                       DKG,
                       0x92,
                       0x3B,
                       0x6E,
                       0x6F,
                       OWL,
                       HWL,
                    // --- //
                       0xB6,
                       0xB6,
                       0x88,
                       0x72,
                       LTM,
                       0x97,
                       0x91,
                       0x6E,
                       0x6F };





BOOL in_lobby(){
    CHAR* gm = GAME_MODE;
    CHAR* ml = MAP_LOBBY;

    return ((*gm==0x0D)&&(*ml!=0));
    //return (getScreenConst()==LOC_LOBBY);
}

BYTE* sectionData(LPVOID hpud, DWORD sname){
    PUDSECT* sptr = PUDfind_section(hpud,sname);
    if (sptr!=NULL) return (BYTE*)sptr->data;
    return NULL;
}

int getPudSize(LPVOID hpud){
    WORD* pdim = (WORD*) sectionData(hpud,sDIM_);
    if(pdim) return (int) *pdim;
    return 0;
}

int get_tile_color(int mval){
    int r=0;
    if(mval<0xD0){
        r = mval>>4;
    }else{              
        r = (mval>>8)+0x0C;          
    }
    if(r>0x15){r=0;}
    return tilecolors[r];
}

BOOL safe_set_pixel(HMIBMP* hbm, int x, int y, int pval){
    // make sure we dont draw out of bounds 
    // when doing the mines/start locatons
    if(x<0||y<0||x>=hbm->width||y>=hbm->height){
        return FALSE;
    }else{
        set_pixel(hbm,x,y,pval);
        return TRUE;
    }
}


void draw_mine(HMIBMP* hbm,int xpos,int ypos,int res,int color){
    int d=1;
    if(res>=50000){d++;}
    xpos++;ypos++;
    for(int y=ypos-d;y<=ypos+d;y++){
        for(int x=xpos-d;x<=xpos+d;x++){
            safe_set_pixel(hbm,x,y,color);
        }
    }
}

void draw_start(HMIBMP* hbm,int x,int y,int player){
    int c=playercolors[player];
    safe_set_pixel(hbm,x,y,c);    
    safe_set_pixel(hbm,x-1,y-1,0);    
    safe_set_pixel(hbm,x+1,y+1,0);    
    safe_set_pixel(hbm,x+1,y-1,0);    
    safe_set_pixel(hbm,x-1,y+1,0);
    
    safe_set_pixel(hbm,x-1,y,c);    
    safe_set_pixel(hbm,x+1,y,c);    
    safe_set_pixel(hbm,x,y-1,c);    
    safe_set_pixel(hbm,x,y+1,c);    
}





// create a thumbnail BMP from the PUD file
HMIBMP* PUDthumbnail( CHAR* pudpath ){

    // load the pud file
    if(!file_exists(pudpath)){return make_bitmap(8,8,8);}
    LPVOID hPud = PUDload(pudpath);

    // get some info from the pud
    int mapsize = getPudSize(hPud);
    PUDSECT* mtxm  = PUDfind_section(hPud,sMTXM);
    PUDSECT* units = PUDfind_section(hPud,sUNIT);
    WORD*    pTile = (WORD*)mtxm->data;   

    int scale = 1;

    // check for invalid sections (partial download)
    if(!mapsize||!mtxm){PUDdestroy(hPud); return make_bitmap(8,8,8);}
    if(mtxm->size<(mapsize*mapsize*2)){PUDdestroy(hPud); return make_bitmap(8,8,8);}

    // make a bitmap in memory
    HMIBMP* hbm = make_bitmap(mapsize,mapsize,8);
    
    // set the pixels according to the mtxm values    
    for(int y=0;y<mapsize;y++){
        for(int x=0;x<mapsize;x++){
          set_pixel(hbm,x,y,get_tile_color((int)*pTile));
          pTile++;
        }    
    }
    
    
    if(units){ 
        int nUnits  = int(units->size/sizeof(PUDUNIT));
        PUDUNIT* pUnit = (PUDUNIT*)units->data;

        for(int i=0;i<nUnits;i++){
            switch(pUnit->type){
              case 0x5C:
                // mine
                draw_mine(hbm,pUnit->x,pUnit->y,pUnit->ai*2500,GOLD);
                break;
              case 0x5D:
                // patch 
                draw_mine(hbm,pUnit->x,pUnit->y,pUnit->ai*2500,OIL); 
                break;
            }
            pUnit++;
        }
        
        if(mapsize==64){
            scale = 2;  
        }
        if(mapsize==32){
            scale = 4;  
        }
        if(scale>1){
            HMIBMP* hbms = scale_bitmap(hbm,scale);
            free_bitmap(hbm);
            hbm=hbms;
        }   
         
        pUnit = (PUDUNIT*)units->data;
        for(int i=0;i<nUnits;i++){
            switch(pUnit->type){
              case 0x5E:
                // start
                draw_start(hbm,pUnit->x*scale,pUnit->y*scale,pUnit->owner);
                break;
              case 0x5F:
                // start
                draw_start(hbm,pUnit->x*scale,pUnit->y*scale,pUnit->owner);
                break;
            }
            pUnit++;
        }
    }

    // free the PUD structure from memory
    PUDdestroy(hPud);
    return hbm;
    
}



