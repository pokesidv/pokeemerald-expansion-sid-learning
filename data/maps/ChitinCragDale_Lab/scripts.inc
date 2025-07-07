ChitinCragDale_Lab_MapScripts::
# 2 "data/maps/ChitinCragDale_Lab/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, ChitinCragDale_Lab_EventScript_OnTransition
	.byte 0


ChitinCragDale_Lab_EventScript_OnTransition::
# 6 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_GRASS_SPECIES, SPECIES_BULBASAUR
# 7 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_FIRE_SPECIES, SPECIES_CHARMANDER
# 8 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_WATER_SPECIES, SPECIES_SQUIRTLE
	return


ChitinCragDale_Lab_EventScript_ClickOnGrassBall::
# 17 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_SELECTED_STARTER_TYPE, 0
# 18 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_PickSelectedStarter
	return


ChitinCragDale_Lab_EventScript_ClickOnFireBall::
# 21 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_SELECTED_STARTER_TYPE, 1
# 22 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_PickSelectedStarter
	return


ChitinCragDale_Lab_EventScript_ClickOnWaterBall::
# 25 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_SELECTED_STARTER_TYPE, 2
# 26 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_PickSelectedStarter
	return


ChitinCragDale_Lab_EventScript_PickSelectedStarter::
# 30 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lock
# 31 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_GRASS, ChitinCragDale_Lab_EventScript_PickSelectedStarter_2
# 31 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_FIRE, ChitinCragDale_Lab_EventScript_PickSelectedStarter_2
# 31 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_WATER, ChitinCragDale_Lab_EventScript_PickSelectedStarter_2
# 37 "data/maps/ChitinCragDale_Lab/scripts.pory"
	switch VAR_SELECTED_STARTER_TYPE
# 38 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 0, ChitinCragDale_Lab_EventScript_PickSelectedStarter_10
# 40 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 1, ChitinCragDale_Lab_EventScript_PickSelectedStarter_11
# 42 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 2, ChitinCragDale_Lab_EventScript_PickSelectedStarter_12
# 45 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_1
# 46 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 47 "data/maps/ChitinCragDale_Lab/scripts.pory"
	release
	return

ChitinCragDale_Lab_EventScript_PickSelectedStarter_2:
# 32 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_0
# 33 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 34 "data/maps/ChitinCragDale_Lab/scripts.pory"
	release
	return

ChitinCragDale_Lab_EventScript_PickSelectedStarter_8:
# 51 "data/maps/ChitinCragDale_Lab/scripts.pory"
	showmonpic VAR_SELECTED_STARTER_SPECIES, 10, 3
# 52 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_SELECTED_STARTER_SPECIES
# 53 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_2, MSGBOX_YESNO
# 54 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_15
# 85 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 86 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_5
ChitinCragDale_Lab_EventScript_PickSelectedStarter_14:
# 89 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 90 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 91 "data/maps/ChitinCragDale_Lab/scripts.pory"
	release
	return

ChitinCragDale_Lab_EventScript_PickSelectedStarter_10:
# 39 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_SELECTED_STARTER_SPECIES, VAR_GRASS_SPECIES
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_8

ChitinCragDale_Lab_EventScript_PickSelectedStarter_11:
# 41 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_SELECTED_STARTER_SPECIES, VAR_FIRE_SPECIES
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_8

ChitinCragDale_Lab_EventScript_PickSelectedStarter_12:
# 43 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_SELECTED_STARTER_SPECIES, VAR_WATER_SPECIES
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_8

ChitinCragDale_Lab_EventScript_PickSelectedStarter_15:
# 55 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_SetStartingFlags
# 56 "data/maps/ChitinCragDale_Lab/scripts.pory"
	givemon VAR_SELECTED_STARTER_SPECIES, 50, ITEM_MASTER_BALL
# 57 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_SELECTED_STARTER_SPECIES
# 58 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_18
# 62 "data/maps/ChitinCragDale_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 63 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_4
# 64 "data/maps/ChitinCragDale_Lab/scripts.pory"
	switch VAR_SELECTED_STARTER_TYPE
# 65 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 0, ChitinCragDale_Lab_EventScript_PickSelectedStarter_23
# 68 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 1, ChitinCragDale_Lab_EventScript_PickSelectedStarter_24
# 71 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 2, ChitinCragDale_Lab_EventScript_PickSelectedStarter_25
ChitinCragDale_Lab_EventScript_PickSelectedStarter_21:
# 77 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_26
# 80 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_27
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_14

