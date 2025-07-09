EventScript_QolMenu::
# 3 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_2
# 6 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_1, 1
EventScript_QolMenu_1:
# 10 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 11 "data/scripts/qol_menu.pory"
	copyvar VAR_0x8005, VAR_0x8006
# 12 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 13 "data/scripts/qol_menu.pory"
	copyvar VAR_0x8004, VAR_0x8006
# 14 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8005
# 15 "data/scripts/qol_menu.pory"
	compare VAR_0x8005, 0
	goto_if_eq EventScript_QolMenu_6
# 17 "data/scripts/qol_menu.pory"
	compare VAR_0x8005, 1
	goto_if_eq EventScript_QolMenu_7
# 20 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 2
EventScript_QolMenu_5:
# 24 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 2
# 25 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 3
# 26 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_7, 4
# 40 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
# 41 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 42 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_13
EventScript_QolMenu_11:
	end

EventScript_QolMenu_2:
# 4 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 1
	goto EventScript_QolMenu_1

EventScript_QolMenu_6:
# 16 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_7:
# 18 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_13:
# 43 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_15
# 47 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 48 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_9
EventScript_QolMenu_14:
# 50 "data/scripts/qol_menu.pory"
	waitmessage
# 51 "data/scripts/qol_menu.pory"
	release
	goto EventScript_QolMenu_11

EventScript_QolMenu_15:
# 44 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 45 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_8
	goto EventScript_QolMenu_14


EventScript_QolMenu_Text_0:
# 4 "data/scripts/qol_menu.pory"
	.string "Repel:  {COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_1:
# 6 "data/scripts/qol_menu.pory"
	.string "Repel:  off$"

EventScript_QolMenu_Text_2:
# 16 "data/scripts/qol_menu.pory"
	.string "Pokévial: empty$"

EventScript_QolMenu_Text_3:
# 18 "data/scripts/qol_menu.pory"
	.string "Pokévial: {COLOR GREEN}{SHADOW LIGHT_GREEN}1{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} use$"

EventScript_QolMenu_Text_4:
# 20 "data/scripts/qol_menu.pory"
	.string "Pokévial: {COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} uses$"

EventScript_QolMenu_Text_5:
# 24 "data/scripts/qol_menu.pory"
	.string "Option 2$"

EventScript_QolMenu_Text_6:
# 25 "data/scripts/qol_menu.pory"
	.string "Option 3$"

EventScript_QolMenu_Text_7:
# 26 "data/scripts/qol_menu.pory"
	.string "Option 4$"

EventScript_QolMenu_Text_8:
# 45 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_9:
# 48 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"
