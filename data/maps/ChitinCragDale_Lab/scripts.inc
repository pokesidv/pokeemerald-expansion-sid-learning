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
# 12 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lockall
# 13 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_GRASS, ChitinCragDale_Lab_EventScript_ClickOnGrassBall_2
# 13 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_FIRE, ChitinCragDale_Lab_EventScript_ClickOnGrassBall_2
# 13 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_WATER, ChitinCragDale_Lab_EventScript_ClickOnGrassBall_2
# 19 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_SELECTED_STARTER_TYPE, 0
# 20 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_PickSelectedStarter
# 21 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 22 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 23 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end

ChitinCragDale_Lab_EventScript_ClickOnGrassBall_2:
# 14 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_ClickOnGrassBall_Text_0
# 15 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 16 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end


ChitinCragDale_Lab_EventScript_ClickOnFireBall::
# 27 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lockall
# 28 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_GRASS, ChitinCragDale_Lab_EventScript_ClickOnFireBall_2
# 28 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_FIRE, ChitinCragDale_Lab_EventScript_ClickOnFireBall_2
# 28 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_WATER, ChitinCragDale_Lab_EventScript_ClickOnFireBall_2
# 34 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_SELECTED_STARTER_TYPE, 1
# 35 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_PickSelectedStarter
# 36 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 37 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 38 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end

ChitinCragDale_Lab_EventScript_ClickOnFireBall_2:
# 29 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_ClickOnGrassBall_Text_0
# 30 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 31 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end


ChitinCragDale_Lab_EventScript_ClickOnWaterBall::
# 42 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lockall
# 43 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_GRASS, ChitinCragDale_Lab_EventScript_ClickOnWaterBall_2
# 43 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_FIRE, ChitinCragDale_Lab_EventScript_ClickOnWaterBall_2
# 43 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_WATER, ChitinCragDale_Lab_EventScript_ClickOnWaterBall_2
# 49 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_SELECTED_STARTER_TYPE, 2
# 50 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_PickSelectedStarter
# 51 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 52 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 53 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end

ChitinCragDale_Lab_EventScript_ClickOnWaterBall_2:
# 44 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_ClickOnGrassBall_Text_0
# 45 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 46 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end


ChitinCragDale_Lab_EventScript_PickSelectedStarter::
# 58 "data/maps/ChitinCragDale_Lab/scripts.pory"
	switch VAR_SELECTED_STARTER_TYPE
# 59 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 0, ChitinCragDale_Lab_EventScript_PickSelectedStarter_3
# 61 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 1, ChitinCragDale_Lab_EventScript_PickSelectedStarter_4
# 63 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 2, ChitinCragDale_Lab_EventScript_PickSelectedStarter_5
# 66 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_0
# 67 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 68 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	return

ChitinCragDale_Lab_EventScript_PickSelectedStarter_1:
# 72 "data/maps/ChitinCragDale_Lab/scripts.pory"
	showmonpic VAR_SELECTED_STARTER_SPECIES, 10, 3
# 73 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_SELECTED_STARTER_SPECIES
# 74 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_1, MSGBOX_YESNO
# 75 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_8
# 103 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 104 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_4
ChitinCragDale_Lab_EventScript_PickSelectedStarter_7:
# 107 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 108 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	return

ChitinCragDale_Lab_EventScript_PickSelectedStarter_3:
# 60 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_SELECTED_STARTER_SPECIES, VAR_GRASS_SPECIES
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_1

ChitinCragDale_Lab_EventScript_PickSelectedStarter_4:
# 62 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_SELECTED_STARTER_SPECIES, VAR_FIRE_SPECIES
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_1

ChitinCragDale_Lab_EventScript_PickSelectedStarter_5:
# 64 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_SELECTED_STARTER_SPECIES, VAR_WATER_SPECIES
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_1

ChitinCragDale_Lab_EventScript_PickSelectedStarter_8:
# 76 "data/maps/ChitinCragDale_Lab/scripts.pory"
	givemon SPECIES_TREECKO, 50, ITEM_MASTER_BALL
# 77 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_11
# 82 "data/maps/ChitinCragDale_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 83 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_3
# 84 "data/maps/ChitinCragDale_Lab/scripts.pory"
	switch VAR_SELECTED_STARTER_TYPE
# 85 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 0, ChitinCragDale_Lab_EventScript_PickSelectedStarter_16
# 88 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 1, ChitinCragDale_Lab_EventScript_PickSelectedStarter_17
# 91 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 2, ChitinCragDale_Lab_EventScript_PickSelectedStarter_18
ChitinCragDale_Lab_EventScript_PickSelectedStarter_14:
# 95 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_19
# 98 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq ChitinCragDale_Lab_EventScript_PickSelectedStarter_20
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_7

ChitinCragDale_Lab_EventScript_PickSelectedStarter_11:
# 78 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 79 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_2
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_7

