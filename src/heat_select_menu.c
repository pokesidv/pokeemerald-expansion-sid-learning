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
#include "io_reg.h"
#include "event_scripts.h"
#include "tv.h"
#include "fieldmap.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "field_weather.h"
#include "field_screen_effect.h"
#include "frontier_pass.h"
#include "item_icon.h"
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
#include "config/heat_menus.h"
#include "config/save.h"


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
static void HSelM_RefreshUI(void);
static void HSelM_Handle_ABUTTON(u8 taskId);
static void HSelM_Handle_DPADDOWN(u8 taskId);
static void HSelM_Handle_DPADUP(u8 taskId);
static void HSelM_Handle_LBUTTON(u8 taskId);
static void HSelM_Handle_RBUTTON(u8 taskId);
static void HSelM_Handle_SELECTBUTTON(u8 taskId);
static void HSelM_Handle_STARTBUTTON(u8 taskId);

// BACKGROUND
static const u32 *HSelM_GetCurrentTilemap(void);
static void HSelM_LoadBackground(void);
static void HSelM_RefreshTilemap(void);

// SPRITES
static bool32 HSelM_ShouldHandleFlash(void);
static void HSelM_LoadTimeIconPalette(u16 tag);
static u32 HSelM_AddTimeIcon(u16 tag, const struct SpriteTemplate *spriteTemplate);
static void HSelM_PrintItemIconParametrized(u16 itemId, bool32 flash);
static void HSelM_PrintStartIconParametrized(bool32 flash);
static void HSelM_PrintSelectIconParametrized(bool32 flash);
static void HSelM_PrintLeftIconParametrized(bool32 flash);
static void HSelM_PrintRightIconParametrized(bool32 flash);
static void HSelM_PrintItemIcon(u16 itemId);
static void HSelM_PrintStartIcon(void);
static void HSelM_PrintSelectIcon(void);
static void HSelM_PrintLeftIcon(void);
static void HSelM_PrintRightIcon(void);
static void HSelM_CreateSprites(void);

// TEXT WINDOWS
static void HSelM_CreateTextWindows(void);
static const struct WindowTemplate *HSelM_GetTopWindowTemplate(void); // a different window is created depending on whether there are registered items or not or if we are in time picker mode
static void HSelM_UpdateTopTextWindow(void);
static void HSelM_UpdateLTextWindow(void);
static void HSelM_UpdateRTextWindow(void);
static void HSelM_UpdateSelectTextWindow(void);
static void HSelM_UpdateStartTextWindow(void);
static void HSelM_PrintCenteredStringVar4(u8, u32, u16);
static void HSelM_PrintCenteredStringVar4Background(u8, u32, u16, bool8);

// EXIT AND CLEANUP
static void HSelM_ExitAndCleanup(bool32 unfreeze);
static void HSelM_CleanupTextWindow(u32 windowId);
static void HSelM_CleanupSprites(void);
static void HSelM_RemoveItemIcon(void);
static void HSelM_RemoveStartIcon(void);
static void HSelM_RemoveSelectIcon(void);
static void HSelM_RemoveLeftIcon(void);
static void HSelM_RemoveRightIcon(void);

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

struct HeatSelectMenu
{
    MainCallback savedCallback; // The callback to return to when exiting the menu
    u32 inputDelay;              // input delay to prevent the button that opened the menu from being processed immediately
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
    // duplicate sprites to handle when we are in a dark cave and need to show them with a specific property enabled to make them visible
    u32 spriteIdRegisteredKeyItemFlash;
    u32 spriteIdLeftFlash;
    u32 spriteIdRightFlash;
    u32 spriteIdSelectFlash;
    u32 spriteIdStartFlash;
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
    sHeatSelectMenu->inputDelay = 1;
    sHeatSelectMenu->mode = HSELM_MODE_MAIN;
    #if ENABLE_MULTIPLE_REGISTERED_ITEMS
    sHeatSelectMenu->registeredItemIndex = gSaveBlock1Ptr->registeredItemLastSelected;
    #else 
    sHeatSelectMenu->registeredItemIndex = 0;
    #endif
    sHeatSelectMenu->spriteIdRegisteredKeyItem = SPRITE_NONE;
    sHeatSelectMenu->spriteIdLeft = SPRITE_NONE;
    sHeatSelectMenu->spriteIdRight = SPRITE_NONE;
    sHeatSelectMenu->spriteIdSelect = SPRITE_NONE;
    sHeatSelectMenu->spriteIdStart = SPRITE_NONE;
    sHeatSelectMenu->spriteIdRegisteredKeyItemFlash = SPRITE_NONE;
    sHeatSelectMenu->spriteIdLeftFlash = SPRITE_NONE;
    sHeatSelectMenu->spriteIdRightFlash = SPRITE_NONE;
    sHeatSelectMenu->spriteIdSelectFlash = SPRITE_NONE;
    sHeatSelectMenu->spriteIdStartFlash = SPRITE_NONE;
    sHeatSelectMenu->sTopTextWindowId = 0;
    sHeatSelectMenu->sLTextWindowId = 0;
    sHeatSelectMenu->sRTextWindowId = 0;
    sHeatSelectMenu->sSelectTextWindowId = 0;
    sHeatSelectMenu->sStartTextWindowId = 0;
    HSelM_LoadBackground();
    HSelM_CreateTextWindows();
    HSelM_CreateSprites();
    
