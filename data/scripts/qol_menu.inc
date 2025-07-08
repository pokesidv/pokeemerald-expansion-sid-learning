EventScript_QolMenu::
# 3 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_2
# 6 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_1, 1
EventScript_QolMenu_1:
# 8 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
# 9 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 3
# 10 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 4
# 11 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 5
# 12 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 6
# 13 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_7, 7
# 14 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_8, 8
# 16 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 8, FALSE, 1, DYN_MULTICHOICE_CB_NONE
# 17 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 18 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_7
EventScript_QolMenu_5:
	end

EventScript_QolMenu_2:
# 4 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 1
	goto EventScript_QolMenu_1

EventScript_QolMenu_7:
# 19 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_9
# 23 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 24 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_10
EventScript_QolMenu_8:
# 26 "data/scripts/qol_menu.pory"
	waitmessage
# 27 "data/scripts/qol_menu.pory"
	release
	goto EventScript_QolMenu_5

EventScript_QolMenu_9:
# 20 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 21 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_9
	goto EventScript_QolMenu_8


EventScript_QolMenu_Text_0:
# 4 "data/scripts/qol_menu.pory"
	.string "Repel:  {COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_1:
# 6 "data/scripts/qol_menu.pory"
	.string "Repel:  off$"

EventScript_QolMenu_Text_2:
# 8 "data/scripts/qol_menu.pory"
	.string "Option 2$"

EventScript_QolMenu_Text_3:
# 9 "data/scripts/qol_menu.pory"
	.string "Option 3$"

EventScript_QolMenu_Text_4:
# 10 "data/scripts/qol_menu.pory"
	.string "Option 4$"

EventScript_QolMenu_Text_5:
# 11 "data/scripts/qol_menu.pory"
	.string "Option 5$"

EventScript_QolMenu_Text_6:
# 12 "data/scripts/qol_menu.pory"
	.string "Option 6$"

EventScript_QolMenu_Text_7:
# 13 "data/scripts/qol_menu.pory"
	.string "Option 7$"

EventScript_QolMenu_Text_8:
# 14 "data/scripts/qol_menu.pory"
	.string "Option 8$"

EventScript_QolMenu_Text_9:
# 21 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_10:
# 24 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"
