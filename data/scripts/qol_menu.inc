EventScript_QolMenu::
# 21 "data/scripts/qol_menu.pory"
	lock
	checkitem ITEM_POKEVIAL
# 0 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 0
	goto_if_ne EventScript_QolMenu_2
EventScript_QolMenu_1:
# 62 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_8, 10
# 63 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_9, 11
# 64 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_10, 12
# 66 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 9, DYN_MULTICHOICE_CB_NONE
# 69 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 70 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_6
# 78 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_7
# 80 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_8
# 83 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_9
# 85 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_10
# 87 "data/scripts/qol_menu.pory"
	case 6, EventScript_QolMenu_11
# 89 "data/scripts/qol_menu.pory"
	case 7, EventScript_QolMenu_12
# 91 "data/scripts/qol_menu.pory"
	case 8, EventScript_QolMenu_13
# 99 "data/scripts/qol_menu.pory"
	case 9, EventScript_QolMenu_14
# 101 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_15
# 103 "data/scripts/qol_menu.pory"
	case 11, EventScript_QolMenu_16
# 105 "data/scripts/qol_menu.pory"
	case 12, EventScript_QolMenu_17
EventScript_QolMenu_4:
# 109 "data/scripts/qol_menu.pory"
	waitmessage
# 110 "data/scripts/qol_menu.pory"
	release
	end

EventScript_QolMenu_2:
# 26 "data/scripts/qol_menu.pory"
	pokevialgetsize
# 27 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 28 "data/scripts/qol_menu.pory"
	pokevialgetdose
# 29 "data/scripts/qol_menu.pory"
	buffernumberstring STR_VAR_1, VAR_0x8006
# 30 "data/scripts/qol_menu.pory"
	compare VAR_0x8006, 0
	goto_if_eq EventScript_QolMenu_19
# 33 "data/scripts/qol_menu.pory"
	pokevialisfull
# 34 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 1
	goto_if_eq EventScript_QolMenu_28
# 37 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_2, 2
EventScript_QolMenu_18:
# 41 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_3, 3
# 42 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_4, 4
# 43 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_5, 5
# 44 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_6, 6
# 45 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_7, 7
	goto EventScript_QolMenu_1

EventScript_QolMenu_6:
# 71 "data/scripts/qol_menu.pory"
	goto_if_set FLAG_SID_REPEL, EventScript_QolMenu_22
# 75 "data/scripts/qol_menu.pory"
	setflag FLAG_SID_REPEL
# 76 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_12
	goto EventScript_QolMenu_4

EventScript_QolMenu_7:
# 79 "data/scripts/qol_menu.pory"
	pokevialtryuse
	goto EventScript_QolMenu_4

EventScript_QolMenu_8:
# 81 "data/scripts/qol_menu.pory"
	pokevialincreasesize
# 82 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_4

EventScript_QolMenu_9:
# 84 "data/scripts/qol_menu.pory"
	pokevialdecreasesize
	goto EventScript_QolMenu_4

EventScript_QolMenu_10:
# 86 "data/scripts/qol_menu.pory"
	pokevialadddose
	goto EventScript_QolMenu_4

EventScript_QolMenu_11:
# 88 "data/scripts/qol_menu.pory"
	pokevialremovedose
	goto EventScript_QolMenu_4

EventScript_QolMenu_12:
# 90 "data/scripts/qol_menu.pory"
	pokevialrefill
	goto EventScript_QolMenu_4

EventScript_QolMenu_13:
# 92 "data/scripts/qol_menu.pory"
	goto_if_set I_EXP_SHARE_FLAG, EventScript_QolMenu_25
# 96 "data/scripts/qol_menu.pory"
	setflag I_EXP_SHARE_FLAG
# 97 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_14
	goto EventScript_QolMenu_4

EventScript_QolMenu_14:
# 100 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_Wait
	goto EventScript_QolMenu_4

EventScript_QolMenu_15:
# 102 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_PickAbiliChangeMon
	goto EventScript_QolMenu_4

EventScript_QolMenu_16:
# 104 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_PickNatureChangeMon
	goto EventScript_QolMenu_4

EventScript_QolMenu_17:
# 106 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_GiveRockClimbMon
	goto EventScript_QolMenu_4

EventScript_QolMenu_19:
# 31 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_0, 2
	goto EventScript_QolMenu_18

EventScript_QolMenu_22:
# 72 "data/scripts/qol_menu.pory"
	clearflag FLAG_SID_REPEL
# 73 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_11
	goto EventScript_QolMenu_4

