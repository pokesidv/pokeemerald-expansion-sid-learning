#include "option_menu.h"
#include "heat_select_menu.h"
#include "heat_menu_palettes.h"
#include "global.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_object_lock.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "field_weather.h"
#include "field_screen_effect.h"
#include "frontier_pass.h"
#include "frontier_util.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "item_menu.h"
#include "link.h"
#include "load_save.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "new_game.h"
#include "option_menu.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokenav.h"
#include "region_map.h"
#include "safari_zone.h"
#include "save.h"
#include "scanline_effect.h"
#include "script.h"
#include "sprite.h"
#include "sound.h"
#include "start_menu.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "time_waiting.h"
#include "trainer_card.h"
#include "window.h"
#include "union_room.h"
#include "constants/battle_frontier.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "rtc.h"
#include "fake_rtc.h"
#include "event_object_movement.h"
#include "constants/layouts.h"
#include "gba/isagbprint.h"

// LOGIC AND STATE
static bool8 HSelM_AreThereRegisteredItems(void);
static u32 HSelM_HowManyRegisteredItems(void);
static bool8 HSelM_TopHasSprite(void);
static bool8 HSelM_LSectionState(void);
static bool8 HSelM_RSectionState(void);
static bool8 HSelM_SelectSectionState(void);
static bool8 HSelM_StartSectionState(void);

// NAVIGATION AND INPUT HANDLING
static void Task_HSelM_HandleMainInput(u8 taskId);
static void HSelM_Handle_ABUTTON(void);
static void HSelM_Handle_DPADDOWN(void);
static void HSelM_Handle_DPADUP(void);
static void HSelM_Handle_LBUTTON(void);
static void HSelM_Handle_RBUTTON(void);
static void HSelM_Handle_SELECTBUTTON(void);
static void HSelM_Handle_STARTBUTTON(void);

static void HSelM_DoCleanUpAndChangeCallback(MainCallback callback);

// BACKGROUND
static const u32 *HSelM_GetCurrentTilemap(void);
static void HSelM_LoadBackground(void);
static void HSelM_RefreshTilemap(void);

// SPRITES
static void HSelM_CreateSprites(void);
static void HSelM_UpdateSpritePalettes(void); // called in handle input as well for when we return from other screens and the sprite palettes could be blended with the OW?

// TEXT WINDOWS
static void HSelM_CreateTextWindows(void);
static const struct WindowTemplate *HSelM_GetTopWindowTemplate(void); // a different window is created depending on whether there are registered items or not or if we are in time picker mode
static void HSelM_UpdateTextWindows(void);
static void HSelM_UpdateTopTextWindow(void);
static void HSelM_UpdateLTextWindow(void);
static void HSelM_UpdateRTextWindow(void);
static void HSelM_UpdateSelectTextWindow(void);
static void HSelM_UpdateStartTextWindow(void);
static void HSelM_PrintCenteredStringVar4(u8, u32, u16);
static void HSelM_PrintCenteredStringVar4Background(u8, u32, u16, bool8);

// EXIT AND CLEANUP
static void HSelM_ExitAndCleanup(void);
static void HSelM_CleanupTextWindow(u32 windowId);
static void HSelM_CleanupSprites(void);
static void HSelM_CleanupSprite(struct Sprite *sprite);


// the menu has a top section that shows the registered items if there is any, and below it there are L, R, Select, and Start buttons
// in time picker mode, the top section shows a prompt to pick a time of day, and the L, R, Select, and Start buttons set the time to morning, day, evening, and night respectively

// in main mode, the L, R, SELECT, and START buttons are mapped to different menu options
// in time picker mode, they are mapped to changing the time to a specific time of day if it's different than the current time of day
enum SELECT_MENU_MODES
{
  HSELM_MODE_MAIN,
  HSELM_MODE_TIME_PICKER,
  HSELM_MODE_COUNT,
};