    CreateTask(Task_HSelM_HandleMainInput, 0);
}

bool8 HSelM_AreThereRegisteredItems(void)
{
    #if ENABLE_MULTIPLE_REGISTERED_ITEMS
    // we assume that registeredItems is a compacted list, so if the first slot is empty, there are no registered items at all
    return gSaveBlock1Ptr->registeredItems[0].itemId != ITEM_NONE;
    #else
    return gSaveBlock1Ptr->registeredItem != ITEM_NONE;
    #endif
}
u32 HSelM_HowManyRegisteredItems(void)
{
    #if ENABLE_MULTIPLE_REGISTERED_ITEMS
    s8 i;
    for (i = 0; i < REGISTERED_ITEMS_MAX; i++)
    {
        if (gSaveBlock1Ptr->registeredItems[i].itemId == ITEM_NONE)
            return i;
    }
    return REGISTERED_ITEMS_MAX;
    #else 
    return gSaveBlock1Ptr->registeredItem == ITEM_NONE ? 0 : 1;
    #endif
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
        return TRUE; // TODO: read L button state
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
        return TRUE; // R activates time picking mode
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
        if(INFINITE_REPEL_FLAG > TEMP_FLAGS_END){
            return FlagGet(INFINITE_REPEL_FLAG);
        }
        return TRUE; // TODO: read SELECT button state if you don't use it for infinite repel toggling
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
        // only used if I_EXP_SHARE_FLAG is defined in config/item.h
        if(I_EXP_SHARE_FLAG > TEMP_FLAGS_END){
            return FlagGet(I_EXP_SHARE_FLAG);
        }
        return TRUE; // TODO: customize START button state if you don't use it for Exp. Share toggling
    }
}

///// ======================================================================================================================================
///// ============ navigation and input handling ===========================================================================================
///// ======================================================================================================================================

static void Task_HSelM_HandleMainInput(u8 taskId)
{
    // Handle input delay to prevent immediate processing of the button that opened the menu
    if (sHeatSelectMenu->inputDelay > 0)
    {
        sHeatSelectMenu->inputDelay--;
        return;
    }
    
    if (JOY_NEW(A_BUTTON))
    {
        HSelM_Handle_ABUTTON(taskId);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        HSelM_Handle_DPADDOWN(taskId);
    }
    else if (JOY_NEW(DPAD_UP))
    {
        HSelM_Handle_DPADUP(taskId);
    }
    else if (JOY_NEW(L_BUTTON))
    {
        HSelM_Handle_LBUTTON(taskId);
    }
    else if (JOY_NEW(R_BUTTON))
    {
        HSelM_Handle_RBUTTON(taskId);
    }
    else if (JOY_NEW(SELECT_BUTTON))
    {
        HSelM_Handle_SELECTBUTTON(taskId);
    }
    else if (JOY_NEW(START_BUTTON))
    {
        HSelM_Handle_STARTBUTTON(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        if(sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
        {
            sHeatSelectMenu->mode = HSELM_MODE_MAIN;
            HSelM_RefreshUI();
            return;
        }
        PlaySE(SE_SELECT);
        HSelM_ExitAndCleanup(TRUE);
        DestroyTask(taskId);
    }
}


static void HSelM_RefreshUI(void)
{
    // top gets destroyed and recreated because it can change size depending on whether there are registered items or not or if we are in time picker mode
    HSelM_CleanupTextWindow(sHeatSelectMenu->sTopTextWindowId);

    HSelM_RefreshTilemap();

    sHeatSelectMenu->sTopTextWindowId = AddWindow(HSelM_GetTopWindowTemplate());
    HSelM_UpdateTopTextWindow();

    HSelM_UpdateLTextWindow();
    HSelM_UpdateRTextWindow();
    HSelM_UpdateSelectTextWindow();
    HSelM_UpdateStartTextWindow();

    HSelM_CreateSprites();
}

static void Task_CloseAfterMessage(u8 taskId)
{
    if (JOY_NEW(A_BUTTON) || JOY_NEW(B_BUTTON))
    {
        ClearDialogWindowAndFrame(0, TRUE);
        DestroyTask(taskId);
        ScriptUnfreezeObjectEvents();
        UnlockPlayerFieldControls();
    }
}

static void HSelM_Handle_DPADDOWN(u8 taskId)
{
    #if ENABLE_MULTIPLE_REGISTERED_ITEMS
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, DPAD does nothing
        return;
    }
    u32 n = HSelM_HowManyRegisteredItems();
    if (n <= 1)
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
    // the tilemap doesn't change, and the size of the text window doesn't change, 
    // but the text in the top box does and the sprite in the top box does
    HSelM_CreateSprites();
    HSelM_UpdateTopTextWindow();
    #endif
}
static void HSelM_Handle_DPADUP(u8 taskId)
{
    #if ENABLE_MULTIPLE_REGISTERED_ITEMS
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        // in time picker mode, DPAD does nothing
        return;
    }
    u32 n = HSelM_HowManyRegisteredItems();
    if (n <= 1)
    {
        sHeatSelectMenu->registeredItemIndex = 0;
        return;
    }
    PlaySE(SE_SELECT);
    if (sHeatSelectMenu->registeredItemIndex <= 0)
    {
        sHeatSelectMenu->registeredItemIndex = n - 1;
    }
    else
    {
        sHeatSelectMenu->registeredItemIndex--;
    }
    // the tilemap doesn't change, and the size of the text window doesn't change, 
    // but the text in the top box does and the sprite in the top box does
    HSelM_CreateSprites();
    HSelM_UpdateTopTextWindow();
    #endif
}
static void HSelM_Handle_ABUTTON(u8 taskId)
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
    #if ENABLE_MULTIPLE_REGISTERED_ITEMS
    u8 index = sHeatSelectMenu->registeredItemIndex;
    #endif
    PlaySE(SE_SELECT);
    HSelM_ExitAndCleanup(TRUE);
    DestroyTask(taskId);
    #if ENABLE_MULTIPLE_REGISTERED_ITEMS
    UseRegisteredKeyItemOnField(index);
    #else
    UseRegisteredKeyItemOnField();
    #endif
}
static void HSelM_Handle_LBUTTON(u8 taskId){
    if(sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        #if OW_USE_FAKE_RTC
        if(AccurateTimeOfDay() == TIME_MORNING) return; // already morning, do nothing
        PlaySE(SE_SELECT);
        HSelM_ExitAndCleanup(TRUE);
        DestroyTask(taskId);
        WaitTillMorning();
        return;
        #else
        return; // RTC not enabled, can't wait until a time of day
        #endif
    } else {
        PlaySE(SE_SELECT);
        HSelM_ExitAndCleanup(TRUE);
        DestroyTask(taskId);
        // TODO: add functionality for L button in main mode
        return;
    }
}
static void HSelM_Handle_RBUTTON(u8 taskId){
    if(sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        #if OW_USE_FAKE_RTC
        if(AccurateTimeOfDay() == TIME_DAY) return; // already day, do nothing
        PlaySE(SE_SELECT);
        HSelM_ExitAndCleanup(TRUE);
        DestroyTask(taskId);
        WaitTillDay();
        return;
        #else
        return; // RTC not enabled, can't wait until a time of day
        #endif
    } else {
        PlaySE(SE_SELECT);
        sHeatSelectMenu->mode = HSELM_MODE_TIME_PICKER; 
        HSelM_RefreshUI();
    }
}