EventScript_QolMenu_25:
# 93 "data/scripts/qol_menu.pory"
	clearflag I_EXP_SHARE_FLAG
# 94 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_Text_13
	goto EventScript_QolMenu_4

EventScript_QolMenu_28:
# 35 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Text_1, 2
	goto EventScript_QolMenu_18


EventScript_QolMenu_Wait::
# 120 "data/scripts/qol_menu.pory"
	lock
# 122 "data/scripts/qol_menu.pory"
	qoltime
# 123 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_WaitText
# 125 "data/scripts/qol_menu.pory"
	switch VAR_0x8000
# 126 "data/scripts/qol_menu.pory"
	case TIME_MORNING, EventScript_QolMenu_Wait_3
# 131 "data/scripts/qol_menu.pory"
	case TIME_DAY, EventScript_QolMenu_Wait_4
# 136 "data/scripts/qol_menu.pory"
	case TIME_EVENING, EventScript_QolMenu_Wait_5
# 141 "data/scripts/qol_menu.pory"
	case TIME_NIGHT, EventScript_QolMenu_Wait_6
# 147 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 148 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 149 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 150 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 151 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
EventScript_QolMenu_Wait_1:
# 154 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 155 "data/scripts/qol_menu.pory"
	case 10, EventScript_QolMenu_Wait_10
# 157 "data/scripts/qol_menu.pory"
	case 20, EventScript_QolMenu_Wait_11
# 159 "data/scripts/qol_menu.pory"
	case 30, EventScript_QolMenu_Wait_12
# 161 "data/scripts/qol_menu.pory"
	case 40, EventScript_QolMenu_Wait_13
EventScript_QolMenu_Wait_8:
# 165 "data/scripts/qol_menu.pory"
	waitmessage
# 166 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_Wait_3:
# 127 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 128 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 129 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 130 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 20, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_4:
# 132 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 133 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 134 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 135 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 30, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_5:
# 137 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_2, 40
# 138 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 139 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 140 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 40, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_6:
# 142 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_3, 10
# 143 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_0, 20
# 144 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_Wait_Text_1, 30
# 145 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 10, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_Wait_1

EventScript_QolMenu_Wait_10:
# 156 "data/scripts/qol_menu.pory"
	waittillmorning
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_11:
# 158 "data/scripts/qol_menu.pory"
	waittillday
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_12:
# 160 "data/scripts/qol_menu.pory"
	waittillevening
	goto EventScript_QolMenu_Wait_8

EventScript_QolMenu_Wait_13:
# 162 "data/scripts/qol_menu.pory"
	waittillnight
	goto EventScript_QolMenu_Wait_8


EventScript_QolMenu_PickAbiliChangeMon::
# 171 "data/scripts/qol_menu.pory"
	lock
# 172 "data/scripts/qol_menu.pory"
	getpartysize
# 173 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 174 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_PickAbiliChangeMon_2
# 180 "data/scripts/qol_menu.pory"
	special ChoosePartyMon
# 181 "data/scripts/qol_menu.pory"
	waitstate
# 182 "data/scripts/qol_menu.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge EventScript_QolMenu_PickAbiliChangeMon_4
# 188 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_ShowAbilityMultichoice
	return

EventScript_QolMenu_PickAbiliChangeMon_2:
# 175 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_0
# 176 "data/scripts/qol_menu.pory"
	waitmessage
# 177 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickAbiliChangeMon_4:
# 183 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_1
# 184 "data/scripts/qol_menu.pory"
	waitmessage
# 185 "data/scripts/qol_menu.pory"
	release
	return


EventScript_QolMenu_ShowAbilityMultichoice::
# 197 "data/scripts/qol_menu.pory"
	getchosenmonabilities
# 198 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 199 "data/scripts/qol_menu.pory"
	case -1, EventScript_QolMenu_ShowAbilityMultichoice_3
# 204 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_4
# 209 "data/scripts/qol_menu.pory"
	case 5, EventScript_QolMenu_ShowAbilityMultichoice_5
# 214 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_6
# 220 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_7
# 226 "data/scripts/qol_menu.pory"
	case 3, EventScript_QolMenu_ShowAbilityMultichoice_8
# 232 "data/scripts/qol_menu.pory"
	case 4, EventScript_QolMenu_ShowAbilityMultichoice_9
# 240 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_7
# 241 "data/scripts/qol_menu.pory"
	waitmessage
# 242 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_1:
# 247 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 248 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_ShowAbilityMultichoice_13
# 251 "data/scripts/qol_menu.pory"
	case 1, EventScript_QolMenu_ShowAbilityMultichoice_14
