EventScript_QolMenu::
# 20 "data/scripts/qol_menu.pory"
	lock
# 22 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 9
	checkitem ITEM_POKEVIAL
# 0 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 0
	goto_if_ne EventScript_QolMenu_2
EventScript_QolMenu_1:
# 47 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_5
# 50 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 1
EventScript_QolMenu_4:
	checkitem ITEM_EXP_ALL
# 0 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 0
	goto_if_ne EventScript_QolMenu_12
EventScript_QolMenu_11:
# 61 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_8, 10
# 62 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_9, 11
# 64 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 9, DYN_MULTICHOICE_CB_NONE
# 66 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 67 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_19
# 75 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_20
# 77 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_21
# 80 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_22
# 82 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_23
# 84 "data/scripts/qol_menu.pory"
	case 6, EventScript_QolMenu_24
# 86 "data/scripts/qol_menu.pory"
	case 7, EventScript_QolMenu_25
# 88 "data/scripts/qol_menu.pory"
	case 8, EventScript_QolMenu_26
# 96 "data/scripts/qol_menu.pory"
	case 9, EventScript_QolMenu_27
# 98 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_28
# 100 "data/scripts/qol_menu.pory"
	case 11, EventScript_QolMenu_29
EventScript_QolMenu_17:
# 104 "data/scripts/qol_menu.pory"
	waitmessage
# 105 "data/scripts/qol_menu.pory"
	release
	end

EventScript_QolMenu_2:
# 25 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 26 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 27 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 28 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8006
# 29 "data/scripts/qol_menu.pory"
	compare VAR_0x8006, 0
	goto_if_eq EventScript_QolMenu_8
# 32 "data/scripts/qol_menu.pory"
	pokevialisfull
# 33 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 1
	goto_if_eq EventScript_QolMenu_14
# 36 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 2
	goto EventScript_QolMenu_1

EventScript_QolMenu_5:
# 48 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 1
	goto EventScript_QolMenu_4

EventScript_QolMenu_8:
# 30 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_1, 2
	goto EventScript_QolMenu_1

EventScript_QolMenu_12:
# 54 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_30
# 57 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_7, 8
	goto EventScript_QolMenu_11

EventScript_QolMenu_14:
# 34 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
	goto EventScript_QolMenu_1

EventScript_QolMenu_19:
# 68 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_33
# 72 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 73 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_11
	goto EventScript_QolMenu_17

EventScript_QolMenu_20:
# 76 "data/scripts/qol_menu.pory"
	pokevialtryuse
	goto EventScript_QolMenu_17

EventScript_QolMenu_21:
# 78 "data/scripts/qol_menu.pory"
	pokevialincreasesize
# 79 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_17

EventScript_QolMenu_22:
# 81 "data/scripts/qol_menu.pory"
	pokevialdecreasesize
	goto EventScript_QolMenu_17

EventScript_QolMenu_23:
# 83 "data/scripts/qol_menu.pory"
	pokevialadddose
	goto EventScript_QolMenu_17

EventScript_QolMenu_24:
# 85 "data/scripts/qol_menu.pory"
	pokevialremovedose
	goto EventScript_QolMenu_17

EventScript_QolMenu_25:
# 87 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_17

EventScript_QolMenu_26:
# 89 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_I_EXP_SHARE, EventScript_QolMenu_36
# 93 "data/scripts/qol_menu.pory"
	setflag FLAG_I_EXP_SHARE
# 94 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_13
	goto EventScript_QolMenu_17

EventScript_QolMenu_27:
# 97 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_Wait
	goto EventScript_QolMenu_17

EventScript_QolMenu_28:
# 99 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_PickAbiliChangeMon
	goto EventScript_QolMenu_17

EventScript_QolMenu_29:
# 101 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_PickNatureChangeMon
	goto EventScript_QolMenu_17

EventScript_QolMenu_30:
# 55 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 8
	goto EventScript_QolMenu_11

EventScript_QolMenu_33:
# 69 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 70 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_10
	goto EventScript_QolMenu_17

EventScript_QolMenu_36:
# 90 "data/scripts/qol_menu.pory"
	clearflag FLAG_I_EXP_SHARE
# 91 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_12
	goto EventScript_QolMenu_17


EventScript_QolMenu_Wait::
# 115 "data/scripts/qol_menu.pory"
	lock
# 117 "data/scripts/qol_menu.pory"
	qoltime
# 118 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_WaitText
# 120 "data/scripts/qol_menu.pory"
	switch VAR_0x8000
# 121 "data/scripts/qol_menu.pory"
	case TIME_MORNING, EventScript_QolMenu_Wait_3
