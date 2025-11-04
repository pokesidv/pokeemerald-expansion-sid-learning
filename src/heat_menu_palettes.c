

#include "global.h"
#include "heat_menu_palettes.h"
#include "palette.h"
#include "menu.h"
#include "config/heat_menus.h"


static const u16 sStartMenuPalette[] = INCBIN_U16("graphics/heat_start_menu/bg.gbapal");

// --alternate BG pals--
static const u16 sStartMenuPalettes[MENU_PAL_COUNT][16] = {
    INCBIN_U16("graphics/heat_start_menu/bg.gbapal"),
    INCBIN_U16("graphics/heat_start_menu/bg1.gbapal"),
    INCBIN_U16("graphics/heat_start_menu/bg2.gbapal"),
    INCBIN_U16("graphics/heat_start_menu/bg3.gbapal"),

};

static const u16 *GetStartMenuPalette(u8 id)
{
  if (id >= MENU_PAL_COUNT)
    return sStartMenuPalettes[0]; // Return the default if ID is out of bounds
  else
    return sStartMenuPalettes[id];
}

void HeatMenus_LoadPalettes(void)
{
    // Load the standard menu palette for text windows
    LoadPalette(gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);

    // Load the start menu palette based on the persistent setting or just the default if such use of saveblock 2 is not enabled.
    #if HEAT_MENUS_SAVEBLOCK_PALETTES
    const u16 *selectedPalette = GetStartMenuPalette(gSaveBlock2Ptr->optionsStartMenuPalette);
    # else
    const u16 *selectedPalette = GetStartMenuPalette(0);
    # endif
    
    LoadPalette(selectedPalette, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
}