// /* STRUCTs */
struct HeatSelectMenu
{
    MainCallback savedCallback; // The callback to return to when exiting the menu
    u32 loadState;              // used to initiate a fade before performing a menu action
    u32 sTopTextWindowId;       // window ID for the top box
    u32 sLTextWindowId;      // window ID for the left box
    u32 sRTextWindowId;     // window ID for the right box
    u32 sSelectTextWindowId;    // window ID for the select box
    u32 sStartTextWindowId;     // window ID for the start box

    u32 mode; // current menu mode (main or time picker)
    u32 registeredItemIndex; // current registered item index, the user can cycle through them if there are multiple registered items with the horizontal D-pad buttons

    // sprite IDs to access them in various functions
    u32 spriteIdRegisteredKeyItem;
    u32 spriteIdLeft;
    u32 spriteIdRight;
    u32 spriteIdSelect;
    u32 spriteIdStart;
};

static EWRAM_DATA struct HeatSelectMenu *sHeatSelectMenu = NULL;


///// ======================================================================================================================================
///// ============== Logic and state initialization ========================================================================================
///// ======================================================================================================================================

void HeatSelectMenu_Init(void)
{
    if (!IsOverworldLinkActive())
    {
        FreezeObjectEvents();
        PlayerFreeze();
        StopPlayerAvatar();
    }

    LockPlayerFieldControls();

    if (sHeatSelectMenu == NULL)
    {
        sHeatSelectMenu = AllocZeroed(sizeof(struct HeatSelectMenu));
    }

    if (sHeatSelectMenu == NULL)
    {
        SetMainCallback2(CB2_ReturnToFieldWithOpenSelectMenu);
        return;
    }

    sHeatSelectMenu->savedCallback = CB2_ReturnToFieldWithOpenSelectMenu;
    sHeatSelectMenu->loadState = 0;
    sHeatSelectMenu->mode = HSELM_MODE_MAIN;
    sHeatSelectMenu->registeredItemIndex = 0;
    sHeatSelectMenu->spriteIdRegisteredKeyItem = SPRITE_NONE;
    sHeatSelectMenu->spriteIdLeft = SPRITE_NONE;
    sHeatSelectMenu->spriteIdRight = SPRITE_NONE;
    sHeatSelectMenu->spriteIdSelect = SPRITE_NONE;
    sHeatSelectMenu->spriteIdStart = SPRITE_NONE;
    sHeatSelectMenu->sTopTextWindowId = 0;
    sHeatSelectMenu->sLTextWindowId = 0;
    sHeatSelectMenu->sRTextWindowId = 0;
    sHeatSelectMenu->sSelectTextWindowId = 0;
    sHeatSelectMenu->sStartTextWindowId = 0;
    HSelM_CreateSprites();
    HSelM_LoadBackground();
    HSelM_CreateTextWindows();
    HSelM_UpdateTextWindows();
    CreateTask(Task_HSelM_HandleMainInput, 0);
}

bool8 HSelM_AreThereRegisteredItems(void)
{
    return FALSE;
}
u32 HSelM_HowManyRegisteredItems(void)
{
    return 0;
}
bool8 HSelM_TopHasSprite(void){
    return sHeatSelectMenu->mode == HSELM_MODE_MAIN && HSelM_AreThereRegisteredItems();
}
bool8 HSelM_LSectionState(void)
{
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, L button sets time to morning if it's not already morning
        enum TimeOfDay timeOfDay = AccurateTimeOfDay();
        return timeOfDay != TIME_MORNING; // if it's already morning, don't highlight the button
    }
    else
    {
        // TODO: implement L button state in main mode
        return FALSE;
    }
}
bool8 HSelM_RSectionState(void){
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, L button sets time to day if it's not already day
        enum TimeOfDay timeOfDay = AccurateTimeOfDay();
        return timeOfDay != TIME_DAY; // if it's already day, don't highlight the button
    }
    else
    {
        // TODO: implement R button state in main mode
        return FALSE;
    }
}
bool8 HSelM_SelectSectionState(void){
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, L button sets time to evening if it's not already evening
        enum TimeOfDay timeOfDay = AccurateTimeOfDay();
        return timeOfDay != TIME_EVENING; // if it's already evening, don't highlight the button
    }
    else
    {
        // TODO: implement Select button state in main mode
        return FALSE;
    }
}
bool8 HSelM_StartSectionState(void){
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, L button sets time to night if it's not already night
        enum TimeOfDay timeOfDay = AccurateTimeOfDay();
        return timeOfDay != TIME_NIGHT; // if it's already night, don't highlight the button
    }
    else
    {
        // TODO: implement Start button state in main mode
        return TRUE;
    }
}

