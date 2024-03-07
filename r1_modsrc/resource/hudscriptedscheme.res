///////////////////////////////////////////////////////////
// Tracker scheme resource file
//
// sections:
//		Colors			- all the colors used by the scheme
//		BaseSettings	- contains settings for app to use to draw controls
//		Fonts			- list of all the fonts used by app
//		Borders			- description of all the borders
//
///////////////////////////////////////////////////////////
Scheme
{
	//////////////////////// COLORS ///////////////////////////
	// color details
	// this is a list of all the colors used by the scheme
	Colors
	{
		HudOrange					"229 86 23 255"
		HudBlue						"49 86 23 255"

		HudOrangeTrans				"229 86 23 128"
		HudBlueTrans				"49 86 23 128"

		HudBase255					"180 210 255 255"
		HudBase220					"180 210 255 220"
		HudBase200					"180 210 255 200"
		HudBase180					"180 210 255 180"
		HudBase160					"220 220 220 160"
		HudBase140					"180 210 255 140"
		HudBase128					"180 210 255 128"

		// base colors
		Orange						"178 82 22 255"
		OrangeDim					"178 82 22 120"
		LightOrange					"188 112 0 128"
		GoalOrange					"255 133 0"

		White						"235 235 235 255"
		Red							"192 28 0 140"
		RedSolid					"192 28 0 255"
		Blue						"0 28 162 140"
		Yellow						"251 235 202 255"
		TransparentYellow			"251 235 202 140"
		//Black						"0 0 0 255"
		Black						"46 43 42 255" // Changed black to a NTSC safe color
		TransparentBlack			"0 0 0 196"
		TransparentLightBlack		"0 0 0 90"
		FooterBGBlack				"52 48 55 255"

		HUDBlueTeam					"104 124 155 127"
		HUDRedTeam					"180 92 77 127"
		HUDSpectator				"124 124 124 127"
		HUDBlueTeamSolid			"104 124 155 255"
		HUDRedTeamSolid				"180 92 77 255"
		HUDDeathWarning				"255 0 0 255"
		HudWhite					"255 255 255 255"
		HudOffWhite					"200 187 161 255"

		Gray						"178 178 178 255"

		Blank						"0 0 0 0"
		ForTesting					"255 0 0 32"
		ForTesting_Magenta			"255 0 255 255"
		ForTesting_MagentaDim		"255 0 255 120"

		HudPanelForeground			"123 110 59 184"
		HudPanelBackground			"123 110 59 184"
		HudPanelBorder				"255 255 255 102"

		HudProgressBarActive		"240 207 78 255"
		HudProgressBarInActive		"140 120 73 255"
		HudProgressBarActiveLow		"240 30 30 255"
		HudProgressBarInActiveLow	"240 30 30 99"

		HudTimerProgressActive		"251 235 202 255"
		HudTimerProgressInActive	"52 48 45 255"
		HudTimerProgressWarning		"240 30 30 255"

		TanDark						"117 107 94 255"
		TanLight					"235 226 202 255"
		TanDarker					"46 43 42 255"

		// Building HUD Specific
		LowHealthRed				"255 0 0 255"
		ProgressOffWhite			"251 235 202 255"
		ProgressBackground			"250 234 201 51"
		HealthBgGrey				"72 71 69 255"

		ProgressOffWhiteTransparent	"251 235 202 128"

		LabelDark					"48 43 42 255"
		LabelTransparent			"109 96 80 180"

		BuildMenuActive				"248 231 198 255"

		DisguiseMenuIconRed			"192 56 63 255"
		DisguiseMenuIconBlue		"92 128 166 255"

 		MatchmakingDialogTitleColor			"200 184 151 255"
 		MatchmakingMenuItemBackground		"46 43 42 255"
 		MatchmakingMenuItemBackgroundActive	"150 71 0 255"
		MatchmakingMenuItemTitleColor		"200 184 151 255"
		MatchmakingMenuItemDescriptionColor	"200 184 151 255"

		HTMLBackground				"95 92 101 255"

		QualityColorNormal			"178 178 178 255"
		QualityColorrarity1			"77 116 85 255"
		QualityColorrarity2			"141 131 75 255"
		QualityColorrarity3			"207 106 50 255"
		QualityColorrarity4			"134 80 172 255"
		QualityColorVintage			"71 98 145 255"
		QualityColorUnique			"255 215 0 255"
		QualityColorCommunity		"112 176 74 255"
		QualityColorDeveloper		"165 15 121 255"
		QualityColorSelfMade		"112 176 74 255"
		QualityColorCustomized		"71 98 145 255"
		QualityColorStrange			"205 155 29 255"
	}

	///////////////////// BASE SETTINGS ////////////////////////
	// default settings for all panels
	// controls use these to determine their settings
	BaseSettings
	{
		Label.TextDullColor				HudBase160
		Label.TextColor					HudBase160
		Label.TextBrightColor			HudBase160
		Label.SelectedTextColor			HudBase160
		Label.BgColor					Blank
		Label.FgColor					HudBase160
		Label.DisabledFgColor1			HudBase160
		Label.DisabledFgColor2			HudBase160

		Rosette.DefaultFgColor			White
		Rosette.DefaultBgColor			Blank
		Rosette.ArmedBgColor			Blank
		Rosette.DisabledBgColor			Blank
		Rosette.DisabledBorderColor		Blank
		Rosette.LineColor				"192 192 192 128"
		Rosette.DrawBorder				1
		Rosette.DefaultFont				DefaultSmall
		Rosette.ArmedFont				Default

		Frame.TopBorderImage			"vgui/menu_backgroud_top"
		Frame.BottomBorderImage			"vgui/menu_backgroud_bottom"
		Frame.SmearColor				"0 0 0 225"		[$X360]
		Frame.SmearColor				"0 0 0 180"		[$WIN32]

		FooColor						"255 0 255 255"

		FgColor							"248 255 248 200"
		BgColor							"39 63 82 0"

		Panel.FgColor					"248 255 248 200"
		Panel.BgColor					"39 63 82 0"

		BrightFg						"255 255 255 128"

		DamagedBg						"180 0 0 200"
		DamagedFg						"180 0 0 230"
		BrightDamagedFg					"255 0 0 255"

		YellowBg						"180 113 0 200"
		YellowFg						"180 113 0 230"
		BrightYellowFg					"255 160 0 255"

		// checkboxes and radio buttons
		BaseText						OffWhite
		BrightControlText				White
		CheckBgColor					TransparentBlack
		CheckButtonBorder1 				Border.Dark 		// the left checkbutton border
		CheckButtonBorder2  			Border.Bright		// the right checkbutton border
		CheckButtonCheck				White				// color of the check itself

		// weapon selection colors
		SelectionNumberFg				"255 255 225 255"
		SelectionTextFg					"255 255 225 255"
		SelectionEmptyBoxBg 			"0 0 0 80"
		SelectionBoxBg 					"0 0 0 80"
		SelectionSelectedBoxBg 			"0 0 0 80"

		// HL1-style QuickHUD colors
		Yellowish						"255 160 0 255"
		Normal							"255 255 225 128"
		Caution							"255 48 0 255"

		// Top-left corner of the "Half-Life 2" on the main screen
		Main.Title1.X					32
		Main.Title1.Y					280
		Main.Title1.Y_hidef				130
		Main.Title1.Color				"255 255 255 0"

		// Top-left corner of secondary title e.g. "DEMO" on the main screen
		Main.Title2.X					76
		Main.Title2.Y					190
		Main.Title2.Y_hidef				174
		Main.Title2.Color				"255 255 255 0"

		// Top-left corner of the menu on the main screen
		Main.Menu.X						32
		Main.Menu.X_hidef				76
		Main.Menu.Y						340
		Main.Menu.Color					"168 97 64 255"
		Menu.TextColor					"0 0 0 255"
		Menu.BgColor					"125 125 125 255"

		// Blank space to leave beneath the menu on the main screen
		Main.BottomBorder				32

		ScrollBar.Wide					12

		ScrollBarButton.FgColor			Black
		ScrollBarButton.BgColor			Blank
		ScrollBarButton.ArmedFgColor	White
		ScrollBarButton.ArmedBgColor	Blank
		ScrollBarButton.DepressedFgColor White
		ScrollBarButton.DepressedBgColor Blank

		ScrollBarSlider.FgColor			"0 0 0 255"		// nob color
		ScrollBarSlider.BgColor			"0 0 0 40"		// slider background color
		ScrollBarSlider.NobFocusColor	White
		ScrollBarSlider.NobDragColor	White
		ScrollBarSlider.Inset			3
	}

	//////////////////////// FONTS /////////////////////////////

	BitmapFontFiles
	{
		ControllerButtons		"materials/vgui/fonts/controller_buttons.vbf"			[$DURANGO]
		ControllerButtons		"materials/vgui/fonts/controller_buttons_xbox360.vbf"	[!$DURANGO]
	}
	Fonts
	{
		// fonts are used in order that they are listed
		// fonts listed later in the order will only be used if they fulfill a range not already filled
		// if a font fails to load then the subsequent fonts will replace

		DebugFixed
		{
			1
			{
				name			"Lucida Console"
				tall			14
				antialias 		1
			}
		}

		DebugFixedSmall
		{
			1
			{
				name			"Lucida Console"
				tall			14
				antialias 		1
			}
		}

		DebugOverlay
		{
			1
			{
				name			"Lucida Console"
				tall			14
				antialias 		1
				outline 		1
			}
		}

		Default [!$GAMECONSOLE]
		{
			1
			{
				name			"Tahoma"
				tall			9
				weight			700
				antialias 		1
			}
		}

		Default [$GAMECONSOLE]
		{
			1
			{
				name			"Tahoma"
				tall			14
				weight			900
				antialias 		1
			}
		}

		DefaultSmall
		{
			1
			{
				name			"Tahoma"
				tall			12
				weight			0
				range			"0x0000 0x017F"
				yres			"480 599"
			}
			2
			{
				name			"Tahoma"
				tall			13
				weight			0
				range			"0x0000 0x017F"
				yres			"600 767"
			}
			3
			{
				name			"Tahoma"
				tall			14
				weight			0
				range			"0x0000 0x017F"
				yres			"768 1023"
				antialias		1
			}
			4
			{
				name			"Tahoma"
				tall			20
				weight			0
				range			"0x0000 0x017F"
				yres			"1024 1199"
				antialias		1
			}
			5
			{
				name			"Tahoma"
				tall			24
				weight			0
				range			"0x0000 0x017F"
				yres			"1200 6000"
				antialias		1
			}
			6
			{
				name			"Tahoma"
				tall			12
				range 			"0x0000 0x00FF"
				weight			0
			}
		}

		DefaultVerySmall
		{
			1
			{
				name			"Tahoma"
				tall			12
				weight			0
				range			"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
				yres			"480 599"
			}
			2
			{
				name			"Tahoma"
				tall			13
				weight			0
				range			"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
				yres			"600 767"
			}
			3
			{
				name			"Tahoma"
				tall			14
				weight			0
				range			"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
				yres			"768 1023"
				antialias		1
			}
			4
			{
				name			"Tahoma"
				tall			20
				weight			0
				range			"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
				yres			"1024 1199"
				antialias		1
			}
			5
			{
				name			"Tahoma"
				tall			24
				weight			0
				range			"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
				yres			"1200 6000"
				antialias		1
			}
			6
			{
				name			"Tahoma"
				tall			12
				range 			"0x0000 0x00FF"
				weight			0
			}
			7
			{
				name			"Tahoma"
				tall			11
				range 			"0x0000 0x00FF"
				weight			0
			}
		}

		HudNumbers
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			64
				weight			400
				antialias 		1
				additive		1
			}
		}

		HudNumbersGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			64
				weight			0
				blur			2
				scanlines		2
				antialias 		1
				additive		1
			}
		}

		HudNumbersMedium
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			48
				weight			1000
				additive		1
				antialias 		1
			}
		}

		HudNumbersSmall
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			32
				weight			1000
				additive		1
				antialias 		1
			}
		}

		HudNumbersTiny
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			16
				weight			1000
				additive		1
				antialias 		1
			}
		}

		HudNumbersTinyGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			16
				weight			1000
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		BurnCardDescriptionMed
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			1000
				dropshadow		1
				additive		0
				antialias 		1
			}
		}

		BurnCardTitleMed
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			14
				weight			200
				dropshadow		1
				additive		0
				antialias 		1
			}
		}

		MenuTitleFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		31
				antialias	1
			}
		}


		BurnCardSlotText
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			40
				weight			1000
				dropshadow		1
				additive		0
				antialias 		1
			}
		}

		EnemyAnnounceCard_ListHeader
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			36
				dropshadow 		1
				additive		0
				antialias 		1
			}
		}

		EnemyAnnounceCard_EnemyName
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			30
				dropshadow 		1
				outline 		1
				additive		0
				antialias 		1
			}
		}

		EnemyAnnounceCard_EnemyDesc
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			24
				dropshadow 		1
				additive		0
				antialias 		1
			}
		}

		EnemyAnnounceCard_Number
		{
			isproportional 	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			40
				dropshadow 		1
				antialias		1
				outline 		1
				additive 		0
			}
		}


		RespawnPreviewTitle
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			26
				weight			1000
				dropshadow		1
				additive		0
				antialias 		1
			}
		}

		RespawnPreviewDescription
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			17
				weight			2000
				dropshadow		0
				additive		0
				antialias 		1
			}
		}

		RespawnPreviewFlavorText
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				weight			500
				dropshadow		0
				additive		0
				antialias 		1
				italic			1
			}
		}

		RespawnSelect
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			1000
				dropshadow 		1
				additive		0
				antialias 		1
			}
		}

		RespawnSelectDescription
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			1000
				dropshadow 		1
				additive		0
				antialias 		1
			}
		}

		RespawnSelectTitleSmall
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			10
				antialias		1
				weight			400
				additive		0
			}
		}

		RespawnSelectTitle
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				antialias	1
				weight			400
				additive		0
			}
		}

		RespawnSlotText
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			17
				antialias	1
				weight			400
				additive		0
			}
		}

		RespawnSelectCountSmall
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			10
				weight			1000
				dropshadow		0
				additive		0
				antialias 		1
			}
		}

		RespawnSelectCount
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			1000
				dropshadow		0
				additive		0
				antialias 		1
			}
		}

		HudTitle
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			24
				weight			1000
				additive		0
				dropshadow 		1
				antialias 		1
			}
		}

		HudSelectionNumbers
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			11
				weight			700
				antialias 		1
				additive		1
			}
		}

		HudHintText
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			14
				weight			1000
				antialias 		1
				additive		1
			}
		}

		HudHintTextLarge
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			14
				weight			1000
				antialias 		1
				additive		1
			}
		}

		HudHintTextSmall
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			11
				weight			0
				antialias 		1
				additive		1
			}
		}

		// this is the symbol font
		Marlett
		{
			1
			{
				name			"Marlett"
				tall			14
				weight			0
				symbol			1
			}
		}

		LargeHUDTitle
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				weight			400
				antialias 		1
			}
		}

		ItemFontNameSmallest
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			10
				weight			500
				additive		0
				antialias 		1
			}
		}

		ItemFontNameSmall
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			11
				weight			500
				additive		0
				antialias 		1
			}
		}

		ItemFontNameLarge
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			400
				antialias		1
				yres			"501 6000" [$OSX]
			}
		}

		ItemFontAttribSmallest
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			7
				weight			500
				additive		0
				antialias 		1
			}
		}

		ItemFontAttribSmall
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			8
				weight			500
				additive		0
				antialias 		1
			}
		}

		ItemFontAttribLarge
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			11
				weight			500
				additive		0
				antialias 		1
			}
		}

		EconButtonText
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			18
				weight			400
				antialias		1
			}
		}

		XpText
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			400
				antialias		1
			}
		}

		LoaderBig
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			400
				antialias		1
			}
		}

		LoaderDescription
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			400
				antialias		1
			}
		}

		MissileLabNameLarge
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			38
				weight			400
				antialias		1
			}
		}

		MissileLabNameMedium
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			31
				weight			400
				antialias		1
			}
		}

		MissileLabNameSmall
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			24
				weight			400
				antialias		1
			}
		}

		MissileLabNameStatKnob
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			18
				weight			400
				antialias		1
			}
		}

		MissileLabNameStatType
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			24
				weight			400
				antialias		1
			}
		}

		MissileLabCost
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			22
				weight			400
				antialias		1
			}
		}

		PlayerNames
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			400
				antialias		1
				//outline 		1
			}
		}

		KillShot
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			25
				weight			400
				antialias		1
			}
		}

		GameUIButtons
		{
			1
			{
				bitmap			1
				name			"ControllerButtons"
				scalex			0.375
				scaley			0.375
			}
		}

		GameUIButtonsTiny
		{
			1
			{
				bitmap		1
				name		ControllerButtons
				scalex		0.25
				scaley		0.25
			}
		}


		KillShotGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			25
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		AiKillShot
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			13
				weight			400
				antialias		1
			}
		}

		BigKillShot
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			25
				weight			400
				antialias		1
				outline 		1
			}
		}

		WinScreenFont
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			64
				antialias		1
			}
		}

		OperatorCooldown
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			25
				weight			400
				antialias		1
			}
		}

		OperatorCooldownGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			25
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		OperatorCost
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			400
				antialias		1
			}
		}

		OperatorCostGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		OperatorSelection
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			400
				antialias		1
			}
		}

		OperatorSelectionGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		ScoreSplash
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			14
				weight			400
				antialias		1
			}
		}

		ScoreSplashGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			14
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		ScoreSplashSmall
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			400
				antialias		1
			}
		}

		ScoreSplashSmallGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		ScoreSplashTotal
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			33
				weight			400
				antialias		1
				 additive		1
			}
		}

		ScoreSplashTotalGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			33
				weight			0
				antialias		1
  				blur			2
	  			additive		1

			}
		}

		MPObituary
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			400
				antialias		1
			}
		}

		MPObituaryGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		CapturePointWorldOverlay
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			100
				weight			400
				antialias		1
				additive		1
			}
		}

		CapturePointWorldOverlayGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			100
				weight			0
				antialias		1
  				blur			2
  				additive		1

			}
		}

		CapturePointDistance
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			400
				antialias		1
			}
		}

		CapturePointDistanceGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		CapturePointStatusHUD
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			400
				antialias		1
			}
		}

		CapturePointStatusHUDGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		CapturePointEnemyCount
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			13
				weight			400
				antialias		1
			}
		}

		CapturePointName
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			400
				antialias		1
			}
		}

		CapturePointNameGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		MPScoreBarLarge
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			14
				weight			400
				antialias		1
			}
		}

		MPScoreBarLargeGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			14
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		MPScoreBarSmall
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			11
				weight			400
				antialias		1
			}
		}

		MPScoreBarSmallGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			11
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		FooterFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
				shadowglow	2
			}
		}

		BurnCardLetterTitle
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				weight			400
				dropshadow		0
				additive		0
				antialias 		1
			}
		}

		BurnCardLetterContents
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				weight			400
				dropshadow		0
				additive		0
				antialias 		1
				italic			1
			}
		}

		TitanHUD
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			400
				antialias		1
			}
		}

		TitanHUDGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		TitanHUDSmall
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			400
				antialias		1
			}
		}

		TitanHUDSmallGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		OperatorAbilityName
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			400
				antialias		1
			}
		}

		OperatorAbilityNameGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		SmartPistolStatus
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			400
				antialias		1
			}
		}

		SmartPistolStatusGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		ObjectiveTitle
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			30
				weight			400
				antialias		1
			}
		}

		ObjectiveTitleGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			30
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		ObjectiveDesc
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			22
				weight			400
				antialias		1
			}
		}

		ObjectiveDescGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			22
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		ObjectiveDistance
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			400
				antialias		1
			}
		}

		ObjectiveDistanceGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		FlyoutTitle
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			19
				weight			400
				antialias		1
			}
		}

		FlyoutTitleGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			19
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		FlyoutDescription
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			400
				antialias		1
			}
		}

		FlyoutDescriptionGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		SuperBarHUDName
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			22
				weight			400
				antialias		1
			}
		}

		SuperBarHUDNameGlow
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			22
				weight			0
				antialias		1
  				blur			2
  				additive		1
				scanlines		2
			}
		}

		CriticalHitFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				antialias		1
			}
		}

		ConduitMedium15
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				antialias		1
			}
		}

		ConduitMedium20
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				antialias		1
			}
		}

		ConduitMedium20-DropShadow
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				antialias		1
				dropshadow 		1
			}
		}

		ConduitBold20
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				antialias		1
			}
		}

		ConduitBold36
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			36
				antialias		1
				outline 		1
			}
		}

		ConduitBold42
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			42
				antialias		1
			}
		}

		DpadTimer
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			70
				weight			400
				antialias		1
				outline 		1
				dropshadow 		1
			}
		}

		// designed to be scaled down on a vgui
		TechScreenSmall
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			40
				antialias		1
				shadowglow		5
			}
		}

		// designed to be scaled down on a vgui
		TechScreenTiny
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			32
				antialias		1
				shadowglow		5
			}
		}

		HudFontExtraLarge
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			32
				antialias		1
				shadowglow		3
			}
		}

		HudFontLarge
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				antialias		1
				shadowglow		3
			}
		}

		HudFontMed
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			18
				weight			100
				antialias		1
				shadowglow		3
			}
		}

		HudFontMedOutlineDropShadow
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			18
				weight			100
				antialias		1
				shadowglow		3
				outline 		1
				dropshadow 		1
			}
		}

		HudFontMedSmall
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				weight			100
				antialias		1
				shadowglow		3
			}
		}

		HudFontMedSmallGlow
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				weight			100
				antialias		1
				blur			2
				additive		1
			}
		}

		HudFontSmall
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				antialias		1
				shadowglow		3
			}
		}

		HudFontBurnCard
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				antialias		0
				shadowglow		3
			}
		}

		HudFontObituary
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				antialias		1
				shadowglow		3
			}
		}

		HudFontTiny
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			10
				antialias		1
				shadowglow		3
			}
		}


		HudFontLargeOutline
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				antialias		1
				outline 		1
			}
		}

		HudFontMedOutline
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			18
				weight			100
				antialias		1
				outline 		1
			}
		}

		HudFontMedSmallOutline
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				weight			100
				antialias		1
				outline 		1
			}
		}

		HudFontMedSmallOutlineShadowGlow
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				weight			100
				antialias		1
				outline 		1
				shadowglow 		3
			}
		}

		HudFontSmallOutline
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				antialias		1
				outline 		1
			}
		}

		HudFontSmallBold
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
				antialias		1
				shadowglow		3
			}
		}

		HudFontMedBold
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			18
				antialias		1
			}
		}

		HudFontLargeBold
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				antialias		1
			}
		}

		HudFontSmallOutlineShadowGlow
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				weight			100
				antialias		1
				outline 		1
				shadowglow 		3
			}
		}

		HudFontTinyOutlineShadowGlow
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			10
				weight			100
				antialias		1
				outline 		1
				shadowglow 		3
			}
		}

		HudFontAmmo
		{
			1
			{
				name			"ConduitITCPro-Bold"
				tall			22
				antialias		1
			}
		}

		HudFontLargePlain
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			20
				antialias		1
			}
		}

		HudFontMedPlain
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			18
				weight			100
				antialias		1
			}
		}

		HudFontMedSmallPlain
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				weight			100
				antialias		1
			}
		}

		HudFontSmallPlain
		{
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				antialias		1
			}
		}

		ScoreboardTitleFont
		{
			isproportional		only
			1
			{
				name			ConduitITCPro-Bold
				tall			25
				antialias		1
			}
		}

		ScoreboardHeaderFont
		{
			isproportional		only
			1
			{
				name			ConduitITCPro-Bold
				tall			25
				antialias		1
			}
		}

		ScoreboardFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				antialias		1
			}
		}

		ScoreboardColumnHeaderFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			10
				antialias		1
			}
		}

		ScoreboardTeamScoreFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			25
				antialias		1
			}
		}

		AnnouncementFont
		{
			isproportional		only
			1
			{
				name			"Titanfall"
				//tall			32
				tall			24
				weight			0
				antialias 		1
				scanlines		2
				additive		1
			}
		}

		AnnouncementScoreFont
		{
			isproportional		only
			1
			{
				name			"Titanfall"
				tall			24
				weight			0
				antialias 		1
				scanlines		2
			}
		}

		AnnouncementBGFont
		{
			isproportional		only
			1
			{
				name			"Titanfall"
				//tall			32
				tall			24
				weight			0
				antialias 		1
				scanlines		2
				shadowglow		3
			}
		}
	}

	InheritableProperties
	{
		ScoreboardTeamScore
		{
			zpos				1012
			wide				101
			tall				36
			visible				0
			font				ScoreboardTeamScoreFont
			textAlignment		center
			textinsety			5
			labelText			""
			fgcolor_override 	"230 230 230 255"
			//bgcolor_override 	"64 64 64 200"
		}

		ScoreboardTeamLogo
		{
			zpos				1012
			wide				72
			tall				72
			visible				0
			scaleImage			1
			//border				ScoreboardTeamLogoBorder
			//drawColor			"255 255 255 255"
		}

		ScoreboardPlayer
		{
			ypos				1
			zpos				1010
			wide				594
			tall				20
			visible				0
			scaleImage			1
			//bgcolor_override 	"64 64 64 200"
		}

		ScoreboardPlayerPartyLeader
		{
			ypos				0
			zpos				1012
			wide				2
			tall				20
			visible				0
			scaleImage			1
			image					"hud/white"
			drawColor				"179 255 204 255"
		}

		ScoreboardPlayerSelection
		{
			ypos				0
			zpos				1014
			wide				594
			tall				20
			visible				0
			scaleImage			1
			image				"../ui/menu/scoreboard/player_selected"
		}

		ScoreboardPlayerMic
		{
			zpos				1012
			wide				21
			tall				20
			visible				0
			scaleImage			1
			drawColor			"230 230 230 255"
		}

		ScoreboardPlayerNumber
		{
			zpos				1012
			wide				20
			tall				20
			visible				0
			scaleImage			1
			fillColor 			"0 0 0 255"
		}

		ScoreboardPlayerStatus
		{
			xpos				1
			zpos				1013
			wide				20
			tall				20
			visible				0
			scaleImage			1
		}

		ScoreboardPlayerArt
		{
			xpos				1
			zpos				1013
			wide				40
			tall				20
			visible				1
			controlSettingsFile		"resource/UI/HudRankIcon.res"
		}

		ScoreboardPlayerLevel
		{
			zpos				1012
			wide				20
			tall				20
			visible				0
			font				ScoreboardFont
			textAlignment		center
			labelText			""
			fgcolor_override 	"230 230 230 255"
			bgcolor_override 	"0 0 0 255"
			paintbackground		1
		}

		ScoreboardPlayerName
		{
			xpos				1
			zpos				1012
			wide				300
			tall				20
			visible				0
			font				ScoreboardFont
			textAlignment		west
			textinsetx			8
			fgcolor_override 	"230 230 230 255"
		}

		ScoreboardColumnHeader
		{
			zpos				1012
			wide 				45
			tall				28
			visible				0
			font				ScoreboardColumnHeaderFont
			centerwrap			1
			textAlignment		"center"
			textinsety			-1
			allcaps				1
			fgcolor_override 	"232 232 232 255"
		}

		ScoreboardColumnLine
		{
			zpos				1013
			wide 				1
			tall				138
			visible				0
			labelText			""
			bgcolor_override 	"25 27 30 255" // Should actually be this "18 22 26 255" but in game looks different
			//bgcolor_override 	"255 0 255 127"
			paintbackground		1
		}

		ScoreboardColumnIconBackground
		{
			zpos				1012
			wide 				36
			tall				36
			visible				0
			labelText			""
			bgcolor_override 	"25 27 30 192" // Should actually be this "18 22 26 255" but in game looks different
			paintbackground		1
		}

		ScoreboardColumnIcon
		{
			zpos				1013
			wide 				36
			tall				36
			visible				0
			scaleImage			1
		}

		ScoreboardColumnData
		{
			zpos				1012
			tall				20
			visible				0
			font				ScoreboardFont
			labelText			""
			textAlignment		center
			fgcolor_override 	"230 230 230 255"
			bgcolor_override 	"0 0 0 0"
			paintbackground		1
		}

		ScoreboardPing
		{
			xpos					7
			zpos					1012
			auto_wide_tocontents 	1
			tall					20
			visible					0
			font					ScoreboardFont
			labelText				""
			fgcolor_override 		"230 230 230 255"
			//bgcolor_override 		"255 0 0 128"
		}

		ScoreboardColumnConnection
		{
			zpos				1012
			wide 				45
			tall				20
			visible				0

			scaleImage			1 					[$GAMECONSOLE]
			textAlignment		center 				[!$GAMECONSOLE]
			font				ScoreboardFont 		[!$GAMECONSOLE]
			fgcolor_override 	"155 178 194 255"	[!$GAMECONSOLE]
		}

		ScoreboardGamepadFooterButton
		{
			classname				ScoreboardGamepadFooterButtonClass
			zpos					3
			auto_wide_tocontents 	1
			tall 					16
			labelText				"DEFAULT"
			font					FooterFont
			allcaps					1
			fgcolor_override 		"255 255 255 255" // HudBase160 is bad, and is defaulting everything to have 160 alpha
			enabled					1
			visible					1
			activeInputExclusivePaint	gamepad
		}

		ScoreboardTD_WaveEnemy
		{
			zpos					1100
			wide					112
			tall					60
			allcaps					1
			controlSettingsFile	"resource/UI/ScoreboardTD_WaveEnemyType.res"
		}
	}

	//////////////////// BORDERS //////////////////////////////
	// describes all the border types
	Borders
	{
		ScoreboardTeamLogoBorder
		{
			bordertype			scalable_image
			backgroundtype		2

			image					"../ui/borders/scoreboard_teamlogo_border"
			src_corner_height		16				// pixels inside the image
			src_corner_width		16
			draw_corner_width		7				// screen size of the corners ( and sides ), proportional
			draw_corner_height 		7
		}

		ScoreboardPlayerBorder
		{
			bordertype				scalable_image
			backgroundtype			2

			image					"../ui/borders/scoreboard_player_border"
			src_corner_height		2				// pixels inside the image
			src_corner_width		2
			draw_corner_width		2				// screen size of the corners ( and sides ), proportional
			draw_corner_height 		2
		}
	}

	//////////////////////// CUSTOM FONT FILES /////////////////////////////
	// specifies all the custom (non-system) font files that need to be loaded to service the above described fonts
	CustomFontFiles // [!$GAMECONSOLE]
	{
		1		"resource/ConduitITCPro-Medium.vfont"
		2		"resource/ConduitITCPro-Bold.vfont"
		3		"resource/Titanfall-Regular.vfont"
		4 		"resource/PFDinTextCondPro-Light.vfont"
		5 		"resource/PFDinTextCondPro-Medium.vfont"
		6 		"resource/arialuni.vfont" [$WINDOWS]
	}

	FontRemap
	{
		"ConduitITCPro-Medium"	"PFDinTextCondPro-Light" [$RUSSIAN]
		"ConduitITCPro-Bold"	"PFDinTextCondPro-Medium" [$RUSSIAN]
		"Titanfall"				"PFDinTextCondPro-Medium" [$RUSSIAN]

		"ConduitITCPro-Medium"	"arial unicode ms" [$JAPANESE || $KOREAN || $TCHINESE]
		"ConduitITCPro-Bold"	"arial unicode ms" [$JAPANESE || $KOREAN || $TCHINESE]
		"Titanfall"				"arial unicode ms" [$JAPANESE || $KOREAN || $TCHINESE]

		// Dev only fonts
		"Tahoma"				"ConduitITCPro-Medium" [$GAMECONSOLE]
		"Lucida Console"		"ConduitITCPro-Medium" [$GAMECONSOLE]
	}
}
