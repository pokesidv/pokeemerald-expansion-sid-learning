#include "option_menu.h"
#include "heat_start_menu.h"
#include "heat_menu_palettes.h"
#include "global.h"
#include "debug.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_object_lock.h"
#include "event_scripts.h"
#include "io_reg.h"
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

/* CALLBACKS */
static void SpriteCB_IconPoketch(struct Sprite *sprite);
static void SpriteCB_IconPokedex(struct Sprite *sprite);
static void SpriteCB_IconParty(struct Sprite *sprite);
static void SpriteCB_IconBag(struct Sprite *sprite);
static void SpriteCB_IconTrainerCard(struct Sprite *sprite);
static void SpriteCB_IconSave(struct Sprite *sprite);
static void SpriteCB_IconOptions(struct Sprite *sprite);
static void SpriteCB_IconFlag(struct Sprite *sprite);

/* helper for sprite callbacks */
static void SpriteCB_Icon_Common(struct Sprite *sprite, u8 menu);

/* TASKs */
static void Task_HeatStartMenu_HandleMainInput(u8 taskId);
static void Task_HandleSave(u8 taskId);

/* OTHER FUNCTIONS */
static void HeatStartMenu_LoadSprites(void);
static void HeatStartMenu_CreateSprites(void);
static void HeatStartMenu_CreateSprite(u8 menu, u32 x, u32 y, bool8 flash);
static void HeatStartMenu_CreateStaticSprite(u8 menu, u32 x, u32 y, bool8 flash);
static void HeatStartMenu_LoadBgGfx(void);
static void HeatStartMenu_ShowTimeWindow(void);
static void HeatStartMenu_UpdateClockDisplay(void);
static void HeatStartMenu_ShowMapNameWindow(void);
static void HeatStartMenu_UpdateMenuName(void);
static u8 RunSaveCallback(void);
static u8 SaveDoSaveCallback(void);
static void HideSaveInfoWindow(void);
static void HideSaveMessageWindow(void);
static u8 SaveOverwriteInputCallback(void);
static u8 SaveConfirmOverwriteDefaultNoCallback(void);
static void ShowSaveMessage(const u8 *message, u8 (*saveCallback)(void));
static u8 SaveFileExistsCallback(void);
static u8 SaveSavingMessageCallback(void);
static u8 SaveConfirmInputCallback(void);
static u8 SaveYesNoCallback(void);
static void ShowSaveInfoWindow(void);
static u8 SaveConfirmSaveCallback(void);
static void InitSave(void);

static void SetInitialSelectedOption(void);
static bool8 IsLShortcutEnabledInGame();
static bool8 IsMenuOptionEnabledInGame(u8 menu);
static bool8 IsMenuOptionConfiguredToShowUp(u8 menu);
static bool8 IsMenuOptionShown(u8 menu);
static u8 HowManyOptionsShown(void);
static u8 IndexToShownOption(u8 index);
static u8 ShownOptionToIndex(u8 option);
static void ShowSafariBallsWindow(void);
static void HeatStartMenu_ExitAndClearTilemap(bool8 enableMovement);
static void HeatStartMenu_CleanupTextWindow(u32 windowId);
static void HeatStartMenu_CleanupSprite(struct Sprite *sprite);
static void HeatStartMenu_CleanupSpriteFromMenuOption(u8 menu, bool8 flash);
static void HeatStartMenu_OpenMenu(void);
static void DoCleanUpAndStartSaveMenu(void);
static void DoCleanUpAndStartSafariZoneRetire(void);

/* ENUMs */
enum MENU
{
  HSMO_POKEDEX,
  HSMO_PARTY,
  HSMO_BAG,
  HSMO_POKETCH,
  HSMO_TRAINER_CARD,
  HSMO_OPTIONS,
  HSMO_SAVE,
  HSMO_FLAG,
  HSMO_COUNT,
};

enum FLAG_VALUES
{
  FLAG_VALUE_NOT_SET,
  FLAG_VALUE_SET,
};

enum SAVE_STATES
{
  SAVE_IN_PROGRESS,
  SAVE_SUCCESS,
  SAVE_CANCELED,
  SAVE_ERROR
};

/* STRUCTs */
struct HeatStartMenu
{
  MainCallback savedCallback;
  u32 loadState;
  u32 inputDelay;              // input delay to prevent the button that opened the menu from being processed immediately
  u32 sDayWindowId;
  u32 sTimeWindowId;
  u32 sMapNameWindowId;
  u32 sMenuNameWindowId;
  u32 sSafariBallsWindowId;
  u32 flag; // some u32 holding values for controlling the sprite anims and lifetime

  u32 spriteIdPoketch;
  u32 spriteIdPokedex;
  u32 spriteIdParty;
  u32 spriteIdBag;
  u32 spriteIdTrainerCard;
  u32 spriteIdSave;
  u32 spriteIdOptions;
  u32 spriteIdFlag;
  // if we are in a dark cave, we need to show sprites twice, the second time with a specific property enabled to make them visible
  u32 spriteIdPoketchFlash;
  u32 spriteIdPokedexFlash;
  u32 spriteIdPartyFlash;
  u32 spriteIdBagFlash;
  u32 spriteIdTrainerCardFlash;
  u32 spriteIdSaveFlash;
  u32 spriteIdOptionsFlash;
  u32 spriteIdFlagFlash;
};

static EWRAM_DATA struct HeatStartMenu *sHeatStartMenu = NULL;
static EWRAM_DATA u8 menuSelected;
static EWRAM_DATA u8 (*sSaveDialogCallback)(void) = NULL;
static EWRAM_DATA u8 sSaveDialogTimer = 0;
static EWRAM_DATA u8 sSaveInfoWindowId = 0;

// --BG-GFX--
static const u32 sStartMenuTiles[] = INCBIN_U32("graphics/heat_start_menu/bg.4bpp.lz");

static const u32 sStartMenuTilemap2[] = INCBIN_U32("graphics/heat_start_menu/bg_reg_2slots.bin.lz");
static const u32 sStartMenuTilemap3[] = INCBIN_U32("graphics/heat_start_menu/bg_reg_3slots.bin.lz");
static const u32 sStartMenuTilemap4[] = INCBIN_U32("graphics/heat_start_menu/bg_reg_4slots.bin.lz");
static const u32 sStartMenuTilemap5[] = INCBIN_U32("graphics/heat_start_menu/bg_reg_5slots.bin.lz");
static const u32 sStartMenuTilemap6[] = INCBIN_U32("graphics/heat_start_menu/bg_reg_6slots.bin.lz");
static const u32 sStartMenuTilemap7[] = INCBIN_U32("graphics/heat_start_menu/bg_reg_7slots.bin.lz");
static const u32 sStartMenuTilemapSafari2[] = INCBIN_U32("graphics/heat_start_menu/bg_safari_2slots.bin.lz");
static const u32 sStartMenuTilemapSafari3[] = INCBIN_U32("graphics/heat_start_menu/bg_safari_2slots.bin.lz");
static const u32 sStartMenuTilemapSafari4[] = INCBIN_U32("graphics/heat_start_menu/bg_safari_4slots.bin.lz");
static const u32 sStartMenuTilemapSafari5[] = INCBIN_U32("graphics/heat_start_menu/bg_safari_5slots.bin.lz");
static const u32 sStartMenuTilemapSafari6[] = INCBIN_U32("graphics/heat_start_menu/bg_safari_6slots.bin.lz");
static const u32 sStartMenuTilemapSafari7[] = INCBIN_U32("graphics/heat_start_menu/bg_safari_7slots.bin.lz");
static const u32 sStartMenuTilemapL2[] = INCBIN_U32("graphics/heat_start_menu/bg_L_reg_2slots.bin.lz");
static const u32 sStartMenuTilemapL3[] = INCBIN_U32("graphics/heat_start_menu/bg_L_reg_3slots.bin.lz");
static const u32 sStartMenuTilemapL4[] = INCBIN_U32("graphics/heat_start_menu/bg_L_reg_4slots.bin.lz");
static const u32 sStartMenuTilemapL5[] = INCBIN_U32("graphics/heat_start_menu/bg_L_reg_5slots.bin.lz");
static const u32 sStartMenuTilemapL6[] = INCBIN_U32("graphics/heat_start_menu/bg_L_reg_6slots.bin.lz");
static const u32 sStartMenuTilemapL7[] = INCBIN_U32("graphics/heat_start_menu/bg_L_reg_7slots.bin.lz");
static const u32 sStartMenuTilemapLSafari2[] = INCBIN_U32("graphics/heat_start_menu/bg_L_safari_2slots.bin.lz");
static const u32 sStartMenuTilemapLSafari3[] = INCBIN_U32("graphics/heat_start_menu/bg_L_safari_2slots.bin.lz");
static const u32 sStartMenuTilemapLSafari4[] = INCBIN_U32("graphics/heat_start_menu/bg_L_safari_4slots.bin.lz");
static const u32 sStartMenuTilemapLSafari5[] = INCBIN_U32("graphics/heat_start_menu/bg_L_safari_5slots.bin.lz");
static const u32 sStartMenuTilemapLSafari6[] = INCBIN_U32("graphics/heat_start_menu/bg_L_safari_6slots.bin.lz");
static const u32 sStartMenuTilemapLSafari7[] = INCBIN_U32("graphics/heat_start_menu/bg_L_safari_7slots.bin.lz");