///// ======================================================================================================================================
///// ============ navigation and input handling ===========================================================================================
///// ======================================================================================================================================

static void Task_HSelM_HandleMainInput(u8 taskId)
{
    if (sHeatSelectMenu->loadState == 0 && !gPaletteFade.active)
    {
        HSelM_UpdateSpritePalettes();
    }

    // no need to update text windows here to refresh every tick. only update texts when we perform actions that make them change

    if (sHeatSelectMenu->loadState == 1)
    {
        // HSelM_OpenMenu(); // TODO (vi): this remains from the start menu where pressing A just sets the loadState to 1 and waits for the next handleMainInput to notice it and open the selected menu, idk why we can't just trigger the appropriate action right away
    }
    else if (sHeatSelectMenu->loadState != 0)
    {
        return;
    }
    else if (JOY_NEW(A_BUTTON))
    {
        HSelM_Handle_ABUTTON();
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        HSelM_Handle_DPADDOWN();
    }
    else if (JOY_NEW(DPAD_UP))
    {
        HSelM_Handle_DPADUP();
    }
    else if (JOY_NEW(L_BUTTON))
    {
        HSelM_Handle_LBUTTON();
    }
    else if (JOY_NEW(R_BUTTON))
    {
        HSelM_Handle_RBUTTON();
    }
    else if (JOY_NEW(SELECT_BUTTON))
    {
        HSelM_Handle_SELECTBUTTON();
    }
    else if (JOY_NEW(START_BUTTON))
    {
        HSelM_Handle_STARTBUTTON();
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        HSelM_ExitAndCleanup();
        DestroyTask(taskId);
    }
}

static void HSelM_Handle_DPADDOWN(void)
{
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, DPAD does nothing
        return;
    }
    u32 n = HSelM_HowManyRegisteredItems();
    if (n == 0)
    {
        sHeatSelectMenu->registeredItemIndex = 0;
        return;
    }
    PlaySE(SE_SELECT);
    sHeatSelectMenu->registeredItemIndex++;
    if (sHeatSelectMenu->registeredItemIndex >= n)
    {
        sHeatSelectMenu->registeredItemIndex = 0;
    }

    HSelM_UpdateTextWindows();
}
static void HSelM_Handle_DPADUP(void)
{
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, DPAD does nothing
        return;
    }
    u32 n = HSelM_HowManyRegisteredItems();
    if (n == 0)
    {
        sHeatSelectMenu->registeredItemIndex = 0;
        return;
    }
    PlaySE(SE_SELECT);
    sHeatSelectMenu->registeredItemIndex--;
    if (sHeatSelectMenu->registeredItemIndex <= 0)
    {
        sHeatSelectMenu->registeredItemIndex = n-1;
    }
}
static void HSelM_Handle_ABUTTON(void)
{
    if(sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, A button does nothing
        return;
    }
    u32 n = HSelM_HowManyRegisteredItems();
    if (n == 0)
    {
        sHeatSelectMenu->registeredItemIndex = 0;
        return;
    }
    PlaySE(SE_SELECT);
    // TODO (vi): implement using the registered item
}
static void HSelM_Handle_LBUTTON(void){
    // implement
}
static void HSelM_Handle_RBUTTON(void){
    // implement
}
static void HSelM_Handle_SELECTBUTTON(void){
    // implement
}
static void HSelM_Handle_STARTBUTTON(void){
    // implement
}

// used by some of the menu options to exit the select menu and either return to field or start that menu option
static void HSelM_DoCleanUpAndChangeCallback(MainCallback callback)
{
  if (!gPaletteFade.active)
  {
    DestroyTask(FindTaskIdByFunc(Task_HSelM_HandleMainInput));
    PlayRainStoppingSoundEffect();
    HSelM_ExitAndCleanup();
    CleanupOverworldWindowsAndTilemaps();
    SetMainCallback2(callback);
    gMain.savedCallback = CB2_ReturnToFieldWithOpenSelectMenu;
  }
}
   