ChitinCragDale_Lab_EventScript_PickSelectedStarter_16:
# 86 "data/maps/ChitinCragDale_Lab/scripts.pory"
	removeobject 2
# 87 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_STARTER_GRASS
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_14

ChitinCragDale_Lab_EventScript_PickSelectedStarter_17:
# 89 "data/maps/ChitinCragDale_Lab/scripts.pory"
	removeobject 3
# 90 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_STARTER_FIRE
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_14

ChitinCragDale_Lab_EventScript_PickSelectedStarter_18:
# 92 "data/maps/ChitinCragDale_Lab/scripts.pory"
	removeobject 4
# 93 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setflag FLAG_STARTER_WATER
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_14

ChitinCragDale_Lab_EventScript_PickSelectedStarter_19:
# 96 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call NicknamePartyMon
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_7

ChitinCragDale_Lab_EventScript_PickSelectedStarter_20:
# 99 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call NicknameBoxMon
	goto ChitinCragDale_Lab_EventScript_PickSelectedStarter_7


ChitinCragDale_Lab_EventScript_EditGeneration::
# 113 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lockall
# 114 "data/maps/ChitinCragDale_Lab/scripts.pory"
	faceplayer
# 116 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_GRASS, ChitinCragDale_Lab_EventScript_EditGeneration_2
# 116 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_FIRE, ChitinCragDale_Lab_EventScript_EditGeneration_2
# 116 "data/maps/ChitinCragDale_Lab/scripts.pory"
	goto_if_set FLAG_STARTER_WATER, ChitinCragDale_Lab_EventScript_EditGeneration_2
# 122 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGeneration_Text_1
# 123 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, ChitinCragDale_Lab_EventScript_EditGeneration_Text_2, ChitinCragDale_Lab_EventScript_EditGeneration_Text_3, ChitinCragDale_Lab_EventScript_EditGeneration_Text_4
# 124 "data/maps/ChitinCragDale_Lab/scripts.pory"
	switch VAR_RESULT
# 125 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 0, ChitinCragDale_Lab_EventScript_EditGeneration_10
# 127 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 1, ChitinCragDale_Lab_EventScript_EditGeneration_11
# 129 "data/maps/ChitinCragDale_Lab/scripts.pory"
	case 2, ChitinCragDale_Lab_EventScript_EditGeneration_12
# 132 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGeneration_Text_5
ChitinCragDale_Lab_EventScript_EditGeneration_8:
# 134 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end

ChitinCragDale_Lab_EventScript_EditGeneration_2:
# 117 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGeneration_Text_0
# 118 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 119 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	end

ChitinCragDale_Lab_EventScript_EditGeneration_10:
# 126 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_EditGrassStarter
	goto ChitinCragDale_Lab_EventScript_EditGeneration_8

ChitinCragDale_Lab_EventScript_EditGeneration_11:
# 128 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_EditFireStarter
	goto ChitinCragDale_Lab_EventScript_EditGeneration_8

ChitinCragDale_Lab_EventScript_EditGeneration_12:
# 130 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call ChitinCragDale_Lab_EventScript_EditWaterStarter
	goto ChitinCragDale_Lab_EventScript_EditGeneration_8


ChitinCragDale_Lab_EventScript_EditGrassStarter::
# 139 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lockall
# 140 "data/maps/ChitinCragDale_Lab/scripts.pory"
	faceplayer
# 141 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_0
# 143 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_BULBASAUR
# 144 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_BULBASAUR
# 145 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
# 146 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_CHIKORITA
# 147 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_TREECKO
# 148 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_TREECKO
# 149 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_TURTWIG
# 150 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_TURTWIG
# 151 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_SNIVY
# 152 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_SNIVY
# 153 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_CHESPIN
# 154 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_CHESPIN
# 155 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_ROWLET
# 156 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_ROWLET
# 157 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_GROOKEY
# 158 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_GROOKEY
# 159 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_SPRIGATITO
# 160 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1, SPECIES_SPRIGATITO
# 161 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, SPECIES_BULBASAUR, DYN_MULTICHOICE_CB_SHOW_MON
# 162 "data/maps/ChitinCragDale_Lab/scripts.pory"
	setvar VAR_GRASS_SPECIES, VAR_RESULT
# 164 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_GRASS_SPECIES, VAR_RESULT
# 165 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, VAR_GRASS_SPECIES
# 166 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_2
# 167 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 168 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	return


ChitinCragDale_Lab_EventScript_EditFireStarter::
# 173 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lockall
# 174 "data/maps/ChitinCragDale_Lab/scripts.pory"
	faceplayer