const u8 gText_RepelTurnedOn[] = _("Infinite Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}.\nYou're scaring wild Pokémon away!");
const u8 gText_RepelTurnedOff[] = _("Infinite Repel turned off.\nCatch 'em all!");
#define TOGGLE_INFINITE_REPEL_WITHOUT_EXITING FALSE
static void HSelM_Handle_SELECTBUTTON(u8 taskId){
    if(sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        #if OW_USE_FAKE_RTC
        if(AccurateTimeOfDay() == TIME_EVENING) return; // already evening, do nothing
        PlaySE(SE_SELECT);
        HSelM_ExitAndCleanup(TRUE);
        DestroyTask(taskId);
        WaitTillEvening();
        return;
        #else
        return; // RTC not enabled, can't wait until a time of day
        #endif
    } else {
        if (INFINITE_REPEL_FLAG > TEMP_FLAGS_END)
        {
            PlaySE(SE_SELECT);
            bool32 isTurningOn = !FlagGet(INFINITE_REPEL_FLAG);
            FlagToggle(INFINITE_REPEL_FLAG);
            #if TOGGLE_INFINITE_REPEL_WITHOUT_EXITING
            HSelM_RefreshUI();
            #else
            StringExpandPlaceholders(gStringVar4, isTurningOn ? gText_RepelTurnedOn : gText_RepelTurnedOff);
            HSelM_ExitAndCleanup(FALSE);
            DisplayItemMessageOnField(taskId, gStringVar4, Task_CloseAfterMessage);
            #endif
        }
        else
        {
            PlaySE(SE_SELECT);
            // TODO: customize functionality for select button in main mode if you're not using infinite repel toggle
            HSelM_ExitAndCleanup(TRUE);
            DestroyTask(taskId);
        }
        return;
    }
}