///// ======================================================================================================================================
///// ============== BACKGROUND ============================================================================================================
///// ======================================================================================================================================

// tiles 
static const u32 sHSelMTiles[] = INCBIN_U32("graphics/heat_select_menu/qol_menu_tiles.4bpp.lz"); 

// tilemaps for every possible state of top, L, R, Select, and Start boxes (on/off for each of them so 32 total, encoded as 5 bits)
// we will swap the tilemap based on which boxes are toggled on or off 
static const u32 sHSelMTilemap00000[] = INCBIN_U32("graphics/heat_select_menu/cselm_00000.bin.lz");
static const u32 sHSelMTilemap00001[] = INCBIN_U32("graphics/heat_select_menu/cselm_00001.bin.lz");
static const u32 sHSelMTilemap00010[] = INCBIN_U32("graphics/heat_select_menu/cselm_00010.bin.lz");
static const u32 sHSelMTilemap00011[] = INCBIN_U32("graphics/heat_select_menu/cselm_00011.bin.lz");
static const u32 sHSelMTilemap00100[] = INCBIN_U32("graphics/heat_select_menu/cselm_00100.bin.lz");
static const u32 sHSelMTilemap00101[] = INCBIN_U32("graphics/heat_select_menu/cselm_00101.bin.lz");
static const u32 sHSelMTilemap00110[] = INCBIN_U32("graphics/heat_select_menu/cselm_00110.bin.lz");
static const u32 sHSelMTilemap00111[] = INCBIN_U32("graphics/heat_select_menu/cselm_00111.bin.lz");
static const u32 sHSelMTilemap01000[] = INCBIN_U32("graphics/heat_select_menu/cselm_01000.bin.lz");
static const u32 sHSelMTilemap01001[] = INCBIN_U32("graphics/heat_select_menu/cselm_01001.bin.lz");
static const u32 sHSelMTilemap01010[] = INCBIN_U32("graphics/heat_select_menu/cselm_01010.bin.lz");
static const u32 sHSelMTilemap01011[] = INCBIN_U32("graphics/heat_select_menu/cselm_01011.bin.lz");
static const u32 sHSelMTilemap01100[] = INCBIN_U32("graphics/heat_select_menu/cselm_01100.bin.lz");
static const u32 sHSelMTilemap01101[] = INCBIN_U32("graphics/heat_select_menu/cselm_01101.bin.lz");
static const u32 sHSelMTilemap01110[] = INCBIN_U32("graphics/heat_select_menu/cselm_01110.bin.lz");
static const u32 sHSelMTilemap01111[] = INCBIN_U32("graphics/heat_select_menu/cselm_01111.bin.lz");
static const u32 sHSelMTilemap10000[] = INCBIN_U32("graphics/heat_select_menu/cselm_10000.bin.lz");
static const u32 sHSelMTilemap10001[] = INCBIN_U32("graphics/heat_select_menu/cselm_10001.bin.lz");
static const u32 sHSelMTilemap10010[] = INCBIN_U32("graphics/heat_select_menu/cselm_10010.bin.lz");
static const u32 sHSelMTilemap10011[] = INCBIN_U32("graphics/heat_select_menu/cselm_10011.bin.lz");
static const u32 sHSelMTilemap10100[] = INCBIN_U32("graphics/heat_select_menu/cselm_10100.bin.lz");
static const u32 sHSelMTilemap10101[] = INCBIN_U32("graphics/heat_select_menu/cselm_10101.bin.lz");
static const u32 sHSelMTilemap10110[] = INCBIN_U32("graphics/heat_select_menu/cselm_10110.bin.lz");
static const u32 sHSelMTilemap10111[] = INCBIN_U32("graphics/heat_select_menu/cselm_10111.bin.lz");
static const u32 sHSelMTilemap11000[] = INCBIN_U32("graphics/heat_select_menu/cselm_11000.bin.lz");
static const u32 sHSelMTilemap11001[] = INCBIN_U32("graphics/heat_select_menu/cselm_11001.bin.lz");
static const u32 sHSelMTilemap11010[] = INCBIN_U32("graphics/heat_select_menu/cselm_11010.bin.lz");
static const u32 sHSelMTilemap11011[] = INCBIN_U32("graphics/heat_select_menu/cselm_11011.bin.lz");
static const u32 sHSelMTilemap11100[] = INCBIN_U32("graphics/heat_select_menu/cselm_11100.bin.lz");
static const u32 sHSelMTilemap11101[] = INCBIN_U32("graphics/heat_select_menu/cselm_11101.bin.lz");
static const u32 sHSelMTilemap11110[] = INCBIN_U32("graphics/heat_select_menu/cselm_11110.bin.lz");
static const u32 sHSelMTilemap11111[] = INCBIN_U32("graphics/heat_select_menu/cselm_11111.bin.lz");

