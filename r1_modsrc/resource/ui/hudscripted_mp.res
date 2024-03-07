#base "HudWeapons.res"
#base "MPSplash.res"
#base "MPObituary.res"
#base "MPPrematch.res"
#base "TitanHUD.res"
#base "HUDDev.res"
#base "HudFlyouts.res"
#base "HudIndicators.res"
#base "HudEscalation.res"
//#base "HudMissileLab.res"
//#base "HudMissileLab_CostBubbles.res"
#base "MPvdu.res"
#base "HudRodeo.res"
#base "HudReplacementTitan.res"
#base "MPDamageDebug.res"
#base "HudVoice.res"
#base "HudDeathRecap.res"
#base "MPPlaying.res"
#base "HudKillReplay.res"
#base "DebugOverlays.res"
#base "MPCapturePoint.res"
#base "MPCaptureTheFlag.res"
#base "MPExfiltration.res"
#base "MPSpectator.res"
#base "HudMinimapFullscreen.res"
#base "HudCoopEOG.res"
#base "HudRanked.res"
#base "HudRanked2X.res"

Resource/UI/HudScripted_mp.res
{
	Screen
	{
		ControlName		ImagePanel
		wide			%100
		tall			%100
		visible			1
		scaleImage		1
		fillColor		"0 0 0 0"
		drawColor		"0 0 0 0"
	}

	SafeArea
	{
		ControlName		ImagePanel
		wide			%90
		tall			%90
		visible			1
		scaleImage		1
		fillColor		"0 0 0 0"
		drawColor		"0 0 0 0"

		pin_to_sibling				Screen
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	SafeAreaCenter
	{
		ControlName		ImagePanel
		wide			%90
		tall			%90
		visible			1
		scaleImage		1
		fillColor		"0 0 0 0"
		drawColor		"0 0 0 0"

		pin_to_sibling				Screen
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	Vignette
	{
		ControlName		ImagePanel
		wide			%100
		tall			%100
		visible			0
		scaleImage		1
		image			HUD/vignette
		drawColor		"0 0 0 255"
	}

	publicMessage
	{
		ControlName			Label
		visible				0
		font				HudFontMed
		labelText			"Rebalancing teams"
		ypos				-100
		xpos				-60
		wide				400
		tall				100
		allCaps				1
		textAlignment		center
		fgcolor_override 	"255 255 255 255"
		//bgcolor_override 	"0 0 255 200"

		pin_to_sibling				Screen
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	HudBaseColor
	{
		ControlName		ImagePanel
		wide			0
		tall			0
		visible			0
		scaleImage		0
		drawColor		HudBase160
	}

	testIconAnchor
	{
		ControlName		ImagePanel
		xpos			c-8
		ypos			c-8
		wide			16
		tall			16
		visible			0
		scaleImage		1
		drawColor		"255 255 255 255"
	}

	testIcon
	{
		ControlName		ImagePanel
		xpos			100
		ypos			200
		wide			100
		tall			100
		visible			0
		image			HUD/white
		scaleImage		1
		drawColor		"255 255 255 32"
	}


	testLabel
	{
		ControlName		CHudBaseTimer
		xpos			100
		ypos			200
		wide			100
		tall			100
		visible			1
		font			HudFontMed
		NumberFont		HudFontMed
		labelText		"TestLabel"
		textAlignment	center
		//fgcolor_override 	"255 255 255 240"
	}

	EMPScreenFX
	{
		ControlName		ImagePanel
		wide			%200
		tall			%200
		visible			0
		scaleImage		1
		image			HUD/pilot_flashbang_overlay
		drawColor		"255 255 255 64"

		zpos			2999
	}

	EMPScreenFlash
	{
		ControlName		ImagePanel
		wide			%100
		tall			%100
		visible			0
		scaleImage		1
		image			HUD/white
		drawColor		"255 255 255 255"

		zpos			-1000
	}

	damageOverlayRedBloom
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide			%100
		tall			%100
		visible			0
		image			HUD/damage/damage_overlay_redbloom
		scaleImage		1
		drawColor		"255 255 255 255"
	}

	damageOverlayOrangeBloom
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide			%100
		tall			%100
		visible			0
		image			HUD/damage/damage_overlay_orangebloom
		scaleImage		1
		drawColor		"255 255 255 255"
	}

	damageOverlayLightLines
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide			%100
		tall			%100
		visible			0
		image			HUD/damage/damage_add_techlines
		scaleImage		1
		drawColor		"255 255 255 255"
	}

	damageOverlayDarkLines
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide			%100
		tall			%100
		visible			0
		image			HUD/damage/damage_overlay_dark_lines
		scaleImage		1
		drawColor		"255 255 255 255"
	}

	damageOverlaySpiderSense
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide			%100
		tall			%100
		visible			0
		image			HUD/damage/spider_sense_techlines
		scaleImage		1.0
		drawColor		"246 134 40 255"
	}

	ShoutOutAnchor
	{
		ControlName		ImagePanel
		xpos			c-0
		ypos			c-180
		wide			0
		tall			0
		visible			1
		scaleImage		1

		zpos			5
	}

	ShoutOutMessageText
	{
		ControlName		Label
		xpos			0
		ypos			0
		wide			512
		tall			256
		visible			0
		font			HudFontSmall
		labelText		"^FF8000FFPreston ^FFFFFFFF[R101] ^2E9AFEFFRoger"
		textAlignment	center
		auto_wide_tocontents	1
		fgcolor_override 	"255 255 255 240"

		zpos			5
		pin_to_sibling				ShoutOutAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	ShoutOutDescText
	{
		ControlName		Label
		xpos			0
		ypos			40
		wide			512
		tall			256
		visible			0
		font			KillShot
		labelText		"DESC"
		textAlignment	center
		fgcolor_override 	"255 255 255 205"

		zpos			5
		pin_to_sibling				ShoutOutAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	ShoutOutDescTextGlow
	{
		ControlName		Label
		xpos			0
		ypos			40
		wide			512
		tall			256
		visible			0
		font			KillShotGlow
		labelText		"DESC"
		textAlignment	center
		fgcolor_override 	"255 255 255 205"

		zpos			5
		pin_to_sibling				ShoutOutAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	ShoutOutImage
	{
		ControlName		ImagePanel
		xpos			0
		ypos			90
		wide			256
		tall			128
		visible			0
		image			../effects/health_overlay_1
		scaleImage		1

		pin_to_sibling				ShoutOutAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	countdownText
	{
		ControlName		Label
		xpos			c-256
		ypos			c
		wide			512
		tall			64
		visible			0
		font			KillShot
		labelText		"Exiting in 10"
		textAlignment	center
		fgcolor_override 	"255 255 255 205"

		zpos			5
	}

	change_class_bg
	{
		ControlName			ImagePanel
		xpos				c-55
		ypos				c-200
		wide				110
		tall				35
		visible				0
		image				HUD/loadout/fullscreen_bg
		scaleImage			1
		zpos				-5

		fillcolor			"125 125 125 50"
	}

	change_class_text
	{
		ControlName			Label
		xpos				0
		ypos				-5
		wide				100
		tall				10
		visible				0
		enabled				1
		labelText			"[classname]"
		textAlignment		center
		fgcolor_override 	"255 255 255 255"

		pin_to_sibling				change_class_bg
		pin_corner_to_sibling		4
		pin_to_sibling_corner		4
	}

	titanModeText
	{
		ControlName			Label
		xpos				-32
		ypos				-14
		wide				120
		tall				18
		visible				0
		font				HudFontMed
		labelText			"Titan Follow"
		textAlignment		west
		allCaps				1

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		2
		pin_to_sibling_corner		2
	}

	titanModeSubText
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				120
		tall				14
		visible				0
		font				HudFontSmall
		labelText			"100%"
		textAlignment		west
		allCaps				1

		pin_to_sibling				titanModeText
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	titanModeIcon
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		visible				0
		image				HUD/white
		scaleImage			1
		drawColor			"255 255 255 225"

		pin_to_sibling				titanModeText
		pin_corner_to_sibling		1
		pin_to_sibling_corner		0
	}

	pathsOutOfDate
	{
		ControlName			Label
		xpos				250
		ypos				150
		wide				440
		tall				22
		visible				0
		enable				1
		font				XpText
		labelText			"Paths Out of Date. Type buildainfile at console."
		textAlignment		center
		zpos				0

		fgcolor_override 	"255 255 0 255"
	}

	sniperCamRingAnchor
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				256
		tall				256
		visible				1
		scaleImage			1
	}

	sniperCamRingIcon
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				128
		tall				128
		visible				0
		image				HUD/snipercam_ring_mid
		scaleImage			1
		//drawColor			"255 255 255 225"

		pin_to_sibling				sniperCamRingAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		0

		zpos				2
	}

	sniperCamRingIconZoom
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		visible				0
		image				HUD/snipercam_ring_mid
		scaleImage			1
		//drawColor			"255 255 255 225"

		pin_to_sibling				sniperCamRingAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		0

		zpos				2
	}

	FullscreenNoise
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				%100
		tall				%100
		visible				0
		image				fullscreen_noise
		scaleImage			1
		//fillColor			"255 255 0 0"
		//drawColor			"255 0 0 255"

	}

	idAnchor
	{
		ControlName			ImagePanel
		xpos				c-16
		ypos				c+128
		wide				32
		tall				32
		visible				0
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	idFrame
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				224
		tall				112
		visible				0
		image				HUD/id_badges/badge_mainshape
		scaleImage			1
		drawColor			"255 255 255 255"

		zpos 500

		pin_to_sibling				idAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	idBackground
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				224
		tall				112
		visible				0
		image				HUD/id_badges/badge_mainshape_backscreen
		scaleImage			1
		drawColor			"255 255 255 255"
		zpos 0

		pin_to_sibling				idAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	idLogo
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				48
		tall				48
		visible				0
		image				HUD/ability_wallrun
		scaleImage			1
		drawColor			"255 0 0 180"

		zpos 200

		pin_to_sibling				idAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	idLogoShadow
	{
		ControlName			ImagePanel
		xpos				4
		ypos				4
		wide				48
		tall				48
		visible				0
		image				HUD//ability_wallrun
		scaleImage			1
		drawColor			"0 0 0 180"

		zpos 199

		pin_to_sibling				idAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	idName
	{
		ControlName		Label
		xpos			0
		ypos			8
		wide			128
		tall			24
		visible			0
		font			Killshot
		labelText		"stagger"
		textAlignment	center
		fgcolor_override 	"255 200 100 200"

		zpos	300

		pin_to_sibling				idAnchor
		pin_corner_to_sibling		6
		pin_to_sibling_corner		4
	}

	idNameShadow
	{
		ControlName		Label
		xpos			0
		ypos			8
		wide			128
		tall			24
		visible			0
		font			KillShotGlow
		labelText		"stagger"
		textAlignment	center
		fgcolor_override 	"255 200 100 200"

		zpos	300

		pin_to_sibling				idAnchor
		pin_corner_to_sibling		6
		pin_to_sibling_corner		4
	}

	ScreenFade_Background
	{
		ControlName			ImagePanel
		image				HUD/white
		visible				1
		enable				1
		scaleImage			1
		wide				%100
		tall				%100
		xpos				0
		ypos				0
		zpos				3000
		drawColor			"0 0 0 255"
	}

	RespawnSelect
	{
		ControlName			CNestedPanel
		xpos				0
		ypos				0
		zpos 				199

		wide				300
		tall				115
		visible				0
		controlSettingsFile	"resource/UI/HudRespawnSelect.res"

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		6
		pin_to_sibling_corner		6
	}

	deathSelectionBackground_TOP
	{
		ControlName			ImagePanel

		xpos				0
		ypos				30

		zpos 				80
		wide				900
		tall				130
		visible				0
		image				HUD/white
		scaleImage			1
		drawColor			"0 0 0 245"

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		4
		pin_to_sibling_corner		4
	}

	deathSelectionBackground_BOTTOM
	{
		ControlName			ImagePanel

		xpos				0
		ypos				30

		zpos 				80
		wide				900
		tall				130
		visible				0
		image				HUD/white
		scaleImage			1
		drawColor			"0 0 0 245"

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		6
		pin_to_sibling_corner		6
	}

	deathSelection_TEXT
	{
		ControlName			Label
		xpos				0
		ypos				5
		zpos 				120
		//auto_wide_tocontents 1
		//auto_tall_tocontents 1
		wide				200
		tall				20
		visible				0
		//font				LobbyPlayerFont
		font				HudTitle
		labelText			"Choose your respawn"
		allCaps				1
		textAlignment		center
		fgcolor_override 	"204 234 255 255"
		fillColor			"50 50 50 100"
		//bgcolor_override 	"0 0 255 200"

		pin_to_sibling				deathSelectionBackground_BOTTOM
		pin_corner_to_sibling		6
		pin_to_sibling_corner		4
	}


	deathSelection_SHADOW
	{
		ControlName			Label
		xpos				1.5
		ypos				3
		zpos 118
		//auto_wide_tocontents 1
		//auto_tall_tocontents 1
		wide				400
		tall				20
		visible				0
		//font				LobbyPlayerFont
		font				HudTitle
		labelText			"Choose your respawn"
		allCaps				1
		textAlignment		center
		fgcolor_override 	"0 0 0 255"
		//bgcolor_override 	"0 0 255 200"

		pin_to_sibling				deathSelection_TEXT
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}


//		image				"../ui/icon_status_titan"


	changeLoadoutBackground
	{
		ControlName			ImagePanel
		ypos				-48
		wide				200
		tall				24
		visible				0
		image				"../ui/instruction_bg"
		scaleImage			1

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	changeLoadoutText
	{
		ControlName			Label
		xpos				12
		ypos				0
		zpos 120
		//auto_wide_tocontents 1
		//auto_tall_tocontents 1
		wide				400
		tall				50
		visible				0
		font				HudFontMed
		labelText			"#CHANGE_LOADOUT"
		allCaps				1
		textAlignment		center
		fgcolor_override 	"255 255 255 255"
		//bgcolor_override 	"0 0 255 200"

		pin_to_sibling				changeLoadoutBackground
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	BurnCardCoinValueDisplay
	{
		ControlName				Label
		xpos					575
		ypos 					83
		zpos					3 // Needed or clicking on the background can hide this
		font					HudFontMed
		auto_tall_tocontents 	1
		textinsetx				6
		allcaps					0
		fgcolor_override		"210 170 0 255"
		textAlignment			west

		visible					1
		wrap					0
		//wide					250
		auto_wide_tocontents 	1

		labelText				""
	}

	BurnCardCoinValueIcon
	{
		ControlName				ImagePanel
		classname				"CoinCountIconClass"
		xpos 					5
		zpos					3
		wide					16
		tall					16
		visible					0
		image					"../vgui/black_market/coin"
		scaleImage				1
		drawColor				"204 234 255 255"

		pin_to_sibling				BurnCardCoinValueDisplay
		pin_corner_to_sibling		7
		pin_to_sibling_corner		5
	}

	BurnCardTipDisplay
	{
		ControlName				Label
		//auto_wide_tocontents 	1
		auto_tall_tocontents 	1
		zpos					3 // Needed or clicking on the background can hide this
		font					HudFontMed
		textinsetx				6
		allcaps					0
		fgcolor_override		"204 234 255 255"
		textAlignment			west
		//activeInputExclusivePaint	gamepad

		visible					0
		wrap					0
		wide					700
		//tall					50
		xpos					60
		ypos					83


		//pin_to_sibling			BurnCardsImgTopBar
		//pin_corner_to_sibling	0
		//pin_to_sibling_corner	2
		labelText				"lasts for one life"
	}

	BurnCardWarningDisplay
	{
		ControlName				Label
		//auto_wide_tocontents 	1
		auto_tall_tocontents 	1
		zpos					3 // Needed or clicking on the background can hide this
		font					HudFontMedOutlineDropShadow
		textinsetx				6
		allcaps					0
		fgcolor_override		"204 234 255 255"
		textAlignment			west
		//activeInputExclusivePaint	gamepad

		visible					0
		wrap					0
		wide					700
		//tall					50
		xpos					60
		ypos					80


		//pin_to_sibling			BurnCardsImgTopBar
		//pin_corner_to_sibling	0
		//pin_to_sibling_corner	2
		labelText				"lasts for one life"
	}

	OnDeckCard_RespawnSelect_Anchor
	{
		ControlName			ImagePanel
		xpos				180
		ypos				-20
		zpos				150
		wide				71
		tall				97
		visible				1
		scaleImage			1

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		6
		pin_to_sibling_corner		6
	}

	OnDeckCard_Prematch_Anchor
	{
		ControlName			ImagePanel
		xpos				-96
		ypos				-55
		zpos				150
		wide				71
		tall				97
		visible				1
		scaleImage			1

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		2
		pin_to_sibling_corner		2
	}

	HudBurnCard_OnDeckCard
	{
		ControlName			CNestedPanel
		xpos				0
		ypos				10
		zpos				3990

		wide				110
		tall				110
		visible				0
		controlSettingsFile	"scripts/screens/vgui_burn_card_mid.res"

		pin_to_sibling				OnDeckCard_RespawnSelect_Anchor
		pin_corner_to_sibling		1
		pin_to_sibling_corner		1
	}

	HudBurnCard_OnDeckCard_Select
	{
		ControlName			Label
		xpos				0
		ypos				-03
		visible				0
		zpos				3990
		wide				150
		tall				20
		labelText			"#BURNCARD_SELECT"
		font				HudFontMed
		textAlignment		center
		drawColor			"255 255 255 255"
		visible				0

		pin_to_sibling				HudBurnCard_OnDeckCard
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	HudBurnCard_Selector1
	{
		ControlName			CNestedPanel
		xpos				-20
		ypos				6
		zpos				3990

		wide				110
		tall				110
		visible				0
		controlSettingsFile	"scripts/screens/vgui_burn_card_mid.res"

		pin_to_sibling				OnDeckCard_RespawnSelect_Anchor
		pin_corner_to_sibling		1
		pin_to_sibling_corner		1
	}

	HudBurnCard_Selector1_button
	{
		ControlName			Label
		xpos				0
		ypos				-7
		visible				0
		zpos				3991
		wide				150
		tall				20
		labelText			"#BURNCARD_SELECTOR1"
		font				HudFontMed
		textAlignment		center
		drawColor			"255 255 255 255"
		visible				0

		pin_to_sibling				HudBurnCard_Selector1
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	HudBurnCard_Selector2
	{
		ControlName			CNestedPanel
		xpos				50
		ypos				6
		zpos				3990

		wide				110
		tall				110
		visible				0
		controlSettingsFile	"scripts/screens/vgui_burn_card_mid.res"

		pin_to_sibling				OnDeckCard_RespawnSelect_Anchor
		pin_corner_to_sibling		1
		pin_to_sibling_corner		1
	}

	HudBurnCard_Selector2_button
	{
		ControlName			Label
		xpos				0
		ypos				-7
		visible				0
		zpos				3991
		wide				150
		tall				20
		labelText			"#BURNCARD_SELECTOR2"
		font				HudFontMed
		textAlignment		center
		drawColor			"255 255 255 255"
		visible				0

		pin_to_sibling				HudBurnCard_Selector2
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	HudBurnCard_Selector3
	{
		ControlName			CNestedPanel
		xpos				120
		ypos				6
		zpos				3990

		wide				110
		tall				110
		visible				0
		controlSettingsFile	"scripts/screens/vgui_burn_card_mid.res"

		pin_to_sibling				OnDeckCard_RespawnSelect_Anchor
		pin_corner_to_sibling		1
		pin_to_sibling_corner		1
	}

	HudBurnCard_Selector3_button
	{
		ControlName			Label
		xpos				0
		ypos				-7
		visible				0
		zpos				3991
		wide				150
		tall				20
		labelText			"#BURNCARD_SELECTOR3"
		font				HudFontMed
		textAlignment		center
		drawColor			"255 255 255 255"
		visible				0

		pin_to_sibling				HudBurnCard_Selector3
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	//rescue ship
	RescueShipArrow_0
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				48
		tall				48
		visible				0
		enable				1
		image				offscreen_arrow
		scaleImage			1
		drawColor			"255 255 255 255"

		zpos				1
	}

	RescueShipIcon_0
	{
		ControlName			ImagePanel
		xpos				c0
		ypos				0
		wide				24
		tall				24
		visible				0
		enable				1
		image				HUD/call_in_drop_ship
		scaleImage			1
		drawColor			"255 255 255 255"

		zpos				1
	}

	RescueShipText_0
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				300
		tall				20
		visible				0
		enabled				1
		labelText			"ETA:"
		textAlignment		center
		font				HudFontSmall
		fgcolor_override 	"255 255 255 255"

		pin_to_sibling				RescueShipIcon_0
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	RescueShipLabel_0
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				300
		tall				20
		visible				0
		enabled				1
		labelText			"ETA:"
		textAlignment		center
		font				HudFontMedSmall
		fgcolor_override 	"255 255 255 255"

		pin_to_sibling				RescueShipIcon_0
		pin_corner_to_sibling		6
		pin_to_sibling_corner		4
	}

	Scoreboard
	{
		ControlName			CNestedPanel
		xpos				0
		ypos				0
		wide				%100
		tall				%100
		visible				0

		zpos				4000

		controlSettingsFile	"resource/UI/HudScoreboard.res"
	}

	ClientHud
	{
		ControlName			CNestedPanel
		xpos				0
		ypos				0
		wide				852
		tall				480
		visible				0

		zpos				2000

		controlSettingsFile	"resource/UI/HudMain.res"
	}

	TargetOverheadHealthBar
	{
		ControlName			CHudProgressBar
		xpos				0
		ypos				0
		wide				42
		tall				8
		visible				0
		bg_image			HUD/overhead_shieldbar_bg
		fg_image			HUD/overhead_shieldbar_health
		change_image		HUD/overhead_shieldbar_health_change
		fgcolor_override	"255 255 255 255"
		bgcolor_override	"255 255 255 255"
		SegmentSize			42
		SegmentGap			0
		Inset				0
		Margin				0
		ProgressDirection	0
		SegmentFill			2
		ChangeStyle			1
		ChangeTime			0.25
		ChangeDir			0
		//ChangeColor			"255 128 64 255"

		zpos 97
	}

	TargetOverheadShieldHealthBar
	{
		ControlName			CHudProgressBar
		xpos				0
		ypos				0
		wide				42
		tall				8
		visible				0
		bg_image			HUD/white
		fg_image			HUD/overhead_shieldbar_shield
		fgcolor_override	"255 255 255 255"
		bgcolor_override	"0 0 0 0"
		SegmentSize			42
		SegmentGap			0
		Inset				0
		Margin				0
		ProgressDirection	0
		SegmentFill			2

		zpos 98
	}

	TargetOverheadDoomedHealthBar
	{
		ControlName			CHudProgressBar
		xpos				0
		ypos				0
		wide				42
		tall				4
		visible				0
		bg_image			HUD/overhead_bar_doomed
		fg_image			HUD/overhead_bar
		fgcolor_override	"196 32 0 255"
		bgcolor_override	"255 255 255 255"
		SegmentSize			43
		SegmentGap			0
		Inset				0
		Margin				0
		ProgressDirection	0
		SegmentFill			2

		zpos 99
	}

	CrosshairWeakHitIndicator
	{
		ControlName			ImagePanel
		xpos				c-36
		ypos				c-36
		wide				72
		tall				72
		visible				0
		image				HUD/crosshairs/hit_indicator_weak
		scaleImage			1

		zpos				202
	}

	//BurnCardsMenuTitle2
	//{
	//	ControlName				Label
	//	xpos					63
	//	ypos					330
	//	zpos					10
	//	//auto_wide_tocontents 	1
	//
	//	visible					1
	//	font					TitanHUD
	//	wide					230
	//	tall					100
	//	wrap					1
	//
	//	allcaps					1
	//	fgcolor_override		"204 234 255 255"
	//	labelText				"The top three Burn Cards from your deck may be used when you spawn. When you use a Burn Card, it is gone forever."
    //
	//	//pin_to_sibling				SafeArea
	//	//pin_corner_to_sibling		2
	//	//pin_to_sibling_corner		2
	//}


	BurnCardsMenuText1
	{
		ControlName				Label
		xpos					10
		ypos					-100
		zpos					10
		//auto_wide_tocontents 	1

		visible					0
		font					BurnCardLetterTitle
		wide					400
		tall					100
		wrap					1

		allcaps					1
		fgcolor_override		"204 234 255 255"
		labelText				"An envelope has been left under your door. It has no post mark or identification."
		pin_to_sibling				SafeArea
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	BurnCardsMenuText2
	{
		ControlName				Label
		xpos					0
		ypos					-10
		zpos					10
		//auto_wide_tocontents 	1

		visible					0
		font					BurnCardLetterContents
		wide					400
		tall					80
		wrap					1

		allcaps					1
		fgcolor_override		"204 234 255 255"
		labelText				"Your performance in the field has been noted. Please find therein a set of cards. They are not playing cards. They are favors. When you wish to redeem one, burn it. The favor will follow."
		pin_to_sibling				BurnCardsMenuText1
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	BurnCardsMenuText3
	{
		ControlName				Label
		xpos					0
		ypos					10
		zpos					10
		//auto_wide_tocontents 	1

		visible					0
		font					BurnCardLetterContents
		wide					400
		tall					20
		textAlignment			east
		labelText				"-An Advocate"

		allcaps					1
		fgcolor_override		"204 234 255 255"
		pin_to_sibling				BurnCardsMenuText2
		pin_corner_to_sibling		1
		pin_to_sibling_corner		3
	}

	BurnCardsMenuText4
	{
		ControlName				Label
		xpos					0
		ypos					20
		zpos					10
		//auto_wide_tocontents 	1

		visible					0
		font					BurnCardLetterContents
		wide					400
		tall					80
		wrap					1

		allcaps					1
		fgcolor_override		"204 234 255 255"
		labelText				"P.S. Please Be mindful of the order you put them in."
		pin_to_sibling				BurnCardsMenuText2
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	BurnCardContinue
	{
		ControlName				Label
		xpos					0
		ypos					85
		auto_wide_tocontents 	1
		auto_tall_tocontents 	1
		zpos					3 // Needed or clicking on the background can hide this
		visible					0
		font					BurnCardLetterTitle
		textinsetx				20 // This is so we can just place them all side by side and spacing is built in.

		labelText				"#BURNCARD_CONTINUE_PROMPT"

		pin_to_sibling				BurnCardsMenuText2
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	BurnCardServerMessage
	{
		ControlName				Label
		xpos					0
		ypos					0
		auto_wide_tocontents 	1
		auto_tall_tocontents 	1
		zpos					3 // Needed or clicking on the background can hide this
		visible					0
		font					ConduitBold36

		labelText				"#BURNCARD_SERVER_MESSAGE"
		fgcolor_override		"204 234 255 255"

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	BurnCardsStarterHelpText
	{
		ControlName				Label
		xpos					0
		ypos					162
		zpos					20

		visible					0
		font					BurnCardLetterTitle
		wide					570
		tall					40
		textAlignment			center
		//centerwrap				0

		allcaps					0
		fgcolor_override		"204 234 255 255"
		labelText				"This is your active Burn Card slot."
		//labelText				"Place a Burn Card into the active slot. You can spend it during your next match."


		pin_to_sibling				SafeArea
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8

		//pin_to_sibling				BurnCardStarterHelpImage
		//pin_corner_to_sibling		7
		//pin_to_sibling_corner		5
	}


	BurnCardsStarterHelpTextBackground
	{
		ControlName			ImagePanel
		xpos				0
		image				HUD/white
		visible				0
		enable				1
		scaleImage			1
		wide				420
		tall				32
		zpos				0
		drawColor			"70 70 90 255"
		pin_to_sibling				BurnCardsStarterHelpText
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	BurnCardIntroEnvelopeImage
	{
		ControlName			ImagePanel
		xpos				45
		ypos				120
		zpos				10
		visible				0
		wide				113
		tall				157
		scaleImage			1
		image				"../vgui/black_market/cardpack_standard"
	}

	OutOfBoundsWarning_Anchor
	{
		ControlName				Label
		xpos					c-1
		ypos					c-20
		wide					2
		tall					2
		visible					0
		enabled					1
		labelText				""
		textAlignment			center
		fgcolor_override 		"255 255 0 255"
		font					HudFontLarge
	}

	OutOfBoundsWarning_Message
	{
		ControlName				Label
		//xpos					0
		//ypos					0
		//xpos					-50
		//ypos					50
		xpos					100
		ypos					35
		wide					300
		tall					20
		visible					0
		enabled					1
		auto_wide_tocontents	1
		//labelText				"#OUT_OF_BOUNDS_WARNING"
		labelText				""
		textAlignment			center
		fgcolor_override 		"255 255 0 255"
		bgcolor_override 		"0 0 0 200"
		font					HudFontLarge

		pin_to_sibling			OutOfBoundsWarning_Anchor
		pin_corner_to_sibling	4
		pin_to_sibling_corner	6
	}

	OutOfBoundsWarning_Timer
	{
		ControlName				Label
		xpos					0
		ypos					0
		wide					300
		tall					20
		visible					0
		enabled					1
		auto_wide_tocontents	1
		labelText				":00"
		textAlignment			center
		fgcolor_override 		"255 255 0 255"
		bgcolor_override 		"0 0 0 200"
		font					HudFontLarge

		pin_to_sibling			OutOfBoundsWarning_Message
		pin_corner_to_sibling	4
		pin_to_sibling_corner	6
	}

	IntroScreenBackground
	{
		ControlName			ImagePanel
		image				HUD/white
		visible				0
		enable				1
		scaleImage			1
		wide				%100
		tall				%100
		xpos				0
		ypos				0
		zpos				998
		drawColor			"0 0 0 255"
	}

	IntroScreenFactionLogo
	{
		ControlName			ImagePanel
		xpos				c-50
		ypos				c-50
		wide				100
		tall				100
		visible				0
		scaleImage			1
		zpos				1001
	}

	IntroScreenFactionLogoFlare
	{
		ControlName			ImagePanel
		xpos				c-50
		ypos				c-50
		wide				100
		tall				100
		image				HUD/flare_announcement
		visible				0
		scaleImage			1

		zpos			1000
	}

	IntroScreenTextLine0
	{
		ControlName			Label
		xpos				c-300
		ypos				200
		wide				600
		tall				35
		visible				0
		enabled				1
		labelText			"INTRO SCREEN LINE 1"
		textAlignment		center
		fgcolor_override 	"255 255 255 255"
		font				HudFontExtraLarge
		zpos				999
	}

	IntroScreenTextLine1
	{
		ControlName			Label
		xpos				0
		ypos				10
		wide				600
		tall				20
		visible				0
		enabled				1
		labelText			"INTRO SCREEN LINE 2"
		textAlignment		center
		fgcolor_override 	"255 255 255 255"
		font				HudFontLarge
		zpos				999

		pin_to_sibling				IntroScreenTextLine0
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	IntroScreenTextLine2
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				600
		tall				20
		visible				0
		enabled				1
		labelText			"INTRO SCREEN LINE 3"
		textAlignment		center
		fgcolor_override 	"255 255 255 255"
		font				HudFontLarge
		zpos				999

		pin_to_sibling				IntroScreenTextLine1
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	IntroScreenTextLine3
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				600
		tall				20
		visible				0
		enabled				1
		labelText			"INTRO SCREEN LINE 4"
		textAlignment		center
		fgcolor_override 	"255 255 255 255"
		font				HudFontLarge
		zpos				999

		pin_to_sibling				IntroScreenTextLine2
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	IntroScreenTextLine4
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				600
		tall				20
		visible				0
		enabled				1
		labelText			"INTRO SCREEN LINE 5"
		textAlignment		center
		fgcolor_override 	"255 255 255 255"
		font				HudFontLarge
		zpos				999

		pin_to_sibling				IntroScreenTextLine3
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	ScreenFade
	{
		ControlName			ImagePanel
		image				HUD/white
		visible				0
		scaleImage			1
		wide				%100
		tall				%100
		xpos				0
		ypos				0
		zpos				3000
		drawColor			"0 0 0 255"
	}

	AnnouncementAnchor
	{
		ControlName		ImagePanel
		xpos			c-200
		//ypos			c-100
		ypos			c-140
		wide			400
		tall			30
		//image			HUD/flare_fat
		visible			1
		scaleImage		1
		drawColor		"0 0 0 0"
	}

	Announcement
	{
		ControlName				Label
		xpos					0
		ypos					0
		wide					400
		tall					30
		visible					0
		font					AnnouncementFont
		allCaps 				0 	[!$RUSSIAN]
		allCaps 				1 	[$RUSSIAN]
		labelText				"TITAN READY"
		textAlignment			center
		auto_wide_tocontents	1
		fgcolor_override 		"255 255 255 255"

		zpos			3501

		pin_to_sibling				AnnouncementAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}


	AnnouncementBG
	{
		ControlName				Label
		xpos					0
		ypos					0
		wide					400
		tall					30
		visible					0
		font					AnnouncementBGFont
		allCaps 				0 	[!$RUSSIAN]
		allCaps 				1 	[$RUSSIAN]
		labelText				"TITAN READY"
		textAlignment			center
		auto_wide_tocontents	1
		fgcolor_override 		"0 0 0 255"

		zpos			3500

		pin_to_sibling				AnnouncementAnchor
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	AnnouncementScan
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide			400
		tall			30
		image			HUD/flare_announcement
		visible			0
		scaleImage		1

		zpos			3502

		pin_to_sibling				Announcement
		pin_corner_to_sibling		7
		pin_to_sibling_corner		7
	}

	AnnouncementSubText
	{
		ControlName				Label
		xpos					0
		ypos					-6
		wide					400
		tall					30
		visible					0
		font					HudFontMedSmall
		labelText				""
		textAlignment			center
		auto_wide_tocontents	1
		fgcolor_override 		"255 255 255 255"
		allCaps				1

		zpos			3500

		pin_to_sibling				Announcement
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	AnnouncementSubText2
	{
		ControlName				Label
		xpos					0
		ypos					16
		wide					600
		tall					200
		visible					0
		font					HudFontMedSmall
		labelText				""
		textAlignment			north
		centerwrap				1
		//auto_wide_tocontents	1
		fgcolor_override 		"255 255 255 160"
		allCaps					0

		zpos			3500

		pin_to_sibling				Announcement
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	AnnouncementSubText2Large
	{
		ControlName				Label
		xpos					0
		ypos					19
		wide					400
		tall					30
		visible					0
		font					AnnouncementFont
		allCaps 				0 	[!$RUSSIAN]
		allCaps 				1 	[$RUSSIAN]
		labelText				"TITAN READY"
		textAlignment			center
		auto_wide_tocontents	1
		fgcolor_override 		"0 255 0 255"

		zpos			3500

		pin_to_sibling				Announcement
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	AnnouncementSubText2LargeBG
	{
		ControlName				Label
		xpos					0
		ypos					19
		wide					400
		tall					30
		visible					0
		font					AnnouncementBGFont
		allCaps 				0 	[!$RUSSIAN]
		allCaps 				1 	[$RUSSIAN]
		labelText				"TITAN READY"
		textAlignment			center
		auto_wide_tocontents	1
		fgcolor_override 		"0 0 0 255"

		zpos			3499

		pin_to_sibling				Announcement
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	AnnouncementIcon
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide			64
		tall			64
		visible			0
		scaleImage		1
		image			"../ui/scoreboard_imc_logo"
		drawColor		"255 255 255 255"

		zpos			3500

		pin_to_sibling				AnnouncementAnchor
		pin_corner_to_sibling		6
		pin_to_sibling_corner		4
	}

	AnnouncementIconLabel
	{
		ControlName				Label
		xpos					0
		ypos					0
		wide					64
		tall					64
		visible					0
		font					AnnouncementFont
		allCaps 				0 	[!$RUSSIAN]
		allCaps 				1 	[$RUSSIAN]
		labelText				""
		textAlignment			center
		fgcolor_override 		"255 255 255 255"
		allCaps					1

		zpos			3501

		pin_to_sibling				AnnouncementIcon
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	AnnouncementLeftIcon
	{
		ControlName		ImagePanel
		xpos			-40
		ypos			44
		wide			64
		tall			64
		visible			0
		scaleImage		1
		image			"../ui/scoreboard_imc_logo"
		drawColor		"255 255 255 255"

		zpos			3500

		pin_to_sibling				AnnouncementAnchor
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	AnnouncementRightIcon
	{
		ControlName		ImagePanel
		xpos			40
		ypos			44
		wide			64
		tall			64
		visible			0
		scaleImage		1
		image			"../ui/scoreboard_mcorp_logo"
		drawColor		"255 255 255 255"

		zpos			3500

		pin_to_sibling				AnnouncementAnchor
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	AnnouncementLeftText
	{
		ControlName		Label
		xpos			0
		ypos			0
		wide			128
		tall			20
		visible			0
		font			AnnouncementScoreFont
		allCaps 		0 	[!$RUSSIAN]
		allCaps 		1 	[$RUSSIAN]
		labelText		"2/3 Wins"
		textAlignment	center
		drawColor		"255 255 255 255"

		zpos			3500

		pin_to_sibling				AnnouncementLeftIcon
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	AnnouncementRightText
	{
		ControlName		Label
		xpos			0
		ypos			0
		wide			128
		tall			20
		visible			0
		font			AnnouncementScoreFont
		allCaps 		0 	[!$RUSSIAN]
		allCaps 		1 	[$RUSSIAN]
		labelText		"0/3 Wins"
		textAlignment	center
		drawColor		"255 255 255 255"

		zpos			3500

		pin_to_sibling				AnnouncementRightIcon
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	EventNotification
	{
		ControlName				Label
		xpos					0
		ypos					-30
		wide					400
		tall					30
		visible					0
		font					HudFontLarge
		labelText				"Something is going on!"
		textAlignment			center
		auto_wide_tocontents	1
		fgcolor_override 		"255 255 255 255"
		allCaps					1

		zpos			1000

		pin_to_sibling				AnnouncementAnchor
		pin_corner_to_sibling		6
		pin_to_sibling_corner		4
	}

	TrainingPromptLabel_Keyboard
	{
		ControlName		Label
		xpos			-180
		ypos			-30
		auto_wide_tocontents 1
		tall 			25
		visible			0
		font 			HudFontMedSmallOutlineShadowGlow
		labelText		"Training button prompt KEYBOARD"
		textAlignment	west
		fgcolor_override 	"255 255 255 255"
		bgcolor_override 	"50 50 50 170"
		paintbackground		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		0
		pin_to_sibling_corner		0
	}

	TrainingPromptLabel_Keyboard_Condensed
	{
		ControlName		Label
		xpos			-180
		ypos			-30
		auto_wide_tocontents 1
		tall 			25
		visible			0
		font			HudFontSmallOutlineShadowGlow
		labelText		"Training button prompt KEYBOARD CONDENSED"
		textAlignment	west
		fgcolor_override 	"255 255 255 255"
		bgcolor_override 	"50 50 50 170"
		paintbackground		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		0
		pin_to_sibling_corner		0
	}

	TrainingPromptHeader_BufferBottom_Keyboard
	{
		ControlName		ImagePanel
		xpos			-1
		ypos			0
		wide 			128
		tall 			2
		visible			0
		font			HudFontMedPlain
		textAlignment 	west
		labelText 		""
		drawColor 		"60 100 140 220"
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Keyboard
		pin_corner_to_sibling		2
		pin_to_sibling_corner		0
	}


	TrainingPromptHeader_Keyboard
	{
		ControlName		Label
		xpos			0
		ypos			0
		auto_wide_tocontents 1
		tall			19
		visible			0
		font			HudFontMedPlain
		labelText		" INSTRUCTION "
		textAlignment	west
		fgcolor_override 	"255 234 0 255"
		bgcolor_override 	"60 100 140 220"
		paintbackground		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				TrainingPromptHeader_BufferBottom_Keyboard
		pin_corner_to_sibling		2
		pin_to_sibling_corner		0
	}

	TrainingPromptLabel_BufferLeft_Keyboard
	{
		ControlName 	ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/text_tab_l"
		drawColor 		"50 50 50 170"
		scaleImage 		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Keyboard
		pin_corner_to_sibling		1
		pin_to_sibling_corner		0
	}

	TrainingPromptLabel_BufferRight_Keyboard
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/text_tab_r"
		drawColor 		"50 50 50 170"
		scaleImage 		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Keyboard
		pin_corner_to_sibling		0
		pin_to_sibling_corner		1
	}

	TrainingPromptLabel_BufferRight_Keyboard_Condensed
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/text_tab_r"
		drawColor 		"50 50 50 170"
		scaleImage 		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Keyboard_Condensed
		pin_corner_to_sibling		0
		pin_to_sibling_corner		1
	}

	TrainingPromptHeader_BufferLeft_Keyboard
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/header_tab_l"
		drawColor 		"60 100 140 220"
		scaleImage 		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				TrainingPromptHeader_Keyboard
		pin_corner_to_sibling		3
		pin_to_sibling_corner		2
	}

	TrainingPromptHeader_BufferRight_Keyboard
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/header_tab_r"
		drawColor 		"60 100 140 220"
		scaleImage 		1
		activeInputExclusivePaint "keyboard"

		zpos 1000

		pin_to_sibling				TrainingPromptHeader_Keyboard
		pin_corner_to_sibling		2
		pin_to_sibling_corner		3
	}

	TrainingPromptHeader_SeparatorLine_Keyboard
	{
		ControlName		ImagePanel
		xpos			16
		ypos			0
		wide 			256
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/textbar_line"
		scaleImage 		1
		drawColor 		"255 255 255 255"

		activeInputExclusivePaint "keyboard"

		zpos 1001

		pin_to_sibling				TrainingPromptHeader_BufferBottom_Keyboard
		pin_corner_to_sibling		2
		pin_to_sibling_corner		2
	}

	/////////////////////////////////////////////////////////////////
	TrainingPromptLabel_Gamepad
	{
		ControlName		Label
		xpos			-180
		ypos			-30
		auto_wide_tocontents 1
		tall 			25
		visible			0
		font 			HudFontMedSmallOutlineShadowGlow
		labelText		"Training button prompt GAMEPAD"
		textAlignment	west
		fgcolor_override 	"255 255 255 255"
		bgcolor_override 	"50 50 50 170"
		paintbackground		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		0
		pin_to_sibling_corner		0
	}

	TrainingPromptLabel_Gamepad_Condensed
	{
		ControlName		Label
		xpos			-180
		ypos			-30
		auto_wide_tocontents 1
		tall 			25
		visible			0
		font			HudFontSmallOutlineShadowGlow
		labelText		"Training button prompt GAMEPAD CONDENSED"
		textAlignment	west
		fgcolor_override 	"255 255 255 255"
		bgcolor_override 	"50 50 50 170"
		paintbackground		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		0
		pin_to_sibling_corner		0
	}

	TrainingPromptHeader_BufferBottom_Gamepad
	{
		ControlName		ImagePanel
		xpos			-1
		ypos			0
		wide 			128
		tall 			2
		visible			0
		font			HudFontMedPlain
		textAlignment 	west
		labelText 		""
		drawColor 		"60 100 140 220"
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Gamepad
		pin_corner_to_sibling		2
		pin_to_sibling_corner		0
	}


	TrainingPromptHeader_Gamepad
	{
		ControlName		Label
		xpos			0
		ypos			0
		auto_wide_tocontents 1
		tall			19
		visible			0
		font			HudFontMedPlain
		labelText		" INSTRUCTION "
		textAlignment	west
		fgcolor_override 	"255 234 0 255"
		bgcolor_override 	"60 100 140 220"
		paintbackground		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				TrainingPromptHeader_BufferBottom_Gamepad
		pin_corner_to_sibling		2
		pin_to_sibling_corner		0
	}

	TrainingPromptLabel_BufferLeft_Gamepad
	{
		ControlName 	ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/text_tab_l"
		drawColor 		"50 50 50 170"
		scaleImage 		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Gamepad
		pin_corner_to_sibling		1
		pin_to_sibling_corner		0
	}

	TrainingPromptLabel_BufferRight_Gamepad
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/text_tab_r"
		drawColor 		"50 50 50 170"
		scaleImage 		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Gamepad
		pin_corner_to_sibling		0
		pin_to_sibling_corner		1
	}

	TrainingPromptLabel_BufferRight_Gamepad_Condensed
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/text_tab_r"
		drawColor 		"50 50 50 170"
		scaleImage 		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				TrainingPromptLabel_Gamepad_Condensed
		pin_corner_to_sibling		0
		pin_to_sibling_corner		1
	}

	TrainingPromptHeader_BufferLeft_Gamepad
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/header_tab_l"
		drawColor 		"60 100 140 220"
		scaleImage 		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				TrainingPromptHeader_Gamepad
		pin_corner_to_sibling		3
		pin_to_sibling_corner		2
	}

	TrainingPromptHeader_BufferRight_Gamepad
	{
		ControlName		ImagePanel
		xpos			0
		ypos			0
		wide 			16
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/header_tab_r"
		drawColor 		"60 100 140 220"
		scaleImage 		1
		activeInputExclusivePaint "gamepad"

		zpos 1000

		pin_to_sibling				TrainingPromptHeader_Gamepad
		pin_corner_to_sibling		2
		pin_to_sibling_corner		3
	}

	TrainingPromptHeader_SeparatorLine_Gamepad
	{
		ControlName		ImagePanel
		xpos			16
		ypos			0
		wide 			256
		tall 			32
		visible			0
		image 			"HUD/textbar_elements/textbar_line"
		scaleImage 		1
		drawColor 		"255 255 255 255"

		activeInputExclusivePaint "gamepad"

		zpos 1001

		pin_to_sibling				TrainingPromptHeader_BufferBottom_Gamepad
		pin_corner_to_sibling		2
		pin_to_sibling_corner		2
	}
	/////////////////////////////////////////////////////////////////


	ControllerImage
	{
		ControlName			ImagePanel
		xpos				23
		ypos				0
		wide				240
		tall				170
		image 				"../ui/menu/controls_menu/xboxone_gamepad_stick_layout" [$DURANGO]
		image 				"../ui/menu/controls_menu/x360_gamepad_stick_layout" [!$DURANGO]
		visible				0
		scaleImage			1

		zpos				1001

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		5
		pin_to_sibling_corner		5
	}

	// these images hide the dark analog sticks for when we want to highlight other buttons
	Controller_GrayStickOverlay_L
	{
		ControlName			ImagePanel
		xpos				-71
		ypos				-5
		wide				37
		tall				36
		image 				"../vgui/hud/thumbstick_pressed"
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		8
		pin_to_sibling_corner		7
	}

	Controller_GrayStickOverlay_R
	{
		ControlName			ImagePanel
		xpos				-95
		ypos				21
		wide				38
		tall				38
		image 				"../vgui/hud/thumbstick_pressed"
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		8
		pin_to_sibling_corner		5
	}

	ControllerCallout_Bumper_Left
	{
		ControlName			ImagePanel
		xpos				-75
		ypos				-46
		wide				64
		tall				32
		image 				"../vgui/HUD/LB_pressed" [$DURANGO]
		image 				"../vgui/HUD/x360_LB_pressed" [!$DURANGO]
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		8
		pin_to_sibling_corner		0
	}

	ControllerCallout_Bumper_Right
	{
		ControlName			ImagePanel
		xpos				-75
		ypos				-46
		wide				64
		tall				32
		image 				"../vgui/HUD/RB_pressed" [$DURANGO]
		image 				"../vgui/HUD/x360_RB_pressed" [!$DURANGO]
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		8
		pin_to_sibling_corner		1
	}

	ControllerCallout_BumperGlow_Left
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				64
		tall				32
		image 				"../vgui/HUD/LB_pressed_callout" [$DURANGO]
		image 				"../vgui/HUD/x360_LB_pressed_callout" [!$DURANGO]
		visible				0
		scaleImage			1
		drawColor			"255 234 0 255"

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerCallout_Bumper_Left
		pin_corner_to_sibling		0
		pin_to_sibling_corner		0
	}

	ControllerCallout_BumperGlow_Right
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				64
		tall				32
		image 				"../vgui/HUD/RB_pressed_callout" [$DURANGO]
		image 				"../vgui/HUD/x360_RB_pressed_callout" [!$DURANGO]
		visible				0
		scaleImage			1
		drawColor			"255 234 0 255"

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerCallout_Bumper_Right
		pin_corner_to_sibling		0
		pin_to_sibling_corner		0
	}

	ControllerCallout_DPad
	{
		ControlName			ImagePanel
		xpos				-24
		ypos				22
		wide				32
		tall				32
		image 				"../vgui/HUD/dpad_pressed_down"
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	ControllerCallout_DPadGlow_Left
	{
		ControlName			ImagePanel
		xpos				1
		ypos				6
		wide				62
		tall				62
		image 				"../vgui/HUD/dpad_pressed_left_callout"
		visible				0
		scaleImage			1
		drawColor			"255 234 0 255"

		zpos				1003

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerCallout_DPad
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	ControllerCallout_DPadGlow_Down
	{
		ControlName			ImagePanel
		xpos				1
		ypos				6
		wide				62
		tall				62
		image 				"../vgui/HUD/dpad_pressed_down_callout"
		visible				0
		scaleImage			1
		drawColor			"255 234 0 255"

		zpos				1003

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerCallout_DPad
		pin_corner_to_sibling		8
		pin_to_sibling_corner		8
	}

	ControllerCallout_DPad_Arrow_Left
	{
		ControlName			ImagePanel
		xpos				-5
		ypos				1
		wide				10
		tall				10
		image 				"../vgui/HUD/dpad_arrow_left"
		visible				0
		scaleImage			1

		zpos				1004

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerCallout_DPad
		pin_corner_to_sibling		8
		pin_to_sibling_corner		7
	}

	ControllerCallout_DPad_Arrow_Down
	{
		ControlName			ImagePanel
		xpos				1
		ypos				-5
		wide				10
		tall				10
		image 				"../vgui/HUD/dpad_arrow_down"
		visible				0
		scaleImage			1

		zpos				1004

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerCallout_DPad
		pin_corner_to_sibling		8
		pin_to_sibling_corner		6
	}


	Controller_StickClick_Left
	{
		ControlName			ImagePanel
		xpos				-71
		ypos				-30
		wide				28
		tall				28
		image 				"../ui/menu/controls_menu/stickClick_up"
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		8
		pin_to_sibling_corner		0
	}

	Controller_StickClick_Right
	{
		ControlName			ImagePanel
		xpos				-95
		ypos				-114
		wide				28
		tall				28
		image 				"../ui/menu/controls_menu/stickClick_up"
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		8 //6
		pin_to_sibling_corner		3 //4
	}

	ControllerCallout_LeftStick
	{
		ControlName			ImagePanel
		xpos				-71
		ypos				-11
		wide				36
		tall				36
		image 				"../ui/menu/controls_menu/arrow_down"
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		6
		pin_to_sibling_corner		7
	}

	ControllerCallout_RightStick
	{
		ControlName			ImagePanel
		xpos				25
		ypos				15
		wide				36
		tall				36
		image 				"../ui/menu/controls_menu/arrow_down"
		visible				0
		scaleImage			1

		zpos				1002

		activeInputExclusivePaint "gamepad"

		pin_to_sibling				ControllerImage
		pin_corner_to_sibling		6
		pin_to_sibling_corner		8
	}

	IngameTextChat [$WINDOWS]
	{
		ControlName				CBaseHudChat
		pin_to_sibling			Screen
		pin_corner_to_sibling	0
		pin_to_sibling_corner	0
		xpos					-20
		ypos					-274
		wide					280
		tall					60
		visible 				0
		bgcolor_override 		"0 0 0 180"

		chatBorderThickness		3
		chatHistoryBgColor		"24 27 30 200"
		chatEntryBgColor		"24 27 30 200"
		chatEntryBgColorFocused	"24 27 30 200"
	}

	HudCheaterMessage
	{
		ControlName			Label
		font				HudFontLarge
		labelText			"#FAIRFIGHT_CHEATER"
		visible				0
		enabled				1
		fgcolor_override 	"255 255 255 205"
		zpos				10
		wide				200
		tall				26
		textAlignment		center

		pin_to_sibling				SafeArea
		pin_corner_to_sibling		4
		pin_to_sibling_corner		4
	}

	FriendlyFlagArrow
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		visible				0
		enable				1
		image				offscreen_arrow
		scaleImage			1
		drawColor			"255 255 255 255"

		zpos				1
	}

	FlagArrow
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		visible				0
		enable				1
		image				offscreen_arrow
		scaleImage			1
		drawColor			"255 255 255 255"

		zpos				1
	}

	FlagIcon
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		visible				0
		enable				1
		image				HUD/ctf_flag_friendly_notext
		drawColor			"255 255 255 255"
		scaleImage			1

		zpos				1
	}

	FlagLabel
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				256
		tall				32
		visible				0
		font				HudFontSmall
		labelText			"STATUS"
		allcaps				1
		textAlignment		center
		fgcolor_override 	"255 255 255 255"

		zpos				1
	}

	HomeIcon
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		visible				0
		enable				1
		image				HUD/ctf_flag_friendly_missing
		drawColor			"255 255 255 255"
		scaleImage			1

		zpos				1
	}

	HomeLabel
	{
		ControlName			Label
		xpos				0
		ypos				0
		wide				256
		tall				12
		visible				0
		font				HudFontSmall
		labelText			"STATUS"
		allcaps				0
		textAlignment		center
		fgcolor_override 	"192 192 192 255"
		zpos				1
	}

	HomeArrow
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		visible				0
		enable				1
		image				offscreen_arrow
		scaleImage			1
		drawColor			"255 255 255 255"

		zpos				1
	}


	CoopHeroCharIcon_0
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_brp_m"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1007
	}
	CoopHeroCharFrame_0
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_frame_p1"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1006
	}

	CoopHeroCharIcon_1
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_brp_m"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1005
	}
	CoopHeroCharFrame_1
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_frame_p2"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1004
	}

	CoopHeroCharIcon_2
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_brp_m"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1003
	}
	CoopHeroCharFrame_2
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_frame_p3"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1002
	}

	CoopHeroCharIcon_3
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_brp_m"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1001
	}
	CoopHeroCharFrame_3
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"hud\coop\coop_char_frame_p4"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1000
	}



	LoadoutCrateIcon_0
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"HUD\coop\coop_ammo_locker_icon"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1
	}
	LoadoutCrateIcon_1
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"HUD\coop\coop_ammo_locker_icon"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1
	}
	LoadoutCrateIcon_2
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				32
		tall				32
		image				"HUD\coop\coop_ammo_locker_icon"
		drawColor			"255 255 255 255"
		visible				0
		scaleImage			1
		zpos 				-1
	}

	TowerDefenseTitan0
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan1
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan2
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan3
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan4
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan5
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan6
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan7
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan8
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	TowerDefenseTitan9
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				28
		tall				28
		visible				0
		image				HUD/titan_stance_icon_follow_burn
		scaleImage			1
		drawColor			"255 255 255 255"
	}

	CoopPlayerTurret0
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret1
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret2
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret3
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret4
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret5
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret6
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret7
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret8
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret9
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret10
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	CoopPlayerTurret11
	{
		ControlName					CNestedPanel
		wide						300
		tall						32
		visible						0
		controlSettingsFile			"scripts/screens/coop_turret_world_icon.res"
	}

	TurretPlacementHint_Keyboard
	{
		ControlName				Label
		xpos						0
		ypos						15
		wide						400
		tall						30
		visible						0
		font						HudFontMedSmall
		labelText					"#SENTRY_TURRET_PLACEMENT_SPLASH_HINT_KB"

		textAlignment				center
		auto_wide_tocontents		1
		fgcolor_override 			"255 255 255 255"
		allCaps						1
		activeInputExclusivePaint	"keyboard"

		pin_to_sibling				Announcement
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6

	}

	TurretPlacementHint_Gamepad
	{
		ControlName					Label
		xpos						0
		ypos						15
		wide						400
		tall						30
		visible						0
		font						HudFontMedSmall
		labelText					"#SENTRY_TURRET_PLACEMENT_SPLASH_HINT_GP"

		textAlignment				center
		auto_wide_tocontents		1
		fgcolor_override 			"255 255 255 255"
		allCaps						1
		activeInputExclusivePaint	"gamepad"

		pin_to_sibling				Announcement
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	TurretPlacementHint_Invalid
	{
		ControlName			ImagePanel
		xpos				0
		ypos				15
		wide				48
		tall				48
		visible				0
		image				HUD/coop/coop_turret_invalid
		scaleImage			1
		drawColor			"255 255 255 255"

		pin_to_sibling				Announcement
		pin_corner_to_sibling		4
		pin_to_sibling_corner		6
	}

	TD_GeneratorIcon
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		zpos				0
		wide				40
		tall				40
		visible				0
		image				HUD/coop/coop_harvester
		scaleImage			1
		drawColor			"255 255 255 255"
	}
	TD_GeneratorLabel
	{
		ControlName					Label
		xpos						0
		ypos						0
		wide						100
		tall						16
		visible						0
		font						HudFontSmallOutlineShadowGlow
		labelText					"#HARVESTER"
		textAlignment				center
		fgcolor_override 			"255 255 255 255"
		//allCaps						1

	//	pin_to_sibling				TD_GeneratorIcon
	//	pin_corner_to_sibling		6
	//	pin_to_sibling_corner		4
	}
	TD_GeneratorIconArrow
	{
		ControlName			ImagePanel
		xpos				0
		ypos				0
		wide				50
		tall				50
		visible				0
		enable				1
		image				offscreen_arrow
		scaleImage			1
		drawColor			"255 255 255 255"
	}
}


