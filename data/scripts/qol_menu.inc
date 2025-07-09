EventScript_QolMenu::
# 11 "data/scripts/qol_menu.pory"
	lock
# 13 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_2
# 16 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_1, 1
EventScript_QolMenu_1:
# 19 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 20 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 21 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 22 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8006
# 23 "data/scripts/qol_menu.pory"
	compare VAR_0x8006, 0
	goto_if_eq EventScript_QolMenu_6
# 26 "data/scripts/qol_menu.pory"
	pokevialisfull
# 27 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 1
	goto_if_eq EventScript_QolMenu_18
# 30 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 2
EventScript_QolMenu_5:
# 40 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
# 42 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 43 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_11
# 51 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_12
# 53 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_13
# 56 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_14
# 58 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_15
# 60 "data/scripts/qol_menu.pory"
	case 6, EventScript_QolMenu_16
# 62 "data/scripts/qol_menu.pory"
	case 7, EventScript_QolMenu_17
EventScript_QolMenu_9:
# 66 "data/scripts/qol_menu.pory"
	waitmessage
# 67 "data/scripts/qol_menu.pory"
	release
	end

EventScript_QolMenu_2:
# 14 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 1
	goto EventScript_QolMenu_1

EventScript_QolMenu_6:
# 24 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_11:
# 44 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_21
# 48 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 49 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_6
	goto EventScript_QolMenu_9

EventScript_QolMenu_12:
# 52 "data/scripts/qol_menu.pory"
	pokevialtryuse
	goto EventScript_QolMenu_9

EventScript_QolMenu_13:
# 54 "data/scripts/qol_menu.pory"
	pokevialincreasesize
# 55 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_9

EventScript_QolMenu_14:
# 57 "data/scripts/qol_menu.pory"
	pokevialdecreasesize
	goto EventScript_QolMenu_9

EventScript_QolMenu_15:
# 59 "data/scripts/qol_menu.pory"
	pokevialadddose
	goto EventScript_QolMenu_9

EventScript_QolMenu_16:
# 61 "data/scripts/qol_menu.pory"
	pokevialremovedose
	goto EventScript_QolMenu_9

EventScript_QolMenu_17:
# 63 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_9

EventScript_QolMenu_18:
# 28 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_21:
# 45 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 46 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_5
	goto EventScript_QolMenu_9


EventScript_QolMenu_Text_0:
# 14 "data/scripts/qol_menu.pory"
	.string "Repel:  {COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_1:
# 16 "data/scripts/qol_menu.pory"
	.string "Repel:  off$"

EventScript_QolMenu_Text_2:
# 24 "data/scripts/qol_menu.pory"
	.string "Pokévial: 0/{STR_VAR_2}$"

EventScript_QolMenu_Text_3:
# 28 "data/scripts/qol_menu.pory"
	.string "Pokévial: {COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_4:
# 30 "data/scripts/qol_menu.pory"
	.string "Pokévial: {COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_5:
# 46 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_6:
# 49 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"