// Array of all 32 tilemaps indexed by the 5-bit state combination
static const u32 *const sHSelMTilemaps[32] = {
    sHSelMTilemap00000, sHSelMTilemap00001, sHSelMTilemap00010, sHSelMTilemap00011,
    sHSelMTilemap00100, sHSelMTilemap00101, sHSelMTilemap00110, sHSelMTilemap00111,
    sHSelMTilemap01000, sHSelMTilemap01001, sHSelMTilemap01010, sHSelMTilemap01011,
    sHSelMTilemap01100, sHSelMTilemap01101, sHSelMTilemap01110, sHSelMTilemap01111,
    sHSelMTilemap10000, sHSelMTilemap10001, sHSelMTilemap10010, sHSelMTilemap10011,
    sHSelMTilemap10100, sHSelMTilemap10101, sHSelMTilemap10110, sHSelMTilemap10111,
    sHSelMTilemap11000, sHSelMTilemap11001, sHSelMTilemap11010, sHSelMTilemap11011,
    sHSelMTilemap11100, sHSelMTilemap11101, sHSelMTilemap11110, sHSelMTilemap11111,
};

// Helper to get the correct tilemap based on current states
static const u32 *HSelM_GetCurrentTilemap(void)
{
    u8 stateIndex = 0;
    
    if (HSelM_TopHasSprite())      stateIndex |= (1 << 4);  // bit 4 for top
    if (HSelM_LSectionState())     stateIndex |= (1 << 3);  // bit 3 for L
    if (HSelM_RSectionState())     stateIndex |= (1 << 2);  // bit 2 for R  
    if (HSelM_SelectSectionState()) stateIndex |= (1 << 1); // bit 1 for Select
    if (HSelM_StartSectionState())  stateIndex |= (1 << 0); // bit 0 for Start
    
    return sHSelMTilemaps[stateIndex];
}

static void HSelM_LoadBackground(void)
{
    u8 *buf = GetBgTilemapBuffer(0);
    LoadBgTilemap(0, 0, 0, 0);
    DecompressAndCopyTileDataToVram(0, sHSelMTiles, 0, 0, 0); // Keep as sHSelMTiles (u32)

    DecompressDataWithHeaderWram(HSelM_GetCurrentTilemap(), buf);

    HeatMenus_LoadPalettes();

    ScheduleBgCopyTilemapToVram(0);
}

static void HSelM_RefreshTilemap(void)
{
    u8 *buf = GetBgTilemapBuffer(0);
    DecompressDataWithHeaderWram(HSelM_GetCurrentTilemap(), buf);
    ScheduleBgCopyTilemapToVram(0);
}

///// =====================================================================================================================================
///// ============== SPRITES ==============================================================================================================
///// =====================================================================================================================================

// #define HSELM_TAG_ICON_GFX 1234
// #define HSELM_TAG_ICON_PAL 0x4654

// TODO (vi): every sprite will have its own function to source the right sprite (some are item sprites, some we have to provide our own version of, etc.)

static void HSelM_CreateSprites(void)
{
    // TODO (vi): do whatever to create the sprites of the top slot, left, right, select, start slots and the same for the time picking mode
    //     sHeatStartMenu->spriteIdPokedex = CreateSprite(&gSpriteIconPokedex, x, y, 0);
}