# 175 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditFireStarter_Text_0
# 177 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_CHARMANDER
# 178 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_CHARMANDER
# 179 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_CYNDAQUIL
# 180 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_CYNDAQUIL
# 181 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_TORCHIC
# 182 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_TORCHIC
# 183 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_CHIMCHAR
# 184 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_CHIMCHAR
# 185 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_TEPIG
# 186 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_TEPIG
# 187 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_FENNEKIN
# 188 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_FENNEKIN
# 189 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_LITTEN
# 190 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_LITTEN
# 191 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_SCORBUNNY
# 192 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_SCORBUNNY
# 193 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_FUECOCO
# 194 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1, SPECIES_FUECOCO
# 195 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, SPECIES_CHARMANDER, DYN_MULTICHOICE_CB_SHOW_MON
# 198 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_FIRE_SPECIES, VAR_RESULT
# 199 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, VAR_FIRE_SPECIES
# 200 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditFireStarter_Text_2
# 201 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 202 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	return


ChitinCragDale_Lab_EventScript_EditWaterStarter::
# 207 "data/maps/ChitinCragDale_Lab/scripts.pory"
	lockall
# 208 "data/maps/ChitinCragDale_Lab/scripts.pory"
	faceplayer
# 209 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_0
# 211 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_SQUIRTLE
# 212 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_SQUIRTLE
# 213 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_TOTODILE
# 214 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_TOTODILE
# 215 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_MUDKIP
# 216 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_MUDKIP
# 217 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_PIPLUP
# 218 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_PIPLUP
# 219 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_OSHAWOTT
# 220 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_OSHAWOTT
# 221 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_FROAKIE
# 222 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_FROAKIE
# 223 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_POPPLIO
# 224 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_POPPLIO
# 225 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_SOBBLE
# 226 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_SOBBLE
# 227 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, SPECIES_QUAXLY
# 228 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultipush ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1, SPECIES_QUAXLY
# 229 "data/maps/ChitinCragDale_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, SPECIES_SQUIRTLE, DYN_MULTICHOICE_CB_SHOW_MON
# 231 "data/maps/ChitinCragDale_Lab/scripts.pory"
	copyvar VAR_WATER_SPECIES, VAR_RESULT
# 232 "data/maps/ChitinCragDale_Lab/scripts.pory"
	bufferspeciesname STR_VAR_3, VAR_WATER_SPECIES
# 233 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_2
# 234 "data/maps/ChitinCragDale_Lab/scripts.pory"
	waitmessage
# 235 "data/maps/ChitinCragDale_Lab/scripts.pory"
	releaseall
	return


NicknamePartyMon::
# 240 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox NicknamePartyMon_Text_0, MSGBOX_YESNO
# 241 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 242 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NicknamePartyMon_2
NicknamePartyMon_1:
	return

NicknamePartyMon_2:
# 243 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 244 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
	goto NicknamePartyMon_1


NicknameBoxMon::
# 250 "data/maps/ChitinCragDale_Lab/scripts.pory"
	msgbox NicknamePartyMon_Text_0, MSGBOX_YESNO
# 251 "data/maps/ChitinCragDale_Lab/scripts.pory"
	hidemonpic
# 252 "data/maps/ChitinCragDale_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NicknameBoxMon_2
NicknameBoxMon_1:
# 255 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
	return

NicknameBoxMon_2:
# 253 "data/maps/ChitinCragDale_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
	goto NicknameBoxMon_1


ChitinCragDale_Lab_EventScript_ClickOnGrassBall_Text_0:
# 14 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Don't be greedy!$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_0:
# 66 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "No starter selected.$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_1:
# 74 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Wanna pick {STR_VAR_1}?$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_2:
# 79 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "No more room.$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_3:
# 83 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Received {STR_VAR_1}!$"

ChitinCragDale_Lab_EventScript_PickSelectedStarter_Text_4:
# 104 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_1} sits there patiently.$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_0:
# 117 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Enjoy your starter!$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_1:
# 122 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Want to change where a starter comes\n"
	.string "from?$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_2:
# 123 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Grass$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_3:
# 123 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Fire$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_4:
# 123 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Water$"

ChitinCragDale_Lab_EventScript_EditGeneration_Text_5:
# 132 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Ok go pick one then!$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_0:
# 141 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Which grass starter do you want?$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_1:
# 144 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_1}$"

ChitinCragDale_Lab_EventScript_EditGrassStarter_Text_2:
# 166 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_3} is now available as the\n"
	.string "grass starter!$"

ChitinCragDale_Lab_EventScript_EditFireStarter_Text_0:
# 175 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Which fire starter do you want?$"

ChitinCragDale_Lab_EventScript_EditFireStarter_Text_1:
# 178 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_2}$"

ChitinCragDale_Lab_EventScript_EditFireStarter_Text_2:
# 200 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_3} is now available as the\n"
	.string "fire starter!$"

ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_0:
# 209 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Which water starter do you want?$"

ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_1:
# 212 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_3}$"

ChitinCragDale_Lab_EventScript_EditWaterStarter_Text_2:
# 233 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "{STR_VAR_3} is now available as the\n"
	.string "water starter!$"

NicknamePartyMon_Text_0:
# 240 "data/maps/ChitinCragDale_Lab/scripts.pory"
	.string "Give it a nickname?$"