ChitinCragDale_Lab_EventScript_PickSelectedStarter_18:
# 59 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 60 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_3
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_14

ChitinCragDale_Lab_EventScript_PickSelectedStarter_23:
# 66 "data/maps/ChitinCragDale_Lab/scripts.pory"
	removeobject 2
# 67 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_STARTER_GRASS
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_21

ChitinCragDale_Lab_EventScript_PickSelectedStarter_24:
# 69 "data/maps/ChitinCragDale_Lab/scripts.pory"
	removeobject 3
# 70 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_STARTER_FIRE
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_21

ChitinCragDale_Lab_EventScript_PickSelectedStarter_25:
# 72 "data/maps/ChitinCragDale_Lab/scripts.pory"
	removeobject 4
# 73 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_STARTER_WATER
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_21

ChitinCragDale_Lab_EventScript_PickSelectedStarter_26:
# 78 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call NicknamePartyMon
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_14

ChitinCragDale_Lab_EventScript_PickSelectedStarter_27:
# 81 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call NicknameBoxMon
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_14


ChitinCragDale_Lab_EventScript_SetStartingFlags::
# 97 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 98 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_RESCUED_BIRCH
# 99 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
# 100 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 101 "data/maps/ChitinCragDale_Lab/scripts.pory"
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
# 102 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
# 103 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_BIRCH_LAB_STATE, 2
# 104 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_ROUTE101_STATE, 3
# 105 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 106 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_SYS_POKENAV_GET
# 107 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag DN_FLAG_DEXNAV_GET
# 108 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag DN_FLAG_DETECTOR_MODE
# 109 "data/maps/ChitinCragDale_Lab/scripts.pory"
	special SetUnlockedPokedexFlags
# 110 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setflag OW_FLAG_POKE_RIDER
# 111 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 2
# 112 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_SYS_NATIONAL_DEX
# 113 "data/maps/ChitinCragDale_Lab/scripts.pory"
	special EnableNationalPokedex
# 114 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_RECEIVED_RUNNING_SHOES
# 115 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_SYS_B_DASH
# 116 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_ACRO_BIKE
# 117 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_MASTER_BALL, 50
# 118 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_TM01
# 119 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_TM02
# 120 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_TM03
# 121 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_TM04
# 122 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_TM05
# 123 "data/maps/ChitinCragDale_Lab/scripts.pory"
	giveitem ITEM_TM24
# 125 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
# 127 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 7
# 129 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2
# 131 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
# 133 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
	return


ChitinCragDale_Lab_EventScript_EditGeneration::
# 137 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lock
# 138 "data/maps/ChitinCragDale_Lab/scripts.pory"
	faceplayer
# 140 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_GRASS, ChitinCragDale_Lab_EventScript_EditGeneration_2
# 140 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_FIRE, ChitinCragDale_Lab_EventScript_EditGeneration_2
# 140 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_WATER, ChitinCragDale_Lab_EventScript_EditGeneration_2
# 147 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGeneration_Text_1
# 148 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 149 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_EditGrassStarter
# 150 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 151 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_EditFireStarter
# 152 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 153 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_EditWaterStarter
# 154 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 155 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGeneration_Text_2
# 156 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 157 "data/maps/ChitinCragDale_Lab/scripts.pory"
	release
	end

ChitinCragDale_Lab_EventScript_EditGeneration_2:
# 141 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGeneration_Text_0
# 142 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 143 "data/maps/ChitinCragDale_Lab/scripts.pory"
	release
	end


ChitinCragDale_Lab_EventScript_EditGrassStarter::
# 162 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_0
# 164 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_BULBASAUR
# 165 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_2, SPECIES_CHIKORITA
# 166 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_3, SPECIES_TREECKO
# 167 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_4, SPECIES_TURTWIG
# 168 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_5, SPECIES_SNIVY
# 169 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_6, SPECIES_CHESPIN
# 170 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_7, SPECIES_ROWLET
# 171 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_8, SPECIES_GROOKEY
# 172 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_9, SPECIES_SPRIGATITO
# 174 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, SPECIES_BULBASAUR, DYN_MULTICHOICE_CB_SHOW_MON
# 175 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_GRASS_SPECIES, VAR_RESULT
# 176 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, VAR_GRASS_SPECIES
# 177 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_10
	return