static void HSelM_UpdateSpritePalettes(void)
{
    // u32 index;
    // //   LoadSpritePalette(sSpritePal_Icon);
    // index = IndexOfSpritePaletteTag(TAG_ICON_PAL);
    // LoadPalette(sIconPal, OBJ_PLTT_ID(index), PLTT_SIZE_4BPP);
}

////// =====================================================================================================================================
////// ================== TEXT WINDOWS =====================================================================================================
////// =====================================================================================================================================

static const struct WindowTemplate sWindowTemplate_L = {
    .bg = 0,
    .tilemapLeft = 5,
    .tilemapTop = 7,
    .width = 4,
    .height = 2,
    .paletteNum = 14, // palette 14 as it's on top of the menu BG not inside a white box like the top text window
    .baseBlock = 0x30};

static const struct WindowTemplate sWindowTemplate_R = {
    .bg = 0,
    .tilemapLeft = 25,
    .tilemapTop = 7,
    .width = 4,
    .height = 2,
    .paletteNum = 14,
    .baseBlock = 0x30 + (4 * 2 * 1)};

static const struct WindowTemplate sWindowTemplate_Select = {
    .bg = 0,
    .tilemapLeft = 7,
    .tilemapTop = 14,
    .width = 4,
    .height = 2,
    .paletteNum = 14,
    .baseBlock = 0x30 + (4 * 2 * 2)};

static const struct WindowTemplate sWindowTemplate_Start = {
    .bg = 0,
    .tilemapLeft = 23,
    .tilemapTop = 14,
    .width = 4,
    .height = 2,
    .paletteNum = 14,
    .baseBlock = 0x30 + (4 * 2 * 3)};

static const struct WindowTemplate sWindowTemplate_TopItems = {
    .bg = 0,
    .tilemapLeft = 9,
    .tilemapTop = 1,
    .width = 12,
    .height = 2,
    .paletteNum = 15, // the top section has a white box around this text window so we use the standard text palette
    .baseBlock = 0x30 + (4 * 2 * 4)};
static const struct WindowTemplate sWindowTemplate_TopEmpty = {
    .bg = 0,
    .tilemapLeft = 7,
    .tilemapTop = 1,
    .width = 16,
    .height = 2,
    .paletteNum = 15, 
    .baseBlock = 0x30 + (4 * 2 * 4)};

static void HSelM_CreateTextWindows(void)
{
    sHeatSelectMenu->sTopTextWindowId = AddWindow(HSelM_GetTopWindowTemplate()); // this is its own method because we need to update the window template depending on whether there are registered items or not or if we are in time picker mode
    sHeatSelectMenu->sLTextWindowId = AddWindow(&sWindowTemplate_L);
    sHeatSelectMenu->sRTextWindowId = AddWindow(&sWindowTemplate_R);
    sHeatSelectMenu->sSelectTextWindowId = AddWindow(&sWindowTemplate_Select);
    sHeatSelectMenu->sStartTextWindowId = AddWindow(&sWindowTemplate_Start);
}

static void HSelM_UpdateTextWindows(void)
{
    HSelM_UpdateTopTextWindow();
    HSelM_UpdateLTextWindow();
    HSelM_UpdateRTextWindow();
    HSelM_UpdateSelectTextWindow();
    HSelM_UpdateStartTextWindow();
}

// Return pointer to the correct top-window template based on current state.
// Returning a pointer avoids copying the struct and matches AddWindow's parameter.
static const struct WindowTemplate *HSelM_GetTopWindowTemplate(void)
{
    if (HSelM_TopHasSprite())
        return &sWindowTemplate_TopItems;
    return &sWindowTemplate_TopEmpty;
}

// helpers to clean windows before printing onto them
// white windows use the standard text palette (slot 15)
static void HSelM_CleanWhiteWindow(u32 windowId)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_WHITE));
    PutWindowTilemap(windowId);
}