///// =====================================================================================
///// ============== Text window templates ================================================
///// =====================================================================================

static const struct WindowTemplate sSaveInfoWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 14,
    .height = 10,
    .paletteNum = 15,
    .baseBlock = 8};

static const struct WindowTemplate sWindowTemplate_MenuName = {
    .bg = 0,
    .tilemapLeft = 17,
    .tilemapTop = 17,
    .width = 7,
    .height = 2,
    .paletteNum = 15,
    .baseBlock = 0x30};
    
static const struct WindowTemplate sWindowTemplate_MapName = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 17,
    .width = 14, 
    .height = 2,
    .paletteNum = 15,
    .baseBlock = 0x30 + (7 * 2)};

static const struct WindowTemplate sWindowTemplate_StartClock = {
    .bg = 0,
    .tilemapLeft = 14, 
    .tilemapTop = 1, 
    .width = 5, 
    .height = 2,
    .paletteNum = 15,
    .baseBlock = 0x30 + (7 * 2) + (14 * 2)};

static const struct WindowTemplate sWindowTemplate_StartDay = {
    .bg = 0,
    .tilemapLeft = 1, 
    .tilemapTop = 1, 
    .width = 11, // If you want to shorten the dates to Sat., Sun., etc., change this to 8?
    .height = 2,
    .paletteNum = 15,
    .baseBlock = 0x30 + (7 * 2) + (14 * 2) + (5 * 2)};

static const struct WindowTemplate sWindowTemplate_SafariBalls = {
    .bg = 0,
    .tilemapLeft = 2,
    .tilemapTop = 1,
    .width = 7,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x30 + (7 * 2) + (14 * 2)};

    


///// =====================================================================================
///// ============== Sprite data ==========================================================
///// =====================================================================================

#define TAG_ICON_GFX 0x8009 // we use tags greater than 0x8000 to avoid the menu sprites being blended by the day / night system
#define TAG_ICON_PAL 0x8009

static const u32 sIconGfx[] = INCBIN_U32("graphics/heat_start_menu/icons.4bpp.lz");
static const u16 sIconPal[] = INCBIN_U16("graphics/heat_start_menu/icons.gbapal");

static const struct SpritePalette sSpritePal_Icon[] =
    {
        {sIconPal, TAG_ICON_PAL},
        {NULL},
};

static const struct CompressedSpriteSheet sSpriteSheet_Icon[] =
    {
        {sIconGfx, 32 * 512 / 2, TAG_ICON_GFX},
        {NULL},
};