# 126 "data/scripts/qol_menu.pory"
	case TIME_DAY, EventScript_QolMenu_Wait_4
# 131 "data/scripts/qol_menu.pory"
	case TIME_EVENING, EventScript_QolMenu_Wait_5
# 136 "data/scripts/qol_menu.pory"
	case TIME_NIGHT, EventScript_QolMenu_Wait_6
# 142 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 143 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 144 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 145 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 146 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
EventScript_QolMenu_Wait_1:
# 149 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 150 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_Wait_10
# 152 "data/scripts/qol_menu.pory"
	case 20, EventScript_QolMenu_Wait_11
# 154 "data/scripts/qol_menu.pory"
	case 30, EventScript_QolMenu_Wait_12
# 156 "data/scripts/qol_menu.pory"
	case 40, EventScript_QolMenu_Wait_13
EventScript_QolMenu_Wait_8:
# 160 "data/scripts/qol_menu.pory"
	waitmessage
# 161 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_Wait_3:
# 122 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 123 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 124 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 125 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 20, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_4:
# 127 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 128 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 129 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 130 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 30, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_5:
# 132 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 133 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 134 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 135 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 40, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_6:
# 137 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 138 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 139 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 140 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_10:
# 151 "data/scripts/qol_menu.pory"
	waittillmorning
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_11:
# 153 "data/scripts/qol_menu.pory"
	waittillday
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_12:
# 155 "data/scripts/qol_menu.pory"
	waittillevening
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_13:
# 157 "data/scripts/qol_menu.pory"
	waittillnight
	goto EventScript_QolMenu_Wait_8


EventScript_QolMenu_PickAbiliChangeMon::
# 166 "data/scripts/qol_menu.pory"
	lock
# 167 "data/scripts/qol_menu.pory"
	getpartysize
# 168 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 169 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_PickAbiliChangeMon_2
# 175 "data/scripts/qol_menu.pory"
	special ChoosePartyMon
# 176 "data/scripts/qol_menu.pory"
	waitstate
# 177 "data/scripts/qol_menu.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge EventScript_QolMenu_PickAbiliChangeMon_4
# 183 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_ShowAbilityMultichoice
	return

EventScript_QolMenu_PickAbiliChangeMon_2:
# 170 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_0
# 171 "data/scripts/qol_menu.pory"
	waitmessage
# 172 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickAbiliChangeMon_4:
# 178 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_1
# 179 "data/scripts/qol_menu.pory"
	waitmessage
# 180 "data/scripts/qol_menu.pory"
	release
	return


EventScript_QolMenu_ShowAbilityMultichoice::
# 192 "data/scripts/qol_menu.pory"
	getchosenmonabilities
# 193 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 194 "data/scripts/qol_menu.pory"
	case -1, EventScript_QolMenu_ShowAbilityMultichoice_3
# 199 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_4
# 204 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_ShowAbilityMultichoice_5
# 209 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_6
# 215 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_7
# 221 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_ShowAbilityMultichoice_8
# 227 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_ShowAbilityMultichoice_9
# 235 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_7
# 236 "data/scripts/qol_menu.pory"
	waitmessage
# 237 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_1:
# 242 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 243 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_13
# 246 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_14
# 249 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_15
# 253 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_11
EventScript_QolMenu_ShowAbilityMultichoice_11:
# 255 "data/scripts/qol_menu.pory"
	waitmessage
# 256 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_3:
# 195 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_0
# 196 "data/scripts/qol_menu.pory"
	waitmessage
# 197 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_4:
# 200 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_1
# 201 "data/scripts/qol_menu.pory"
	waitmessage
# 202 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_5:
# 205 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_2
# 206 "data/scripts/qol_menu.pory"
	waitmessage
# 207 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_6:
# 211 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 212 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 213 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 214 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_7:
# 217 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 218 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 219 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 220 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_8:
# 223 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 224 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 225 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 226 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_9:
# 229 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 230 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 231 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 232 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 233 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_13:
# 244 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_8
# 245 "data/scripts/qol_menu.pory"
	setchosenmonfirstability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_14:
# 247 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_9
# 248 "data/scripts/qol_menu.pory"
	setchosenmonsecondability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_15:
# 250 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_10
# 251 "data/scripts/qol_menu.pory"
	setchosenmonhiddenability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11


EventScript_QolMenu_PickNatureChangeMon::
# 261 "data/scripts/qol_menu.pory"
	lock
# 262 "data/scripts/qol_menu.pory"
	getpartysize
# 263 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 264 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_PickNatureChangeMon_2
# 270 "data/scripts/qol_menu.pory"
	special ChoosePartyMon
