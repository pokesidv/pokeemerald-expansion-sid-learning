EventScript_QolMenu::
# 19 "data/scripts/qol_menu.pory"
	lock
# 21 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_2
# 24 "data/scripts/qol_menu.pory"
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
# 58 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_7, 9
# 60 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_8, 10
# 62 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
# 64 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 65 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_16
# 73 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_17
# 75 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_18
# 78 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_19
# 80 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_20
# 82 "data/scripts/qol_menu.pory"
	case 6, EventScript_QolMenu_21
# 84 "data/scripts/qol_menu.pory"
	case 7, EventScript_QolMenu_22
# 86 "data/scripts/qol_menu.pory"
	case 8, EventScript_QolMenu_23
# 94 "data/scripts/qol_menu.pory"
	case 9, EventScript_QolMenu_24
# 96 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_25
EventScript_QolMenu_14:
# 100 "data/scripts/qol_menu.pory"
	waitmessage
# 101 "data/scripts/qol_menu.pory"
	release
	end

EventScript_QolMenu_2:
# 22 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 1
	goto EventScript_QolMenu_1

EventScript_QolMenu_6:
# 28 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 29 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 30 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 31 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8006
# 32 "data/scripts/qol_menu.pory"
	compare VAR_0x8006, 0
	goto_if_eq EventScript_QolMenu_11
# 35 "data/scripts/qol_menu.pory"
	pokevialisfull
# 36 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 1
	goto_if_eq EventScript_QolMenu_29
# 39 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_9:
# 51 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_26
# 54 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 8
	goto EventScript_QolMenu_8

EventScript_QolMenu_11:
# 33 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_16:
# 66 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_32
# 70 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 71 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_10
	goto EventScript_QolMenu_14

EventScript_QolMenu_17:
# 74 "data/scripts/qol_menu.pory"
	pokevialtryuse
	goto EventScript_QolMenu_14

EventScript_QolMenu_18:
# 76 "data/scripts/qol_menu.pory"
	pokevialincreasesize
# 77 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_14

EventScript_QolMenu_19:
# 79 "data/scripts/qol_menu.pory"
	pokevialdecreasesize
	goto EventScript_QolMenu_14

EventScript_QolMenu_20:
# 81 "data/scripts/qol_menu.pory"
	pokevialadddose
	goto EventScript_QolMenu_14

EventScript_QolMenu_21:
# 83 "data/scripts/qol_menu.pory"
	pokevialremovedose
	goto EventScript_QolMenu_14

EventScript_QolMenu_22:
# 85 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_14

EventScript_QolMenu_23:
# 87 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_35
# 91 "data/scripts/qol_menu.pory"
	setflag FLAG_I_EXP_SHARE
# 92 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_12
	goto EventScript_QolMenu_14

EventScript_QolMenu_24:
# 95 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_Wait
	goto EventScript_QolMenu_14

EventScript_QolMenu_25:
# 97 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_PickAbiliChangeMon
	goto EventScript_QolMenu_14

EventScript_QolMenu_26:
# 52 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 8
	goto EventScript_QolMenu_8

EventScript_QolMenu_29:
# 37 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 2
	goto EventScript_QolMenu_5

EventScript_QolMenu_32:
# 67 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 68 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_9
	goto EventScript_QolMenu_14

EventScript_QolMenu_35:
# 88 "data/scripts/qol_menu.pory"
	clearflag FLAG_I_EXP_SHARE
# 89 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_11
	goto EventScript_QolMenu_14


EventScript_QolMenu_Wait::
# 107 "data/scripts/qol_menu.pory"
	lock
# 108 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 10
# 109 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 20
# 110 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 30
# 111 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 40
# 113 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
# 115 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 116 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_Wait_3
# 118 "data/scripts/qol_menu.pory"
	case 20, EventScript_QolMenu_Wait_4
# 120 "data/scripts/qol_menu.pory"
	case 30, EventScript_QolMenu_Wait_5
# 122 "data/scripts/qol_menu.pory"
	case 40, EventScript_QolMenu_Wait_6
EventScript_QolMenu_Wait_1:
# 126 "data/scripts/qol_menu.pory"
	waitmessage
# 127 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_Wait_3:
# 117 "data/scripts/qol_menu.pory"
	waittillmorning
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_4:
# 119 "data/scripts/qol_menu.pory"
	waittillday
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_5:
# 121 "data/scripts/qol_menu.pory"
	waittillevening
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_6:
# 123 "data/scripts/qol_menu.pory"
	waittillnight
	goto EventScript_QolMenu_Wait_1


EventScript_QolMenu_PickAbiliChangeMon::
# 132 "data/scripts/qol_menu.pory"
	lock
# 133 "data/scripts/qol_menu.pory"
	getpartysize
# 134 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 135 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_PickAbiliChangeMon_2
# 141 "data/scripts/qol_menu.pory"
	special ChoosePartyMon
# 142 "data/scripts/qol_menu.pory"
	waitstate