static const struct OamData gOamIcon = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const union AnimCmd gAnimCmdPoketch_NotSelected[] = {
    ANIMCMD_FRAME(112, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdPoketch_Selected[] = {
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconPoketchAnim[] = {
    gAnimCmdPoketch_NotSelected,
    gAnimCmdPoketch_Selected,
};
static const union AnimCmd *const gIconPoketchAnimStatic[] = {
    gAnimCmdPoketch_Selected,
};

static const union AnimCmd gAnimCmdPokedex_NotSelected[] = {
    ANIMCMD_FRAME(128, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdPokedex_Selected[] = {
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconPokedexAnim[] = {
    gAnimCmdPokedex_NotSelected,
    gAnimCmdPokedex_Selected,
};
static const union AnimCmd *const gIconPokedexAnimStatic[] = {
    gAnimCmdPokedex_Selected,
};

static const union AnimCmd gAnimCmdParty_NotSelected[] = {
    ANIMCMD_FRAME(144, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdParty_Selected[] = {
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconPartyAnim[] = {
    gAnimCmdParty_NotSelected,
    gAnimCmdParty_Selected,
};
static const union AnimCmd *const gIconPartyAnimStatic[] = {
    gAnimCmdParty_Selected,
};

static const union AnimCmd gAnimCmdBag_NotSelected[] = {
    ANIMCMD_FRAME(160, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdBag_Selected[] = {
    ANIMCMD_FRAME(48, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconBagAnim[] = {
    gAnimCmdBag_NotSelected,
    gAnimCmdBag_Selected,
};
static const union AnimCmd *const gIconBagAnimStatic[] = {
    gAnimCmdBag_Selected,
};

static const union AnimCmd gAnimCmdTrainerCard_NotSelected[] = {
    ANIMCMD_FRAME(176, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdTrainerCard_Selected[] = {
    ANIMCMD_FRAME(64, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconTrainerCardAnim[] = {
    gAnimCmdTrainerCard_NotSelected,
    gAnimCmdTrainerCard_Selected,
};
static const union AnimCmd *const gIconTrainerCardAnimStatic[] = {
    gAnimCmdTrainerCard_Selected,
};

static const union AnimCmd gAnimCmdSave_NotSelected[] = {
    ANIMCMD_FRAME(192, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdSave_Selected[] = {
    ANIMCMD_FRAME(80, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconSaveAnim[] = {
    gAnimCmdSave_NotSelected,
    gAnimCmdSave_Selected,
};
static const union AnimCmd *const gIconSaveAnimStatic[] = {
    gAnimCmdSave_Selected,
};

static const union AnimCmd gAnimCmdOptions_NotSelected[] = {
    ANIMCMD_FRAME(208, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdOptions_Selected[] = {
    ANIMCMD_FRAME(96, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconOptionsAnim[] = {
    gAnimCmdOptions_NotSelected,
    gAnimCmdOptions_Selected,
};
static const union AnimCmd *const gIconOptionsAnimStatic[] = {
    gAnimCmdOptions_Selected,
};

static const union AnimCmd gAnimCmdFlag_NotSelected[] = {
    ANIMCMD_FRAME(240, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdFlag_Selected[] = {
    ANIMCMD_FRAME(224, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconFlagAnim[] = {
    gAnimCmdFlag_NotSelected,
    gAnimCmdFlag_Selected,
};
static const union AnimCmd *const gIconFlagAnimStatic[] = {
    gAnimCmdFlag_Selected,
};

static const union AffineAnimCmd sAffineAnimIcon_NoAnim[] =
    {
        AFFINEANIMCMD_FRAME(0, 0, 0, 60),
        AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnimIcon_Anim[] =
    {
        AFFINEANIMCMD_FRAME(20, 20, 0, 5),    // Scale big
        AFFINEANIMCMD_FRAME(-10, -10, 0, 10), // Scale smol
        AFFINEANIMCMD_FRAME(0, 0, 1, 4),      // Begin rotating

        AFFINEANIMCMD_FRAME(0, 0, -1, 4), // Loop starts from here ; Rotate/Tilt left
        AFFINEANIMCMD_FRAME(0, 0, 0, 2),
        AFFINEANIMCMD_FRAME(0, 0, -1, 4),
        AFFINEANIMCMD_FRAME(0, 0, 0, 2),
        AFFINEANIMCMD_FRAME(0, 0, -1, 4),

        AFFINEANIMCMD_FRAME(0, 0, 1, 4), // Rotate/Tilt Right
        AFFINEANIMCMD_FRAME(0, 0, 0, 2),
        AFFINEANIMCMD_FRAME(0, 0, 1, 4),
        AFFINEANIMCMD_FRAME(0, 0, 0, 2),
        AFFINEANIMCMD_FRAME(0, 0, 1, 4),

        AFFINEANIMCMD_JUMP(3),
};

static const union AffineAnimCmd *const sAffineAnimsIcon[] =
    {
        sAffineAnimIcon_NoAnim,
        sAffineAnimIcon_Anim,
};

static const struct SpriteTemplate gSpriteIconPoketch = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPoketchAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconPoketch,
};

static const struct SpriteTemplate gSpriteIconPokedex = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPokedexAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconPokedex,
};

static const struct SpriteTemplate gSpriteIconParty = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPartyAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconParty,
};

static const struct SpriteTemplate gSpriteIconBag = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconBagAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconBag,
};

static const struct SpriteTemplate gSpriteIconTrainerCard = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconTrainerCardAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconTrainerCard,
};

static const struct SpriteTemplate gSpriteIconSave = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconSaveAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconSave,
};

static const struct SpriteTemplate gSpriteIconOptions = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconOptionsAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconOptions,
};

static const struct SpriteTemplate gSpriteIconFlag = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconFlagAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconFlag,
};

static const struct SpriteTemplate gSpriteIconPoketchStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPoketchAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gSpriteIconPokedexStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPokedexAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gSpriteIconPartyStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPartyAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gSpriteIconBagStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconBagAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gSpriteIconTrainerCardStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconTrainerCardAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gSpriteIconSaveStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconSaveAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gSpriteIconOptionsStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconOptionsAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gSpriteIconFlagStatic = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconFlagAnimStatic,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};


// sprite animation callbacks for each icon
static void SpriteCB_IconPoketch(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_POKETCH);
}

static void SpriteCB_IconPokedex(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_POKEDEX);
}

static void SpriteCB_IconParty(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_PARTY);
}

static void SpriteCB_IconBag(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_BAG);
}

static void SpriteCB_IconTrainerCard(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_TRAINER_CARD);
}

static void SpriteCB_IconSave(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_SAVE);
}

static void SpriteCB_IconOptions(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_OPTIONS);
}

static void SpriteCB_IconFlag(struct Sprite *sprite)
{
  SpriteCB_Icon_Common(sprite, HSMO_FLAG);
}

// common code for all icon sprite callbacks
static void SpriteCB_Icon_Common(struct Sprite *sprite, u8 menu)
{
  if (menuSelected == menu && sHeatStartMenu->flag == FLAG_VALUE_NOT_SET)
  {
    sHeatStartMenu->flag = FLAG_VALUE_SET;
    StartSpriteAnim(sprite, 1);
    StartSpriteAffineAnim(sprite, 1);
  }
  else if (menuSelected != menu)
  {
    StartSpriteAnim(sprite, 0);
    StartSpriteAffineAnim(sprite, 0);
  }
}


///// =====================================================================================
///// ============== Logic and state initialization =======================================
///// =====================================================================================

void HeatStartMenu_Init(void)
{
  if (!IsOverworldLinkActive())
  {
    FreezeObjectEvents();
    PlayerFreeze();
    StopPlayerAvatar();
  }

  LockPlayerFieldControls();

  if (sHeatStartMenu == NULL)
  {
    sHeatStartMenu = AllocZeroed(sizeof(struct HeatStartMenu));
  }

  if (sHeatStartMenu == NULL)
  {
    SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    return;
  }

  sHeatStartMenu->savedCallback = CB2_ReturnToFieldWithOpenMenu;
  sHeatStartMenu->inputDelay = 1;
  sHeatStartMenu->loadState = 0;
  sHeatStartMenu->sDayWindowId = 0;
  sHeatStartMenu->sTimeWindowId = 0;
  sHeatStartMenu->sMapNameWindowId = 0;
  sHeatStartMenu->flag = 0;
  
  SetInitialSelectedOption();
  HeatStartMenu_LoadSprites();
  HeatStartMenu_CreateSprites();
  HeatStartMenu_LoadBgGfx();
  if (GetSafariZoneFlag())
  {
    ShowSafariBallsWindow();
  }
  else
  {
    HeatStartMenu_ShowTimeWindow();
  }
  HeatStartMenu_ShowMapNameWindow();
  sHeatStartMenu->sMenuNameWindowId = AddWindow(&sWindowTemplate_MenuName);
  HeatStartMenu_UpdateMenuName();
  CreateTask(Task_HeatStartMenu_HandleMainInput, 0);
}

static void SetInitialSelectedOption(void)
{
  u8 m;
  for(m = 0; m < HSMO_COUNT; m++)
  {
    if (IsMenuOptionShown(m))
    {
      menuSelected = m;
      return;
    }
  }
  menuSelected = HSMO_BAG; // Fallback, should never happen
}


static bool8 IsLShortcutEnabledInGame(){
  if(HSM_CONFIG_L_SHORTCUT == HSMO_COUNT)
  {
    return FALSE;
  }
  return IsMenuOptionEnabledInGame(HSM_CONFIG_L_SHORTCUT);
}

static bool8 IsMenuOptionEnabledInGame(u8 menu)
{
  switch (menu)
  {
  case HSMO_POKEDEX:
    return FlagGet(FLAG_SYS_POKEDEX_GET);
  case HSMO_PARTY:
    return FlagGet(FLAG_SYS_POKEMON_GET);
  case HSMO_BAG:
    return TRUE;
  case HSMO_POKETCH:
    return GetSafariZoneFlag() == FALSE && FlagGet(FLAG_SYS_POKENAV_GET) == TRUE;
  case HSMO_TRAINER_CARD:
    return TRUE;
  case HSMO_SAVE:
    return GetSafariZoneFlag() == FALSE;
  case HSMO_OPTIONS:
    return TRUE;
  case HSMO_FLAG:
    return GetSafariZoneFlag() == TRUE;
  default:
    return FALSE; // Fallback, should never happen
  }
  return FALSE; // Fallback, should never happen
}

static bool8 IsMenuOptionConfiguredToShowUp(u8 menu)
{
  if(menu == HSM_CONFIG_L_SHORTCUT)
  {
    return FALSE;
  }

  switch (menu)
  {
  case HSMO_POKEDEX:
    return HSM_CONFIG_SHOW_POKEDEX;
  case HSMO_PARTY:
    return HSM_CONFIG_SHOW_PARTY;
  case HSMO_BAG:
    return HSM_CONFIG_SHOW_BAG;
  case HSMO_POKETCH:
    return HSM_CONFIG_SHOW_POKETCH;
  case HSMO_TRAINER_CARD:
    return HSM_CONFIG_SHOW_TRAINER_CARD;
  case HSMO_SAVE:
    return TRUE;
  case HSMO_OPTIONS:
    return HSM_CONFIG_SHOW_OPTIONS;
  case HSMO_FLAG:
    return TRUE;
  default:
    return FALSE; // Fallback, should never happen
  }
  return FALSE; // Fallback, should never happen
}
static bool8 IsMenuOptionShown(u8 menu)
{
  return IsMenuOptionConfiguredToShowUp(menu) && IsMenuOptionEnabledInGame(menu);
}

static u8 HowManyOptionsShown(void)
{
  u8 count = 0;
  u8 m;
  for(m = 0; m < HSMO_COUNT; m++)
  {
    if (IsMenuOptionShown(m))
    {
      count++;
    }
  }
  return count;
}

static u8 IndexToShownOption(u8 index)
{
  u8 count = 0;
  u8 m;
  for(m = 0; m < HSMO_COUNT; m++)
  {
    if (IsMenuOptionShown(m))
    {
      if(count == index)
      {
        return m;
      }
      count++;
    }
  }
  // if the index was out of bounds for the shown options, return the first shown option
  for(m = 0; m < HSMO_COUNT; m++)
  {
    if (IsMenuOptionShown(m))
    {
        return m;
    }
  }
  return HSMO_BAG; // Fallback, should never happen
}

static u8 ShownOptionToIndex(u8 option)
{
  u8 count = 0;
  u8 m;
  for(m = 0; m < HSMO_COUNT; m++)
  {
    if (IsMenuOptionShown(m))
    {
      if(m == option)
      {
        return count;
      }
      count++;
    }
  }
  return 0; // Fallback, should never happen
}
   
///// =====================================================================================
///// ============== Background and sprites ===============================================
///// =====================================================================================

static void HeatStartMenu_LoadBgGfx(void)
{
  u8 *buf = GetBgTilemapBuffer(0);
  LoadBgTilemap(0, 0, 0, 0);
  DecompressAndCopyTileDataToVram(0, sStartMenuTiles, 0, 0, 0); // Keep as sStartMenuTiles (u32)

  if (IsLShortcutEnabledInGame() == FALSE)
  {
    if (GetSafariZoneFlag())
    {
      switch (HowManyOptionsShown())
      {
      case 2:
        DecompressDataWithHeaderWram(sStartMenuTilemapSafari2, buf);
        break;
      case 3:
        DecompressDataWithHeaderWram(sStartMenuTilemapSafari3, buf);
        break;
      case 4:
        DecompressDataWithHeaderWram(sStartMenuTilemapSafari4, buf);
        break;
      case 5:
        DecompressDataWithHeaderWram(sStartMenuTilemapSafari5, buf);
        break;
      case 6:
        DecompressDataWithHeaderWram(sStartMenuTilemapSafari6, buf);
        break;
      default:
        DecompressDataWithHeaderWram(sStartMenuTilemapSafari7, buf);
        break;
      }
    }
    else
    {
      switch (HowManyOptionsShown())
      {
      case 2:
        DecompressDataWithHeaderWram(sStartMenuTilemap2, buf);
        break;
      case 3:
        DecompressDataWithHeaderWram(sStartMenuTilemap3, buf);
        break;
      case 4:
        DecompressDataWithHeaderWram(sStartMenuTilemap4, buf);
        break;
      case 5:
        DecompressDataWithHeaderWram(sStartMenuTilemap5, buf);
        break;
      case 6:
        DecompressDataWithHeaderWram(sStartMenuTilemap6, buf);
        break;
      default:
        DecompressDataWithHeaderWram(sStartMenuTilemap7, buf);
        break;
      }
    }
  }
  else
  {
    if (GetSafariZoneFlag())
    {
      switch (HowManyOptionsShown())
      {
      case 2:
        DecompressDataWithHeaderWram(sStartMenuTilemapLSafari2, buf);
        break;
      case 3:
        DecompressDataWithHeaderWram(sStartMenuTilemapLSafari3, buf);
        break;
      case 4:
        DecompressDataWithHeaderWram(sStartMenuTilemapLSafari4, buf);
        break;
      case 5:
        DecompressDataWithHeaderWram(sStartMenuTilemapLSafari5, buf);
        break;
      case 6:
        DecompressDataWithHeaderWram(sStartMenuTilemapLSafari6, buf);
        break;
      default:
        DecompressDataWithHeaderWram(sStartMenuTilemapLSafari7, buf);
        break;
      }
    }
    else
    {
      switch (HowManyOptionsShown())
      {
      case 2:
        DecompressDataWithHeaderWram(sStartMenuTilemapL2, buf);
        break;
      case 3:
        DecompressDataWithHeaderWram(sStartMenuTilemapL3, buf);
        break;
      case 4:
        DecompressDataWithHeaderWram(sStartMenuTilemapL4, buf);
        break;
      case 5:
        DecompressDataWithHeaderWram(sStartMenuTilemapL5, buf);
        break;
      case 6:
        DecompressDataWithHeaderWram(sStartMenuTilemapL6, buf);
        break;
      default:
        DecompressDataWithHeaderWram(sStartMenuTilemapL7, buf);
        break;
      }
    }
  }

  HeatMenus_LoadPalettes();

  ScheduleBgCopyTilemapToVram(0);
}

static void HeatStartMenu_LoadSprites(void)
{
  u32 index;
  LoadSpritePalette(sSpritePal_Icon);
  index = IndexOfSpritePaletteTag(TAG_ICON_PAL);
  LoadPalette(sIconPal, OBJ_PLTT_ID(index), PLTT_SIZE_4BPP);
  LoadCompressedSpriteSheet(sSpriteSheet_Icon);
}

static void HeatStartMenu_CreateSprites(void)
{
  u32 x = 224;

  u8 count = HowManyOptionsShown();

  // perfect for the sweet spot of 5 options
  u32 start = 16;
  u32 delta = 32;
  u32 last = 18*8;

  switch (count)
  {
  case 2:
    start += 24;
    delta += 8;
    last -= 24;
    break;
  case 3:
    start += 8;
    delta += 8;
    last -= 16;
    break;
  case 4:
    delta += 8;
    break;
  case 6:
    delta -= 8;
    break;
  case 7:
  start -= 4;
    delta -= 9;
    last += 4;
    break;
  default:
    break;
  }

  bool8 handleFlash = GetFlashLevel() > 0 || InBattlePyramid_();
  if(handleFlash)
  {
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
  }

  u8 i;
  for(i = 0; i < count; i++){
    u8 menu = IndexToShownOption(i);
    HeatStartMenu_CreateSprite(menu, x, i==count-1 ? last : start + (i * delta), handleFlash);
  }

  if(IsLShortcutEnabledInGame())
  {
    HeatStartMenu_CreateStaticSprite(HSM_CONFIG_L_SHORTCUT, 2*8, 8*8, handleFlash);
  }

}

static void HeatStartMenu_CreateSprite(u8 menu, u32 x, u32 y, bool8 flash)
{
  switch (menu)
  {
  case HSMO_POKEDEX:
    sHeatStartMenu->spriteIdPokedex = CreateSprite(&gSpriteIconPokedex, x, y, 0);
    break;
  case HSMO_PARTY:
    sHeatStartMenu->spriteIdParty = CreateSprite(&gSpriteIconParty, x, y, 0);
    break;
  case HSMO_BAG:
    sHeatStartMenu->spriteIdBag = CreateSprite(&gSpriteIconBag, x, y, 0);
    break;
  case HSMO_POKETCH:
    sHeatStartMenu->spriteIdPoketch = CreateSprite(&gSpriteIconPoketch, x, y, 0);
    break;
  case HSMO_TRAINER_CARD:
    sHeatStartMenu->spriteIdTrainerCard = CreateSprite(&gSpriteIconTrainerCard, x, y, 0);
    break;
  case HSMO_SAVE:
    sHeatStartMenu->spriteIdSave = CreateSprite(&gSpriteIconSave, x, y, 0);
    break;
  case HSMO_OPTIONS:
    sHeatStartMenu->spriteIdOptions = CreateSprite(&gSpriteIconOptions, x, y, 0);
    break;
  case HSMO_FLAG:
    sHeatStartMenu->spriteIdFlag = CreateSprite(&gSpriteIconFlag, x, y, 0);
    break;
  }

  if (flash)
  {

    switch (menu)
    {
    case HSMO_POKEDEX:
      sHeatStartMenu->spriteIdPokedexFlash = CreateSprite(&gSpriteIconPokedex, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdPokedexFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_PARTY:
      sHeatStartMenu->spriteIdPartyFlash = CreateSprite(&gSpriteIconParty, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdPartyFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_BAG:
      sHeatStartMenu->spriteIdBagFlash = CreateSprite(&gSpriteIconBag, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdBagFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_POKETCH:
      sHeatStartMenu->spriteIdPoketchFlash = CreateSprite(&gSpriteIconPoketch, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdPoketchFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_TRAINER_CARD:
      sHeatStartMenu->spriteIdTrainerCardFlash = CreateSprite(&gSpriteIconTrainerCard, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdTrainerCardFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_SAVE:
      sHeatStartMenu->spriteIdSaveFlash = CreateSprite(&gSpriteIconSave, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdSaveFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_OPTIONS:
      sHeatStartMenu->spriteIdOptionsFlash = CreateSprite(&gSpriteIconOptions, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdOptionsFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_FLAG:
      sHeatStartMenu->spriteIdFlagFlash = CreateSprite(&gSpriteIconFlag, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdFlagFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    }
  }


}

static void HeatStartMenu_CreateStaticSprite(u8 menu, u32 x, u32 y, bool8 flash)
{
  switch (menu)
  {
  case HSMO_POKEDEX:
    sHeatStartMenu->spriteIdPokedex = CreateSprite(&gSpriteIconPokedexStatic, x, y, 0);
    break;
  case HSMO_PARTY:
    sHeatStartMenu->spriteIdParty = CreateSprite(&gSpriteIconPartyStatic, x, y, 0);
    break;
  case HSMO_BAG:
    sHeatStartMenu->spriteIdBag = CreateSprite(&gSpriteIconBagStatic, x, y, 0);
    break;
  case HSMO_POKETCH:
    sHeatStartMenu->spriteIdPoketch = CreateSprite(&gSpriteIconPoketchStatic, x, y, 0);
    break;
  case HSMO_TRAINER_CARD:
    sHeatStartMenu->spriteIdTrainerCard = CreateSprite(&gSpriteIconTrainerCardStatic, x, y, 0);
    break;
  case HSMO_SAVE:
    sHeatStartMenu->spriteIdSave = CreateSprite(&gSpriteIconSaveStatic, x, y, 0);
    break;
  case HSMO_OPTIONS:
    sHeatStartMenu->spriteIdOptions = CreateSprite(&gSpriteIconOptionsStatic, x, y, 0);
    break;
  case HSMO_FLAG:
    sHeatStartMenu->spriteIdFlag = CreateSprite(&gSpriteIconFlagStatic, x, y, 0);
    break;
  }
  if (flash)
  {
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);

    switch (menu)
    {
    case HSMO_POKEDEX:
      sHeatStartMenu->spriteIdPokedexFlash = CreateSprite(&gSpriteIconPokedex, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdPokedexFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_PARTY:
      sHeatStartMenu->spriteIdPartyFlash = CreateSprite(&gSpriteIconParty, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdPartyFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_BAG:
      sHeatStartMenu->spriteIdBagFlash = CreateSprite(&gSpriteIconBag, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdBagFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_POKETCH:
      sHeatStartMenu->spriteIdPoketchFlash = CreateSprite(&gSpriteIconPoketch, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdPoketchFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_TRAINER_CARD:
      sHeatStartMenu->spriteIdTrainerCardFlash = CreateSprite(&gSpriteIconTrainerCard, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdTrainerCardFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_SAVE:
      sHeatStartMenu->spriteIdSaveFlash = CreateSprite(&gSpriteIconSave, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdSaveFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_OPTIONS:
      sHeatStartMenu->spriteIdOptionsFlash = CreateSprite(&gSpriteIconOptions, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdOptionsFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    case HSMO_FLAG:
      sHeatStartMenu->spriteIdFlagFlash = CreateSprite(&gSpriteIconFlag, x, y, 0);
      gSprites[sHeatStartMenu->spriteIdFlagFlash].oam.objMode = ST_OAM_OBJ_WINDOW;
      break;
    }
  }
}

////// =======================================================================
////// ================== All text windows  ==================================
////// =======================================================================

static void ShowSafariBallsWindow(void)
{
  sHeatStartMenu->sSafariBallsWindowId = AddWindow(&sWindowTemplate_SafariBalls);
  FillWindowPixelBuffer(sHeatStartMenu->sSafariBallsWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sSafariBallsWindowId);
  ConvertIntToDecimalStringN(gStringVar1, gNumSafariBalls, STR_CONV_MODE_RIGHT_ALIGN, 2);
  StringExpandPlaceholders(gStringVar4, gText_SafariBallStock);
  AddTextPrinterParameterized(sHeatStartMenu->sSafariBallsWindowId, FONT_NARROW, gStringVar4, 0, 1, TEXT_SKIP_DRAW, NULL);
  CopyWindowToVram(sHeatStartMenu->sSafariBallsWindowId, COPYWIN_GFX);
}

static const u8 gText_Friday[]    = _("Friday");
static const u8 gText_Saturday[]  = _("Saturday");
static const u8 gText_Sunday[]    = _("Sunday");
static const u8 gText_Monday[]    = _("Monday");
static const u8 gText_Tuesday[]   = _("Tuesday");
static const u8 gText_Wednesday[] = _("Wednesday");
static const u8 gText_Thursday[]  = _("Thursday");

static const u8 *const gDayNameStringsTable[7] = {
    gText_Sunday,
    gText_Monday,
    gText_Tuesday,
    gText_Wednesday,
    gText_Thursday,
    gText_Friday,
    gText_Saturday,
};

static const u8 *const gTimeOfDayStringsTable[TIMES_OF_DAY_COUNT] = {
    COMPOUND_STRING(" morning"),
    COMPOUND_STRING(""),
    COMPOUND_STRING(" evening"),
    COMPOUND_STRING(" night"),
};

static const u8 gText_CurrentTime[] = _("{STR_VAR_1}");
static const u8 gText_CurrentDay[] = _("{STR_VAR_3}{STR_VAR_2}");

static void HeatStartMenu_ShowTimeWindow(void)
{
  // get time
  u32 day;
  s8 hours;
  s8 minutes;

  if (OW_USE_FAKE_RTC)
  {
      struct SiiRtcInfo *rtc = FakeRtc_GetCurrentTime();
      day = rtc->dayOfWeek;
      hours = rtc->hour;
      minutes = rtc->minute;
  }
  else
  {
      day = ((gLocalTime.days - 1) + 6) % 7 ;
      RtcCalcLocalTime();
      hours = gLocalTime.hours;
      minutes = gLocalTime.minutes;
  }
  
  // create windows
  sHeatStartMenu->sDayWindowId = AddWindow(&sWindowTemplate_StartDay);
  FillWindowPixelBuffer(sHeatStartMenu->sDayWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sDayWindowId);
  sHeatStartMenu->sTimeWindowId = AddWindow(&sWindowTemplate_StartClock);
  FillWindowPixelBuffer(sHeatStartMenu->sTimeWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sTimeWindowId);
  FlagSet(FLAG_TEMP_5);


  // day
  StringCopy(gStringVar3, gDayNameStringsTable[(day % 7)]);
  // time of day
  enum TimeOfDay timeOfDay = AccurateTimeOfDay();
  StringExpandPlaceholders(gStringVar2, gTimeOfDayStringsTable[timeOfDay]);
  // display text
  StringExpandPlaceholders(gStringVar4, gText_CurrentDay);
  u8 x;
  x = GetStringCenterAlignXOffset(FONT_SMALL, gStringVar4, 11*8);
  AddTextPrinterParameterized(sHeatStartMenu->sDayWindowId, FONT_SMALL, gStringVar4, x, 0, 0xFF, NULL);
  CopyWindowToVram(sHeatStartMenu->sDayWindowId, COPYWIN_GFX);
  
  // time
  u8* ptr;
  ptr = ConvertIntToDecimalStringN(gStringVar1, hours, STR_CONV_MODE_LEADING_ZEROS, 2);
  *ptr = 0xF0;
  ConvertIntToDecimalStringN(ptr + 1, minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
  // display text
  StringExpandPlaceholders(gStringVar4, gText_CurrentTime);
  x = GetStringCenterAlignXOffset(FONT_SMALL, gStringVar4, 5*8);
  AddTextPrinterParameterized(sHeatStartMenu->sTimeWindowId, FONT_SMALL, gStringVar4, x, 0, 0xFF, NULL);
  CopyWindowToVram(sHeatStartMenu->sTimeWindowId, COPYWIN_GFX);
}

static void HeatStartMenu_UpdateClockDisplay(void)
{
  if (!FlagGet(FLAG_TEMP_5))
  return;

  // get time
  u32 day;
  s8 hours;
  s8 minutes;
  bool8 onOffColon;

  if (OW_USE_FAKE_RTC)
  {
    struct SiiRtcInfo *rtc = FakeRtc_GetCurrentTime();
    day = rtc->dayOfWeek;
    hours = rtc->hour;
    minutes = rtc->minute;
    onOffColon = (OW_ALTERED_TIME_RATIO == GEN_8_PLA) ? TRUE : // the minutes already go by every second so just always show the colon
                     (OW_ALTERED_TIME_RATIO == GEN_9)    ? (rtc->minute % 2 ? (rtc->second / 20) % 2 : !((rtc->second / 20) % 2))
                 : (OW_ALTERED_TIME_RATIO == TIME_DEBUG) ? rtc->second % 2
                                                         : rtc->second % 2;
  }
  else
  {
    day = ((gLocalTime.days - 1) + 6) % 7;
    RtcCalcLocalTime();
    hours = gLocalTime.hours;
    minutes = gLocalTime.minutes;
    onOffColon = gLocalTime.seconds % 2;
  }
  
  // clean the text windows first
  FillWindowPixelBuffer(sHeatStartMenu->sDayWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sDayWindowId);
  FillWindowPixelBuffer(sHeatStartMenu->sTimeWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sTimeWindowId);
  
  // day
  StringCopy(gStringVar3, gDayNameStringsTable[(day % 7)]);
  // time of day
  enum TimeOfDay timeOfDay = AccurateTimeOfDay();
  StringExpandPlaceholders(gStringVar2, gTimeOfDayStringsTable[timeOfDay]);
  // display text
  StringExpandPlaceholders(gStringVar4, gText_CurrentDay);
  u8 x;
  x = GetStringCenterAlignXOffset(FONT_SMALL, gStringVar4, 11*8);
  AddTextPrinterParameterized(sHeatStartMenu->sDayWindowId, FONT_SMALL, gStringVar4, x, 0, 0xFF, NULL);
  CopyWindowToVram(sHeatStartMenu->sDayWindowId, COPYWIN_GFX);
  
  // time
  u8* ptr;
  ptr = ConvertIntToDecimalStringN(gStringVar1, hours, STR_CONV_MODE_LEADING_ZEROS, 2);
  
  // blinking colon. 0xF0 means :, 0x83 means a space that takes up 7 pixels. 
  // if you open the latin_normal.png font file you can see it's divided in 16x16 pixel tiles. the x83 one is 7 pixels of space.
  // this text uses the latin_small.png font, where the ':' character is at index 0xF0 and is 7 pixels wide, which is why we use the 0x83 tile for the space 
  *ptr = onOffColon ? 0xF0 : 0x83; 
  
  ConvertIntToDecimalStringN(ptr + 1, minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
  // display text
  StringExpandPlaceholders(gStringVar4, gText_CurrentTime);
  x = GetStringCenterAlignXOffset(FONT_SMALL, gStringVar4, 5*8);
  AddTextPrinterParameterized(sHeatStartMenu->sTimeWindowId, FONT_SMALL, gStringVar4, x, 0, 0xFF, NULL);
  CopyWindowToVram(sHeatStartMenu->sTimeWindowId, COPYWIN_GFX);
}

static const u8 sText_PyramidFloor1[] = _("PYRAMID FLOOR 1");
static const u8 sText_PyramidFloor2[] = _("PYRAMID FLOOR 2");
static const u8 sText_PyramidFloor3[] = _("PYRAMID FLOOR 3");
static const u8 sText_PyramidFloor4[] = _("PYRAMID FLOOR 4");
static const u8 sText_PyramidFloor5[] = _("PYRAMID FLOOR 5");
static const u8 sText_PyramidFloor6[] = _("PYRAMID FLOOR 6");
static const u8 sText_PyramidFloor7[] = _("PYRAMID FLOOR 7");
static const u8 sText_Pyramid[] = _("PYRAMID");

static const u8 *const sBattlePyramid_MapHeaderStrings[FRONTIER_STAGES_PER_CHALLENGE + 1] =
{
    sText_PyramidFloor1,
    sText_PyramidFloor2,
    sText_PyramidFloor3,
    sText_PyramidFloor4,
    sText_PyramidFloor5,
    sText_PyramidFloor6,
    sText_PyramidFloor7,
    sText_Pyramid,
};

static void HeatStartMenu_ShowMapNameWindow(void)
{
    u8 mapDisplayHeader[24];
    u8 *withoutPrefixPtr;
    u8 x;
    const u8 *mapDisplayHeaderSource;

    if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP)
        {
            withoutPrefixPtr = &(mapDisplayHeader[3]);
            mapDisplayHeaderSource = sBattlePyramid_MapHeaderStrings[FRONTIER_STAGES_PER_CHALLENGE];
        }
        else
        {
            withoutPrefixPtr = &(mapDisplayHeader[3]);
            mapDisplayHeaderSource = sBattlePyramid_MapHeaderStrings[gSaveBlock2Ptr->frontier.curChallengeBattleNum];
        }
        StringCopy(withoutPrefixPtr, mapDisplayHeaderSource);
    }
    else
    {
        withoutPrefixPtr = &(mapDisplayHeader[3]);
        GetMapName(withoutPrefixPtr, gMapHeader.regionMapSectionId, 0);
    }
    
    sHeatStartMenu->sMapNameWindowId = AddWindow(&sWindowTemplate_MapName);
    FillWindowPixelBuffer(sHeatStartMenu->sMapNameWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
    PutWindowTilemap(sHeatStartMenu->sMapNameWindowId);

    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;

    u32 font = GetFontIdToFit(withoutPrefixPtr, FONT_NORMAL, 0, 14*8);
    x = GetStringCenterAlignXOffset(font, withoutPrefixPtr, 14*8);
    AddTextPrinterParameterized(sHeatStartMenu->sMapNameWindowId, font, mapDisplayHeader, x, 0, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(sHeatStartMenu->sMapNameWindowId, COPYWIN_GFX);
}

static const u8 gText_Poketch[] = _("PokeNav");
static const u8 gText_Pokedex[] = _("Pokédex");
static const u8 gText_Party[]   = _("Party");
static const u8 gText_Bag[]     = _("Bag");
static const u8 gText_Trainer[] = _("Trainer");
static const u8 gText_Save[]    = _("Save");
static const u8 gText_Options[] = _("Options");
static const u8 gText_Flag[]    = _("Retire");

static void HeatStartMenu_UpdateMenuName(void)
{
  u8 x;

  FillWindowPixelBuffer(sHeatStartMenu->sMenuNameWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sMenuNameWindowId);

  const u8 *menuNameString;

  switch (menuSelected)
  {
  case HSMO_POKETCH:
    menuNameString = gText_Poketch;
    break;
  case HSMO_POKEDEX:
    menuNameString = gText_Pokedex;
    break;
  case HSMO_PARTY:
    menuNameString = gText_Party;
    break;
  case HSMO_BAG:
    menuNameString = gText_Bag;
    break;
  case HSMO_TRAINER_CARD:
    menuNameString = gText_Trainer;
    break;
  case HSMO_SAVE:
    menuNameString = gText_Save;
    break;
  case HSMO_OPTIONS:
    menuNameString = gText_Options;
    break;
  case HSMO_FLAG:
    menuNameString = gText_Flag;
    break;
  default:
    menuNameString = gText_Bag;
    break;
  }
  
  u32 font = GetFontIdToFit(menuNameString, FONT_NORMAL, 0, 7*8);
  x = GetStringCenterAlignXOffset(font, menuNameString, 7*8);
  AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, font, menuNameString, x, 0, 0xFF, NULL);
  CopyWindowToVram(sHeatStartMenu->sMenuNameWindowId, COPYWIN_GFX);
}



///// =================================================================================
///// ============ navigation and input handling ======================================
///// =================================================================================



static void HeatStartMenu_HandleInput_DPADDOWN(void)
{
  // Needs to be set to 0 so that the selected icons change in the frontend
  sHeatStartMenu->flag = 0;

  u8 index = ShownOptionToIndex(menuSelected);
  u8 count = HowManyOptionsShown();

  if(index >= count-1)
  {
    index = 0;
  }
  else {
    index++;
  }

  PlaySE(SE_SELECT);
  menuSelected = IndexToShownOption(index);

  HeatStartMenu_UpdateMenuName();
}

static void HeatStartMenu_HandleInput_DPADUP(void)
{
  sHeatStartMenu->flag = 0;

  u8 index = ShownOptionToIndex(menuSelected);
  u8 count = HowManyOptionsShown();

  if(index <= 0)
  {
    index = count - 1;
  }
  else {
    index--;
  }

  PlaySE(SE_SELECT);
  menuSelected = IndexToShownOption(index);

  HeatStartMenu_UpdateMenuName();
}

static void Task_HeatStartMenu_HandleMainInput(u8 taskId)
{

  // Handle input delay to prevent immediate processing of the button that opened the menu
  if (sHeatStartMenu->inputDelay > 0)
  {
      sHeatStartMenu->inputDelay--;
      return;
  }

  if(GetSafariZoneFlag() == FALSE){
    HeatStartMenu_UpdateClockDisplay();
  }
  if (JOY_NEW(A_BUTTON))
  {
    PlaySE(SE_SELECT);
    if (sHeatStartMenu->loadState == 0)
    {
      if (menuSelected != HSMO_SAVE)
      {
        FadeScreen(FADE_TO_BLACK, 0);
      }
      sHeatStartMenu->loadState = 1;
    }
  }
  else if (JOY_NEW(L_BUTTON))
  {
    if(IsLShortcutEnabledInGame() && sHeatStartMenu->loadState == 0)
    {
      menuSelected = HSM_CONFIG_L_SHORTCUT;
      HeatStartMenu_UpdateMenuName();
      PlaySE(SE_SELECT);
      if (HSM_CONFIG_L_SHORTCUT != HSMO_SAVE)
      {
        FadeScreen(FADE_TO_BLACK, 0);
      }
      sHeatStartMenu->loadState = 1;
    }
  }
  else if (JOY_NEW(R_BUTTON) && HSM_CONFIG_R_DEBUG && sHeatStartMenu->loadState == 0)
  {
    if (DEBUG_OVERWORLD_MENU)
    {
      PlaySE(SE_SELECT);
      HeatStartMenu_ExitAndClearTilemap(FALSE);
      DestroyTask(taskId);
      FreezeObjectEvents();
      Debug_ShowMainMenu();
    }
  }
  else if ((JOY_NEW(B_BUTTON) || JOY_NEW(START_BUTTON)) && sHeatStartMenu->loadState == 0)
  {
    PlaySE(SE_SELECT);
    HeatStartMenu_ExitAndClearTilemap(TRUE);
    DestroyTask(taskId);
  }
  else if (gMain.newKeys & DPAD_DOWN && sHeatStartMenu->loadState == 0)
  {
    HeatStartMenu_HandleInput_DPADDOWN();
  }
  else if (gMain.newKeys & DPAD_UP && sHeatStartMenu->loadState == 0)
  {
    HeatStartMenu_HandleInput_DPADUP();
  }
  else if (sHeatStartMenu->loadState == 1)
  {
    if (menuSelected == HSMO_FLAG)
    {
      DoCleanUpAndStartSafariZoneRetire();
    }
    else if (menuSelected == HSMO_SAVE)
    {
      DoCleanUpAndStartSaveMenu();
    }
    else
    {
      HeatStartMenu_OpenMenu();
    }
  }
}

///// =================================================================================
///// ============ menu actions =======================================================
///// =================================================================================

// used by many of the menu options to exit the start menu and either return to field or start that menu option
static void DoCleanUpAndChangeCallback(MainCallback callback)
{
  if (!gPaletteFade.active)
  {
    DestroyTask(FindTaskIdByFunc(Task_HeatStartMenu_HandleMainInput));
    PlayRainStoppingSoundEffect();
    HeatStartMenu_ExitAndClearTilemap(TRUE);
    CleanupOverworldWindowsAndTilemaps();
    SetMainCallback2(callback);
    gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
  }
}

static void DoCleanUpAndOpenTrainerCard(void)
{
  if (!gPaletteFade.active)
  {
    PlayRainStoppingSoundEffect();
    HeatStartMenu_ExitAndClearTilemap(TRUE);
    CleanupOverworldWindowsAndTilemaps();
    if (IsOverworldLinkActive() || InUnionRoom())
    {
      ShowPlayerTrainerCard(CB2_ReturnToFieldWithOpenMenu); // Display trainer card
      DestroyTask(FindTaskIdByFunc(Task_HeatStartMenu_HandleMainInput));
    }
    else if (FlagGet(FLAG_SYS_FRONTIER_PASS))
    {
      ShowFrontierPass(CB2_ReturnToFieldWithOpenMenu); // Display frontier pass
      DestroyTask(FindTaskIdByFunc(Task_HeatStartMenu_HandleMainInput));
    }
    else
    {
      ShowPlayerTrainerCard(CB2_ReturnToFieldWithOpenMenu); // Display trainer card
      DestroyTask(FindTaskIdByFunc(Task_HeatStartMenu_HandleMainInput));
    }
  }
}

static u8 RunSaveCallback(void)
{
  // True if text is still printing
  if (RunTextPrintersAndIsPrinter0Active() == TRUE)
  {
    return SAVE_IN_PROGRESS;
  }

  return sSaveDialogCallback();
}

static void SaveStartTimer(void)
{
  sSaveDialogTimer = 60;
}

static bool8 SaveSuccesTimer(void)
{
  sSaveDialogTimer--;

  if (JOY_HELD(A_BUTTON) || JOY_HELD(B_BUTTON))
  {
    PlaySE(SE_SELECT);
    return TRUE;
  }
  if (sSaveDialogTimer == 0)
  {
    return TRUE;
  }

  return FALSE;
}

static bool8 SaveErrorTimer(void)
{
  if (sSaveDialogTimer != 0)
  {
    sSaveDialogTimer--;
  }
  else if (JOY_HELD(A_BUTTON))
  {
    return TRUE;
  }

  return FALSE;
}

static u8 SaveReturnSuccessCallback(void)
{
  if (!IsSEPlaying() && SaveSuccesTimer())
  {
    HideSaveInfoWindow();
    return SAVE_SUCCESS;
  }
  else
  {
    return SAVE_IN_PROGRESS;
  }
}

static u8 SaveSuccessCallback(void)
{
  if (!IsTextPrinterActive(0))
  {
    PlaySE(SE_SAVE);
    sSaveDialogCallback = SaveReturnSuccessCallback;
  }

  return SAVE_IN_PROGRESS;
}

static u8 SaveReturnErrorCallback(void)
{
  if (!SaveErrorTimer())
  {
    return SAVE_IN_PROGRESS;
  }
  else
  {
    HideSaveInfoWindow();
    return SAVE_ERROR;
  }
}

static u8 SaveErrorCallback(void)
{
  if (!IsTextPrinterActive(0))
  {
    PlaySE(SE_BOO);
    sSaveDialogCallback = SaveReturnErrorCallback;
  }

  return SAVE_IN_PROGRESS;
}

static u8 SaveDoSaveCallback(void)
{
  u8 saveStatus;

  IncrementGameStat(GAME_STAT_SAVED_GAME);
  PausePyramidChallenge();

  if (gDifferentSaveFile == TRUE)
  {
    saveStatus = TrySavingData(SAVE_OVERWRITE_DIFFERENT_FILE);
    gDifferentSaveFile = FALSE;
  }
  else
  {
    saveStatus = TrySavingData(SAVE_NORMAL);
  }

  if (saveStatus == SAVE_STATUS_OK)
    ShowSaveMessage(gText_PlayerSavedGame, SaveSuccessCallback);
  else
    ShowSaveMessage(gText_SaveError, SaveErrorCallback);

  SaveStartTimer();
  return SAVE_IN_PROGRESS;
}

static void HideSaveInfoWindow(void)
{
  ClearStdWindowAndFrame(sSaveInfoWindowId, FALSE);
  RemoveWindow(sSaveInfoWindowId);
}

static void HideSaveMessageWindow(void)
{
  ClearDialogWindowAndFrame(0, TRUE);
}

static u8 SaveOverwriteInputCallback(void)
{
  switch (Menu_ProcessInputNoWrapClearOnChoose())
  {
  case 0: // Yes
    sSaveDialogCallback = SaveSavingMessageCallback;
    return SAVE_IN_PROGRESS;
  case MENU_B_PRESSED:
  case 1: // No
    HideSaveInfoWindow();
    HideSaveMessageWindow();
    return SAVE_CANCELED;
  }

  return SAVE_IN_PROGRESS;
}

static u8 SaveConfirmOverwriteDefaultNoCallback(void)
{
  DisplayYesNoMenuWithDefault(1); // Show Yes/No menu (No selected as default)
  sSaveDialogCallback = SaveOverwriteInputCallback;
  return SAVE_IN_PROGRESS;
}

static void ShowSaveMessage(const u8 *message, u8 (*saveCallback)(void))
{
  StringExpandPlaceholders(gStringVar4, message);
  LoadMessageBoxAndFrameGfx(0, TRUE);
  AddTextPrinterForMessage_2(TRUE);
  sSaveDialogCallback = saveCallback;
}

static u8 SaveFileExistsCallback(void)
{
  if (gDifferentSaveFile == TRUE)
  {
    ShowSaveMessage(gText_DifferentSaveFile, SaveConfirmOverwriteDefaultNoCallback);
  }
  else
  {
    sSaveDialogCallback = SaveSavingMessageCallback;
  }

  return SAVE_IN_PROGRESS;
}

static u8 SaveSavingMessageCallback(void)
{
  ShowSaveMessage(gText_SavingDontTurnOff, SaveDoSaveCallback);
  return SAVE_IN_PROGRESS;
}

static u8 SaveConfirmInputCallback(void)
{
  switch (Menu_ProcessInputNoWrapClearOnChoose())
  {
  case 0: // Yes
    switch (gSaveFileStatus)
    {
    case SAVE_STATUS_EMPTY:
    case SAVE_STATUS_CORRUPT:
      if (gDifferentSaveFile == FALSE)
      {
        sSaveDialogCallback = SaveFileExistsCallback;
        return SAVE_IN_PROGRESS;
      }

      sSaveDialogCallback = SaveSavingMessageCallback;
      return SAVE_IN_PROGRESS;
    default:
      sSaveDialogCallback = SaveFileExistsCallback;
      return SAVE_IN_PROGRESS;
    }
  case MENU_B_PRESSED: // No break, thats smart
  case 1:              // No
    HideSaveInfoWindow();
    HideSaveMessageWindow();
    return SAVE_CANCELED;
  }

  return SAVE_IN_PROGRESS;
}

static u8 SaveYesNoCallback(void)
{
  DisplayYesNoMenuDefaultYes(); // Show Yes/No menu
  sSaveDialogCallback = SaveConfirmInputCallback;
  return SAVE_IN_PROGRESS;
}

static void ShowSaveInfoWindow(void)
{
  struct WindowTemplate saveInfoWindow = sSaveInfoWindowTemplate;
  u8 gender;
  u8 color;
  u32 xOffset;
  u32 yOffset;

  if (FlagGet(FLAG_SYS_POKEDEX_GET) == FALSE)
  {
    saveInfoWindow.height -= 2;
  }

  sSaveInfoWindowId = AddWindow(&saveInfoWindow);
  DrawStdWindowFrame(sSaveInfoWindowId, FALSE);

  gender = gSaveBlock2Ptr->playerGender;
  color = TEXT_COLOR_RED; // Red when female, blue when male.

  if (gender == MALE)
  {
    color = TEXT_COLOR_BLUE;
  }

  // Print region name
  yOffset = 1;
  BufferSaveMenuText(SAVE_MENU_LOCATION, gStringVar4, TEXT_COLOR_GREEN);
  AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, 0, yOffset, TEXT_SKIP_DRAW, NULL);

  // Print player name
  yOffset += 16;
  AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingPlayer, 0, yOffset, TEXT_SKIP_DRAW, NULL);
  BufferSaveMenuText(SAVE_MENU_NAME, gStringVar4, color);
  xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
  PrintPlayerNameOnWindow(sSaveInfoWindowId, gStringVar4, xOffset, yOffset);

  // Print badge count
  yOffset += 16;
  AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingBadges, 0, yOffset, TEXT_SKIP_DRAW, NULL);
  BufferSaveMenuText(SAVE_MENU_BADGES, gStringVar4, color);
  xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
  AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, xOffset, yOffset, TEXT_SKIP_DRAW, NULL);

  if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE)
  {
    // Print pokedex count
    yOffset += 16;
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingPokedex, 0, yOffset, TEXT_SKIP_DRAW, NULL);
    BufferSaveMenuText(SAVE_MENU_CAUGHT, gStringVar4, color);
    xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, xOffset, yOffset, TEXT_SKIP_DRAW, NULL);
  }

  // Print play time
  yOffset += 16;
  AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingTime, 0, yOffset, TEXT_SKIP_DRAW, NULL);
  BufferSaveMenuText(SAVE_MENU_PLAY_TIME, gStringVar4, color);
  xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
  AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, xOffset, yOffset, TEXT_SKIP_DRAW, NULL);

  CopyWindowToVram(sSaveInfoWindowId, COPYWIN_GFX);
}

static u8 SaveConfirmSaveCallback(void)
{
  ClearStdWindowAndFrame(GetStartMenuWindowId(), FALSE);
  // RemoveStartMenuWindow();
  ShowSaveInfoWindow();

  if (InBattlePyramid_())
  {
    ShowSaveMessage(gText_BattlePyramidConfirmRest, SaveYesNoCallback);
  }
  else
  {
    ShowSaveMessage(gText_ConfirmSave, SaveYesNoCallback);
  }
  return SAVE_IN_PROGRESS;
}

static void InitSave(void)
{
  SaveMapView();
  sSaveDialogCallback = SaveConfirmSaveCallback;
}

static void Task_HandleSave(u8 taskId)
{
  switch (RunSaveCallback())
  {
  case SAVE_IN_PROGRESS:
    break;
  case SAVE_SUCCESS:
  case SAVE_CANCELED: // Back to start menu
    ClearDialogWindowAndFrameToTransparent(0, TRUE);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
    DestroyTask(taskId);
    break;
  case SAVE_ERROR: // Close start menu
    ClearDialogWindowAndFrameToTransparent(0, TRUE);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
    SoftResetInBattlePyramid();
    DestroyTask(taskId);
    break;
  }
}

#define STD_WINDOW_BASE_TILE_NUM 0x214
#define STD_WINDOW_PALETTE_NUM 14

static void DoCleanUpAndStartSaveMenu(void)
{
  if (!gPaletteFade.active)
  {
    HeatStartMenu_ExitAndClearTilemap(TRUE);
    FreezeObjectEvents();
    LoadUserWindowBorderGfx(sSaveInfoWindowId, STD_WINDOW_BASE_TILE_NUM, BG_PLTT_ID(STD_WINDOW_PALETTE_NUM));
    LockPlayerFieldControls();
    DestroyTask(FindTaskIdByFunc(Task_HeatStartMenu_HandleMainInput));
    InitSave();
    CreateTask(Task_HandleSave, 0x80);
  }
}

static void DoCleanUpAndStartSafariZoneRetire(void)
{
  if (!gPaletteFade.active)
  {
    HeatStartMenu_ExitAndClearTilemap(TRUE);
    FreezeObjectEvents();
    LockPlayerFieldControls();
    DestroyTask(FindTaskIdByFunc(Task_HeatStartMenu_HandleMainInput));
    SafariZoneRetirePrompt();
  }
}

static void HeatStartMenu_OpenMenu(void)
{
  switch (menuSelected)
  {
  case HSMO_POKETCH:
    DoCleanUpAndChangeCallback(CB2_InitPokeNav);
    break;
  case HSMO_POKEDEX:
    DoCleanUpAndChangeCallback(CB2_OpenPokedex);
    break;
  case HSMO_PARTY:
    DoCleanUpAndChangeCallback(CB2_PartyMenuFromStartMenu);
    break;
  case HSMO_BAG:
    DoCleanUpAndChangeCallback(CB2_BagMenuFromStartMenu);
    break;
  case HSMO_TRAINER_CARD:
    DoCleanUpAndOpenTrainerCard();
    break;
  case HSMO_OPTIONS:
    DoCleanUpAndChangeCallback(CB2_InitOptionMenu);
    break;
  }
}

/////// =================================================================================
/////// ============ exit and cleanup ===================================================
/////// =================================================================================

static void HeatStartMenu_ExitAndClearTilemap(bool8 enableMovement)
{
  u32 i;
  u8 *buf = GetBgTilemapBuffer(0);

  // remove text windows
  HeatStartMenu_CleanupTextWindow(sHeatStartMenu->sMenuNameWindowId);
  HeatStartMenu_CleanupTextWindow(sHeatStartMenu->sMapNameWindowId);

  if (GetSafariZoneFlag() == TRUE)
  {
    HeatStartMenu_CleanupTextWindow(sHeatStartMenu->sSafariBallsWindowId);
  } else {
    HeatStartMenu_CleanupTextWindow(sHeatStartMenu->sDayWindowId);
    HeatStartMenu_CleanupTextWindow(sHeatStartMenu->sTimeWindowId);
  }

  // clear tilemap
  for (i = 0; i < 2048; i++)
  {
    buf[i] = 0;
  }
  ScheduleBgCopyTilemapToVram(0);

  bool8 handleFlash = GetFlashLevel() > 0 || InBattlePyramid_();

  u8 m;
  for (m = 0; m < HSMO_COUNT; m++)
  {
    if(IsMenuOptionShown(m))
    {
      HeatStartMenu_CleanupSpriteFromMenuOption(m, handleFlash);
    }
  }

  if(IsLShortcutEnabledInGame())
  {
    HeatStartMenu_CleanupSpriteFromMenuOption(HSM_CONFIG_L_SHORTCUT, handleFlash);
  }

  // finishing touches
  if (sHeatStartMenu != NULL)
  {
    FreeSpriteTilesByTag(TAG_ICON_GFX);
    Free(sHeatStartMenu);
    sHeatStartMenu = NULL;
  }

  if(enableMovement)
  {
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
  }
}

static void HeatStartMenu_CleanupTextWindow(u32 windowId)
{
  FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
  ClearWindowTilemap(windowId);
  CopyWindowToVram(windowId, COPYWIN_GFX);
  RemoveWindow(windowId);
}

static void HeatStartMenu_CleanupSpriteFromMenuOption(u8 menu, bool8 flash)
{
  switch (menu)
  {
  case HSMO_POKEDEX:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdPokedex]);
    break;
  case HSMO_PARTY:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdParty]);
    break;
  case HSMO_BAG:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdBag]);    
    break;
  case HSMO_POKETCH:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdPoketch]);
    break;
  case HSMO_TRAINER_CARD:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdTrainerCard]);
    break;
  case HSMO_SAVE:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdSave]);
    break;
  case HSMO_OPTIONS:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdOptions]);
    break;
  case HSMO_FLAG:
    HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdFlag]);
    break;
  default:
    break;
  }

  if (flash)
  {
    switch (menu)
    {
    case HSMO_POKEDEX:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdPokedexFlash]);
      break;
    case HSMO_PARTY:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdPartyFlash]);
      break;
    case HSMO_BAG:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdBagFlash]);
      break;
    case HSMO_POKETCH:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdPoketchFlash]);
      break;
    case HSMO_TRAINER_CARD:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdTrainerCardFlash]);
      break;
    case HSMO_SAVE:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdSaveFlash]);
      break;
    case HSMO_OPTIONS:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdOptionsFlash]);
      break;
    case HSMO_FLAG:
      HeatStartMenu_CleanupSprite(&gSprites[sHeatStartMenu->spriteIdFlagFlash]);
      break;
    default:
      break;
    }
  }
  
}

static void HeatStartMenu_CleanupSprite(struct Sprite *sprite)
{
  FreeSpriteOamMatrix(sprite);
  DestroySprite(sprite);
}