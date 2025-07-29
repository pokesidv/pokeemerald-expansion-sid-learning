EventScript_QolMenu::
# 19 "data/scripts/qol_menu.pory"
	lock
# 21 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 9
	checkitem ITEM_POKEVIAL
# 0 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 0
	goto_if_ne EventScript_QolMenu_2
EventScript_QolMenu_1:
# 46 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_5
# 49 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 1
EventScript_QolMenu_4:
	checkitem ITEM_EXP_ALL
# 0 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 0
	goto_if_ne EventScript_QolMenu_12
EventScript_QolMenu_11:
# 60 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_8, 10
# 62 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 9, DYN_MULTICHOICE_CB_NONE
# 64 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 65 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_19
# 73 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_20
# 75 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_21
# 78 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_22
# 80 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_23
# 82 "data/scripts/qol_menu.pory"
	case 6, EventScript_QolMenu_24
# 84 "data/scripts/qol_menu.pory"
	case 7, EventScript_QolMenu_25
# 86 "data/scripts/qol_menu.pory"
	case 8, EventScript_QolMenu_26
# 94 "data/scripts/qol_menu.pory"
	case 9, EventScript_QolMenu_27
# 96 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_28
EventScript_QolMenu_17:
# 100 "data/scripts/qol_menu.pory"
	waitmessage
# 101 "data/scripts/qol_menu.pory"
	release
	end

EventScript_QolMenu_2:
# 24 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 25 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 26 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 27 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8006
# 28 "data/scripts/qol_menu.pory"
	compare VAR_0x8006, 0
	goto_if_eq EventScript_QolMenu_8
# 31 "data/scripts/qol_menu.pory"
	pokevialisfull
# 32 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 1
	goto_if_eq EventScript_QolMenu_14
# 35 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 2
	goto EventScript_QolMenu_1

EventScript_QolMenu_5:
# 47 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 1
	goto EventScript_QolMenu_4

EventScript_QolMenu_8:
# 29 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_1, 2
	goto EventScript_QolMenu_1

EventScript_QolMenu_12:
# 53 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_29
# 56 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_7, 8
	goto EventScript_QolMenu_11

EventScript_QolMenu_14:
# 33 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
	goto EventScript_QolMenu_1

EventScript_QolMenu_19:
# 66 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_32
# 70 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 71 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_10
	goto EventScript_QolMenu_17

EventScript_QolMenu_20:
# 74 "data/scripts/qol_menu.pory"
	pokevialtryuse
	goto EventScript_QolMenu_17

EventScript_QolMenu_21:
# 76 "data/scripts/qol_menu.pory"
	pokevialincreasesize
# 77 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_17

EventScript_QolMenu_22:
# 79 "data/scripts/qol_menu.pory"
	pokevialdecreasesize
	goto EventScript_QolMenu_17

EventScript_QolMenu_23:
# 81 "data/scripts/qol_menu.pory"
	pokevialadddose
	goto EventScript_QolMenu_17

EventScript_QolMenu_24:
# 83 "data/scripts/qol_menu.pory"
	pokevialremovedose
	goto EventScript_QolMenu_17

EventScript_QolMenu_25:
# 85 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_17

EventScript_QolMenu_26:
# 87 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_35
# 91 "data/scripts/qol_menu.pory"
	setflag FLAG_I_EXP_SHARE
# 92 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_12
	goto EventScript_QolMenu_17

EventScript_QolMenu_27:
# 95 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_Wait
	goto EventScript_QolMenu_17

EventScript_QolMenu_28:
# 97 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_PickAbiliChangeMon
	goto EventScript_QolMenu_17

EventScript_QolMenu_29:
# 54 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 8
	goto EventScript_QolMenu_11

EventScript_QolMenu_32:
# 67 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 68 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_9
	goto EventScript_QolMenu_17

EventScript_QolMenu_35:
# 88 "data/scripts/qol_menu.pory"
	clearflag FLAG_I_EXP_SHARE
# 89 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_11
	goto EventScript_QolMenu_17


EventScript_QolMenu_Wait::
# 111 "data/scripts/qol_menu.pory"
	lock
# 113 "data/scripts/qol_menu.pory"
	qoltime
# 114 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_WaitText
# 116 "data/scripts/qol_menu.pory"
	switch VAR_0x8000
# 117 "data/scripts/qol_menu.pory"
	case TIME_MORNING, EventScript_QolMenu_Wait_3
# 122 "data/scripts/qol_menu.pory"
	case TIME_DAY, EventScript_QolMenu_Wait_4
# 127 "data/scripts/qol_menu.pory"
	case TIME_EVENING, EventScript_QolMenu_Wait_5
# 132 "data/scripts/qol_menu.pory"
	case TIME_NIGHT, EventScript_QolMenu_Wait_6
# 138 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 139 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 140 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 141 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 142 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
EventScript_QolMenu_Wait_1:
# 145 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 146 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_Wait_10
# 148 "data/scripts/qol_menu.pory"
	case 20, EventScript_QolMenu_Wait_11
# 150 "data/scripts/qol_menu.pory"
	case 30, EventScript_QolMenu_Wait_12
# 152 "data/scripts/qol_menu.pory"
	case 40, EventScript_QolMenu_Wait_13
EventScript_QolMenu_Wait_8:
# 156 "data/scripts/qol_menu.pory"
	waitmessage
