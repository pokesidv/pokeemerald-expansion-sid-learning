#include "global.h"
#include "vag_ui_palettes.h"
#include "palette.h"
#include "menu.h"

static const u16 sVagUiPalettes[8][16] = {
    INCBIN_U16("graphics/vag_palettes/ui_light_1_vigor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/ui_light_2_ardor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/ui_light_3_guile.gbapal"),
    INCBIN_U16("graphics/vag_palettes/ui_light_4_university.gbapal"),
    INCBIN_U16("graphics/vag_palettes/ui_dark_1_vigor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/ui_dark_2_ardor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/ui_dark_3_guile.gbapal"),
    INCBIN_U16("graphics/vag_palettes/ui_dark_4_university.gbapal"),
};
static const u16 sVagUiTextPalettes[8][16] = {
    INCBIN_U16("graphics/vag_palettes/texts_light_1_vigor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/texts_light_2_ardor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/texts_light_3_guile.gbapal"),
    INCBIN_U16("graphics/vag_palettes/texts_light_4_university.gbapal"),
    INCBIN_U16("graphics/vag_palettes/texts_dark_1_vigor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/texts_dark_2_ardor.gbapal"),
    INCBIN_U16("graphics/vag_palettes/texts_dark_3_guile.gbapal"),
    INCBIN_U16("graphics/vag_palettes/texts_dark_4_university.gbapal"),
};

const u16 *GetVagUiPalette()
{
    switch (gMapHeader.regionMapSectionId)
    {
    case MAPSEC_IRONWILL_MONASTERY:
        return sVagUiPalettes[1];
    case MAPSEC_ARDOR_3A:
        return sVagUiPalettes[0];
    case MAPSEC_ARDOR_3B:
        return sVagUiPalettes[3];
    case MAPSEC_ARDOR_2A:
        return sVagUiPalettes[2];
    default:
        return sVagUiPalettes[3];
    }
}

const u16 *GetVagUiTextsPalette()
{
    switch (gMapHeader.regionMapSectionId)
    {
    case MAPSEC_IRONWILL_MONASTERY:
        return sVagUiTextPalettes[1];
    case MAPSEC_ARDOR_3A:
        return sVagUiTextPalettes[0];
    case MAPSEC_ARDOR_3B:
        return sVagUiTextPalettes[3];
    case MAPSEC_ARDOR_2A:
        return sVagUiTextPalettes[2];
    default:
        return sVagUiTextPalettes[3];
    }
}