# 271 "data/scripts/qol_menu.pory"
	waitstate
# 272 "data/scripts/qol_menu.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge EventScript_QolMenu_PickNatureChangeMon_4
# 278 "data/scripts/qol_menu.pory"
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
# 279 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq EventScript_QolMenu_PickNatureChangeMon_8
# 285 "data/scripts/qol_menu.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 286 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_ShowNatureMultichoice
	return

EventScript_QolMenu_PickNatureChangeMon_2:
# 265 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_0
# 266 "data/scripts/qol_menu.pory"
	waitmessage
# 267 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickNatureChangeMon_4:
# 273 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_1
# 274 "data/scripts/qol_menu.pory"
	waitmessage
# 275 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickNatureChangeMon_8:
# 280 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickNatureChangeMon_Text_0
# 281 "data/scripts/qol_menu.pory"
	waitmessage
# 282 "data/scripts/qol_menu.pory"
	release
	return


EventScript_QolMenu_ShowNatureMultichoice::
# 296 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowNatureMultichoice_Text_0
# 297 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_1, 0
# 298 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_2, 1
# 299 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_3, 2
# 300 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_4, 3
# 301 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_5, 4
# 302 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_6, 5
# 303 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_7, 6
# 304 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_8, 7
# 305 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_9, 8
# 306 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_10, 9
# 307 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_11, 10
# 308 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_12, 11
# 309 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_13, 12
# 310 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_14, 13
# 311 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_15, 14
# 312 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_16, 15
# 313 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_17, 16
# 314 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_18, 17
# 315 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_19, 18
# 316 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_20, 19
# 317 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_21, 20
# 318 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_22, 21
# 319 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_23, 22
# 320 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_24, 23
# 321 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_25, 24
# 322 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 324 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 24
	goto_if_le EventScript_QolMenu_ShowNatureMultichoice_2
EventScript_QolMenu_ShowNatureMultichoice_1:
# 328 "data/scripts/qol_menu.pory"
	waitmessage
# 329 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowNatureMultichoice_2:
# 325 "data/scripts/qol_menu.pory"
	special SetHiddenNature
	goto EventScript_QolMenu_ShowNatureMultichoice_1


EventScript_QolMenu_Text_0:
# 22 "data/scripts/qol_menu.pory"
	.string "Wait until...$"

EventScript_QolMenu_Text_1:
# 30 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}0/{STR_VAR_2}$"

EventScript_QolMenu_Text_2:
# 34 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_3:
# 36 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_4:
# 48 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_5:
# 50 "data/scripts/qol_menu.pory"
	.string "Repel: {CLEAR_TO 60}off$"

EventScript_QolMenu_Text_6:
# 55 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}ON$"

EventScript_QolMenu_Text_7:
# 57 "data/scripts/qol_menu.pory"
	.string "Exp-All: {CLEAR_TO 60}off$"

EventScript_QolMenu_Text_8:
# 61 "data/scripts/qol_menu.pory"
	.string "Change ability$"

EventScript_QolMenu_Text_9:
# 62 "data/scripts/qol_menu.pory"
	.string "Change nature$"

EventScript_QolMenu_Text_10:
# 70 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_11:
# 73 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"

EventScript_QolMenu_Text_12:
# 91 "data/scripts/qol_menu.pory"
	.string "Exp-all turned off. That's the sigma\n"
	.string "grindset way.$"

EventScript_QolMenu_Text_13:
# 94 "data/scripts/qol_menu.pory"
	.string "Exp-all turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. Easy level farming\n"
	.string "for your whole party!$"

EventScript_QolMenu_Wait_Text_0:
# 122 "data/scripts/qol_menu.pory"
	.string "Until day$"

EventScript_QolMenu_Wait_Text_1:
# 123 "data/scripts/qol_menu.pory"
	.string "Until evening$"

EventScript_QolMenu_Wait_Text_2:
# 124 "data/scripts/qol_menu.pory"
	.string "Until night$"

EventScript_QolMenu_Wait_Text_3:
# 129 "data/scripts/qol_menu.pory"
	.string "Until morning$"

EventScript_QolMenu_PickAbiliChangeMon_Text_0:
# 170 "data/scripts/qol_menu.pory"
	.string "You don't have any pokemon with you!$"

EventScript_QolMenu_PickAbiliChangeMon_Text_1:
# 178 "data/scripts/qol_menu.pory"
	.string "Another time then!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_0:
# 195 "data/scripts/qol_menu.pory"
	.string "I can't change the ability of that!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_1:
# 200 "data/scripts/qol_menu.pory"
	.string "This pokemon can only have\n"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_2:
# 205 "data/scripts/qol_menu.pory"
	.string "I can't work with that...$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_3:
# 211 "data/scripts/qol_menu.pory"
	.string "Which ability do you want?$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_4:
# 212 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_5:
# 213 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_2}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_6:
# 219 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_3}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_7:
# 235 "data/scripts/qol_menu.pory"
	.string "I can't work with that.$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_8:
# 244 "data/scripts/qol_menu.pory"
	.string "You picked the primary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_9:
# 247 "data/scripts/qol_menu.pory"
	.string "You picked the secondary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_10:
# 250 "data/scripts/qol_menu.pory"
	.string "You picked the hidden ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_11:
# 253 "data/scripts/qol_menu.pory"
	.string "What kind of choice is that?$"

EventScript_QolMenu_PickNatureChangeMon_Text_0:
# 280 "data/scripts/qol_menu.pory"
	.string "I can't change the nature of an egg!$"

EventScript_QolMenu_ShowNatureMultichoice_Text_0:
# 296 "data/scripts/qol_menu.pory"
	.string "Which hidden nature do you want for\n"
	.string "{STR_VAR_1}?$"

EventScript_QolMenu_ShowNatureMultichoice_Text_1:
# 297 "data/scripts/qol_menu.pory"
	.string "Hardy {CLEAR_TO 60} +Atk / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_2:
# 298 "data/scripts/qol_menu.pory"
	.string "Lonely {CLEAR_TO 60} +Atk / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_3:
# 299 "data/scripts/qol_menu.pory"
	.string "Brave {CLEAR_TO 60} +Atk / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_4:
# 300 "data/scripts/qol_menu.pory"
	.string "Adamant {CLEAR_TO 60} +Atk / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_5:
# 301 "data/scripts/qol_menu.pory"
	.string "Naughty {CLEAR_TO 60} +Atk / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_6:
# 302 "data/scripts/qol_menu.pory"
	.string "Bold {CLEAR_TO 60} +Def / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_7:
# 303 "data/scripts/qol_menu.pory"
	.string "Docile {CLEAR_TO 60} +Def / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_8:
# 304 "data/scripts/qol_menu.pory"
	.string "Relaxed {CLEAR_TO 60} +Def / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_9:
# 305 "data/scripts/qol_menu.pory"
	.string "Impish {CLEAR_TO 60} +Def / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_10:
# 306 "data/scripts/qol_menu.pory"
	.string "Lax {CLEAR_TO 60} +Def / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_11:
# 307 "data/scripts/qol_menu.pory"
	.string "Timid {CLEAR_TO 60} +Spe / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_12:
# 308 "data/scripts/qol_menu.pory"
	.string "Hasty {CLEAR_TO 60} +Spe / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_13:
# 309 "data/scripts/qol_menu.pory"
	.string "Serious {CLEAR_TO 60} +Spe / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_14:
# 310 "data/scripts/qol_menu.pory"
	.string "Jolly {CLEAR_TO 60} +Spe / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_15:
# 311 "data/scripts/qol_menu.pory"
	.string "Naive {CLEAR_TO 60} +Spe / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_16:
# 312 "data/scripts/qol_menu.pory"
	.string "Modest {CLEAR_TO 60} +SpA / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_17:
# 313 "data/scripts/qol_menu.pory"
	.string "Mild {CLEAR_TO 60} +SpA / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_18:
# 314 "data/scripts/qol_menu.pory"
	.string "Quiet {CLEAR_TO 60} +SpA / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_19:
# 315 "data/scripts/qol_menu.pory"
	.string "Bashful {CLEAR_TO 60} +SpA / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_20:
# 316 "data/scripts/qol_menu.pory"
	.string "Rash {CLEAR_TO 60} +SpA / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_21:
# 317 "data/scripts/qol_menu.pory"
	.string "Calm {CLEAR_TO 60} +SpD / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_22:
# 318 "data/scripts/qol_menu.pory"
	.string "Gentle {CLEAR_TO 60} +SpD / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_23:
# 319 "data/scripts/qol_menu.pory"
	.string "Sassy {CLEAR_TO 60} +SpD / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_24:
# 320 "data/scripts/qol_menu.pory"
	.string "Careful {CLEAR_TO 60} +SpD / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_25:
# 321 "data/scripts/qol_menu.pory"
	.string "Quirky {CLEAR_TO 60} +SpD / -SpD$"

EventScript_QolMenu_WaitText::
# 109 "data/scripts/qol_menu.pory"
	.string "It's {COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} at {STR_VAR_2}:{STR_VAR_3}.\n"
	.string "Wait for how long?$"