# 143 "data/scripts/qol_menu.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge EventScript_QolMenu_PickAbiliChangeMon_4
# 149 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_ShowAbilityMultichoice
	return

EventScript_QolMenu_PickAbiliChangeMon_2:
# 136 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_0
# 137 "data/scripts/qol_menu.pory"
	waitmessage
# 138 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickAbiliChangeMon_4:
# 144 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_1
# 145 "data/scripts/qol_menu.pory"
	waitmessage
# 146 "data/scripts/qol_menu.pory"
	release
	return


EventScript_QolMenu_ShowAbilityMultichoice::
# 157 "data/scripts/qol_menu.pory"
	getchosenmonabilities
# 158 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 159 "data/scripts/qol_menu.pory"
	case -1, EventScript_QolMenu_ShowAbilityMultichoice_3
# 164 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_4
# 169 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_ShowAbilityMultichoice_5
# 174 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_6
# 180 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_7
# 186 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_ShowAbilityMultichoice_8
# 192 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_ShowAbilityMultichoice_9
# 200 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_7
# 201 "data/scripts/qol_menu.pory"
	waitmessage
# 202 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_1:
# 207 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 208 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_13
# 211 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_14
# 214 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_15
# 218 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_11
EventScript_QolMenu_ShowAbilityMultichoice_11:
# 220 "data/scripts/qol_menu.pory"
	waitmessage
# 221 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_3:
# 160 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_0
# 161 "data/scripts/qol_menu.pory"
	waitmessage
# 162 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_4:
# 165 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_1
# 166 "data/scripts/qol_menu.pory"
	waitmessage
# 167 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_5:
# 170 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_2
# 171 "data/scripts/qol_menu.pory"
	waitmessage
# 172 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_6:
# 176 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 177 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 178 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 179 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_7:
# 182 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 183 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 184 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 185 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_8:
# 188 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 189 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 190 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 191 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_9:
# 194 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 195 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 196 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 197 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 198 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_13:
# 209 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_8
# 210 "data/scripts/qol_menu.pory"
	setchosenmonfirstability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_14:
# 212 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_9
# 213 "data/scripts/qol_menu.pory"
	setchosenmonsecondability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_15:
# 215 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_10
# 216 "data/scripts/qol_menu.pory"
	setchosenmonhiddenability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11


EventScript_QolMenu_Text_0:
# 22 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_1:
# 24 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}off$"

EventScript_QolMenu_Text_2:
# 33 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}0/{STR_VAR_2}$"

EventScript_QolMenu_Text_3:
# 37 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_4:
# 39 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_5:
# 52 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_6:
# 54 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}off$"

EventScript_QolMenu_Text_7:
# 58 "data/scripts/qol_menu.pory"
	.string "Wait until...$"

EventScript_QolMenu_Text_8:
# 60 "data/scripts/qol_menu.pory"
	.string "Change ability$"

EventScript_QolMenu_Text_9:
# 68 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_10:
# 71 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"

EventScript_QolMenu_Text_11:
# 89 "data/scripts/qol_menu.pory"
	.string "Exp-all turned off. That's the sigma\n"
	.string "grindset way.$"

EventScript_QolMenu_Text_12:
# 92 "data/scripts/qol_menu.pory"
	.string "Exp-all turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. Easy level farming\n"
	.string "for your whole party!$"

EventScript_QolMenu_Wait_Text_0:
# 108 "data/scripts/qol_menu.pory"
	.string "Morning$"

EventScript_QolMenu_Wait_Text_1:
# 109 "data/scripts/qol_menu.pory"
	.string "Day$"

EventScript_QolMenu_Wait_Text_2:
# 110 "data/scripts/qol_menu.pory"
	.string "Evening$"

EventScript_QolMenu_Wait_Text_3:
# 111 "data/scripts/qol_menu.pory"
	.string "Night$"

EventScript_QolMenu_PickAbiliChangeMon_Text_0:
# 136 "data/scripts/qol_menu.pory"
	.string "You don't have any pokemon with you!$"

EventScript_QolMenu_PickAbiliChangeMon_Text_1:
# 144 "data/scripts/qol_menu.pory"
	.string "Another time then!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_0:
# 160 "data/scripts/qol_menu.pory"
	.string "I can't change the ability of that!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_1:
# 165 "data/scripts/qol_menu.pory"
	.string "This pokemon can only have\n"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_2:
# 170 "data/scripts/qol_menu.pory"
	.string "I can't work with that...$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_3:
# 176 "data/scripts/qol_menu.pory"
	.string "Which ability do you want?$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_4:
# 177 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_5:
# 178 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_2}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_6:
# 184 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_3}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_7:
# 200 "data/scripts/qol_menu.pory"
	.string "I can't work with that.$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_8:
# 209 "data/scripts/qol_menu.pory"
	.string "You picked the primary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_9:
# 212 "data/scripts/qol_menu.pory"
	.string "You picked the secondary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_10:
# 215 "data/scripts/qol_menu.pory"
	.string "You picked the hidden ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_11:
# 218 "data/scripts/qol_menu.pory"
	.string "What kind of choice is that?$"
