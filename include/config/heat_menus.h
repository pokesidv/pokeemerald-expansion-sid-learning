#define ENABLE_HEAT_START_MENU           TRUE    // If TRUE, enables the heat start menu feature
#define HEAT_MENUS_SAVEBLOCK_PALETTES    FALSE   // If TRUE, start menu palette setting is saved to SaveBlock2. If FALSE, always uses default palette. In heat_menu_palettes.c you can change the logic that loads the right palette

// change these configs to toggle showing/hiding certain menu options
// note that some options are also dependent on flags or other conditions
// e.g. Pokedex requires the Pokedex flag to be set, 
// while Poketch requires Pokenav flag to be set and Safari Zone to be off
#define HSM_CONFIG_SHOW_POKEDEX        TRUE
#define HSM_CONFIG_SHOW_PARTY          TRUE
#define HSM_CONFIG_SHOW_BAG            TRUE
#define HSM_CONFIG_SHOW_POKETCH        TRUE
#define HSM_CONFIG_SHOW_TRAINER_CARD   TRUE
#define HSM_CONFIG_SHOW_OPTIONS        TRUE

// shortcut to open a menu with the L button without having it show up on one of the options
// if you want to disable the L button shortcut, set this to HSMO_COUNT. 
// Otherwise, set it to HSMO_POKEDEX, HSMO_POKETCH, HSMO_PARTY, HSMO_BAG or another menu option as listed in the MENU enum in heat_start_menu.c
#define HSM_CONFIG_L_SHORTCUT       HSMO_COUNT

// set this to TRUE to enable opening the debug menu by pressing R while in the start menu
#define HSM_CONFIG_R_DEBUG          FALSE

#define ENABLE_HEAT_SELECT_MENU     FALSE   // If TRUE, enables the heat select menu feature. 
// remember to go into config/save.h to enable ENABLE_MULTIPLE_REGISTERED_ITEMS as well if you want to scroll through a list of registered items on this menu
// also remember to enable OW_USE_FAKE_RTC in config/overworld.h if you want to use the time picker feature
// also remember to set up the I_EXP_SHARE_FLAG if you want the start button to toggle Exp-All on/off, and to set I_EXP_SHARE_ITEM to GEN_6 or higher in config/item.h

// in particular, if you want to use the fake RTC and the time picker, be aware that setting the wall clock messes up 
// the link between fake RTC time, and the time of day shown by the overworld day/night blend. 
// In my hack I avoid setting the wall clock altogether because the player can just set the time of day via the select menu, 
// and I have removed the wall clock auto-set from the debug menu action in my project to avoid setting it up accidentally when developing.
// But there should definitely be a way to set up the fake RTC and wall clock properly with the overworld day/night cycle,
// I just never wrapped my head around it. the time waiting functions and AccurateTimeOfDay function are coherent with each other when using Fake RTC and this time-picker, 
// which is what matters most for gameplay purposes.

#define INFINITE_REPEL_FLAG         0 // assign this to an unused flag if you want the select button inside the select menu to toggle between infinite repel ON and OFF