const u8 gText_ExpAllTurnedOn[] = _("Experience Share turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}.\nLevel up your whole team!");
const u8 gText_ExpAllTurnedOff[] = _("Experience Share turned off.\nTrain your favorite Pokémon!");
#define TOGGLE_EXP_ALL_WITHOUT_EXITING FALSE
static void HSelM_Handle_STARTBUTTON(u8 taskId){
    if(sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        #if OW_USE_FAKE_RTC
        if(AccurateTimeOfDay() == TIME_NIGHT) return; // already night, do nothing
        PlaySE(SE_SELECT);
        HSelM_ExitAndCleanup(TRUE);
        DestroyTask(taskId);
        WaitTillNight();
        return;
        #else
        return; // RTC not enabled, can't wait until a time of day
        #endif
    }
    else
    {
        if (I_EXP_SHARE_FLAG > TEMP_FLAGS_END)
        {
            PlaySE(SE_SELECT);
            bool32 isTurningOn = !FlagGet(I_EXP_SHARE_FLAG);
            FlagToggle(I_EXP_SHARE_FLAG);
            #if TOGGLE_EXP_ALL_WITHOUT_EXITING
            HSelM_RefreshUI();
            #else
            StringExpandPlaceholders(gStringVar4, isTurningOn ? gText_ExpAllTurnedOn : gText_ExpAllTurnedOff);
            HSelM_ExitAndCleanup(FALSE);
            DisplayItemMessageOnField(taskId, gStringVar4, Task_CloseAfterMessage);
            #endif
        }
        else
        {
            PlaySE(SE_SELECT);
            // TODO: customize functionality for START button in main mode if you don't want it to toggle Exp. Share
            HSelM_ExitAndCleanup(TRUE);
            DestroyTask(taskId);
        }
        return;
    }
}

   
///// ======================================================================================================================================
///// ============== BACKGROUND ============================================================================================================
///// ======================================================================================================================================

// tiles 
static const u32 sHSelMTiles[] = INCBIN_U32("graphics/heat_select_menu/qol_menu_tiles_2.4bpp.lz"); 

// tilemaps for every possible state of top, L, R, Select, and Start boxes (on/off for each of them so 32 total, encoded as 5 bits)
// we will swap the tilemap based on which boxes are toggled on or off 
static const u32 sHSelMTilemap00000[] = INCBIN_U32("graphics/heat_select_menu/hselm_00000.bin.lz");
static const u32 sHSelMTilemap00001[] = INCBIN_U32("graphics/heat_select_menu/hselm_00001.bin.lz");
static const u32 sHSelMTilemap00010[] = INCBIN_U32("graphics/heat_select_menu/hselm_00010.bin.lz");
static const u32 sHSelMTilemap00011[] = INCBIN_U32("graphics/heat_select_menu/hselm_00011.bin.lz");
static const u32 sHSelMTilemap00100[] = INCBIN_U32("graphics/heat_select_menu/hselm_00100.bin.lz");
static const u32 sHSelMTilemap00101[] = INCBIN_U32("graphics/heat_select_menu/hselm_00101.bin.lz");
static const u32 sHSelMTilemap00110[] = INCBIN_U32("graphics/heat_select_menu/hselm_00110.bin.lz");
static const u32 sHSelMTilemap00111[] = INCBIN_U32("graphics/heat_select_menu/hselm_00111.bin.lz");
static const u32 sHSelMTilemap01000[] = INCBIN_U32("graphics/heat_select_menu/hselm_01000.bin.lz");
static const u32 sHSelMTilemap01001[] = INCBIN_U32("graphics/heat_select_menu/hselm_01001.bin.lz");
static const u32 sHSelMTilemap01010[] = INCBIN_U32("graphics/heat_select_menu/hselm_01010.bin.lz");
static const u32 sHSelMTilemap01011[] = INCBIN_U32("graphics/heat_select_menu/hselm_01011.bin.lz");
static const u32 sHSelMTilemap01100[] = INCBIN_U32("graphics/heat_select_menu/hselm_01100.bin.lz");
static const u32 sHSelMTilemap01101[] = INCBIN_U32("graphics/heat_select_menu/hselm_01101.bin.lz");
static const u32 sHSelMTilemap01110[] = INCBIN_U32("graphics/heat_select_menu/hselm_01110.bin.lz");
static const u32 sHSelMTilemap01111[] = INCBIN_U32("graphics/heat_select_menu/hselm_01111.bin.lz");
static const u32 sHSelMTilemap10000[] = INCBIN_U32("graphics/heat_select_menu/hselm_10000.bin.lz");
static const u32 sHSelMTilemap10001[] = INCBIN_U32("graphics/heat_select_menu/hselm_10001.bin.lz");
static const u32 sHSelMTilemap10010[] = INCBIN_U32("graphics/heat_select_menu/hselm_10010.bin.lz");
static const u32 sHSelMTilemap10011[] = INCBIN_U32("graphics/heat_select_menu/hselm_10011.bin.lz");
static const u32 sHSelMTilemap10100[] = INCBIN_U32("graphics/heat_select_menu/hselm_10100.bin.lz");
static const u32 sHSelMTilemap10101[] = INCBIN_U32("graphics/heat_select_menu/hselm_10101.bin.lz");
static const u32 sHSelMTilemap10110[] = INCBIN_U32("graphics/heat_select_menu/hselm_10110.bin.lz");
static const u32 sHSelMTilemap10111[] = INCBIN_U32("graphics/heat_select_menu/hselm_10111.bin.lz");
static const u32 sHSelMTilemap11000[] = INCBIN_U32("graphics/heat_select_menu/hselm_11000.bin.lz");
static const u32 sHSelMTilemap11001[] = INCBIN_U32("graphics/heat_select_menu/hselm_11001.bin.lz");
static const u32 sHSelMTilemap11010[] = INCBIN_U32("graphics/heat_select_menu/hselm_11010.bin.lz");
static const u32 sHSelMTilemap11011[] = INCBIN_U32("graphics/heat_select_menu/hselm_11011.bin.lz");
static const u32 sHSelMTilemap11100[] = INCBIN_U32("graphics/heat_select_menu/hselm_11100.bin.lz");
static const u32 sHSelMTilemap11101[] = INCBIN_U32("graphics/heat_select_menu/hselm_11101.bin.lz");
static const u32 sHSelMTilemap11110[] = INCBIN_U32("graphics/heat_select_menu/hselm_11110.bin.lz");
static const u32 sHSelMTilemap11111[] = INCBIN_U32("graphics/heat_select_menu/hselm_11111.bin.lz");

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