# 254 "data/scripts/qol_menu.pory"
	case 2, EventScript_QolMenu_ShowAbilityMultichoice_15
# 258 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_11
EventScript_QolMenu_ShowAbilityMultichoice_11:
# 260 "data/scripts/qol_menu.pory"
	waitmessage
# 261 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_3:
# 200 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_0
# 201 "data/scripts/qol_menu.pory"
	waitmessage
# 202 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_4:
# 205 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_1
# 206 "data/scripts/qol_menu.pory"
	waitmessage
# 207 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_5:
# 210 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_2
# 211 "data/scripts/qol_menu.pory"
	waitmessage
# 212 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowAbilityMultichoice_6:
# 216 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 217 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 218 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 219 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_7:
# 222 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 223 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 224 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 225 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_8:
# 228 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 229 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 230 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 231 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_9:
# 234 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_3
# 235 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_4, 0
# 236 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_5, 1
# 237 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowAbilityMultichoice_Text_6, 2
# 238 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 9, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto EventScript_QolMenu_ShowAbilityMultichoice_1

EventScript_QolMenu_ShowAbilityMultichoice_13:
# 249 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_8
# 250 "data/scripts/qol_menu.pory"
	setchosenmonfirstability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_14:
# 252 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_9
# 253 "data/scripts/qol_menu.pory"
	setchosenmonsecondability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11

EventScript_QolMenu_ShowAbilityMultichoice_15:
# 255 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowAbilityMultichoice_Text_10
# 256 "data/scripts/qol_menu.pory"
	setchosenmonhiddenability
	goto EventScript_QolMenu_ShowAbilityMultichoice_11


EventScript_QolMenu_PickNatureChangeMon::
# 266 "data/scripts/qol_menu.pory"
	lock
# 267 "data/scripts/qol_menu.pory"
	getpartysize
# 268 "data/scripts/qol_menu.pory"
	switch VAR_RESULT
# 269 "data/scripts/qol_menu.pory"
	case 0, EventScript_QolMenu_PickNatureChangeMon_2
# 275 "data/scripts/qol_menu.pory"
	special ChoosePartyMon
# 276 "data/scripts/qol_menu.pory"
	waitstate
# 277 "data/scripts/qol_menu.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge EventScript_QolMenu_PickNatureChangeMon_4
# 283 "data/scripts/qol_menu.pory"
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
# 284 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq EventScript_QolMenu_PickNatureChangeMon_8
# 290 "data/scripts/qol_menu.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 291 "data/scripts/qol_menu.pory"
	call EventScript_QolMenu_ShowNatureMultichoice
	return

EventScript_QolMenu_PickNatureChangeMon_2:
# 270 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_0
# 271 "data/scripts/qol_menu.pory"
	waitmessage
# 272 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickNatureChangeMon_4:
# 278 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickAbiliChangeMon_Text_1
# 279 "data/scripts/qol_menu.pory"
	waitmessage
# 280 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_PickNatureChangeMon_8:
# 285 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_PickNatureChangeMon_Text_0
# 286 "data/scripts/qol_menu.pory"
	waitmessage
# 287 "data/scripts/qol_menu.pory"
	release
	return


EventScript_QolMenu_ShowNatureMultichoice::
# 301 "data/scripts/qol_menu.pory"
	msgbox EventScript_QolMenu_ShowNatureMultichoice_Text_0
# 302 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_1, 0
# 303 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_2, 1
# 304 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_3, 2
# 305 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_4, 3
# 306 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_5, 4
# 307 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_6, 5
# 308 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_7, 6
# 309 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_8, 7
# 310 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_9, 8
# 311 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_10, 9
# 312 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_11, 10
# 313 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_12, 11
# 314 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_13, 12
# 315 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_14, 13
# 316 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_15, 14
# 317 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_16, 15
# 318 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_17, 16
# 319 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_18, 17
# 320 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_19, 18
# 321 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_20, 19
# 322 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_21, 20
# 323 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_22, 21
# 324 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_23, 22
# 325 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_24, 23
# 326 "data/scripts/qol_menu.pory"
	dynmultipush EventScript_QolMenu_ShowNatureMultichoice_Text_25, 24
# 327 "data/scripts/qol_menu.pory"
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 329 "data/scripts/qol_menu.pory"
	compare VAR_RESULT, 24
	goto_if_le EventScript_QolMenu_ShowNatureMultichoice_2
EventScript_QolMenu_ShowNatureMultichoice_1:
# 333 "data/scripts/qol_menu.pory"
	waitmessage
# 334 "data/scripts/qol_menu.pory"
	release
	return

