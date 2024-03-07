#include <windows.h>
#include "lamb.h"


HMODULE hLambDll = LoadLibraryA("LC");


pfnpudload  PUDload             = (pfnpudload )GetProcAddress(hLambDll, "PUDload"             );
//pfnpudsave  PUDsave             = (pfnpudsave )GetProcAddress(hLambDll, "PUDsave"             );

//pfnsectcnt  PUDsection_count    = (pfnsectcnt )GetProcAddress(hLambDll, "PUDsection_count"    );
pfndestroy  PUDdestroy          = (pfndestroy )GetProcAddress(hLambDll, "PUDdestroy"          );
//pfndelsect  PUDdelete_section   = (pfndelsect )GetProcAddress(hLambDll, "PUDdelete_section"   );
pfnfindsect PUDfind_section     = (pfnfindsect)GetProcAddress(hLambDll, "PUDfind_section"     );
//pfnupdsect  PUDupdate_section   = (pfnupdsect )GetProcAddress(hLambDll, "PUDupdate_section"   );
//pfngetsect  PUDget_section      = (pfngetsect )GetProcAddress(hLambDll, "PUDget_section"      );
//pfnsectndx  PUDsection_index    = (pfnsectndx )GetProcAddress(hLambDll, "PUDsection_index"    );
//pfnsectset  PUDsection_set_index= (pfnsectset )GetProcAddress(hLambDll, "PUDsection_set_index");
//pfnsectcre  PUDcreate_section   = (pfnsectcre )GetProcAddress(hLambDll, "PUDcreate_section"   );
//pfnrealloc  PUDsection_realloc  = (pfnrealloc )GetProcAddress(hLambDll, "PUDsection_realloc"   );


//pfnunitsize PUDunitSize         = (pfnunitsize)GetProcAddress(hLambDll, "PUDunitSize"         );
//pfnuniticof PUDunitIconFrame    = (pfnuniticof)GetProcAddress(hLambDll, "PUDunitIconFrame"    );
//pfnlistget  PUDlistGet          = (pfnlistget )GetProcAddress(hLambDll, "PUDlistGet"          );
//pfnlistnext PUDlistNext         = (pfnlistnext)GetProcAddress(hLambDll, "PUDlistNext"         );
//pfnlistprev PUDlistPrev         = (pfnlistprev)GetProcAddress(hLambDll, "PUDlistPrev"         );
//pfnlistname PUDlistName         = (pfnlistname)GetProcAddress(hLambDll, "PUDlistName"         );

//pfnrndrmap  PUDrenderMap        = (pfnrndrmap )GetProcAddress(hLambDll, "PUDrenderMap"        );
//pfnrndrtile PUDrenderTile       = (pfnrndrtile)GetProcAddress(hLambDll, "PUDrenderTile"       );
//pfngettile  PUDgetTile          = (pfngettile )GetProcAddress(hLambDll, "PUDgetTile"          );
//pfntileset  PUDtileset          = (pfntileset )GetProcAddress(hLambDll, "PUDtileset"          );
//pfnblack    PUDblack            = (pfnblack   )GetProcAddress(hLambDll, "PUDblack"            );

pfnmakebmp  make_bitmap         = (pfnmakebmp )GetProcAddress(hLambDll, "make_bitmap"         );
pfnfreebmp  free_bitmap         = (pfnfreebmp )GetProcAddress(hLambDll, "free_bitmap"         );
//pfnzerobmp  zero_bitmap         = (pfnzerobmp )GetProcAddress(hLambDll, "zero_bitmap"         );
//pfnsavebmp  save_bitmap         = (pfnsavebmp )GetProcAddress(hLambDll, "save_bitmap"         );
//pfnsavejpg  save_jpeg           = (pfnsavejpg )GetProcAddress(hLambDll, "save_jpeg"           );
//pfnsizebmp  size_bitmap         = (pfnsizebmp )GetProcAddress(hLambDll, "size_bitmap"         );
pfnscalebmp scale_bitmap        = (pfnscalebmp)GetProcAddress(hLambDll, "scale_bitmap"        );
//pfnperfbmp  perforate_bitmap    = (pfnperfbmp )GetProcAddress(hLambDll, "perforate_bitmap"    );
//pfncopyimg  copy_image          = (pfncopyimg )GetProcAddress(hLambDll, "copy_image"          );
//pfncopyfull copy_full_image     = (pfncopyfull)GetProcAddress(hLambDll, "copy_full_image"     );
//pfndispimg  display_image       = (pfndispimg )GetProcAddress(hLambDll, "display_td_image"    );
//pfnsetpal   set_palette         = (pfnsetpal  )GetProcAddress(hLambDll, "set_palette"         );
//pfndrawrect draw_rect           = (pfndrawrect)GetProcAddress(hLambDll, "draw_rect"           );
pfnsetpixel set_pixel           = (pfnsetpixel)GetProcAddress(hLambDll, "set_pixel"           );
//pfnpastestr paste_string        = (pfnpastestr)GetProcAddress(hLambDll, "paste_string"        );
//pfnwc2tpast wc2_trans_paste     = (pfnwc2tpast)GetProcAddress(hLambDll, "wc2_trans_paste"           );
pfngdinfo   getDisplayInfo      = (pfngdinfo  )GetProcAddress(hLambDll, "getDisplayInfo"      );