// background windows use palette 14, the same as the menu background
static void HSelM_CleanBackgroundWindow(u32 windowId, bool8 state)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(state ? 6 : 2)); // darker gray background
    PutWindowTilemap(windowId);
}

// Helpers: center gStringVar4 in a window and print it.
// windowId    - window to print into
// fontId      - font enum (e.g. FONT_SMALL, FONT_NORMAL)
// windowTiles - width in tiles
static void HSelM_PrintCenteredStringVar4(u8 windowId, u32 fontId, u16 windowTiles)
{
    u8 x = GetStringCenterAlignXOffset(fontId, gStringVar4, windowTiles * 8);
    AddTextPrinterParameterized(windowId, fontId, gStringVar4, x, 0, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static void HSelM_PrintCenteredStringVar4Background(u8 windowId, u32 fontId, u16 windowTiles, bool8 state)
{
    u8 color[3];
    if(state){
        color[0] = 6; // bg
        color[1] = 5; // fg
        color[2] = 6; // shadow
    } else {
        color[0] = 2; // bg
        color[1] = 1; // fg
        color[2] = 2; // shadow
    }
    u8 x = GetStringCenterAlignXOffset(fontId, gStringVar4, windowTiles * 8);
    AddTextPrinterParameterized4(windowId, fontId, x, 0, 0, 0, color, TEXT_SKIP_DRAW, gStringVar4);
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

// TODO (vi): real registered item names
static const u8 gText_Friday[]    = _("Bicycleeee");
static const u8 gText_SelectedItem[] = _("{STR_VAR_3}");
static void HSelM_UpdateTopTextWindow(void)
{
    HSelM_CleanWhiteWindow(sHeatSelectMenu->sTopTextWindowId);
    
    // placeholder code for now
    StringCopy(gStringVar3, gText_Friday); // TODO (vi): replace with the name of the registered item at index sHeatSelectMenu->registeredItemIndex
    StringExpandPlaceholders(gStringVar4, gText_Friday);
    
    HSelM_PrintCenteredStringVar4(sHeatSelectMenu->sTopTextWindowId, FONT_SMALL, HSelM_GetTopWindowTemplate()->width);
}

// TODO (vi): real L text
static const u8 gText_On[]    = _("On");
static const u8 gText_Off[]    = _("Off");
static const u8 gText_L[] = _("{STR_VAR_3}");
static const u8 gText_WaitTime_Morning[] = _("Morning");
static void HSelM_UpdateLTextWindow(void)
{
    bool8 state = HSelM_LSectionState();

    HSelM_CleanBackgroundWindow(sHeatSelectMenu->sLTextWindowId, state);
    
    // placeholder code for now
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        StringExpandPlaceholders(gStringVar4, gText_WaitTime_Morning);
    }
    else
    {
        StringCopy(gStringVar3, state? gText_On : gText_Off); // TODO (vi): replace with pokevial dose count
        StringExpandPlaceholders(gStringVar4, gText_L);
    }
    

    HSelM_PrintCenteredStringVar4Background(sHeatSelectMenu->sLTextWindowId, FONT_SMALL, sWindowTemplate_L.width, state);
}

static const u8 gText_Wait[] = _("Wait");
static const u8 gText_WaitTime_Day[] = _("Day");
static void HSelM_UpdateRTextWindow(void)
{
    bool8 state = HSelM_RSectionState();

    HSelM_CleanBackgroundWindow(sHeatSelectMenu->sRTextWindowId, state);

    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        StringExpandPlaceholders(gStringVar4, gText_WaitTime_Day);
    }
    else
    {
        StringExpandPlaceholders(gStringVar4, gText_Wait);
    }
    

    HSelM_PrintCenteredStringVar4Background(sHeatSelectMenu->sRTextWindowId, FONT_SMALL, sWindowTemplate_R.width, state);
}

static const u8 gText_WaitTime_Evening[] = _("Evening");
static void HSelM_UpdateSelectTextWindow(void)
{
    bool8 state = HSelM_SelectSectionState();

    HSelM_CleanBackgroundWindow(sHeatSelectMenu->sSelectTextWindowId, state);

    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        StringExpandPlaceholders(gStringVar4, gText_WaitTime_Evening);
    }
    else
    {
        StringExpandPlaceholders(gStringVar4, state? gText_On : gText_Off);
    }

    HSelM_PrintCenteredStringVar4Background(sHeatSelectMenu->sSelectTextWindowId, FONT_SMALL, sWindowTemplate_Select.width, state);
}

