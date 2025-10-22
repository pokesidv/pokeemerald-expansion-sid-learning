#define ENABLE_HEAT_START_MENU                    TRUE   // If TRUE, enables the heat start menu feature
#define HEAT_MENUS_SAVEBLOCK_PALETTES             FALSE  // If TRUE, start menu palette setting is saved to SaveBlock2. If FALSE, always uses default palette. In heat_menu_palettes.c you can change the logic that loads the right palette

// change these configs to toggle showing/hiding certain menu options
// note that some options are also dependent on flags or other conditions
// e.g. Pokedex requires the Pokedex flag to be set, 
// while Poketch requires Pokenav flag to be set and Safari Zone to be off
#define HSM_CONFIG_SHOW_POKEDEX TRUE
#define HSM_CONFIG_SHOW_PARTY TRUE
#define HSM_CONFIG_SHOW_BAG TRUE
#define HSM_CONFIG_SHOW_POKETCH TRUE
#define HSM_CONFIG_SHOW_TRAINER_CARD TRUE
#define HSM_CONFIG_SHOW_OPTIONS TRUE

// shortcut to open a menu with the L button without having it show up on one of the options
// if you want to disable the L button shortcut, set this to HSMO_COUNT. 
// Otherwise, set it to HSMO_POKETCH or another menu option as listed in the MENU enum in heat_start_menu.c
#define HSM_CONFIG_L_SHORTCUT HSMO_COUNT

// set this to TRUE to enable opening the debug menu by pressing R while in the start menu
#define HSM_CONFIG_R_DEBUG FALSE