static const u32 sTimeIconsGfx[] = INCBIN_U32("graphics/heat_select_menu/time_of_day_icons.4bpp.lz");
static const u16 sTimeIconsPal[] = INCBIN_U16("graphics/heat_select_menu/time_of_day_icons.gbapal");

// from 0x8000 onwards, sprite palette tags are ignored by the overworld day / night blend system, so we use those for our icons to avoid palette conflicts
// from 0x8001 to 0x8004 are already used by OBJ_EVENT_PAL_TAG_LIGHT and similar overworld sprites, so we avoid those as well
#define TAG_ITEM_ICON       0x8010
#define TAG_START_ICON      0x8011
#define TAG_SELECT_ICON     0x8012
#define TAG_LEFT_ICON       0x8013
#define TAG_RIGHT_ICON      0x8014

static const struct OamData gOamIcon = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const union AnimCmd gAnimCmdNight[] = {
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconNightAnim[] = {
    gAnimCmdNight,
};


static const union AnimCmd gAnimCmdMorning[] = {
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconMorningAnim[] = {
    gAnimCmdMorning,
};


static const union AnimCmd gAnimCmdDay[] = {
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconDayAnim[] = {
    gAnimCmdDay,
};


static const union AnimCmd gAnimCmdEvening[] = {
    ANIMCMD_FRAME(48, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconEveningAnim[] = {
    gAnimCmdEvening,
};


static const union AnimCmd gAnimCmdClock[] = {
    ANIMCMD_FRAME(64, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconClockAnim[] = {
    gAnimCmdClock,
};

static const struct SpriteTemplate gSpriteIconNight = {
    .tileTag = TAG_START_ICON,
    .paletteTag = TAG_START_ICON,
    .oam = &gOamIcon,
    .anims = gIconNightAnim,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
static const struct SpriteTemplate gSpriteIconMorning = {
    .tileTag = TAG_LEFT_ICON,
    .paletteTag = TAG_LEFT_ICON,
    .oam = &gOamIcon,
    .anims = gIconMorningAnim,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
static const struct SpriteTemplate gSpriteIconDay = {
    .tileTag = TAG_RIGHT_ICON,
    .paletteTag = TAG_RIGHT_ICON,
    .oam = &gOamIcon,
    .anims = gIconDayAnim,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
static const struct SpriteTemplate gSpriteIconEvening = {
    .tileTag = TAG_SELECT_ICON,
    .paletteTag = TAG_SELECT_ICON,
    .oam = &gOamIcon,
    .anims = gIconEveningAnim,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
static const struct SpriteTemplate gSpriteIconClock = {
    .tileTag = TAG_RIGHT_ICON,
    .paletteTag = TAG_RIGHT_ICON,
    .oam = &gOamIcon,
    .anims = gIconClockAnim,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static bool32 HSelM_ShouldHandleFlash(){
    return GetFlashLevel() > 0 || InBattlePyramid_();
}

static void HSelM_LoadTimeIconPalette(u16 tag)
{
    struct SpritePalette spritePalette;
    spritePalette.data = sTimeIconsPal;
    spritePalette.tag = tag;
    LoadSpritePalette(&spritePalette);
}

static u32 HSelM_AddTimeIcon(u16 tag, const struct SpriteTemplate *spriteTemplate)
{

    const struct CompressedSpriteSheet spriteSheet[] = {
        {sTimeIconsGfx, 32 * 160 / 2, tag},
        {NULL, 0, 0}
    };
    
    LoadCompressedSpriteSheet(spriteSheet);

    HSelM_LoadTimeIconPalette(tag);

    return CreateSprite(spriteTemplate, 0, 0, 0);
}

static void HSelM_PrintItemIconParametrized(u16 itemId, bool32 flash)
{
    u8 spriteId = MAX_SPRITES;
    u32* spriteIdLoc = flash ? &sHeatSelectMenu->spriteIdRegisteredKeyItemFlash : &sHeatSelectMenu->spriteIdRegisteredKeyItem;

    if (*spriteIdLoc == SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_ITEM_ICON);
        FreeSpritePaletteByTag(TAG_ITEM_ICON);
        spriteId = AddItemIconSprite(TAG_ITEM_ICON, TAG_ITEM_ICON, itemId);
        
        if (spriteId != MAX_SPRITES)
        {
            *spriteIdLoc = spriteId;
            gSprites[spriteId].oam.priority = 0;
            gSprites[spriteId].x2 = 2*8+4;
            gSprites[spriteId].y2 = 2*8+4;
            if(flash)
            {
                gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
            }
        }
    }
}

static void HSelM_PrintStartIconParametrized(bool32 flash)
{
    u8 spriteId = MAX_SPRITES;
    u32* spriteIdLoc = flash ? &sHeatSelectMenu->spriteIdStartFlash : &sHeatSelectMenu->spriteIdStart;

    if (*spriteIdLoc == SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_START_ICON);
        FreeSpritePaletteByTag(TAG_START_ICON);
        if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
        {
            spriteId = HSelM_AddTimeIcon(TAG_START_ICON, &gSpriteIconNight);
            if (spriteId != MAX_SPRITES)
            {
                *spriteIdLoc = spriteId;
                gSprites[spriteId].oam.priority = 0;
                gSprites[spriteId].x2 = 19 * 8;
                gSprites[spriteId].y2 = 15 * 8;
                if(flash)
                {
                    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
                }
            }
        }
        else
        {
            // TODO: customize start button sprite if you don't want it to be Exp. Share
            spriteId = AddItemIconSprite(TAG_START_ICON, TAG_START_ICON, ITEM_EXP_ALL);
            if (spriteId != MAX_SPRITES)
            {
                *spriteIdLoc = spriteId;
                gSprites[spriteId].oam.priority = 0;
                gSprites[spriteId].x2 = 19 * 8 + 4;
                gSprites[spriteId].y2 = 15 * 8 + 4;
                if(flash)
                {
                    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
                }
            }
        }
    }
}

static void HSelM_PrintSelectIconParametrized(bool32 flash)
{
    u8 spriteId = MAX_SPRITES;
    u32* spriteIdLoc = flash ? &sHeatSelectMenu->spriteIdSelectFlash : &sHeatSelectMenu->spriteIdSelect;

    if (*spriteIdLoc == SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_SELECT_ICON);
        FreeSpritePaletteByTag(TAG_SELECT_ICON);
        if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
        {
            spriteId = HSelM_AddTimeIcon(TAG_SELECT_ICON, &gSpriteIconEvening);
            if (spriteId != MAX_SPRITES)
            {
                *spriteIdLoc = spriteId;
                gSprites[spriteId].oam.priority = 0;
                gSprites[spriteId].x2 = 4 * 8;
                gSprites[spriteId].y2 = 15 * 8;
                if(flash)
                {
                    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
                }
            }
        }
        else
        {
            // TODO: add another sprite for your select button or implement infinite repel functionality to use this sprite
            spriteId = AddItemIconSprite(TAG_SELECT_ICON, TAG_SELECT_ICON, ITEM_REPEL);
            if (spriteId != MAX_SPRITES)
            {
                *spriteIdLoc = spriteId;
                gSprites[spriteId].oam.priority = 0;
                gSprites[spriteId].x2 = 4 * 8 + 4;
                gSprites[spriteId].y2 = 15 * 8 + 4;
                if(flash)
                {
                    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
                }
            }
        }
    }
}
static void HSelM_PrintLeftIconParametrized(bool32 flash)
{
    u8 spriteId = MAX_SPRITES;
    u32* spriteIdLoc = flash ? &sHeatSelectMenu->spriteIdLeftFlash : &sHeatSelectMenu->spriteIdLeft;

    if (*spriteIdLoc == SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_LEFT_ICON);
        FreeSpritePaletteByTag(TAG_LEFT_ICON);
        if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
        {
            spriteId = HSelM_AddTimeIcon(TAG_LEFT_ICON, &gSpriteIconMorning);
            if (spriteId != MAX_SPRITES)
            {
                *spriteIdLoc = spriteId;
                gSprites[spriteId].oam.priority = 0;
                gSprites[spriteId].x2 = 2 * 8;
                gSprites[spriteId].y2 = 8 * 8;
                if(flash)
                {
                    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
                }
            }
        }
        else
        {
            // TODO: customize left button sprite (and functionality in the other functions with a TODO note)
            spriteId = AddItemIconSprite(TAG_LEFT_ICON, TAG_LEFT_ICON, ITEM_PREMIER_BALL);
            if (spriteId != MAX_SPRITES)
            {
                *spriteIdLoc = spriteId;
                gSprites[spriteId].oam.priority = 0;
                gSprites[spriteId].x2 = 2 * 8 + 4;
                gSprites[spriteId].y2 = 8 * 8 + 4;
                if(flash)
                {
                    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
                }
            }
        }
    }
}
static void HSelM_PrintRightIconParametrized(bool32 flash)
{
    u8 spriteId = MAX_SPRITES;
    u32* spriteIdLoc = flash ? &sHeatSelectMenu->spriteIdRightFlash : &sHeatSelectMenu->spriteIdRight;

    if (*spriteIdLoc == SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_RIGHT_ICON);
        FreeSpritePaletteByTag(TAG_RIGHT_ICON);
        if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
        {
            spriteId = HSelM_AddTimeIcon(TAG_RIGHT_ICON, &gSpriteIconDay);
        }
        else
        {
            spriteId = HSelM_AddTimeIcon(TAG_RIGHT_ICON, &gSpriteIconClock);
        }
        if (spriteId != MAX_SPRITES)
        {
            *spriteIdLoc = spriteId;
            gSprites[spriteId].oam.priority = 0;
            gSprites[spriteId].x2 = 21 * 8;
            gSprites[spriteId].y2 = 8 * 8;
            if(flash)
            {
                gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
            }
        }
    }
}

static void HSelM_PrintItemIcon(u16 itemId)
{
    HSelM_PrintItemIconParametrized(itemId, FALSE);
    if(HSelM_ShouldHandleFlash())
    {
        HSelM_PrintItemIconParametrized(itemId, TRUE);
    }
}

static void HSelM_PrintStartIcon()
{
    HSelM_PrintStartIconParametrized(FALSE);
    if(HSelM_ShouldHandleFlash())
    {
        HSelM_PrintStartIconParametrized(TRUE);
    }
}

static void HSelM_PrintSelectIcon()
{
    HSelM_PrintSelectIconParametrized(FALSE);
    if(HSelM_ShouldHandleFlash())
    {
        HSelM_PrintSelectIconParametrized(TRUE);
    }
}

static void HSelM_PrintLeftIcon()
{
    HSelM_PrintLeftIconParametrized(FALSE);
    if(HSelM_ShouldHandleFlash())
    {
        HSelM_PrintLeftIconParametrized(TRUE);
    }
}

static void HSelM_PrintRightIcon()
{
    HSelM_PrintRightIconParametrized(FALSE);
    if(HSelM_ShouldHandleFlash())
    {
        HSelM_PrintRightIconParametrized(TRUE);
    }
}

static void HSelM_CreateSprites(void)
{
    if(HSelM_ShouldHandleFlash())
    {
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
        SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
    }
    HSelM_RemoveItemIcon();
    if (HSelM_AreThereRegisteredItems() && sHeatSelectMenu->mode == HSELM_MODE_MAIN)
    {
        #if ENABLE_MULTIPLE_REGISTERED_ITEMS
        u16 registeredItem = gSaveBlock1Ptr->registeredItems[sHeatSelectMenu->registeredItemIndex].itemId;
        #else
        u16 registeredItem = gSaveBlock1Ptr->registeredItem;
        #endif
        HSelM_PrintItemIcon(registeredItem);
    }
    HSelM_RemoveStartIcon();
    HSelM_PrintStartIcon();
    HSelM_RemoveSelectIcon();
    HSelM_PrintSelectIcon();
    HSelM_RemoveLeftIcon();
    HSelM_PrintLeftIcon();
    HSelM_RemoveRightIcon();
    HSelM_PrintRightIcon();
}

////// =====================================================================================================================================
////// ================== TEXT WINDOWS =====================================================================================================
////// =====================================================================================================================================

static const struct WindowTemplate sWindowTemplate_L = {
    .bg = 0,
    .tilemapLeft = 5,
    .tilemapTop = 7,
    .width = 5,
    .height = 2,
    .paletteNum = 14, // palette 14 as it's on top of the menu BG not inside a white box like the top text window
    .baseBlock = 0x30};

static const struct WindowTemplate sWindowTemplate_R = {
    .bg = 0,
    .tilemapLeft = 24,
    .tilemapTop = 7,
    .width = 5,
    .height = 2,
    .paletteNum = 14,
    .baseBlock = 0x30 + (5 * 2 * 1)};

static const struct WindowTemplate sWindowTemplate_Select = {
    .bg = 0,
    .tilemapLeft = 7,
    .tilemapTop = 14,
    .width = 5,
    .height = 2,
    .paletteNum = 14,
    .baseBlock = 0x30 + (5 * 2 * 2)};

static const struct WindowTemplate sWindowTemplate_Start = {
    .bg = 0,
    .tilemapLeft = 22,
    .tilemapTop = 14,
    .width = 5,
    .height = 2,
    .paletteNum = 14,
    .baseBlock = 0x30 + (5 * 2 * 3)};

static const struct WindowTemplate sWindowTemplate_TopItems = {
    .bg = 0,
    .tilemapLeft = 8,
    .tilemapTop = 1,
    .width = 14,
    .height = 2,
    .paletteNum = 15, // the top section has a white box around this text window so we use the standard text palette
    .baseBlock = 0x30 + (5 * 2 * 4)};
static const struct WindowTemplate sWindowTemplate_TopEmpty = {
    .bg = 0,
    .tilemapLeft = 7,
    .tilemapTop = 1,
    .width = 16,
    .height = 2,
    .paletteNum = 15, 
    .baseBlock = 0x30 + (5 * 2 * 4)};

static void HSelM_CreateTextWindows(void)
{
    sHeatSelectMenu->sTopTextWindowId = AddWindow(HSelM_GetTopWindowTemplate()); // this is its own method because we need to update the window template depending on whether there are registered items or not or if we are in time picker mode
    sHeatSelectMenu->sLTextWindowId = AddWindow(&sWindowTemplate_L);
    sHeatSelectMenu->sRTextWindowId = AddWindow(&sWindowTemplate_R);
    sHeatSelectMenu->sSelectTextWindowId = AddWindow(&sWindowTemplate_Select);
    sHeatSelectMenu->sStartTextWindowId = AddWindow(&sWindowTemplate_Start);

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

static const u8 gText_WaitTime[]    = _("Wait until...");
static const u8 gText_Friday[]    = _("Bicycleeee");
static const u8 gText_NoRegisteredItem[]    = _("No reg. item");
static const u8 gText_SelectedItem[] = _("{STR_VAR_3}");
static void HSelM_UpdateTopTextWindow(void)
{
    HSelM_CleanWhiteWindow(sHeatSelectMenu->sTopTextWindowId);
    
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        StringExpandPlaceholders(gStringVar4, gText_WaitTime);
    }
    else
    {
        if(HSelM_AreThereRegisteredItems()){
            #if ENABLE_MULTIPLE_REGISTERED_ITEMS
            u16 registeredItem = gSaveBlock1Ptr->registeredItems[sHeatSelectMenu->registeredItemIndex].itemId;
            #else
            u16 registeredItem = gSaveBlock1Ptr->registeredItem;
            #endif
            StringExpandPlaceholders(gStringVar4, GetItemName(registeredItem));
        } else {
            StringExpandPlaceholders(gStringVar4, gText_NoRegisteredItem);
        }
    }
    
    HSelM_PrintCenteredStringVar4(sHeatSelectMenu->sTopTextWindowId, FONT_SMALL, HSelM_GetTopWindowTemplate()->width);
}

static const u8 gText_On[]    = _("On");
static const u8 gText_Off[]    = _("Off");
static const u8 gText_Pokevial_Dose_Count[] = _("{STR_VAR_1}/{STR_VAR_2}");
static const u8 gText_WaitTime_Morning[] = _("Morning");
static void HSelM_UpdateLTextWindow(void)
{
    bool8 state = HSelM_LSectionState();

    HSelM_CleanBackgroundWindow(sHeatSelectMenu->sLTextWindowId, state);
    
    if (sHeatSelectMenu->mode == HSELM_MODE_TIME_PICKER)
    {
        StringExpandPlaceholders(gStringVar4, gText_WaitTime_Morning);
    }
    else
    {
        // TODO: customize L window text for your own use case
        StringExpandPlaceholders(gStringVar4, state? gText_On : gText_Off);
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
        // TODO: customize select window text for your own use case
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
        // TODO: customize L window text for your own use case if you donw't want to enable exp all flag in config/item.h
        StringExpandPlaceholders(gStringVar4, state? gText_On : gText_Off);
    }

    HSelM_PrintCenteredStringVar4Background(sHeatSelectMenu->sStartTextWindowId, FONT_SMALL, sWindowTemplate_Start.width, state);
}

/////// =================================================================================
/////// ============ EXIT AND CLEANUP ===================================================
/////// =================================================================================

static void HSelM_ExitAndCleanup(bool32 unfreeze)
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

    if(unfreeze)
    {
        ScriptUnfreezeObjectEvents();
        UnlockPlayerFieldControls();
    }
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
    HSelM_RemoveItemIcon();
    HSelM_RemoveLeftIcon();
    HSelM_RemoveRightIcon();
    HSelM_RemoveSelectIcon();
    HSelM_RemoveStartIcon();
}

// Helper function to remove any icon sprite
static void HSelM_RemoveIconGeneric(u32 *spriteIdLoc, u32 *spriteIdLocFlash, u16 tag)
{
    if (*spriteIdLoc != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(tag);
        FreeSpritePaletteByTag(tag);
        DestroySprite(&(gSprites[*spriteIdLoc]));
        *spriteIdLoc = SPRITE_NONE;
        if(*spriteIdLocFlash != SPRITE_NONE && HSelM_ShouldHandleFlash())
        {
            DestroySprite(&(gSprites[*spriteIdLocFlash]));
            *spriteIdLocFlash = SPRITE_NONE;
        }
    }
}

static void HSelM_RemoveItemIcon(void)
{
    HSelM_RemoveIconGeneric(&sHeatSelectMenu->spriteIdRegisteredKeyItem, &sHeatSelectMenu->spriteIdRegisteredKeyItemFlash, TAG_ITEM_ICON);
}
static void HSelM_RemoveStartIcon(void)
{
    HSelM_RemoveIconGeneric(&sHeatSelectMenu->spriteIdStart, &sHeatSelectMenu->spriteIdStartFlash, TAG_START_ICON);
}
static void HSelM_RemoveSelectIcon(void)
{
    HSelM_RemoveIconGeneric(&sHeatSelectMenu->spriteIdSelect, &sHeatSelectMenu->spriteIdSelectFlash, TAG_SELECT_ICON);
}

static void HSelM_RemoveLeftIcon(void)
{
    HSelM_RemoveIconGeneric(&sHeatSelectMenu->spriteIdLeft, &sHeatSelectMenu->spriteIdLeftFlash, TAG_LEFT_ICON);
}

static void HSelM_RemoveRightIcon(void)
{
    HSelM_RemoveIconGeneric(&sHeatSelectMenu->spriteIdRight, &sHeatSelectMenu->spriteIdRightFlash, TAG_RIGHT_ICON);
}