EventScript_QolMenu_ShowNatureMultichoice_2:
# 330 "data/scripts/qol_menu.pory"
	special SetHiddenNature
	goto EventScript_QolMenu_ShowNatureMultichoice_1


EventScript_QolMenu_GiveRockClimbMon::
# 339 "data/scripts/qol_menu.pory"
	givemon SPECIES_PIKACHU, 20, ITEM_NONE, ITEM_POKE_BALL, NATURE_ADAMANT, 0, MON_MALE, 0, 252, 4, 252, 0, 0, 31, 31, 31, 31, 31, 31, MOVE_ROCK_CLIMB, MOVE_THUNDER_SHOCK, MOVE_GROWL, MOVE_TAIL_WHIP, TRUE, FALSE, TYPE_STEEL
	return


EventScript_QolMenu_Text_0:
# 31 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}0/{STR_VAR_2}$"

EventScript_QolMenu_Text_1:
# 35 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_2:
# 37 "data/scripts/qol_menu.pory"
	.string "Pokévial: {CLEAR_TO 60}{COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_1}/{STR_VAR_2}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}$"

EventScript_QolMenu_Text_3:
# 41 "data/scripts/qol_menu.pory"
	.string "Size up$"

EventScript_QolMenu_Text_4:
# 42 "data/scripts/qol_menu.pory"
	.string "Size down$"

EventScript_QolMenu_Text_5:
# 43 "data/scripts/qol_menu.pory"
	.string "Dose up$"

EventScript_QolMenu_Text_6:
# 44 "data/scripts/qol_menu.pory"
	.string "Dose down$"

EventScript_QolMenu_Text_7:
# 45 "data/scripts/qol_menu.pory"
	.string "Refill$"

EventScript_QolMenu_Text_8:
# 62 "data/scripts/qol_menu.pory"
	.string "Change ability$"

EventScript_QolMenu_Text_9:
# 63 "data/scripts/qol_menu.pory"
	.string "Change nature$"

EventScript_QolMenu_Text_10:
# 64 "data/scripts/qol_menu.pory"
	.string "Rock climb mon$"

EventScript_QolMenu_Text_11:
# 73 "data/scripts/qol_menu.pory"
	.string "Repel turned off. Catch 'em all!$"

EventScript_QolMenu_Text_12:
# 76 "data/scripts/qol_menu.pory"
	.string "Repel turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. You're scaring wild\n"
	.string "Pokémon away!$"

EventScript_QolMenu_Text_13:
# 94 "data/scripts/qol_menu.pory"
	.string "Exp-all turned off. That's the sigma\n"
	.string "grindset way.$"

EventScript_QolMenu_Text_14:
# 97 "data/scripts/qol_menu.pory"
	.string "Exp-all turned {COLOR GREEN}{SHADOW LIGHT_GREEN}ON{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}. Easy level farming\n"
	.string "for your whole party!$"

EventScript_QolMenu_Wait_Text_0:
# 127 "data/scripts/qol_menu.pory"
	.string "Until day$"

EventScript_QolMenu_Wait_Text_1:
# 128 "data/scripts/qol_menu.pory"
	.string "Until evening$"

EventScript_QolMenu_Wait_Text_2:
# 129 "data/scripts/qol_menu.pory"
	.string "Until night$"

EventScript_QolMenu_Wait_Text_3:
# 134 "data/scripts/qol_menu.pory"
	.string "Until morning$"

EventScript_QolMenu_PickAbiliChangeMon_Text_0:
# 175 "data/scripts/qol_menu.pory"
	.string "You don't have any pokemon with you!$"

EventScript_QolMenu_PickAbiliChangeMon_Text_1:
# 183 "data/scripts/qol_menu.pory"
	.string "Another time then!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_0:
# 200 "data/scripts/qol_menu.pory"
	.string "I can't change the ability of that!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_1:
# 205 "data/scripts/qol_menu.pory"
	.string "This pokemon can only have\n"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_2:
# 210 "data/scripts/qol_menu.pory"
	.string "I can't work with that...$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_3:
# 216 "data/scripts/qol_menu.pory"
	.string "Which ability do you want?$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_4:
# 217 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_1}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_5:
# 218 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_2}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_6:
# 224 "data/scripts/qol_menu.pory"
	.string "{STR_VAR_3}$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_7:
# 240 "data/scripts/qol_menu.pory"
	.string "I can't work with that.$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_8:
# 249 "data/scripts/qol_menu.pory"
	.string "You picked the primary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_9:
# 252 "data/scripts/qol_menu.pory"
	.string "You picked the secondary ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_10:
