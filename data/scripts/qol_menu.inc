EventScript_QolMenu::
# 12 "data/scripts/qol_menu.pory"
	lock
# 14 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_2
# 17 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_1, 1
EventScript_QolMenu_1:
	checkitem ITEM_POKEVIAL
# 0 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 0
	goto_if_ne EventScript_QolMenu_6
EventScript_QolMenu_5:
	checkitem ITEM_EXP_ALL
# 0 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 0
	goto_if_ne EventScript_QolMenu_9
EventScript_QolMenu_8:
# 52 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
# 54 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 55 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_16
# 63 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_17
# 65 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_18
# 68 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_19
# 70 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_20
# 72 "data/scripts/qol_menu.pory"
	case 6, EventScript_QolMenu_21
# 74 "data/scripts/qol_menu.pory"
	case 7, EventScript_QolMenu_22
# 76 "data/scripts/qol_menu.pory"
	case 8, EventScript_QolMenu_23
EventScript_QolMenu_14:
# 86 "data/scripts/qol_menu.pory"
	waitmessage
# 87 "data/scripts/qol_menu.pory"
	release
	end

EventScript_QolMenu_2:
# 15 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 1
	goto EventScript_QolMenu_1

EventScript_QolMenu_6:
# 22 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 23 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 24 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 25 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8006
# 26 "data/scripts/qol_menu.pory"
	compare VAR_0x8006, 0
	goto_if_eq EventScript_QolMenu_11
# 29 "data/scripts/qol_menu.pory"
	pokevialisfull
# 30 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 1
	goto_if_eq EventScript_QolMenu_27
# 33 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_9:
# 45 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_24
# 48 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 8
	goto EventScript_QolMenu_8

EventScript_QolMenu_11:
# 27 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_16:
# 56 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_30
# 60 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 61 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_8
	goto EventScript_QolMenu_14

EventScript_QolMenu_17:
# 64 "data/scripts/qol_menu.pory"
	pokevialtryuse
	goto EventScript_QolMenu_14

EventScript_QolMenu_18:
# 66 "data/scripts/qol_menu.pory"
	pokevialincreasesize
# 67 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_14

EventScript_QolMenu_19:
# 69 "data/scripts/qol_menu.pory"
	pokevialdecreasesize
	goto EventScript_QolMenu_14

EventScript_QolMenu_20:
# 71 "data/scripts/qol_menu.pory"
	pokevialadddose
	goto EventScript_QolMenu_14

EventScript_QolMenu_21:
# 73 "data/scripts/qol_menu.pory"
	pokevialremovedose
	goto EventScript_QolMenu_14

EventScript_QolMenu_22:
# 75 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_14

EventScript_QolMenu_23:
# 77 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_33
# 81 "data/scripts/qol_menu.pory"
	setflag FLAG_I_EXP_SHARE
# 82 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_10
	goto EventScript_QolMenu_14

EventScript_QolMenu_24:
# 46 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 8
	goto EventScript_QolMenu_8

EventScript_QolMenu_27:
# 31 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_30:
# 57 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 58 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_7
	goto EventScript_QolMenu_14

EventScript_QolMenu_33:
# 78 "data/scripts/qol_menu.pory"
	clearflag FLAG_I_EXP_SHARE
# 79 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_9
	goto EventScript_QolMenu_14


EventScript_QolMenu_Text_0:
# 15 "data/scripts/qol_menu.pory"
	.string "Repel:          {COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_1:
# 17 "data/scripts/qol_menu.pory"
	.string "Repel:         off$"

EventScript_QolMenu_Text_2:
# 27 "data/scripts/qol_menu.pory"
	.string "Pokévial: 0/{STR_VAR_2}$"

EventScript_QolMenu_Text_3:
# 31 "data/scripts/qol_menu.pory"
	.string "Pokévial:   {COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_4:
# 33 "data/scripts/qol_menu.pory"
	.string "Pokévial:   {COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_5:
# 46 "data/scripts/qol_menu.pory"
	.string "Exp-All:       {COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_6:
# 48 "data/scripts/qol_menu.pory"
	.string "Exp-All:      off$"

EventScript_QolMenu_Text_7:
# 58 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_8:
# 61 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"

EventScript_QolMenu_Text_9:
# 79 "data/scripts/qol_menu.pory"
	.string "Exp-all turned off. That's the sigma\n"
	.string "grindset way.$"

EventScript_QolMenu_Text_10:
# 82 "data/scripts/qol_menu.pory"
	.string "Exp-all turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. Easy level farming\n"
	.string "for your whole party!$"