ChitinCragDale_Lab_EventScript_EditFireStarter::
# 182 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditFireStarter_Text_0
# 184 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_CHARMANDER
# 185 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_2, SPECIES_CYNDAQUIL
# 186 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_3, SPECIES_TORCHIC
# 187 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_4, SPECIES_CHIMCHAR
# 188 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_5, SPECIES_TEPIG
# 189 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_6, SPECIES_FENNEKIN
# 190 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_7, SPECIES_LITTEN
# 191 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_8, SPECIES_SCORBUNNY
# 192 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_9, SPECIES_FUECOCO
# 194 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, SPECIES_CHARMANDER, DYN_MULTICHOICE_CB_SHOW_MON
# 195 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_FIRE_SPECIES, VAR_RESULT
# 196 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, VAR_FIRE_SPECIES
# 197 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1
	return


ChitinCragDale_Lab_EventScript_EditWaterStarter::
# 204 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_0
# 206 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_SQUIRTLE
# 207 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_2, SPECIES_TOTODILE
# 208 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_3, SPECIES_MUDKIP
# 209 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_4, SPECIES_PIPLUP
# 210 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_5, SPECIES_OSHAWOTT
# 211 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_6, SPECIES_FROAKIE
# 212 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_7, SPECIES_POPPLIO
# 213 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_8, SPECIES_SOBBLE
# 214 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_9, SPECIES_QUAXLY
# 216 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, SPECIES_SQUIRTLE, DYN_MULTICHOICE_CB_SHOW_MON
# 217 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_WATER_SPECIES, VAR_RESULT
# 218 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, VAR_WATER_SPECIES
# 219 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1
	return


NicknamePartyMon::
# 224 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox NicknamePartyMon_Text_0, MSGBOX_YESNO
# 225 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 226 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NicknamePartyMon_2
NicknamePartyMon_1:
	return

NicknamePartyMon_2:
# 227 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 228 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
	goto NicknamePartyMon_1


NicknameBoxMon::
# 234 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox NicknamePartyMon_Text_0, MSGBOX_YESNO
# 235 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 236 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NicknameBoxMon_2
NicknameBoxMon_1:
# 239 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
	return

NicknameBoxMon_2:
# 237 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
	goto NicknameBoxMon_1


ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_0:
# 32 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Don't be greedy!$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_1:
# 45 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "No starter selected.$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_2:
# 53 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Wanna pick {STR_VAR_1}?$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_3:
# 60 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "No more room.$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_4:
# 63 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Received {STR_VAR_1}!$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_5:
# 86 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_1} sits there patiently.$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_0:
# 141 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Enjoy your starter!$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_1:
# 147 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Let's configure your playthrough!$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_2:
# 155 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Playthrough configured!$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_0:
# 162 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Which region founded the {COLOR GREEN}{SHADOW LIGHT_GREEN}Vigor{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}\n"
	.string "province?$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1:
# 164 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "1: Kanto$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_2:
# 165 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "2: Johto$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_3:
# 166 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "3: Hoenn$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_4:
# 167 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "4: Sinnoh$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_5:
# 168 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "5: Unova$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_6:
# 169 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "6: Kalos$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_7:
# 170 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "7: Alola$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_8:
# 171 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "8: Galar$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_9:
# 172 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "9: Paldea$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_10:
# 177 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}{STR_VAR_3}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} is now available as the\n"
	.string "grass starter!$"

ChitinCragDale_Lab_EventScript_EditFireStarter_Text_0:
# 182 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Which region founded the {COLOR RED}{SHADOW LIGHT_RED}Ardor{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}\n"
	.string "province?$"

ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1:
# 197 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{COLOR RED}{SHADOW LIGHT_RED}{STR_VAR_3}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} is now available as the\n"
	.string "fire starter!$"

ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_0:
# 204 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Which region founded the {COLOR BLUE}{SHADOW LIGHT_BLUE}Guile{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}\n"
	.string "province?$"

ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1:
# 219 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{COLOR BLUE}{SHADOW LIGHT_BLUE}{STR_VAR_3}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} is now available as the\n"
	.string "water starter!$"

NicknamePartyMon_Text_0:
# 224 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Give it a nickname?$"