# 255 "data/scripts/qol_menu.pory"
	.string "You picked the hidden ability!$"

EventScript_QolMenu_ShowAbilityMultichoice_Text_11:
# 258 "data/scripts/qol_menu.pory"
	.string "What kind of choice is that?$"

EventScript_QolMenu_PickNatureChangeMon_Text_0:
# 285 "data/scripts/qol_menu.pory"
	.string "I can't change the nature of an egg!$"

EventScript_QolMenu_ShowNatureMultichoice_Text_0:
# 301 "data/scripts/qol_menu.pory"
	.string "Which hidden nature do you want for\n"
	.string "{STR_VAR_1}?$"

EventScript_QolMenu_ShowNatureMultichoice_Text_1:
# 302 "data/scripts/qol_menu.pory"
	.string "Hardy {CLEAR_TO 60} +Atk / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_2:
# 303 "data/scripts/qol_menu.pory"
	.string "Lonely {CLEAR_TO 60} +Atk / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_3:
# 304 "data/scripts/qol_menu.pory"
	.string "Brave {CLEAR_TO 60} +Atk / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_4:
# 305 "data/scripts/qol_menu.pory"
	.string "Adamant {CLEAR_TO 60} +Atk / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_5:
# 306 "data/scripts/qol_menu.pory"
	.string "Naughty {CLEAR_TO 60} +Atk / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_6:
# 307 "data/scripts/qol_menu.pory"
	.string "Bold {CLEAR_TO 60} +Def / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_7:
# 308 "data/scripts/qol_menu.pory"
	.string "Docile {CLEAR_TO 60} +Def / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_8:
# 309 "data/scripts/qol_menu.pory"
	.string "Relaxed {CLEAR_TO 60} +Def / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_9:
# 310 "data/scripts/qol_menu.pory"
	.string "Impish {CLEAR_TO 60} +Def / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_10:
# 311 "data/scripts/qol_menu.pory"
	.string "Lax {CLEAR_TO 60} +Def / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_11:
# 312 "data/scripts/qol_menu.pory"
	.string "Timid {CLEAR_TO 60} +Spe / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_12:
# 313 "data/scripts/qol_menu.pory"
	.string "Hasty {CLEAR_TO 60} +Spe / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_13:
# 314 "data/scripts/qol_menu.pory"
	.string "Serious {CLEAR_TO 60} +Spe / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_14:
# 315 "data/scripts/qol_menu.pory"
	.string "Jolly {CLEAR_TO 60} +Spe / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_15:
# 316 "data/scripts/qol_menu.pory"
	.string "Naive {CLEAR_TO 60} +Spe / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_16:
# 317 "data/scripts/qol_menu.pory"
	.string "Modest {CLEAR_TO 60} +SpA / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_17:
# 318 "data/scripts/qol_menu.pory"
	.string "Mild {CLEAR_TO 60} +SpA / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_18:
# 319 "data/scripts/qol_menu.pory"
	.string "Quiet {CLEAR_TO 60} +SpA / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_19:
# 320 "data/scripts/qol_menu.pory"
	.string "Bashful {CLEAR_TO 60} +SpA / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_20:
# 321 "data/scripts/qol_menu.pory"
	.string "Rash {CLEAR_TO 60} +SpA / -SpD$"

EventScript_QolMenu_ShowNatureMultichoice_Text_21:
# 322 "data/scripts/qol_menu.pory"
	.string "Calm {CLEAR_TO 60} +SpD / -Atk$"

EventScript_QolMenu_ShowNatureMultichoice_Text_22:
# 323 "data/scripts/qol_menu.pory"
	.string "Gentle {CLEAR_TO 60} +SpD / -Def$"

EventScript_QolMenu_ShowNatureMultichoice_Text_23:
# 324 "data/scripts/qol_menu.pory"
	.string "Sassy {CLEAR_TO 60} +SpD / -Spe$"

EventScript_QolMenu_ShowNatureMultichoice_Text_24:
# 325 "data/scripts/qol_menu.pory"
	.string "Careful {CLEAR_TO 60} +SpD / -SpA$"

EventScript_QolMenu_ShowNatureMultichoice_Text_25:
# 326 "data/scripts/qol_menu.pory"
	.string "Quirky {CLEAR_TO 60} +SpD / -SpD$"

EventScript_QolMenu_WaitText::
# 114 "data/scripts/qol_menu.pory"
	.string "It's {COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_1}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} at {STR_VAR_2}:{STR_VAR_3}.\n"
	.string "Wait for how long?$"
