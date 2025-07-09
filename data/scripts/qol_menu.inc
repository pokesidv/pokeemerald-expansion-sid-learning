EventScript_QolMenu::
# 18 "data/scripts/qol_menu.pory"
	lock
# 20 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_2
# 23 "data/scripts/qol_menu.pory"
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
# 57 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_7, 9
# 59 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
# 61 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 62 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_16
# 70 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_17
# 72 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_18
# 75 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_19
# 77 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_20
# 79 "data/scripts/qol_menu.pory"
	case 6, EventScript_QolMenu_21
# 81 "data/scripts/qol_menu.pory"
	case 7, EventScript_QolMenu_22
# 83 "data/scripts/qol_menu.pory"
	case 8, EventScript_QolMenu_23
# 91 "data/scripts/qol_menu.pory"
	case 9, EventScript_QolMenu_24
EventScript_QolMenu_14:
# 95 "data/scripts/qol_menu.pory"
	waitmessage
# 96 "data/scripts/qol_menu.pory"
	release
	end

EventScript_QolMenu_2:
# 21 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 1
	goto EventScript_QolMenu_1

EventScript_QolMenu_6:
# 27 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 28 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 29 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 30 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8006
# 31 "data/scripts/qol_menu.pory"
	compare VAR_0x8006, 0
	goto_if_eq EventScript_QolMenu_11
# 34 "data/scripts/qol_menu.pory"
	pokevialisfull
# 35 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 1
	goto_if_eq EventScript_QolMenu_28
# 38 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_9:
# 50 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_25
# 53 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 8
	goto EventScript_QolMenu_8

EventScript_QolMenu_11:
# 32 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_16:
# 63 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_31
# 67 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 68 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_9
	goto EventScript_QolMenu_14

EventScript_QolMenu_17:
# 71 "data/scripts/qol_menu.pory"
	pokevialtryuse
	goto EventScript_QolMenu_14

EventScript_QolMenu_18:
# 73 "data/scripts/qol_menu.pory"
	pokevialincreasesize
# 74 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_14

EventScript_QolMenu_19:
# 76 "data/scripts/qol_menu.pory"
	pokevialdecreasesize
	goto EventScript_QolMenu_14

EventScript_QolMenu_20:
# 78 "data/scripts/qol_menu.pory"
	pokevialadddose
	goto EventScript_QolMenu_14

EventScript_QolMenu_21:
# 80 "data/scripts/qol_menu.pory"
	pokevialremovedose
	goto EventScript_QolMenu_14

EventScript_QolMenu_22:
# 82 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_14

EventScript_QolMenu_23:
# 84 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_34
# 88 "data/scripts/qol_menu.pory"
	setflag FLAG_I_EXP_SHARE
# 89 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_11
	goto EventScript_QolMenu_14

EventScript_QolMenu_24:
# 92 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_Wait
	goto EventScript_QolMenu_14

EventScript_QolMenu_25:
# 51 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 8
	goto EventScript_QolMenu_8

EventScript_QolMenu_28:
# 36 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_31:
# 64 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 65 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_8
	goto EventScript_QolMenu_14

EventScript_QolMenu_34:
# 85 "data/scripts/qol_menu.pory"
	clearflag FLAG_I_EXP_SHARE
# 86 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_10
	goto EventScript_QolMenu_14


EventScript_QolMenu_Wait::
# 102 "data/scripts/qol_menu.pory"
	lock
# 103 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 10
# 104 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 20
# 105 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 30
# 106 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 40
# 108 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
# 110 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 111 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_Wait_3
# 113 "data/scripts/qol_menu.pory"
	case 20, EventScript_QolMenu_Wait_4
# 115 "data/scripts/qol_menu.pory"
	case 30, EventScript_QolMenu_Wait_5
# 117 "data/scripts/qol_menu.pory"
	case 40, EventScript_QolMenu_Wait_6
EventScript_QolMenu_Wait_1:
# 121 "data/scripts/qol_menu.pory"
	waitmessage
# 122 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_Wait_3:
# 112 "data/scripts/qol_menu.pory"
	waittillmorning
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_4:
# 114 "data/scripts/qol_menu.pory"
	waittillday
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_5:
# 116 "data/scripts/qol_menu.pory"
	waittillevening
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_6:
# 118 "data/scripts/qol_menu.pory"
	waittillnight
	goto EventScript_QolMenu_Wait_1


EventScript_QolMenu_Text_0:
# 21 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_1:
# 23 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}off$"

EventScript_QolMenu_Text_2:
# 32 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}0/{STR_VAR_2}$"

EventScript_QolMenu_Text_3:
# 36 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_4:
# 38 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_5:
# 51 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_6:
# 53 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}off$"

EventScript_QolMenu_Text_7:
# 57 "data/scripts/qol_menu.pory"
	.string "Wait until...$"

EventScript_QolMenu_Text_8:
# 65 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_9:
# 68 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"

EventScript_QolMenu_Text_10:
# 86 "data/scripts/qol_menu.pory"
	.string "Exp-all turned off. That's the sigma\n"
	.string "grindset way.$"

EventScript_QolMenu_Text_11:
# 89 "data/scripts/qol_menu.pory"
	.string "Exp-all turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. Easy level farming\n"
	.string "for your whole party!$"

EventScript_QolMenu_Wait_Text_0:
# 103 "data/scripts/qol_menu.pory"
	.string "Morning$"

EventScript_QolMenu_Wait_Text_1:
# 104 "data/scripts/qol_menu.pory"
	.string "Day$"

EventScript_QolMenu_Wait_Text_2:
# 105 "data/scripts/qol_menu.pory"
	.string "Evening$"

EventScript_QolMenu_Wait_Text_3:
# 106 "data/scripts/qol_menu.pory"
	.string "Night$"