static const u8 gText_WaitTime_Night[] = _("Night");
static void HSelM_UpdateStartTextWindow(void)
{
    bool8 state = HSelM_StartSectionState();
    
    HSelM_CleanBackgroundWindow(sHeatSelectMenu->sStartTextWindowId, state);
    
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        StringExpandPlaceholders(gStringVar4, gText_WaitTime_Night);
    }
    else
    {
        StringExpandPlaceholders(gStringVar4, state? gText_On : gText_Off);
    }

    HSelM_PrintCenteredStringVar4Background(sHeatSelectMenu->sStartTextWindowId, FONT_SMALL, sWindowTemplate_Start.width, state);
}

/////// =================================================================================
/////// ============ EXIT AND CLEANUP ===================================================
/////// =================================================================================

static void HSelM_ExitAndCleanup(void)
{
    u32 i;
    u8 *buf = GetBgTilemapBuffer(0);

    // remove text windows
    HSelM_CleanupTextWindow(sHeatSelectMenu->sTopTextWindowId);
    HSelM_CleanupTextWindow(sHeatSelectMenu->sLTextWindowId);
    HSelM_CleanupTextWindow(sHeatSelectMenu->sRTextWindowId);
    HSelM_CleanupTextWindow(sHeatSelectMenu->sSelectTextWindowId);
    HSelM_CleanupTextWindow(sHeatSelectMenu->sStartTextWindowId);

    // clear tilemap
    for (i = 0; i < 2048; i++)
    {
        buf[i] = 0;
    }
    ScheduleBgCopyTilemapToVram(0);

    HSelM_CleanupSprites();

    // finishing touches
    if (sHeatSelectMenu != NULL)
    {
        // FreeSpriteTilesByTag(HSELM_TAG_ICON_GFX);
        Free(sHeatSelectMenu);
        sHeatSelectMenu = NULL;
    }

    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
}

static void HSelM_CleanupTextWindow(u32 windowId)
{
  FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
  ClearWindowTilemap(windowId);
  CopyWindowToVram(windowId, COPYWIN_GFX);
  RemoveWindow(windowId);
}

static void HSelM_CleanupSprites(void)
{
  if (sHeatSelectMenu->spriteIdRegisteredKeyItem != SPRITE_NONE)
  {
    HSelM_CleanupSprite(&gSprites[sHeatSelectMenu->spriteIdRegisteredKeyItem]);
    sHeatSelectMenu->spriteIdRegisteredKeyItem = SPRITE_NONE;
  }
  if (sHeatSelectMenu->spriteIdLeft != SPRITE_NONE)
  {
    HSelM_CleanupSprite(&gSprites[sHeatSelectMenu->spriteIdLeft]);
    sHeatSelectMenu->spriteIdLeft = SPRITE_NONE;
  }
  if (sHeatSelectMenu->spriteIdRight != SPRITE_NONE)
  {
    HSelM_CleanupSprite(&gSprites[sHeatSelectMenu->spriteIdRight]);
    sHeatSelectMenu->spriteIdRight = SPRITE_NONE;
  }
  if (sHeatSelectMenu->spriteIdSelect != SPRITE_NONE)
  {
    HSelM_CleanupSprite(&gSprites[sHeatSelectMenu->spriteIdSelect]);
    sHeatSelectMenu->spriteIdSelect = SPRITE_NONE;
  }
  if (sHeatSelectMenu->spriteIdStart != SPRITE_NONE)
  {
    HSelM_CleanupSprite(&gSprites[sHeatSelectMenu->spriteIdStart]);
    sHeatSelectMenu->spriteIdStart = SPRITE_NONE;
  }
}

static void HSelM_CleanupSprite(struct Sprite *sprite)
{
  FreeSpriteOamMatrix(sprite);
  DestroySprite(sprite);
}