# 157 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_Wait_3:
# 118 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 119 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 120 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 121 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 20, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_4:
# 123 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 124 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 125 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 126 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 30, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_5:
# 128 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 129 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 130 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 131 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 40, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_6:
# 133 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 134 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 135 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 136 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_10:
# 147 "data/scripts/qol_menu.pory"
	waittillmorning
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_11:
# 149 "data/scripts/qol_menu.pory"
	waittillday
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_12:
# 151 "data/scripts/qol_menu.pory"
	waittillevening
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_13:
# 153 "data/scripts/qol_menu.pory"
	waittillnight
	goto EventScript_QolMenu_Wait_8


EventScript_QolMenu_PickAbiliChangeMon::
# 162 "data/scripts/qol_menu.pory"
	lock
# 163 "data/scripts/qol_menu.pory"
	getpartysize
# 164 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 165 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_PickAbiliChangeMon_2
# 171 "data/scripts/qol_menu.pory"
	special ChoosePartyMon
# 172 "data/scripts/qol_menu.pory"
	waitstate
# 173 "data/scripts/qol_menu.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge EventScript_QolMenu_PickAbiliChangeMon_4
# 179 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_ShowAbilityMultichoice
	return

EventScript_QolMenu_PickAbiliChangeMon_2:
# 166 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_0
# 167 "data/scripts/qol_menu.pory"
	waitmessage
# 168 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickAbiliChangeMon_4:
# 174 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_1
# 175 "data/scripts/qol_menu.pory"
	waitmessage
# 176 "data/scripts/qol_menu.pory"
	release
	return


EventScript_QolMenu_ShowAbilityMultichoice::
# 187 "data/scripts/qol_menu.pory"
	getchosenmonabilities
# 188 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 189 "data/scripts/qol_menu.pory"
	case -1, EventScript_QolMenu_ShowAbilityMultichoice_3
# 194 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_4
# 199 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_ShowAbilityMultichoice_5
# 204 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_6
# 210 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_7
# 216 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_ShowAbilityMultichoice_8
# 222 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_ShowAbilityMultichoice_9
# 230 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_7
# 231 "data/scripts/qol_menu.pory"
	waitmessage
# 232 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_1:
# 237 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 238 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_13
# 241 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_14
# 244 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_15
# 248 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_11
EventScript_QolMenu_ShowAbilityMultichoice_11:
# 250 "data/scripts/qol_menu.pory"
	waitmessage
# 251 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_3:
# 190 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_0
# 191 "data/scripts/qol_menu.pory"
	waitmessage
# 192 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_4:
# 195 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_1
# 196 "data/scripts/qol_menu.pory"
	waitmessage
# 197 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_5:
# 200 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_2
# 201 "data/scripts/qol_menu.pory"
	waitmessage
# 202 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_6:
# 206 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 207 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 208 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 209 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_7:
# 212 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 213 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 214 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 215 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_8:
# 218 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 219 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 220 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 221 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_9:
# 224 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 225 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 226 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 227 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 228 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_13:
# 239 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_8
# 240 "data/scripts/qol_menu.pory"
	setchosenmonfirstability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_14:
# 242 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_9
# 243 "data/scripts/qol_menu.pory"
	setchosenmonsecondability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_15:
# 245 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_10
# 246 "data/scripts/qol_menu.pory"
	setchosenmonhiddenability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11


EventScript_QolMenu_Text_0:
# 21 "data/scripts/qol_menu.pory"
	.string "Wait until...$"

EventScript_QolMenu_Text_1:
# 29 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}0/{STR_VAR_2}$"

EventScript_QolMenu_Text_2:
# 33 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_3:
# 35 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_4:
# 47 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_5:
# 49 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}off$"

EventScript_QolMenu_Text_6:
# 54 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_7:
# 56 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}off$"

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
# 118 "data/scripts/qol_menu.pory"
	.string "Until day$"

EventScript_QolMenu_Wait_Text_1:
# 119 "data/scripts/qol_menu.pory"
	.string "Until evening$"

EventScript_QolMenu_Wait_Text_2:
# 120 "data/scripts/qol_menu.pory"
	.string "Until night$"

EventScript_QolMenu_Wait_Text_3:
# 125 "data/scripts/qol_menu.pory"
	.string "Until morning$"

EventScript_QolMenu_PickAbiliChangeMon_Text_0:
# 166 "data/scripts/qol_menu.pory"
	.string "You don't have any pokemon with you!$"

EventScript_QolMenu_PickAbiliChangeMon_Text_1:
# 174 "data/scripts/qol_menu.pory"
	.string "Another time then!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_0:
# 190 "data/scripts/qol_menu.pory"
	.string "I can't change the ability of that!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_1:
# 195 "data/scripts/qol_menu.pory"
	.string "This pokemon can only have\n"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_2:
# 200 "data/scripts/qol_menu.pory"
	.string "I can't work with that...$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_3:
# 206 "data/scripts/qol_menu.pory"
	.string "Which ability do you want?$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_4:
# 207 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_5:
# 208 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_2}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_6:
# 214 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_3}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_7:
# 230 "data/scripts/qol_menu.pory"
	.string "I can't work with that.$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_8:
# 239 "data/scripts/qol_menu.pory"
	.string "You picked the primary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_9:
# 242 "data/scripts/qol_menu.pory"
	.string "You picked the secondary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_10:
# 245 "data/scripts/qol_menu.pory"
	.string "You picked the hidden ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_11:
# 248 "data/scripts/qol_menu.pory"
	.string "What kind of choice is that?$"

EventScript_QolMenu_WaitText::
# 105 "data/scripts/qol_menu.pory"
	.string "It's {COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} at {STR_VAR_2}:{STR_VAR_3}.\n"
	.string "Wait for how long?$"
