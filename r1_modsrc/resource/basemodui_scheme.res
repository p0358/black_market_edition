///////////////////////////////////////////////////////////
// Object Control Panel scheme resource file
//
// sections:
//		Colors			- all the colors used by the scheme
//		BaseSettings	- contains settings for app to use to draw controls
//		Fonts			- list of all the fonts used by app
//		Borders			- description of all the borders
//
// hit ctrl-alt-shift-R in the app to reload this file
//
///////////////////////////////////////////////////////////
Scheme
{
	//////////////////////// COLORS ///////////////////////////
	// color details
	// this is a list of all the colors used by the scheme
	Colors
	{
		// base colors
		White					"255 255 255 255"
		OffWhite				"221 221 221 255"
		DullWhite				"211 211 211 255"
		Gray					"64 64 64 255"
		MediumGray	   		"145 145 145 255"
		DarkGrey				"128 128 128 255"
		AshGray					"16 16 16 255"
		AshGrayHighAlpha		"16 16 16 192"
		DarkGrayLowAlpha		"32 32 32 64"
		DarkRed					"65 0 0 255"
		DeepRed					"168 26 26 255"
		Orange					"255 155 0 255"
		Red						"255 0 0 255"
		LightBlue				"103 117 127 255"
		GreyBlue				"65 74 96 255"
		DarkBlueTrans			"65 74 96 64"
		TransparentBlack		"0 0 0 128"
		Black					"0 0 0 255"
		Blank					"0 0 0 0"
		Green					"0 128 0 255"
		LightBrown				"120 69 24 255"
		DarkBrown				"57 49 38 255"
		ScrollBarBase			"103 117 127 255"
		ScrollBarHover			"205 236 255 255"
		ScrollBarHold			"205 236 255 255"
		BrightYellow			"242 237 0 255"
		DarkYellow				"136 133 0 255"
		TextYellow				"110 110 84 255"
		AchievementsLightGrey	"79 79 79 255"
		AchievementsDarkGrey	"55 55 55 255"
		Disabled 				"102 102 102 255"
		TextBackground			"24 27 30 255"
	}

	///////////////////// BASE SETTINGS ////////////////////////
	// default settings for all panels
	// controls use these to determine their settings
	BaseSettings
	{
		// vgui_controls color specifications
		Border.Bright						"200 200 200 196"	// the lit side of a control
		Border.Dark							"40 40 40 196"		// the dark/unlit side of a control
		Border.Selection					"0 0 0 196"			// the additional border color for displaying the default/selected button
		Border.DarkRed						DarkRed
		Border.DeepRed						DeepRed
		Border.LightBrown					LightBrown
		Border.DarkBrown					DarkBrown
		Border.White						White

		Button.TextColor					White
		Button.BgColor						Blank
		Button.ArmedTextColor				White
		Button.ArmedBgColor					Blank
		Button.DepressedTextColor			"255 255 0 255"
		Button.DepressedBgColor				Blank
		Button.FocusBorderColor				Black

		CheckButton.TextColor				OffWhite
		CheckButton.SelectedTextColor		White
		CheckButton.BgColor					TransparentBlack
		CheckButton.Border1  				Border.Dark 		// the left checkbutton border
		CheckButton.Border2  				Border.Bright		// the right checkbutton border
		CheckButton.Check					White				// color of the check itself

		ComboBoxButton.ArrowColor			DullWhite
		ComboBoxButton.ArmedArrowColor		White
		ComboBoxButton.BgColor				Blank
		ComboBoxButton.DisabledBgColor		Blank

		Frame.TitleTextInsetX				12
		Frame.ClientInsetX					6
		Frame.ClientInsetY					4
		Frame.BgColor						"80 80 80 255"
		Frame.OutOfFocusBgColor				"80 80 80 255"
		Frame.FocusTransitionEffectTime		0	// time it takes for a window to fade in/out on focus/out of focus
		Frame.TransitionEffectTime			0	// time it takes for a window to fade in/out on open/close
		Frame.AutoSnapRange					0
		FrameGrip.Color1					"200 200 200 196"
		FrameGrip.Color2					"0 0 0 196"
		FrameTitleButton.FgColor			"200 200 200 196"
		FrameTitleButton.BgColor			Blank
		FrameTitleButton.DisabledFgColor	"255 255 255 192"
		FrameTitleButton.DisabledBgColor	Blank
		FrameSystemButton.FgColor			Blank
		FrameSystemButton.BgColor			Blank
		FrameSystemButton.Icon				""
		FrameSystemButton.DisabledIcon		""
		FrameTitleBar.Font					DefaultLarge
		FrameTitleBar.TextColor				White
		FrameTitleBar.BgColor				Blank
		FrameTitleBar.DisabledTextColor		"255 255 255 192"
		FrameTitleBar.DisabledBgColor		Blank

		GraphPanel.FgColor					White
		GraphPanel.BgColor					TransparentBlack

		Label.TextDullColor					Black
		Label.TextColor						OffWhite
		Label.TextBrightColor				LightBlue
		Label.SelectedTextColor				White
		Label.BgColor						Blank
		Label.DisabledFgColor1				"117 117 117 0"
		Label.DisabledFgColor2				Disabled

		ListPanel.TextColor					OffWhite
		ListPanel.BgColor					TransparentBlack
		ListPanel.SelectedTextColor			Black
		ListPanel.SelectedBgColor			LightBlue
		ListPanel.SelectedOutOfFocusBgColor	LightBlue
		ListPanel.EmptyListInfoTextColor	LightBlue

		ImagePanel.fillcolor				Blank

		Menu.TextColor						White
		Menu.BgColor						"160 160 160 64"
		Menu.ArmedTextColor					Black
		Menu.ArmedBgColor					LightBlue
		Menu.TextInset						6

		Panel.FgColor						DullWhite
		Panel.BgColor						Blank

		ProgressBar.FgColor					White
		ProgressBar.BgColor					TransparentBlack

		PropertySheet.TextColor				OffWhite
		PropertySheet.SelectedTextColor		White
		PropertySheet.TransitionEffectTime	0.25	// time to change from one tab to another
		PropertySheet.TabFont				DefaultLarge

		RadioButton.TextColor				DullWhite
		RadioButton.SelectedTextColor		White

		RichText.TextColor					OffWhite
		RichText.BgColor					TextBackground
		RichText.SelectedTextColor			OffWhite
		RichText.SelectedBgColor			LightBlue

		Chat.FriendlyFontColor				"55 233 255 255"
		Chat.EnemyFontColor					"230 83 14 255"
		Chat.NeutralFontColor				OffWhite

		ScrollBar.Wide						11

		ScrollBarButton.FgColor				ScrollBarBase
		ScrollBarButton.BgColor				Black
		ScrollBarButton.ArmedFgColor		ScrollBarHover
		ScrollBarButton.ArmedBgColor		"64 255 64 128"
		ScrollBarButton.DepressedFgColor	ScrollBarHold
		ScrollBarButton.DepressedBgColor	"64 64 255 128"

		ScrollBarSlider.FgColor				ScrollBarBase		// nob color
		ScrollBarSlider.BgColor				"0 0 0 180"			// slider background color
		ScrollBarSlider.NobFocusColor		ScrollBarHover
		ScrollBarSlider.NobDragColor		ScrollBarHold
		ScrollBarSlider.Inset				0

		SectionedListPanel.HeaderTextColor				"205 236 255 255"
		SectionedListPanel.HeaderBgColor				Blank
		SectionedListPanel.DividerColor					"205 236 255 255"
		SectionedListPanel.TextColor					"LightBlue"
		SectionedListPanel.BrightTextColor				OffWhite
		SectionedListPanel.BgColor						TransparentBlack
		SectionedListPanel.SelectedTextColor			"240 240 240 255"
		SectionedListPanel.SelectedBgColor				"205 236 255 20"
		SectionedListPanel.OutOfFocusSelectedTextColor	"240 240 240 255"
		SectionedListPanel.OutOfFocusSelectedBgColor	"205 236 255 20"
		SectionedListPanel.MouseOverBgColor				"205 236 255 5"

		Slider.NobColor						"108 108 108 255"
		Slider.TextColor					"127 140 127 255"
		Slider.TrackColor					"31 31 31 255"
		Slider.DisabledTextColor1			"117 117 117 255"
		Slider.DisabledTextColor2			"30 30 30 255"

		TextEntry.TextColor					OffWhite
		TextEntry.BgColor					TextBackground
		TextEntry.CursorColor				OffWhite
		TextEntry.DisabledTextColor			Disabled
		TextEntry.DisabledBgColor			Blank
		TextEntry.FocusedBgColor			TextBackground
		TextEntry.SelectedTextColor			OffWhite
		TextEntry.SelectedBgColor			LightBlue
		TextEntry.OutOfFocusSelectedBgColor	LightBlue
		TextEntry.FocusEdgeColor			"0 0 0 196"

		ToggleButton.SelectedTextColor		White

		Tooltip.TextColor					"0 0 0 196"
		Tooltip.BgColor						LightBlue

		TreeView.BgColor					TransparentBlack

		WizardSubPanel.BgColor				Blank

		Console.TextColor					OffWhite
		Console.DevTextColor				White

		//
		// portal2
		//
		Logo.X								75	[$GAMECONSOLE && ($GAMECONSOLEWIDE && !$ANAMORPHIC)]
		Logo.X								50	[$GAMECONSOLE && (!$GAMECONSOLEWIDE || $ANAMORPHIC)]
		Logo.X								75	[!$GAMECONSOLE && $WIN32WIDE]
		Logo.X								50	[!$GAMECONSOLE && !$WIN32WIDE]
		Logo.Y								35
		Logo.Width							240
		Logo.Height							60

		SteamCloud.X						350	[$GAMECONSOLE && ($GAMECONSOLEWIDE && !$ANAMORPHIC)]
		SteamCloud.X						325	[$GAMECONSOLE && (!$GAMECONSOLEWIDE || $ANAMORPHIC)]
		SteamCloud.X						350	[!$GAMECONSOLE && $WIN32WIDE]
		SteamCloud.X						325	[!$GAMECONSOLE && !$WIN32WIDE]
		SteamCloud.Y						50
		SteamCloud.Width					40
		SteamCloud.Height					40

		SteamCloudProgress.X				396	[$GAMECONSOLE && ($GAMECONSOLEWIDE && !$ANAMORPHIC)]
		SteamCloudProgress.X				370	[$GAMECONSOLE && (!$GAMECONSOLEWIDE || $ANAMORPHIC)]
		SteamCloudProgress.X				396	[!$GAMECONSOLE && $WIN32WIDE]
		SteamCloudProgress.X				370	[!$GAMECONSOLE && !$WIN32WIDE]
		SteamCloudProgress.Y				73
		SteamCloudProgress.Width			86	[$GAMECONSOLE && ($GAMECONSOLEWIDE && !$ANAMORPHIC)]
		SteamCloudProgress.Width			85	[$GAMECONSOLE && (!$GAMECONSOLEWIDE || $ANAMORPHIC)]
		SteamCloudProgress.Width			86	[!$GAMECONSOLE && $WIN32WIDE]
		SteamCloudProgress.Width			85	[!$GAMECONSOLE && !$WIN32WIDE]
		SteamCloudProgress.Height			5
		SteamCloudProgress.ColorRemaining	"30 67 74 150"
		SteamCloudProgress.ColorDone		"80 179 199 255"
		SteamCloudProgress.ColorDoneFade	"80 179 199 100"

		SteamCloudText.Font					ButtonText
		SteamCloudText.X					350					[$GAMECONSOLE && ($GAMECONSOLEWIDE && !$ANAMORPHIC)]
		SteamCloudText.X					324					[$GAMECONSOLE && (!$GAMECONSOLEWIDE || $ANAMORPHIC)]
		SteamCloudText.X					350					[!$GAMECONSOLE && $WIN32WIDE]
		SteamCloudText.X					324					[!$GAMECONSOLE && !$WIN32WIDE]
		SteamCloudText.Y					49
		SteamCloudText.Color				"140 140 140 255"

		FooterPanel.ButtonFont				GameUIButtonsMini
		FooterPanel.TextFont				DialogMenuItem
		FooterPanel.TextOffsetX				0
		FooterPanel.TextOffsetY				0
		FooterPanel.TextColor				"140 140 140 255"
		FooterPanel.InGameTextColor			"200 200 200 255"
		FooterPanel.ButtonGapX				12					[!$GAMECONSOLE]
		FooterPanel.ButtonGapX				20					[$GAMECONSOLE && ($ENGLISH || $GAMECONSOLEWIDE)]
		FooterPanel.ButtonGapX				16					[$GAMECONSOLE && (!$ENGLISH && !$GAMECONSOLEWIDE)]
		FooterPanel.ButtonGapY				25
		FooterPanel.ButtonPaddingX			20					[!$GAMECONSOLE]
		FooterPanel.OffsetY					8
		FooterPanel.BorderColor				"0 0 0 255"			[!$GAMECONSOLE]
		FooterPanel.BorderArmedColor		"0 0 0 255"			[!$GAMECONSOLE]
		FooterPanel.BorderDepressedColor	"0 0 0 255"			[!$GAMECONSOLE]

		FooterPanel.AvatarSize				32
		FooterPanel.AvatarBorderSize		40
		FooterPanel.AvatarOffsetY			47
		FooterPanel.AvatarNameY				49
		FooterPanel.AvatarFriendsY			66
		FooterPanel.AvatarTextFont			ButtonText

		Dialog.TitleFont					DialogTitle
		Dialog.TitleColor					"0 0 0 255"
		Dialog.MessageBoxTitleColor			"232 232 232 255"
		Dialog.TitleOffsetX					10
		Dialog.TitleOffsetY					9
		Dialog.TileWidth					50
		Dialog.TileHeight					50
		Dialog.PinFromBottom				75
		Dialog.PinFromLeft					100	[$GAMECONSOLE && ($GAMECONSOLEWIDE && !$ANAMORPHIC)]
		Dialog.PinFromLeft					75	[$GAMECONSOLE && (!$GAMECONSOLEWIDE || $ANAMORPHIC)]
		Dialog.PinFromLeft					100	[!$GAMECONSOLE && $WIN32WIDE]
		Dialog.PinFromLeft					75	[!$GAMECONSOLE && !$WIN32WIDE]
		Dialog.ButtonFont					GameUIButtonsMini		[!$PS3]
		Dialog.ButtonFont					GameUIButtonsPs3ctrlr	[$PS3]

		SliderControl.InsetX				-35
		SliderControl.MarkColor				"105 118 132 255"
		SliderControl.MarkFocusColor		"105 118 132 255"
		SliderControl.ForegroundColor		"232 232 232 255"
		SliderControl.BackgroundColor		"255 255 255 10"
		SliderControl.ForegroundFocusColor	"255 255 255 255"
		SliderControl.BackgroundFocusColor	"255 255 255 10"

		LoadingProgress.NumDots				107
		LoadingProgress.DotGap				0
		LoadingProgress.DotWidth			8
		LoadingProgress.DotHeight			3

		ConfirmationDialog.TextFont			ConfirmationText
		ConfirmationDialog.TextOffsetX		5
		ConfirmationDialog.IconOffsetY		0

		NewGameDialog.TextOffsetY			-2	[$GAMECONSOLE]
		SaveLoadGameDialog.TextOffsetY		-2	[$GAMECONSOLE]

		KeyBindings.ActionColumnWidth		260
		KeyBindings.KeyColumnWidth			105
		KeyBindings.HeaderFont				KeyBindingsHeader
		KeyBindings.KeyFont					KeyBindingsKey

		InlineEditPanel.FillColor			"205 236 255 40"
		InlineEditPanel.DashColor			Blank
		InlineEditPanel.LineSize			1
		InlineEditPanel.DashLength			6
		InlineEditPanel.GapLength			3

		//////////////////////// HYBRID BUTTON STYLES /////////////////////////////
		// Custom styles for use with HybridButtons

		// sets the defaults for any hybrid buttons
		// each "styled" hybrid button overrides as necessary
		HybridButton.TextColor						"232 232 232 255"
		HybridButton.FocusColor						"232 232 232 255"
		HybridButton.SelectedColor					"255 255 200 255"
		HybridButton.CursorColor					"50 72 117 0"
		HybridButton.DisabledColor					Disabled
		HybridButton.FocusDisabledColor				Disabled
		HybridButton.Font							DefaultButtonFont //DialogMenuItem
		HybridButton.SymbolFont						MarlettLarge
		HybridButton.TextInsetX						35 //10
		HybridButton.TextInsetY						3
		HybridButton.AllCaps						0
		HybridButton.CursorHeight					20
		HybridButton.MultiLine						25
		HybridButton.ListButtonActiveColor			"255 255 200 255"
		HybridButton.ListButtonInactiveColor		"232 232 232 255"
		HybridButton.ListInsetX						0
		// Special case properties for only a few menus
		HybridButton.MouseOverCursorColor			"0 0 0 40"
		HybridButton.LockedColor					Disabled
		HybridButton.BorderColor 					"0 0 0 255"
		HybridButton.BlotchColor 					"0 0 255 128"

		// any primary menu (not the main menu)
		DefaultButton.Style							0
		DefaultButton.AllCaps						0

		CompactButton.Style							0
		CompactButton.AllCaps						0
		CompactButton.CursorHeight					18
		CompactButton.TextInsetY					2

		LargeButton.Style							0
		LargeButton.Font							LargeButtonFont
		LargeButton.TextInsetY						0
		LargeButton.AllCaps							0
		LargeButton.CursorHeight					25

		CenterButton.Style 							0
		CenterButton.TextInsetX 					0

		SubmenuButton.Style 						0
		SubmenuButton.AllCaps 						0

		KeyBindingsButton.Style 					0
		KeyBindingsButton.TextInsetX				0
		KeyBindingsButton.AllCaps 					0

		CampaignCheatButton.TextColor				"128 128 128 255"
		CampaignCheatButton.FocusColor				"255 255 255 255"
		CampaignCheatButton.TextInsetX				0

		EOGPageButton.Style 						0
		EOGPageButton.AllCaps						1
		EOGPageButton.CursorHeight					20
		EOGPageButton.TextColor 					"204 234 255 255"
		EOGPageButton.FocusColor 					"204 234 255 255"
		EOGPageButton.SelectedColor 				"0 0 0 255"
		EOGPageButton.DisabledColor 				"100 100 100 255"
		EOGPageButton.FocusDisabledColor			"204 234 255 255"

		EOGXPBreakdownButton.Style 					0
		EOGXPBreakdownButton.AllCaps				1
		EOGXPBreakdownButton.CursorHeight			18
		EOGXPBreakdownButton.TextColor 				"0 0 0 255"
		EOGXPBreakdownButton.FocusColor 			"0 0 0 255"
		EOGXPBreakdownButton.SelectedColor 			"0 0 0 255"
		EOGXPBreakdownButton.DisabledColor 			"50 50 50 255"
		EOGXPBreakdownButton.FocusDisabledColor		"0 0 0 255"

		EOGScoreboardPlayerButton.Style				0
		EOGScoreboardPlayerButton.Font				LobbyPlayerFont
		EOGScoreboardPlayerButton.AllCaps			0
		EOGScoreboardPlayerButton.TextInsetX		88
		EOGScoreboardPlayerButton.TextInsetY		3
		EOGScoreboardPlayerButton.CursorHeight		16
		EOGScoreboardPlayerButton.SelectedColor		"210 170 0 255"

		EOGCoopPlayerButton.Style					0
		EOGCoopPlayerButton.Font					LobbyPlayerFont
		EOGCoopPlayerButton.AllCaps					0
		EOGCoopPlayerButton.TextInsetX				10
		EOGCoopPlayerButton.TextInsetY				1
		EOGCoopPlayerButton.CursorHeight			16
		EOGCoopPlayerButton.TextColor 				"125 125 125 255"
		EOGCoopPlayerButton.FocusColor 				"255 255 255 255"
		EOGCoopPlayerButton.SelectedColor 			"125 125 125 255"
		EOGCoopPlayerButton.DisabledColor 			"255 0 0 255"
		EOGCoopPlayerButton.FocusDisabledColor		"255 0 0 255"

		StatsWeaponListButton.Style 				0
		StatsWeaponListButton.AllCaps				1
		StatsWeaponListButton.CursorHeight			60
		StatsWeaponListButton.TextColor 			"204 234 255 255"
		StatsWeaponListButton.FocusColor 			"0 0 0 255"
		StatsWeaponListButton.SelectedColor 		"255 255 255 255"
		StatsWeaponListButton.DisabledColor 		"204 234 255 255"
		StatsWeaponListButton.FocusDisabledColor	"204 234 255 255"

		RankedSeasonListButton.Style 				0
		RankedSeasonListButton.AllCaps				1
		RankedSeasonListButton.CursorHeight			69
		RankedSeasonListButton.TextColor 			"204 234 255 255"
		RankedSeasonListButton.FocusColor 			"0 0 0 255"
		RankedSeasonListButton.SelectedColor 		"255 255 255 255"
		RankedSeasonListButton.DisabledColor 		"204 234 255 255"
		RankedSeasonListButton.FocusDisabledColor	"204 234 255 255"

		BurnCardPackButton.Style 					0
		BurnCardPackButton.AllCaps					1
		BurnCardPackButton.CursorHeight				251
		BurnCardPackButton.TextColor 				"204 234 255 255"
		BurnCardPackButton.FocusColor 				"0 0 0 255"
		BurnCardPackButton.SelectedColor 			"255 255 255 255"
		BurnCardPackButton.DisabledColor 			"204 234 255 255"
		BurnCardPackButton.FocusDisabledColor		"204 234 255 255"

		StatsLevelListButton.Style 					0
		StatsLevelListButton.AllCaps				1
		StatsLevelListButton.CursorHeight			60
		StatsLevelListButton.TextColor 				"204 234 255 255"
		StatsLevelListButton.FocusColor 			"0 0 0 255"
		StatsLevelListButton.SelectedColor 			"255 255 255 255"
		StatsLevelListButton.DisabledColor 			"204 234 255 255"
		StatsLevelListButton.FocusDisabledColor		"204 234 255 255"

		ChallengeListButton.Style 					0
		ChallengeListButton.AllCaps					1
		ChallengeListButton.CursorHeight			74
		ChallengeListButton.TextColor 				"204 234 255 255"
		ChallengeListButton.FocusColor 				"0 0 0 255"
		ChallengeListButton.SelectedColor 			"255 255 255 255"
		ChallengeListButton.DisabledColor 			"204 234 255 255"
		ChallengeListButton.FocusDisabledColor		"204 234 255 255"

		TrackedChallengeListButton.Style 					0
		TrackedChallengeListButton.AllCaps					1
		TrackedChallengeListButton.CursorHeight				74
		TrackedChallengeListButton.TextColor 				"204 234 255 255"
		TrackedChallengeListButton.FocusColor 				"0 0 0 255"
		TrackedChallengeListButton.SelectedColor 			"255 255 255 255"
		TrackedChallengeListButton.DisabledColor 			"204 234 255 255"
		TrackedChallengeListButton.FocusDisabledColor		"204 234 255 255"

		DLCStoreButton.Style 						0
		DLCStoreButton.AllCaps						1
		DLCStoreButton.CursorHeight					68
		DLCStoreButton.TextColor 					"204 234 255 255"
		DLCStoreButton.FocusColor 					"0 0 0 255"
		DLCStoreButton.SelectedColor 				"255 255 255 255"
		DLCStoreButton.DisabledColor 				"204 234 255 255"
		DLCStoreButton.FocusDisabledColor			"204 234 255 255"

		EOGChallengeButton.Style 					0
		EOGChallengeButton.AllCaps					1
		EOGChallengeButton.CursorHeight				74
		EOGChallengeButton.TextColor 				"204 234 255 255"
		EOGChallengeButton.FocusColor 				"0 0 0 255"
		EOGChallengeButton.SelectedColor 			"255 255 255 255"
		EOGChallengeButton.DisabledColor 			"204 234 255 255"
		EOGChallengeButton.FocusDisabledColor		"204 234 255 255"

		LobbyPlayerButton.Style						0
		LobbyPlayerButton.Font						LobbyPlayerFont
		LobbyPlayerButton.AllCaps					0
		LobbyPlayerButton.TextInsetX				88
		LobbyPlayerButton.TextInsetY				3
		LobbyPlayerButton.CursorHeight				21
		LobbyPlayerButton.SelectedColor				"210 170 0 255"

		DataCenterButton.Style 						0
		DataCenterButton.TextInsetX					25

		MapButton.Style								0
		MapButton.CursorHeight						89

		PCFooterButton.Style						0
		PCFooterButton.CursorHeight					16
		PCFooterButton.TextInsetX					5
		PCFooterButton.TextInsetY					0

		OldPCFooterButton.Style						0
		OldPCFooterButton.TextInsetX				10

		PCSubmenuCloseButton.CursorHeight			1000

		TitanDecalButton.Style 						0
		TitanDecalButton.AllCaps					0
		TitanDecalButton.CursorHeight				56

		CoopStoreButton.Style 						0
		CoopStoreButton.AllCaps						0
		CoopStoreButton.CursorHeight				56

		// main menu only
		MainMenuButton.Style						1
		MainMenuButton.TextColor					"200 200 200 255"
		MainMenuButton.FocusColor					"255 204 153 255"
		MainMenuButton.CursorColor					"255 255 255 15"
		MainMenuButton.Font							MainMenuItem
		MainMenuButton.TextInsetX					10
		MainMenuButton.TextInsetY					2
		MainMenuButton.AllCaps						0

		// inside a dialog, left aligned, optional RHS component anchored to right edge
		LeftDialogButton.Style						2
		LeftDialogButton.AllCaps					0

		// inside a dialog, left aligned, RHS list anchored to right edge
		DialogListButton.Style						3
		DialogListButton.AllCaps					0

		// inside of a flyout menu only
		FlyoutMenuButton.Style						4

		// inside a dialog, contains a RHS value, usually causes a flyout
		DropDownButton.Style						5

		// specialized button, only appears in game mode carousel
		GameModeButton.Style						6

		VirtualNavigationButton.Style				7

		// menus where mixed case is used for button text (Steam link dialog)
		MixedCaseButton.Style						8
		MixedCaseButton.CursorHeight				50
		MixedCaseButton.AllCaps						0

		MixedCaseDefaultButton.Style				9
		MixedCaseDefaultButton.AllCaps				0

		BitmapButton.Style							10
		BitmapButton.TextColor						"120 120 120 255"
		BitmapButton.FocusColor						"255 255 255 255"
		BitmapButton.CursorColor					"255 255 255 15"
		BitmapButton.Font							NewGameChapter
		BitmapButton.TextInsetX						4
		BitmapButton.TextInsetY						0

		QuickListBGDeselected						AchievementsDarkGrey
	 	QuickListBGSelected		  				AchievementsLightGrey

		// used by BurnCardButton
	 	BurnCardThumbnailButton.Style				0
	 	BurnCardThumbnailButton.CursorHeight		100

	 	BtnBurnCardPickNew.Style					0
	 	BtnBurnCardPickNew.CursorHeight				220

		// used by BurnCardSlotButton
	 	BurnCardSlotButton.Style					0
	 	BurnCardSlotButton.CursorHeight				174

		// used by BurnCardSlotButtonZoomed
	 	BurnCardSlotButtonZoomed.Style				0
	 	BurnCardSlotButtonZoomed.CursorHeight		273

	 	BtnBurnCardPickStored_Center.Style			0
	 	BtnBurnCardPickStored_Center.CursorHeight	338

	 	BtnBurnCardPickStored_CenterMid.Style			0
	 	BtnBurnCardPickStored_CenterMid.CursorHeight	282

	 	BtnBurnCardPickStored_CenterZoomed.Style		0
	 	BtnBurnCardPickStored_CenterZoomed.CursorHeight	212

	 	BtnBurnCardPickStored_CenterMidZoomed.Style		0
	 	BtnBurnCardPickStored_CenterMidZoomed.CursorHeight	165


	 	BtnBurnCardPickStored_SlowScroll.Style			0
	 	BtnBurnCardPickStored_SlowScroll.CursorHeight	213

	 	BtnBurnCardPickStored_FastScroll.Style			0
	 	BtnBurnCardPickStored_FastScroll.CursorHeight	255

	 	ButtonFullScreen.Style							0
	 	ButtonFullScreen.CursorHeight					480

	 	ButtonBurnCardAutoFill.Style					0
	 	ButtonBurnCardAutoFill.CursorHeight				20


		// used by BurnCardPackButton
	 	BurnCardPackButtonStyle.Style				0
	 	BurnCardPackButtonStyle.CursorHeight			60

		// used by MenuArrowButton
	 	MenuArrowButtonStyle.Style					0
	 	MenuArrowButtonStyle.CursorHeight			40

		ChallengeCategoryButton.Style				0
		ChallengeCategoryButton.AllCaps				0
		ChallengeCategoryButton.SelectedColor		"102 194 204 255"
	}

	//////////////////////// CRITICAL FONTS ////////////////////////////////
	// Very specifc console optimization that precaches critical glyphs to prevent hitching.
	// Adding descriptors here causes super costly memory font pages to be instantly built.
	// CAUTION: Each descriptor could be up to N fonts, due to resolution, proportionality state, etc,
	// so the font page explosion could be quite drastic.
	CriticalFonts
	{
		Default
		{
			uppercase		1
			lowercase		1
			punctuation		1
		}

		CoopLevelSelectFont // Used for load error screen
		{
			uppercase		1
			lowercase		1
			punctuation		1
		}

		InstructorTitle
		{
			commonchars		1
		}

		InstructorKeyBindings
		{
			commonchars		1
		}

		InstructorKeyBindingsSmall
		{
			commonchars		1
		}

		CloseCaption_Console
		{
			commonchars		1
			asianchars		1
			skipifasian		0
			russianchars	1
			uppercase		1
			lowercase		1
		}

		ConfirmationText
		{
			commonchars		1
		}

		InGameChapterTitle
		{
			uppercase		1
			numbers			1
			russianchars	1
		}

		InGameChapterSubtitle
		{
			uppercase		1
			russianchars	1
		}

		ButtonText
		{
			commonchars		1
		}

		MainMenuItem
		{
			commonchars		1
		}

		DialogMenuItem
		{
			commonchars		1
		}

		DialogTitle
		{
			commonchars		1
		}

		DialogButton
		{
			commonchars		1
		}

		ControllerLayout
		{
			commonchars		1
		}

		NewGameChapter
		{
			commonchars		1
		}

		NewGameChapterName
		{
			commonchars		1
		}

		FriendsList
		{
			uppercase		1
			lowercase		1
			numbers			1
			explicit		" _-"
		}

		FriendsListSmall
		{
			uppercase		1
			lowercase		1
			explicit		"2() "
		}

		FriendsListStatusLine [!$GAMECONSOLE]
		{
			uppercase		1
			lowercase		1
			explicit		"2() "
		}
	}

	//////////////////////// BITMAP FONT FILES /////////////////////////////
	// Bitmap Fonts are ****VERY*** expensive static memory resources so they are purposely sparse
	BitmapFontFiles
	{
		ControllerButtons		"materials/vgui/fonts/controller_buttons.vbf"			[$DURANGO]
		ControllerButtons		"materials/vgui/fonts/controller_buttons_xbox360.vbf"	[!$DURANGO]
	}

	//////////////////////// FONTS /////////////////////////////
	// describes all the fonts
	// font options: italic, underline, strikeout, antialias, dropshadow, outline, tall, blur, scanlines
	//   ?: custom, bitmap, rotary, additive
	//
	// by default, the game will make a proportional AND a nonproportional version of each
	// font. If you know ahead of time that the font will only ever be used proportionally
	// or nonproportionally, you can conserve resources by telling the engine so with the
	// "isproportional" key. can be one of: "no", "only", or "both".
	// "both" is the default behavior.
	// "only" means ONLY a proportional version will be made.
	// "no" means NO proportional version will be made.
	// this key should come after the named font glyph sets -- eg, it should be inside "Default" and
	// after "1", "2", "3", etc -- *not* inside the "1","2",.. size specs. That is, it should be
	// at the same indent level as "1", not the same indent level as "yres".

	Fonts
	{
		Default
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias 	1
			}
		}

		DefaultBold
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				weight		1000
			}
		}

		DefaultUnderline
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				weight		500
				underline 	1
			}
		}

		DefaultSmall
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				weight		0
			}
		}

		DefaultSmallDropShadow
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		13
				weight		0
				dropshadow 	1
			}
		}

		DefaultVerySmall
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				weight		0
			}
		}

		DefaultLarge
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				weight		0
			}
		}

		MenuLarge
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				weight		600
				antialias 	1
			}
		}

		ConsoleText
		{
			1
			{
				name		"Lucida Console"
				tall		10
				weight		500
			}
		}

		// Used for Debugging UI, overlays, etc - Not intended for customers
		DefaultSystemUI
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		CoopLevelSelectFont // Used for load error screen
		{
			isproportional	no
			1
			{
				name		ConduitITCPro-Bold
				tall		38
				range		"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
				antialias 	1
			}
		}

		ChatFont
		{
			isproportional	no
			1
			{
				name			ConduitITCPro-Medium
				tall			16
				yres			"480 1079"
				antialias		1
				shadowglow		3
			}
			2
			{
				name			ConduitITCPro-Medium
				tall			18
				yres			"1080 1199"
				antialias		1
				shadowglow		3
			}
			3
			{
				name			ConduitITCPro-Medium
				tall			22
				yres			"1200 10000"
				antialias		1
				shadowglow		3
			}
		}

//////////////////////// MENU UI /////////////////////////////

		// this is the symbol font
		MarlettLarge [!$GAMECONSOLE]
		{
			1
			{
				name		Marlett
				tall		16
				weight		0
				symbol		1
				range		"0x0000 0x007F"	//	Basic Latin
				antialias	1
			}
		}

		// this is the symbol font
		Marlett
		{
			1
			{
				name		Marlett
				tall		12
				weight		0
				symbol		1
				range		"0x0000 0x007F"	//	Basic Latin
				antialias	1
			}
		}

		// this is the symbol font
		MarlettSmall
		{
			1
			{
				name		Marlett
				tall		8
				weight		0
				symbol		1
				range		"0x0000 0x007F"	//	Basic Latin
				antialias	1
			}
		}

		MarlettHalf [!$GAMECONSOLE]
		{
			1
			{
				name		Marlett
				tall		9
				weight		0
				symbol		1
				range		"0x0000 0x007F"	//	Basic Latin
				antialias	1
			}
		}

		GameUIButtons
		{
			1
			{
				bitmap		1
				name		ControllerButtons
				scalex		0.4
				scaley		0.4
			}
		}

		GameUIButtonsMini
		{
			1
			{
				bitmap		1
				name		ControllerButtons
				scalex		0.33
				scaley		0.33
			}
		}

		GameUIButtonsPs3ctrlr
		{
			1
			{
				bitmap		1
				name		ControllerButtons
				scalex		0.5
				scaley		0.5
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

		// attract screen
		AttractTitle
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		34
				antialias	1
			}
		}

		// an item appearing on the main menu
		MainMenuItem
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		22
				antialias	1
			}
		}

		// an item appearing on a dialog menu
		DialogMenuItem
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				antialias	1
			}
		}

		// the title heading for a primary menu
		DialogTitle
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		24
				antialias	1
			}
		}

		// an LHS/RHS item appearing on a dialog menu
		DialogButton
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				antialias	1
			}
		}

		// text for the footer buttons (A/B/X/Y)
		ButtonText
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		15
				antialias	1
			}
		}

		MenuFontTiny
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			10
				antialias		1
				shadowglow		3
			}
		}

		MenuFontSmall
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			12
				antialias		1
				shadowglow		3
				dropshadow		1
			}
		}

		KeyBindingsHeader [!$GAMECONSOLE]
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		20
				antialias	1
			}
		}

		KeyBindingsKey [!$GAMECONSOLE]
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		// text for the controller callouts
		ControllerLayout
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		15
				antialias	1
			}
		}

		// text for the confirmation
		ConfirmationText
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		20
				antialias	1
			}
		}

		FriendsList
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		20
				weight		700
				antialias	1
			}
		}

		FriendsListSmall
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		FriendsListStatusLine [!$GAMECONSOLE]
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		NewGameChapter
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				antialias	1
			}
		}

		NewGameChapterName
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		GamerTag
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		GamerTagStatus
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

//////////////////////// CLOSE CAPTION /////////////////////////////

		CloseCaption_Normal
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				weight		500
				antialias	1
			}
		}

		CloseCaption_Italic
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				weight		500
				italic		1
				antialias	1
			}
		}

		CloseCaption_Bold
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				weight		900
				antialias	1
			}
		}

		CloseCaption_BoldItalic
		{
			1
			{
				name		ConduitITCPro-Medium
				tall		18
				weight		900
				italic		1
				antialias	1
			}
		}

		CloseCaption_Console
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				range		"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
				antialias	1
			}
		}

//////////////////////// CHAPTER TITLES /////////////////////////////

		InGameChapterTitle
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		19
				weight		200
				antialias	1
			}
		}

		InGameChapterSubtitle
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		34
				weight		800
				antialias	1
			}
		}

//////////////////////// INSTRUCTOR /////////////////////////////

		InstructorTitle
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		InstructorButtons
		{
			1
			{
				bitmap		1
				name		ControllerButtons
				scalex		0.4
				scaley		0.4
			}
		}

		InstructorKeyBindings
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		12
				antialias 	1
			}
		}

		InstructorKeyBindingsSmall
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		9
				antialias 	1
			}
		}

//////////////////////// CENTER PRINT /////////////////////////////

		CenterPrintText
		{
			// note that this scales with the screen resolution
			1
			{
				name		ConduitITCPro-Medium
				tall		20
				antialias 	1
				additive	1
			}
		}

		AchievementNotification
		{
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias 	1
			}
		}

		LoadScreenMapNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		38
				shadowglow	3
				antialias	1
			}
		}

		LoadScreenGameModeFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		24
				shadowglow	1.5
				antialias	1
			}
		}

		LoadScreenTip
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

		LoadScreenMapDesc
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16 [!$JAPANESE]
				tall		13 [$JAPANESE]
				antialias	1
			}
		}

		EOGSummaryPageTitleFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		24
				antialias	1
			}
		}

		EOGRankedSummaryCompareCategory
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		EOGSummaryPrevNextFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
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

		MenuTitleMedFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		22
				antialias	1
			}
		}

		MenuTitleSmallFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		10 [$RUSSIAN]
				tall		12 [!$RUSSIAN]
				antialias	1
			}
		}

		SubmenuTitleFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		PlaylistNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		36
				antialias	1
			}
		}

		PlaylistDescriptionFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		15
				antialias	1
			}
		}

		NextGameModeFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias	1
				dropshadow	1
			}
		}

		NextMapFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		25
				antialias	1
				dropshadow	1
			}
		}

		WinStreakHeaderFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias	1
				dropshadow	1
			}
		}

		WinStreakFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
				dropshadow	1
			}
		}

		MapStarsHeaderFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
				dropshadow	1
			}
		}

		MapStarsGamemodesFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		15
				antialias	1
				dropshadow	1
			}
		}

		MapStarsHeaderSmallFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		11
				antialias	1
				dropshadow	1
			}
		}

		MapStarsGamemodesSmallFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
				dropshadow	1
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

		RespawnPreviewTitle_Medium
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			15
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

		RespawnPreviewDescription_Medium
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			12
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


		RespawnPreviewFlavorText_Medium
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			10
				weight			500
				dropshadow		0
				additive		0
				antialias 		1
				italic			1
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
				name			"ConduitITCPro-Medium"
				tall			12
				weight			1000
				dropshadow		0
				additive		0
				antialias 		1
			}
		}

		RespawnSelect
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			16
				weight			1000
				dropshadow		1
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
				antialias	1
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

		DefaultButtonFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

		HashtagFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias	1
			}
		}

		GamepadStickDescFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias	1
				dropshadow	1
				shadowglow	3
			}
		}

		GamepadButtonDescFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias	1
				dropshadow	1
				shadowglow	3
			}
		}

		LargeButtonFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		26
				antialias	1
			}
		}

		LargeMessageButtonFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				antialias		1
				shadowglow		2
			}
		}

		LobbyPlayerFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			15
				antialias		1
			}
		}

		LobbyPlayerArtFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			18
				weight			100
				antialias		1
				shadowglow		3
			}
		}

		DefaultButtonFontMedium
		{
			isproportional	only
			1
			{
				name		"ConduitITCPro-Medium"
				tall		16
				antialias	1
			}
		}

		EditLoadoutInfoItemType
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		12
				antialias	1
			}
		}
		EditLoadoutInfoItemName
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		20
				antialias	1
			}
		}
		EditLoadoutInfoItemDesc
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		LoadoutItemTitleFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		13
				antialias	1
			}
		}

		LoadoutSelectItemTitleFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		LoadoutSelectItemFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		LoadoutSelectItemTitleFontOutlined
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		20
				antialias	1
				dropshadow 	1
			}
		}

		LoadoutSelectItemTitleFontOutlinedSmall
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		15
				antialias	1
				dropshadow 	1
			}
		}

		LoadoutSelectItemTitleFontSmall
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		LoadoutChassisNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		30
				antialias	1
			}
		}

		LoadoutChassisCoreFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

		LoadoutItemLocked
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		15
				antialias	1
				dropshadow 	1
			}
		}

		LoadoutItemLockedChallengeName
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		12
				antialias	1
				dropshadow 	0
			}
		}

		LoadoutItemLockedChallengeDesc
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		10
				antialias	1
				dropshadow 	0
			}
		}

		LoadoutItemNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

		LoadoutAbilityOrPassiveNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		13
				antialias	1
			}
		}

		LoadoutItemDetail
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		10
				antialias	1
			}
		}

		LoadoutItemDescFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		12
				antialias	1
			}
		}

		LoadoutSelectItemDescFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		LoadoutItemStatLabelFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		12
				antialias	1
			}
		}

		LoadoutItemStatFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		24
				antialias	1
			}
		}

		LoadoutItemStatSmallFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
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

		MOTDTitleFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

		MOTDFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		CopyrightFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		9
				antialias	1
			}
		}

		Mod1Font
		{
			isproportional	only
			1
			{
				name		ConduitITCStd-Medium
				tall		21
				//tall		20 // nah, it's not perfectly under "ALL" text, we'd need something like 20.5...
				antialias	1
				shadowglow  2
			}
		}

		DialogMessageFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		24
				antialias	1
			}
		}

		DialogMessageFontMedium
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		DialogDetailsFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias	1
			}
		}

		DialogDetailsSmallFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		PlaylistAnnouncementDialogHeader1Font
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		34
				antialias	1
			}
		}

		PlaylistAnnouncementDialogHeader2Font
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		38
				antialias	1
			}
		}

		CampaignLevelFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		13
				antialias	1
			}
		}

		EOGBarLevelFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		28
				antialias	1
				//outline		1
			}
		}

		EOGBarXPFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Medium
				tall		16
				antialias	1
			}
		}

		EOGLevelUpFont
		{
			isproportional only
			1
			{
				name 		Titanfall
				tall		30
				antialias	1
				//outline		1
			}
		}

		EOGXPEarnedListFont
		{
			isproportional only
			1
			{
				name 		ConduitITCPro-Medium
				tall		14
				antialias	1
				//outline		1
			}
		}

		EOGXPEarnedSubCatListFont
		{
			isproportional only
			1
			{
				name 		ConduitITCPro-Medium
				tall		12
				antialias	1
				//outline		1
			}
		}

		EOGXPEarnedSumFont
		{
			isproportional only
			1
			{
				name 		ConduitITCPro-Bold
				tall		22
				antialias	1
				//outline		1
			}
		}

		EOGChallengeName
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		EOGChallengeDesc
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		EOGChallengeProgress
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		12
				antialias	1
				outline 	1
			}
		}

		ChallengeNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

		ChallengeDescriptionFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		16
				antialias	1
				//dropshadow	1
				outline 	1
			}
		}

		ChallengeRewardDescFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		ChallengeProgressHeaderFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		ChallengeProgressFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		ChallengeTimerFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		15
				antialias	1
				dropshadow	1
			}
		}

		ChallengeRewardFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		26
				antialias	1
				outline 	1
			}
		}

		ChallengeRewardFontSmall
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
				outline 	1
			}
		}

		ChallengeCoinRewardFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		22
				antialias	1
			}
		}

		ChallengeCoinRewardFontSmall
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		ChallengeButtonNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		TrackedChallengeButtonNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		12
				antialias	1
			}
		}

		ChallengeButtonProgressFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		12
				antialias	1
				outline 	1
			}
		}

		EOGUnlockItemNameMediumFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		15
				antialias	1
			}
		}

		EOGUnlockItemNameFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		18
				antialias	1
			}
		}

		EOGUnlockItemHeaderSmallFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Medium
				tall		10
				antialias	1
			}
		}

		EOGUnlockItemHeaderFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		EOGUnlockItemHeaderMediumFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		EOGUnlockItemNameSmallFont
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		12
				antialias	1
			}
		}

		LockedOverlayFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		28
				antialias	1
			}
		}

		LockedRequirementFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		20
				antialias	1
			}
		}

		LockedRequirementDescFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		16
				antialias	1
			}
		}

		StatsSectionHeader
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		18
				antialias	1
				//outline		1
			}
		}

		StatsProgressBarTitle
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		16
				antialias	1
				//outline		1
			}
		}

		StatsProgressBarTitleSmall
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		14
				antialias	1
				//outline		1
			}
		}

		StatsSectionHeaderLarge
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		26
				antialias	1
				//outline		1
			}
		}

		StatsSectionHeaderMedium
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		18
				antialias	1
				//outline		1
			}
		}

		StatsSectionHeaderSmall
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		12
				antialias	1
			}
		}

		StatsOverviewWeaponOverlay
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		12
				antialias	1
				//outline		1
			}
		}

		StatsProgressBarNumbers
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		14
				antialias	1
				//outline		1
			}
		}

		StatsPieChartLabel
		{
			isproportional	only
			1
			{
				name 		ConduitITCPro-Bold
				tall		14
				antialias	1
				//outline		1
			}
		}

		StatsListFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		StatsListFontLarge
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		35
				antialias	1
			}
		}

		StatsWeaponPageSmall
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		11
				antialias	1
			}
		}

		StatsWeaponPageMedium
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		StatsWeaponPageLarge
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		26
				antialias	1
			}
		}

		StatsCampaignLevelHeader
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
				outline 	1
			}
		}

		RankedMenuLarge
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		28
				antialias	1
			}
		}

		RankedTipsFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		11
				antialias	1
			}
		}

		RankedMenu10Thin
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		10
				antialias	1
			}
		}

		RankedMenu12Thin
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		RankedMenu14
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		RankedMenu20
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		20
				antialias	1
			}
		}

		RankedMenu25
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		25
				antialias	1
			}
		}

		RankedMenu55
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		55
				antialias	1
			}
		}

		RankedMenuDivisionsHeader
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		22
				antialias	1
			}
		}

		RankedMenuMedium
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		14
				antialias	1
			}
		}

		RankedMenuMediumThin
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		RankedMenuSmallThin
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		10
				antialias	1
			}
		}

		RankedGemGoalFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		RankedGemScoreFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		DailyChallengeTimerFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
				outline 	1
			}
		}

		BlackmarketPriceMedium
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		BlackmarketPriceLarge
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		26
				antialias	1
			}
		}

		SkipIntroFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		17
				antialias	1
			}
		}

		MapButtonFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}

		RegenAdvocateText
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			16
				weight			400
				dropshadow		0
				additive		0
				antialias 		1
			}
		}

		PlaylistHeaderFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		25 [!$JAPANESE && !$RUSSIAN]
				tall		22 [$RUSSIAN]
				tall		19 [$JAPANESE]
				antialias	1
			}
		}

		TeamNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		25
				antialias	1
			}
		}

		CreditsText
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			16
				antialias 		1
			}
		}

		CreditsTitleText
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Bold"
				tall			20
				antialias 		1
			}
		}

		EndMenuText
		{
			isproportional	only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			22
				antialias 		1
			}
		}

		EOGScoreboardTitleFont
		{
			isproportional		only
			1
			{
				name			ConduitITCPro-Bold
				tall			25
				antialias		1
			}
		}

		EOGScoreboardSmallTitleFont
		{
			isproportional		only
			1
			{
				name			ConduitITCPro-Bold
				tall			19
				antialias		1
			}
		}

		EOGScoreboardFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			13
				antialias		1
			}
		}

		EOGScoreboardColumnHeaderFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			10
				antialias		1
			}
		}

		EOGScoreboardTeamScoreFont
		{
			isproportional		only
			1
			{
				name			"ConduitITCPro-Medium"
				tall			25
				antialias		1
			}
		}

		EOGChallengeFilterDescFont
		{
			isproportional		only
			1
			{
				name			ConduitITCPro-Bold
				tall			22
				antialias		1
			}
		}

		EOGChallengeFilterHintFont
		{
			isproportional		only
			1
			{
				name			ConduitITCPro-Bold
				tall			16
				antialias		1
			}
		}

		DecalNameFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Bold
				tall		20
				antialias	1
			}
		}

		DecalDescFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		14
				antialias	1
			}
		}

		DecalReqFont
		{
			isproportional	only
			1
			{
				name		ConduitITCPro-Medium
				tall		12
				antialias	1
			}
		}
	}

	//////////////////// BORDERS //////////////////////////////
	// describes all the border types
	Borders
	{
		ButtonBorder			RaisedBorder
		PropertySheetBorder		RaisedBorder

		FrameBorder
		{
			backgroundtype		0
		}

		BaseBorder
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	Border.Dark
					offset	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	Border.Bright
					offset	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	Border.Dark
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	Border.Bright
					offset 	"0 0"
				}
			}
		}

		RaisedBorder
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	Border.Bright
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	Border.Dark
					offset 	"0 0"
				}
			}
			Top
			{
				1
				{
					color 	Border.Bright
					offset 	"0 1"
				}
			}
			Bottom
			{
				1
				{
					color 	Border.Dark
					offset 	"0 0"
				}
			}
		}

		TitleButtonBorder
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	BorderBright
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	BorderDark
					offset 	"1 0"
				}
			}
			Top
			{
				4
				{
					color 	BorderBright
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
		}

		TitleButtonDisabledBorder
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	BgColor
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	BgColor
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	BgColor
					offset 	"0 0"
				}
			}

			Bottom
			{
				1
				{
					color 	BgColor
					offset 	"0 0"
				}
			}
		}

		TitleButtonDepressedBorder
		{
			inset 	"1 1 1 1"

			Left
			{
				1
				{
					color 	BorderDark
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	BorderBright
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	BorderBright
					offset 	"0 0"
				}
			}
		}

		ScrollBarButtonBorder
		{
			inset "0 0 0 0"
			Left {}
			Right {}
			Top {}
			Bottom {}
		}
		ScrollBarButtonDepressedBorder ScrollBarButtonBorder

		ScrollBarSliderBorder
		{
			inset "0 0 0 0"
			Left {}
			Right {}
			Top {}
			Bottom {}
		}
		ScrollBarSliderBorderHover ScrollBarSliderBorder
		ScrollBarSliderBorderDragging ScrollBarSliderBorder

		ButtonBorder	[0]
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	BorderBright
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
			Top
			{
				1
				{
					color 	BorderBright
					offset 	"0 1"
				}
			}
			Bottom
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
		}

		TabBorder
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	Border.Bright
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	Border.Dark
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	Border.Bright
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	Border.Bright
					offset 	"0 0"
				}
			}
		}

		TabActiveBorder
		{
			inset 	"0 0 1 0"

			Left
			{
				1
				{
					color 	Border.Bright
					offset 	"0 0"
				}
			}
			Right
			{
				1
				{
					color 	Border.Dark
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	Border.Bright
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	ControlBG
					offset 	"6 2"
				}
			}
		}

		ToolTipBorder
		{
			inset 	"0 0 1 0"

			Left
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
			Right
			{
				1
				{
					color 	BorderDark
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
		}

		// this is the border used for default buttons (the button that gets pressed when you hit enter)
		ButtonKeyFocusBorder
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	Border.Selection
					offset 	"0 0"
				}
				2
				{
					color 	Border.Bright
					offset 	"0 1"
				}
			}
			Top
			{
				1
				{
					color 	Border.Selection
					offset 	"0 0"
				}
				2
				{
					color 	Border.Bright
					offset 	"1 0"
				}
			}
			Right
			{
				1
				{
					color 	Border.Selection
					offset 	"0 0"
				}
				2
				{
					color 	Border.Dark
					offset 	"1 0"
				}
			}
			Bottom
			{
				1
				{
					color 	Border.Selection
					offset 	"0 0"
				}
				2
				{
					color 	Border.Dark
					offset 	"0 0"
				}
			}
		}

		ButtonDepressedBorder
		{
			inset 	"1 1 0 0"

			Left
			{
				1
				{
					color 	"205 236 255 5"
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	"205 236 255 5"
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	"205 236 255 5"
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	"205 236 255 5"
					offset 	"0 0"
				}
			}
		}

		ComboBoxBorder
		{
			inset 	"0 0 1 1"

			Left
			{
				1
				{
					color 	BorderDark
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	BorderBright
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	BorderBright
					offset 	"0 0"
				}
			}
		}

		MenuBorder
		{
			inset 	"1 1 1 1"

			Left
			{
				1
				{
					color 	BorderBright
					offset 	"0 1"
				}
			}
			Right
			{
				1
				{
					color 	BorderDark
					offset 	"1 0"
				}
			}
			Top
			{
				1
				{
					color 	BorderBright
					offset 	"0 0"
				}
			}
			Bottom
			{
				1
				{
					color 	BorderDark
					offset 	"0 0"
				}
			}
		}
	}

	InheritableProperties
	{
		CreditsJobTitle
		{
			ControlName				Label
			xpos					c-305
			ypos					0
			wide					300
			tall					20
			textAlignment			"east"
			//bgcolor_override		"60 60 60 255"
			fgcolor_override		"160 224 250 255"
			font					CreditsText
			visible 				0
			labelText				"Title"
		}

		CreditsName
		{
			ControlName				Label
			xpos					10
			wide					300
			tall					20
			textAlignment			"west"
			//bgcolor_override		"60 60 100 255"
			font					CreditsText
			pin_corner_to_sibling	0
			pin_to_sibling_corner	1
			visible 				0
			labelText				"First Last"
		}

		CreditsCentered
		{
			ControlName				Label
			xpos					c-300
			wide					600
			tall					20
			textAlignment			center
			//bgcolor_override		"60 60 100 255"
			font					CreditsText
			visible 				0
			labelText				"First Last"
		}

		CreditsDepartment
		{
			ControlName				Label
			xpos					c-205
			ypos					0
			zpos					100
			wide					410
			tall					30
			textAlignment			"center"
			//bgcolor_override		"100 60 60 255"
			fgcolor_override		"255 180 75 255"
			font					CreditsTitleText
			visible 				0
			labelText				"Department"
		}

		CreditsDepartmentScan
		{
			ControlName				ImagePanel
			ypos 					12
			zpos					90
			wide					410
			tall					30
			image					HUD/flare_announcement
			visible					0
			scaleImage				1
			pin_corner_to_sibling	8
			pin_to_sibling_corner	8
		}

		EndMenuCongratsLine
		{
			ControlName				Label
			xpos					0
			ypos					0
			wide					600
			tall					30
			textAlignment			"west"
			fgcolor_override		"160 224 250 255"
			//fgcolor_override		"255 180 75 255"
			//bgcolor_override		"100 60 60 100"
			font					EndMenuText
			visible 				0
		}

		EndMenuCongratsLineShadow
		{
			ControlName				Label
			xpos					-2
			ypos					-2
			zpos 					-1
			wide					600
			tall					30
			textAlignment			"west"
			fgcolor_override		"40 40 40 150"
			font					EndMenuText
			visible 				0

			pin_corner_to_sibling	0
			pin_to_sibling_corner	0
		}

		DefaultButton
		{
			wide					300
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					DefaultButton
			allcaps					1
			childGroupNormal		DefaultButtonNormalGroup
			childGroupFocused		DefaultButtonFocusGroup
			childGroupLocked		DefaultButtonLockedGroup
			childGroupNew			DefaultButtonNewGroup
			childGroupSelected		DefaultButtonSelectedGroup
		}

		DefaultMessageButton
		{
			wide					300
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					DefaultButton
			allcaps					1
			childGroupNormal		DefaultButtonNormalGroup
			childGroupFocused		DefaultButtonFocusGroup
			childGroupDisabled		DefaultMessageButtonDisabledGroup
			childGroupNew			DefaultButtonNewGroup
		}

		CompactButton
		{
			wide					300
			tall					18
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					CompactButton
			allcaps					1
			childGroupNormal		CompactButtonNormalGroup
			childGroupFocused		CompactButtonFocusGroup
			childGroupLocked		CompactButtonLockedGroup
			childGroupNew			CompactButtonNewGroup
			childGroupSelected		CompactButtonSelectedGroup
		}

		ChallengeCategoryButton
		{
			wide					300
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					0
			enabled					1
			style					ChallengeCategoryButton
			allcaps					1
			childGroupNormal		DefaultButtonNormalGroup
			childGroupFocused		DefaultButtonFocusGroup
			childGroupLocked		DefaultButtonLockedGroup
			childGroupNew			DefaultButtonNewGroup
			childGroupSelected		ChallengeCategoryButtonSelectedGroup
		}

		LargeButton
		{
			wide					300
			tall					25
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					LargeButton
			allcaps					1
			childGroupNormal		LargeButtonNormalGroup
			childGroupFocused		LargeButtonFocusGroup
			childGroupLocked		LargeButtonLockedGroup
			childGroupNew				LargeButtonNewGroup
		}

		LargeMessageButton
		{
			wide					300
			tall					25
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					LargeButton
			allcaps					1
			childGroupNormal		LargeButtonNormalGroup
			childGroupFocused		LargeButtonFocusGroup
			childGroupDisabled		LargeMessageButtonDisabledGroup
		}

		SubmenuButton
		{
			wide					240
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					SubmenuButton
			allcaps					1
			childGroupNormal		SubmenuButtonNormalGroup
			childGroupFocused		SubmenuButtonFocusGroup
			childGroupLocked		SubmenuButtonLockedGroup
			childGroupNew			SubmenuButtonNewGroup
			childGroupSelected		SubmenuButtonSelectedGroup
		}

		DialogButton
		{
			wide					347
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					DefaultButton
			textAlignment			center
			allcaps					1
			childGroupNormal		DialogButtonNormalGroup
			childGroupFocused		DialogButtonFocusGroup
		}

		CenterButton
		{
			wide					200
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					CenterButton
			textAlignment			center
			allcaps					1
			childGroupNormal		CenterButtonNormalGroup
			childGroupFocused		CenterButtonFocusGroup
		}

		WideButton
		{
			wide					372
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					DefaultButton
			allcaps					1
			childGroupNormal		WideButtonNormalGroup
			childGroupFocused		WideButtonFocusGroup
		}

		SwitchButton
		{
			wide					372
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					DialogListButton
			allcaps					1
			childGroupNormal		WideButtonNormalGroup
			childGroupFocused		WideButtonFocusGroup
		}

		DropDownMenuButton
		{
			wide					300
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					DropDownButton
			allcaps					1
			childGroupNormal		DropDownMenuButtonNormalGroup
			childGroupFocused		DropDownMenuButtonFocusGroup
		}

		FlyoutMenuButton
		{
			wide					300
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					FlyoutMenuButton
			allcaps					1
			childGroupNormal		FlyoutMenuButtonNormalGroup
			childGroupFocused		FlyoutMenuButtonFocusGroup
		}

		AdvocateLine
		{
			classname 				AdvocateLine
			tall					16
			auto_wide_tocontents	1
			visible					1
			font					RegenAdvocateText
			allcaps					1
			textAlignment			west
			fgcolor_override		"204 234 255 255"
			labelText				"--"
		}

		CampaignCheatButton
		{
			style					CampaignCheatButton
			classname				CampaignCheatButton
			pin_to_sibling_corner	2
			pin_corner_to_sibling	2
			wide					100
			tall					200
			xpos					-40
			ypos					0
			zpos 5
			visible					1
			enabled					1
		}

		DataCenterList
		{
			paintborder				0
			NoWrap					0
			panelBorder				0
			//clip 					0
			bgcolor_override		"0 0 0 0"
		}

		DataCenterButton
		{
			wide					283
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					DataCenterButton
			allcaps					1
			childGroupAlways		DataCenterButtonAlwaysGroup
			childGroupFocused		DataCenterButtonFocusGroup
			childGroupSelected		DataCenterButtonSelectedGroup
		}

		RankedPlayDetailsProperties
		{
			classname 				RankedPlayDetails
			wide					386
			zpos					40
			ypos					4

			auto_tall_tocontents 	1
			wrap					1
			visible 				1
			font 					DefaultSmall
			allcaps					0
			fgcolor_override		"163 187 204 255"
			textAlignment			north-west
		}

		LobbyPlayerList
		{
			wide					238
			tall					131
			paintborder				0
			NoWrap					0
			panelBorder				0
			clip 					0
			bgcolor_override		"0 0 0 0"
		}

		LobbyFriendlySlot
		{
			wide					238
			tall					20
			visible					1
			scaleImage				1
			image 					"../ui/menu/lobby/friendly_slot"
		}

		LobbyEnemySlot
		{
			wide					238
			tall					20
			visible					1
			scaleImage				1
			image 					"../ui/menu/lobby/enemy_slot"
		}

		LobbyNeutralSlot
		{
			wide					238
			tall					20
			visible					1
			scaleImage				1
			image 					"../ui/menu/lobby/neutral_slot"
		}

		LobbyFriendlyButton
		{
			wide					238
			tall					20
			visible					1
			enabled					1
			style					LobbyPlayerButton
			scriptid				PlayerListButton
			childGroupAlways		LobbyFriendlyAlwaysGroup
			childGroupNormal		LobbyPlayerNormalGroup
			childGroupFocused		LobbyFriendlyFocusGroup
			clip 					0
		}

		LobbyEnemyButton
		{
			wide					238
			tall					20
			visible					1
			enabled					1
			style					LobbyPlayerButton
			scriptid				PlayerListButton
			childGroupAlways		LobbyEnemyAlwaysGroup
			childGroupNormal		LobbyPlayerNormalGroup
			childGroupFocused		LobbyEnemyFocusGroup
			clip 					0
		}

		EOGScoreboardPlayerButton
		{
			xpos 					0
			ypos					0
			zpos					1020
			wide					553
			tall					16
			visible					1
			enabled					0
			style					EOGScoreboardPlayerButton
			scriptid				EOGScoreboardPlayerButton
			childGroupNormal		EOGScoreboardPlayerEmpty
			childGroupFocused		EOGScoreboardPlayerHover
			clip 					0
		}

		EOGCoopPlayerButton
		{
			xpos 					0
			ypos					0
			zpos					1020
			wide					150
			tall					16
			visible					1
			enabled					1
			textAlignment			west
			style					EOGCoopPlayerButton
			scriptid				EOGCoopPlayerButton
			childGroupNormal		EOGCoopPlayerButtonEmpty
			childGroupFocused		EOGCoopPlayerButtonHover
			clip 					0
		}

		MapButton
		{
			wide					158
			tall					89
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					MapButton
			allcaps					1
			childGroupAlways		MapButtonAlwaysGroup
			childGroupNormal		MapButtonNormalGroup
			childGroupFocused		MapButtonFocusGroup
			childGroupLocked		MapButtonLockedGroup
		}

		EOGPageButton
		{
			xpos 					0
			ypos 					0
			zpos					110 // Needed or clicking on the background can hide this
			wide					20
			tall					20
			visible					1
			enabled					1
			style					EOGPageButton
			labelText				""
			allcaps					1
			textAlignment			center
			childGroupNormal		EOGPageButtonNormalGroup
			childGroupFocused		EOGPageButtonFocusedGroup
			childGroupSelected		EOGPageButtonSelectedGroup
		}

		EOGXPBreakdownButton
		{
			zpos					110 // Needed or clicking on the background can hide this
			wide					405
			tall					18
			visible					1
			enabled					1
			style					EOGXPBreakdownButton
			allcaps					1
			textAlignment			center
			childGroupNormal		EOGXPBreakdownButtonNormalGroup
			childGroupFocused		EOGXPBreakdownButtonFocusedGroup
			childGroupSelected		EOGXPBreakdownButtonSelectedGroup
			childGroupDisabled		EOGXPBreakdownButtonDisabled
		}

		StatsWeaponListButton
		{
			xpos					0
			ypos					0
			zpos					100
			wide					150
			tall					60
			visible					1
			enabled					1
			style					StatsWeaponListButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupNormal		StatsWeaponListButtonNormalGroup
			childGroupFocused		StatsWeaponListButtonFocusedGroup
			childGroupSelected		StatsWeaponListButtonSelectedGroup
			childGroupDisabled		StatsWeaponListButtonNormalGroup
		}

		StatsLevelListButton
		{
			xpos					0
			ypos					0
			zpos					100
			wide					150
			tall					60
			visible					1
			enabled					1
			style					StatsLevelListButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupNormal		StatsLevelListButtonNormalGroup
			childGroupFocused		StatsLevelListButtonFocusedGroup
			childGroupSelected		StatsLevelListButtonSelectedGroup
			childGroupDisabled		StatsLevelListButtonNormalGroup
		}

		RankedSeasonListButton
		{
			xpos					0
			ypos					0
			zpos					100
			wide					249
			tall					69
			visible					1
			enabled					1
			style					RankedSeasonListButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupAlways		RankedSeasonListButtonAlwaysGroup
			childGroupNormal		RankedSeasonListButtonNormalGroup
			childGroupFocused		RankedSeasonListButtonFocusedGroup
			childGroupSelected		RankedSeasonListButtonSelectedGroup
			childGroupDisabled		RankedSeasonListButtonNormalGroup
		}

		BurnCardPackButton
		{
			xpos					0
			ypos					0
			zpos					100
			wide					180
			tall					251
			visible					1
			enabled					1
			style					BurnCardPackButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupAlways		BurnCardPackButtonAlwaysGroup
			childGroupNormal 		BurnCardPackButtonNormalGroup
			childGroupFocused		BurnCardPackButtonFocusedGroup
		}

		TitanDecalButton
		{
			xpos					-4
			ypos					0
			zpos					110
			wide					56
			tall					56
			visible					1
			enabled					1
			style					TitanDecalButton
			allcaps					0
			textAlignment			center
			labelText 				""
			childGroupAlways		TitanDecalButtonAlwaysGroup
			childGroupFocused		TitanDecalButtonFocusedGroup
			childGroupSelected		TitanDecalButtonSelectedGroup
			childGroupLocked		TitanDecalButtonLockedGroup
			childGroupNew			TitanDecalButtonNewGroup
		}

		CoopStoreButton
		{
			xpos					-4
			ypos					0
			zpos					110
			wide					56
			tall					56
			visible					1
			enabled					1
			style					CoopStoreButton
			allcaps					0
			textAlignment			center
			labelText 				""
			childGroupAlways		CoopStoreButtonAlwaysGroup
			childGroupFocused		CoopStoreButtonFocusedGroup
			childGroupSelected		CoopStoreButtonSelectedGroup
			childGroupLocked		CoopStoreButtonLockedGroup
			childGroupNew			CoopStoreButtonNewGroup
		}

		ChallengeListButton
		{
			xpos					0
			ypos					0
			zpos					100
			wide					290
			tall					74
			visible					1
			enabled					1
			style					ChallengeListButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupAlways		ChallengeListButtonAlwaysGroup
			childGroupNormal		ChallengeListButtonNormalGroup
			childGroupFocused		ChallengeListButtonFocusedGroup
			childGroupSelected		ChallengeListButtonSelectedGroup
			//childGroupDisabled		ChallengeListButtonNormalGroup
		}

		TrackedChallengeListButton
		{
			xpos					0
			ypos					0
			zpos					100
			wide					290
			tall					74
			visible					1
			enabled					1
			style					TrackedChallengeListButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupAlways		TrackedChallengeListButtonAlwaysGroup
			childGroupNormal		TrackedChallengeListButtonNormalGroup
			childGroupFocused		TrackedChallengeListButtonFocusedGroup
			childGroupSelected		TrackedChallengeListButtonSelectedGroup
			//childGroupDisabled	TrackedChallengeListButtonNormalGroup
		}

		DLCStoreButton
		{
			xpos					0
			ypos					0
			zpos					30
			wide					258
			tall					68
			visible					1
			enabled					1
			style					DLCStoreButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupAlways		DLCStoreButtonAlwaysGroup
			childGroupFocused		DLCStoreButtonFocusedGroup
		}

		EOGChallengeButton
		{
			xpos					0
			ypos					0
			zpos					200
			wide					320
			tall					74
			visible					1
			enabled					1
			style					EOGChallengeButton
			allcaps					1
			textAlignment			center
			labelText				""
			childGroupNormal		EOGChallengeButtonEmpty
			childGroupFocused		EOGChallengeButtonEmpty
			childGroupSelected		EOGChallengeButtonEmpty
		}

		ChallengeRewardsPanel
		{
			wide					332
			tall					140
			zpos					100
			visible					1
			controlSettingsFile		"resource/UI/menus/challenge_reward.res"
		}

		RankedSeasonHistoryGraphDot
		{
			xpos 					0
			ypos 					0
			zpos					201
			wide					2
			tall					2
			visible					0
			scaleImage				1
			Image 					"../ui/menu/personal_stats/kdratio_graph_dot"
			drawColor				"46 49 51 255"
		}

		RankedSeasonHistoryGraphLine
		{
			xpos					0
			ypos					0
			zpos					200
			wide					10
			tall					2
			visible					0
			scaleImage				1
			Image 					"../ui/menu/personal_stats/kdratio_graph_line"
			drawColor				"46 49 51 255"
		}

		KeyBindingsButton
		{
			wide					132
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					KeyBindingsButton
			textAlignment			center
			allcaps					1
			childGroupNormal		KeyBindingsButtonNormalGroup
			childGroupFocused		KeyBindingsButtonFocusGroup
		}

		KeyBindingsButtonSmall
		{
			wide					80
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					KeyBindingsButton
			textAlignment			center
			allcaps					1
			childGroupNormal		KeyBindingsButtonNormalGroupSmall
			childGroupFocused		KeyBindingsButtonFocusGroupSmall
		}

		SliderControl
		{
			wide					372
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			allcaps					1
		}

		DropDownMenu
		{
			wide					300
			tall					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			allcaps					1
		}

		MenuBackground
		{
			wide					f0
			tall					f0
			image 					"../ui/menu/common/menu_background"
			visible					1
			scaleImage				1
		}

		BackgroundDarken
		{
			wide					f0
			tall					f0
			visible					1
			labelText 				""
			bgcolor_override		"0 0 0 195"
		}

		MenuTopBar
		{
			xpos					54
			ypos					65
			wide					745
			tall					7
			image 					"../ui/menu/common/menu_title_bar"
			visible					1
			scaleImage				1
		}

		MenuBottomBar
		{
			xpos					54
			ypos					445
			wide					745
			tall					7
			image 					"../ui/menu/common/menu_bottom_bar"
			visible					1
			scaleImage				1
		}

		MenuTitle
		{
			xpos					63
			ypos					31
			zpos					3 // Needed or clicking on the background can hide this
			auto_wide_tocontents 	1
			tall					43
			visible					1
			font					MenuTitleFont
			allcaps					1
			fgcolor_override		"204 234 255 255"
		}

		EOGSummaryNextPrevLabel
		{
			xpos					63
			ypos					31
			zpos					3 // Needed or clicking on the background can hide this
			auto_wide_tocontents 	1
			tall					43
			visible					1
			font					MenuTitleFont
			allcaps					1
			fgcolor_override		"204 234 255 128"
		}

		MenuChallengeTrackerBackground
		{
			xpos					455
			ypos					82
			zpos					1
			wide					310
			tall					91
			image 					"../ui/menu/challenges/challengeTrackerIngameBack_1"
			visible					0
			scaleImage				1
		}

		MenuChallengeTrackerText
		{
			xpos					455
			ypos					86
			zpos					3 // Needed or clicking on the background can hide this
			tall					18
			wide					310
			visible					0
			textAlignment			center
			font					PlaylistDescriptionFont
			allcaps					1
			fgcolor_override		"204 234 255 255"
		}

		SubheaderBackground
		{
			wide 					352
			tall					20
			visible					1
			image 					"../ui/menu/common/menu_header_bar"
			visible					1
			scaleImage				1
		}
		SubheaderBackgroundWide
		{
			wide 					704
			tall					20
			visible					1
			image 					"../ui/menu/common/menu_header_bar_wide"
			visible					1
			scaleImage				1
		}
		SubheaderText
		{
			zpos					3 // Needed or clicking on the background can hide this
			auto_wide_tocontents 	1
			tall					20
			visible					1
			font					DefaultButtonFont
			allcaps					1
			fgcolor_override		"204 234 255 255"
		}

		LoadoutsSubheaderBackground
		{
			wide 					264
			tall					20
			visible					1
			image 					"../ui/menu/common/menu_header_bar_short"
			visible					1
			scaleImage				1
		}

		MenuDetail
		{
			xpos					0
			ypos					0
			zpos					3 // Needed or clicking on the background can hide this
			wide					540
			tall					43
			visible					1
			font					DefaultButtonFont
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1

			allcaps					1
			fgcolor_override		"204 234 255 255"
		}

		GamepadFooterButton
		{
			classname				GamepadFooterButtonClass
			zpos					3
			auto_wide_tocontents 	1
			tall 					16
			labelText				"DEFAULT"
			font					FooterFont
			allcaps					1
			enabled					1
			visible					1
			activeInputExclusivePaint	gamepad
		}

		PCFooterButton
		{
			classname				PCFooterButtonClass
			zpos					4
			auto_wide_tocontents 	1
			tall 					16
			labelText				"DEFAULT"
			font					FooterFont
			allcaps					1
			textinsetx				10
			use_proportional_insets	1
			enabled					1
			visible					1
			IgnoreButtonA			1
			style					PCFooterButton
			childGroupFocused		PCFooterButtonFocusGroup
			activeInputExclusivePaint	keyboard
		}

		OldGamepadFooterImage
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			font					GameUIButtonsTiny
			textinsetx				20 // This is so we can just place them all side by side and spacing is built in.
			activeInputExclusivePaint	gamepad
		}
		OldGamepadFooterText
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			font					FooterFont
			textinsetx				6
			allcaps					1
			fgcolor_override		"204 234 255 102"
			activeInputExclusivePaint	gamepad
		}

		OldPCFooterButton
		{
			classname				PCBackButtonClass
			//auto_wide_tocontents 	1
			wide 					60
			tall					20
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					OldPCFooterButton
			font					DialogMenuItem
			allcaps					1
			childGroupFocused		OldPCFooterButtonFocusGroup
			activeInputExclusivePaint	keyboard
		}

		OldPCFooterButtonGeneric
		{
			//auto_wide_tocontents 	1
			wide 					60
			tall					20
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					OldPCFooterButton
			font					DialogMenuItem
			allcaps					1
			childGroupFocused		OldPCFooterButtonFocusGroup
			activeInputExclusivePaint	keyboard
		}

		InvisibleButton
		{
			//zpos					4 // Needed or clicking on the background can hide this
			visible					1
			enabled					1
			style					PCSubmenuCloseButton
			labelText				""
			childGroupFocused		InvisibleButtonFocusGroup
		}

		LoadoutItemTitleBG
		{
			wide					203
			tall					14
			zpos					2 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}
		LoadoutItemTitle
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemTitleFont
			allcaps					1
			fgcolor_override		"208 208 208 255"
		}


		PilotWeaponBG
		{
			wide					203
			tall					116
			zpos					2 // Needed or clicking on the background can hide this
			image 					"../ui/menu/loadouts/loadout_pilot_weapon_background"
			visible					1
			scaleImage				1
		}
		PilotATWeaponBG
		{
			wide					203
			tall					90
			zpos					2 // Needed or clicking on the background can hide this
			image 					"../ui/menu/loadouts/loadout_sidearm_background"
			visible					1
			scaleImage				1
		}
		TitanWeaponBG
		{
			wide					203
			tall					116
			zpos					2 // Needed or clicking on the background can hide this
			image 					"../ui/menu/loadouts/loadout_titan_weapon_background"
			visible					1
			scaleImage				1
		}
		SidearmBG
		{
			wide					203
			tall					90
			zpos					2 // Needed or clicking on the background can hide this
			image 					"../ui/menu/loadouts/loadout_sidearm_background"
			visible					1
			scaleImage				1
		}
		AbilityBG
		{
			wide					203
			tall					44
			zpos					2 // Needed or clicking on the background can hide this
			image 					"../ui/menu/loadouts/loadout_ability_background"
			visible					1
			scaleImage				1
		}
		PassiveBG
		{
			wide					203
			tall					44
			zpos					2 // Needed or clicking on the background can hide this
			image 					"../ui/menu/loadouts/loadout_passive_background"
			visible					1
			scaleImage				1
		}

		SubitemSelectName
		{
			auto_wide_tocontents	1
			auto_tall_tocontents	1
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemTitleFont
			allcaps					1
			fgcolor_override		"64 66 68 255"
		}
		SubitemSelectDesc
		{
			wide 					152
			tall 					10
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemDescFont
			allcaps					1
			fgcolor_override		"64 66 68 255"
		}
		SubitemSelectIcon
		{
			wide 					56
			tall					56
			image 					"../ui/menu/loadouts/loadout_box_small_front"
			visible					1
			scaleImage				1
		}

		SubitemSelectItemTitle
		{
			wide 					310
			tall 					20
			zpos					7
			visible					1
			font					LoadoutSelectItemTitleFont
			allcaps					1
			fgcolor_override		"204 234 255 255"
		}
		SubitemSelectItemName
		{
			wide 					310
			tall 					20
			zpos					7
			visible					1
			font					LoadoutSelectItemFont
			allcaps					1
			fgcolor_override		"204 234 255 255"
		}
		SubitemSelectItemDesc
		{
			wide 					152
			tall 					10
			zpos					7
			visible					1
			font					LoadoutSelectItemDescFont
			allcaps					1
			fgcolor_override		"64 66 68 255"
		}

		AbilitySelectIcon
		{
			wide 					56
			tall					56
			image 					"../ui/menu/loadouts/loadout_box_small_front"
			visible					1
			scaleImage				1
		}

		PassiveSelectIcon
		{
			wide 					56
			tall					56
			image 					"../ui/menu/loadouts/loadout_box_small_front"
			visible					1
			scaleImage				1
		}

		TitanOSSelectIcon
		{
			wide 					56
			tall					56
			image 					"../ui/menu/loadouts/loadout_box_small_front"
			visible					1
			scaleImage				1
		}

		SubmenuTitle
		{
			xpos					64
			ypos					-12
			zpos					3 // Needed or clicking on the background can hide this
			auto_wide_tocontents 	1
			tall					43
			visible					1
			font					SubmenuTitleFont
			allcaps					1
			fgcolor_override		"255 142 56 255"
		}


		Temp
		{
			wide					180
			tall					70
			zpos					3 // Needed or clicking on the background can hide this
			image 					"../ui/menu/loadouts/loadout_box_small_front"
			visible					1
			scaleImage				1
		}
		AbilityFGLockedOverlay
		{
			wide					180
			tall					70
			zpos					4 // Needed or clicking on the background can hide this
			image 					"../ui/menu/items/weapon_locked_overlay"
			visible					0
			scaleImage				1
		}

		ItemPropertyName
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemDetail
			allcaps					1
			fgcolor_override		"0 0 0 255"
		}
		ItemPropertyValue
		{
			wide 					70
			tall					23
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemDescFont
			allcaps					1
			fgcolor_override		"0 0 0 255"
			textAlignment			center
			wrap 					1
		}
		ItemLockedLabelOverlay
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					5 // Needed or clicking on the background can hide this
			visible					0
			font					LockedOverlayFont
			allcaps					1
			fgcolor_override		"255 0 0 255"
			labelText				"#LOADOUT_LOCKED_OVERLAY"
			textAlignment 			"center"
		}
		ItemUnlockRequirementLabel
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					5 // Needed or clicking on the background can hide this
			visible					0
			font					LockedRequirementFont
			allcaps					1
			fgcolor_override		"229 180 80 255"
			labelText				"#LOADOUT_UNLOCK_REQUIREMENTS_HEADER"
			textAlignment 			"west"
		}
		ItemUnlockRequirementDescLabel
		{
			auto_tall_tocontents 	1
			wide 					400
			zpos					5 // Needed or clicking on the background can hide this
			visible					0
			font					LockedRequirementDescFont
			wrap 					1
			allcaps					1
			fgcolor_override		"200 200 200 255"
			labelText				"---"
			textAlignment 			"north-west"
		}
		AbilityIcon
		{
			wide					32
			tall					32
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}

		PilotBodyImage
		{
			wide					184
			tall					432
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}

		WeaponImage
		{
			wide					192
			tall					64
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}
		WeaponName
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemNameFont
			allcaps					1
			fgcolor_override		"0 0 0 255"
		}
		WeaponDesc
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemDescFont
			fgcolor_override		"64 64 64 255"
		}
		WeaponModIcon
		{
			wide					23
			tall					23
			xpos					-4
			ypos					-4
			zpos					5 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}

		SidearmImage
		{
			wide					101
			tall					44
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}

		AbilityImage
		{
			wide					32
			tall					32
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}
		AbilityName
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					5 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemNameFont
			allcaps					1
			fgcolor_override		"0 0 0 255"
		}
		AbilityDesc
		{
			wide 					160
			tall 					26
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			textAlignment			north-west
			font					LoadoutItemDescFont
			wrap 					1
			fgcolor_override		"64 64 64 255"
		}

		PassiveImage
		{
			wide					32
			tall					32
			zpos					5 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}
		PassiveName
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					5 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemNameFont
			allcaps					1
			fgcolor_override		"0 0 0 255"
		}
		PassiveDesc
		{
			wide 					162
			tall 					26
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			textAlignment			north-west
			font					LoadoutItemDescFont
			wrap					1
			fgcolor_override		"64 64 64 255"
		}

		TitanChassisImage
		{
			wide					368
			tall					432
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			scaleImage				1
		}

		TitanWeaponModLabel
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			font					DialogMenuItem
		}

		LoadoutItemStatLabel
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					4 // Needed or clicking on the background can hide this
			visible					1
			font					LoadoutItemStatLabelFont
			allcaps					1
			fgcolor_override		"204 234 255 255"
		}

		ControlsHelpImage
		{
			xpos 					0
			ypos 					130
			zpos					3 // Needed or clicking on the background can hide this
			wide					854
			tall					267
			visible					1
			scaleImage				1
		}

		ButtonTooltip
		{
			classname				ButtonTooltip
			xpos					0
			ypos					0
			zpos					500
			wide					200
			tall					30
			visible					0
			controlSettingsFile		"resource/UI/menus/button_locked_tooltip.res"
		}

		Gamepad
		{
			xpos 					0
			ypos 					30
			zpos					2 // Needed or clicking on the background can hide this
			wide					256
			tall					199
			visible					0
			scaleImage				1
		}

		GamepadLblLeftDiffImg
		{
			pin_corner_to_sibling	1
			pin_to_sibling_corner	0
			tall					8
			wide					8
			xpos					2
			ypos					-6
			visible					0
			scaleImage				1
		}

		GamepadLblRightDiffImg
		{
			pin_corner_to_sibling	1
			pin_to_sibling_corner	1
			tall					8
			wide					8
			xpos					10
			ypos					-6
			visible					0
			scaleImage				1
		}

		GamepadStickHorizontalImage
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					114
			tall					57
			visible					0
			scaleImage				1
		}
		GamepadStickVerticalImage
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					57
			tall					114
			visible					0
			scaleImage				1
		}
		GamepadStickDesc
		{
			auto_wide_tocontents 	1
			auto_tall_tocontents 	1
			zpos					3 // Needed or clicking on the background can hide this
			visible					0
			font					GamepadStickDescFont
		}
		GamepadButtonDesc
		{
			auto_wide_tocontents 	1
			tall 					20
			zpos					3 // Needed or clicking on the background can hide this
			visible					0
			font					GamepadButtonDescFont
			//fgcolor_override		"204 234 255 255"
		}

		TitanfallLogoSmall
		{
			xpos					r208
			ypos					r55
			wide					148
			tall					23
			image 					"../ui/menu/common/menu_titanfall_logo_small"
			visible					1
			scaleImage				1
		}

		LobbyFriendlyBackground
		{
			wide					238
			tall					20
			image 					"../ui/menu/lobby/friendly_player"
			visible					1
			scaleImage				1
		}

		LobbyEnemyBackground
		{
			wide					238
			tall					20
			image 					"../ui/menu/lobby/enemy_player"
			visible					1
			scaleImage				1
		}

		RankedPromoPanelProperties
		{
			wide					400
			tall					300
		}

		PromoBoxProperties
		{
			wide					400
			tall					400
		}

		LobbyNeutralBackground
		{
			wide					238
			tall					20
			image 					"../ui/menu/lobby/neutral_player"
			visible					1
			scaleImage				1
		}

		LobbyColumnLine
		{
			wide 					1
			tall					20
			visible					1
			labelText				""
			bgcolor_override 		"18 22 26 255"
			//bgcolor_override 		"255 0 255 127"
		}

		LobbyPlayerMic
		{
			zpos 					4
			wide					21
			tall					20
			visible					1
			image					"../ui/icon_mic_active"
			scaleImage				1
		}

		LobbyPlayerPartyLeader
		{
			zpos 					4
			wide					2
			tall					20
			visible					0
			image					"hud/white"
			drawColor				"179 255 204 255"
			scaleImage				1
		}

		LobbyPlayerGenImage
		{
			zpos 					3
			wide				 	40
			tall				 	20
			visible					1
			image					"../ui/menu/generation_icons/generation_1"
			scaleImage				1
			fillcolor				"0 0 0 255"
		}

		LobbyPlayerGenOverlayImage
		{
			zpos 					4
			wide				 	40
			tall				 	20
			visible					1
			image					""
			scaleImage				1
		}

		LobbyPlayerGenLabel
		{
			zpos 					5
			wide				 	40
			tall				 	20
			visible					1
			font					LobbyPlayerArtFont
			labelText				""
			textAlignment			"center"
			fgcolor_override 		"230 230 230 255"
		}

		LobbyPlayerLevel
		{
			zpos 					4
			wide				 	20
			tall				 	20
			visible					1
			font					LobbyPlayerFont
			labelText				"99"
			textAlignment			"center"
			bgcolor_override		"0 0 0 255"
		}

		LobbyPlayerFocus
		{
			zpos 					5
			wide					238
			tall					20
			visible					1
			image					"../ui/menu/lobby/player_hover"
			scaleImage				1
		}

		MenuArrowButtonLeft
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					26
			visible					1
			enabled					1
			style					MenuArrowButtonStyle
			labelText				""
			allcaps					1
			childGroupNormal		MenuArrowChildGroupLeftNormal
			childGroupFocused		MenuArrowChildGroupLeftFocused
			childGroupNew			MenuArrowChildGroupLeftNew
		}

		MenuArrowButtonRight
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					26
			visible					1
			enabled					1
			style					MenuArrowButtonStyle
			labelText				""
			allcaps					1
			childGroupNormal		MenuArrowChildGroupRightNormal
			childGroupFocused		MenuArrowChildGroupRightFocused
			childGroupNew			MenuArrowChildGroupRightNew
		}

		MenuArrowButtonUp
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					40
			visible					1
			enabled					1
			style					MenuArrowButtonStyle
			labelText				""
			allcaps					1
			childGroupNormal		MenuArrowChildGroupUpNormal
			childGroupFocused		MenuArrowChildGroupUpFocused
		}

		MenuArrowButtonDown
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					40
			visible					1
			enabled					1
			style					MenuArrowButtonStyle
			labelText				""
			allcaps					1
			childGroupNormal		MenuArrowChildGroupDownNormal
			childGroupFocused		MenuArrowChildGroupDownFocused
		}

		BurnCardButton
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					75
			visible					1
			enabled					1
			//style					DefaultButton
			allcaps					1
			//childGroupFocused		BurnCardFocusGroup
		}

		BurnCardPackButton
		{
			zpos					3 // Needed or clicking on the background can hide this
			wide					100
			visible					1
			enabled					1
			//style					DefaultButton
			allcaps					1
			childGroupNormal		ChildGroupBurnCardPack_Normal
			childGroupFocused		ChildGroupBurnCardPack_Focused
			childGroupNew			ChildGroupBurnCardPack_New
		}

		StatName
		{
			xpos 					0
			ypos 					0
			zpos					200
			tall					14
			wide 					110
			visible					1
			font					StatsListFont
			textAlignment			west
			allcaps					1
			labelText				"[stat name]"
			fgcolor_override		"204 234 255 255"
			//bgcolor_override		"255 0 0 255"
		}

		StatValue
		{
			xpos 					0
			ypos					0
			zpos					200
			wide					70
			tall					14
			visible					1
			font					StatsListFont
			textAlignment			east
			labelText				"[stat value]"
			allcaps					1
			fgcolor_override		"230 161 23 255"
			//bgcolor_override		"0 255 0 255"
		}

		CampaignLevelImage
		{
			zpos					2
			wide					84
			tall					47
			visible					1
			scaleImage				1
		}

		CampaignLevelSelectionHighlight
		{
			zpos					3
			pin_corner_to_sibling	0
			pin_to_sibling_corner	0
			wide					84
			tall					47
			labelText				""
			visible					0
			bgcolor_override		"0 0 0 240"
		}

		CampaignLevelIMCCompletionImage
		{
			pin_corner_to_sibling	3
			pin_to_sibling_corner	3
			zpos					3
			wide					24
			tall					24
			visible					1
			scaleImage				1
			image					"HUD/imc_faction_logo"
		}

		CampaignLevelMilitiaCompletionImage
		{
			pin_corner_to_sibling	1
			pin_to_sibling_corner	1
			zpos					3
			wide					24
			tall					24
			visible					1
			scaleImage				1
			image					"HUD/mcorp_faction_logo"
		}

		EOGXPEarnedLineDesc
		{
			xpos 					5
			ypos 					0
			zpos					102
			wide					390
			tall					20
			visible					1
			font					EOGXPEarnedListFont
			allcaps					1
			textAlignment			west
			fgcolor_override		"0 0 0 255"
		}

		EOGXPEarnedLineValue
		{
			xpos 					5
			ypos 					0
			zpos					102
			wide					390
			tall					20
			visible					1
			font					EOGXPEarnedListFont
			allcaps					0
			textAlignment			east
			fgcolor_override		"0 0 0 255"
		}

		EOGXPEarnedSubCatLineDesc
		{
			zpos					112
			wide					194
			tall					14
			visible					1
			font					EOGXPEarnedSubCatListFont
			allcaps					1
			textAlignment			west
			labelText				"[SUB CAT NAME]"
			fgcolor_override		"0 0 0 255"
			//bgcolor_override		"255 255 0 255"
		}

		EOGXPEarnedSubCatLineValue
		{
			zpos					113
			wide					194
			tall					14
			visible					1
			font					EOGXPEarnedSubCatListFont
			allcaps					1
			textAlignment			east
			labelText				"[1234 XP]"
			fgcolor_override		"0 0 0 255"
			//bgcolor_override		"255 255 0 100"
		}

		SkipIntroInstruction
		{
			wide 				 	300
			tall 				 	100
			xpos					c-150
			ypos					r125
			zpos					3 // Needed or clicking on the background can hide this
			visible					1
			font					SkipIntroFont
			allcaps					1
			textAlignment			center
			labelText				"#HOLD_ABUTTON_TO_SKIP"
		}

		OptionMenuTooltip
		{
			font					MenuFontSmall
			allCaps					0
			tall					250
			wide 					320
			xpos					-380
			ypos					14
			zpos					0
			wrap					1
			TextInsetX				16
			TextInsetY				16
			labelText				""
			textAlignment			"north-west"
			fgcolor_override		"192 192 192 255"
			bgcolor_override		"0 0 0 60"
			visible					1
			enabled					1
		}

		EOGScoreboardColumnHeader
		{
			zpos				1012
			wide 				45
			tall				28
			visible				0
			font				EOGScoreboardColumnHeaderFont
			centerwrap			1
			textAlignment		"center"
			textinsety			-1
			allcaps				1
			fgcolor_override 	"232 232 232 255"
		}

		EOGScoreboardColumnIconBackground
		{
			ypos 				4
			zpos				1012
			wide 				36
			tall				36
			visible				0
			labelText			""
			bgcolor_override 	"25 27 30 192" // Should actually be this "18 22 26 255" but in game looks different
		}

		EOGScoreboardColumnIcon
		{
			ypos 				4
			zpos				1013
			wide 				36
			tall				36
			visible				0
			scaleImage			1
			image 				"../ui/menu/scoreboard/sb_icon_pilot_kills"
		}

		EOGScoreboardColumnData
		{
			xpos				0
			ypos 				0
			zpos				1012
			tall				15
			wide 				45
			visible				0
			font				EOGScoreboardFont
			labelText			"0"
			textAlignment		center
			fgcolor_override 	"230 230 230 255"
			bgcolor_override 	"0 0 0 0"
		}

		ScoreboardTeamLogo
		{
			zpos				1012
			wide				72
			tall				72
			visible				1
			scaleImage			1
			//border				ScoreboardTeamLogoBorder
			//drawColor			"255 255 255 255"
		}

		EOGScoreboardColumnLine
		{
			zpos				1015
			wide 				1
			tall				17
			visible				0
			labelText			""
			bgcolor_override 	"25 27 30 255" // Should actually be this "18 22 26 255" but in game looks different
			//bgcolor_override 	"255 0 255 127"
			paintbackground		1
		}

		EOGContributionPanel
		{
			classname 					ContributionPanel
			zpos						998
			wide						600 //334
			tall						21
			visible						1
			controlSettingsFile			"resource/UI/menus/eog_contribution_bar.res"
		}
	}

	ButtonChildGroups
	{
		InvisibleButtonFocusGroup
		{
			ButtonArea
			{
				ControlName				ImagePanel
				wide 					1000
				tall					1000
				//autoResize				1
				visible					1
				image					"hud/white"
				scaleImage				1
				drawColor				"0 0 255 255"
			}
		}

		MenuArrowChildGroupLeftNormal
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					5
				ypos					18
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_left_off"
				scaleImage				1
			}
		}

		MenuArrowChildGroupLeftFocused
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					5
				ypos					18
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_left_on"
				scaleImage				1
			}
		}

		MenuArrowChildGroupLeftNew
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					5
				ypos					18
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_left_on"
				scaleImage				1
			}

			Arrow
			{
				ControlName				ImagePanel
				wide					27
				tall					27
				xpos					4
				ypos					15
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_left_on"
				scaleImage				1
				drawColor				"100 255 100 255"
			}
		}

		MenuArrowChildGroupRightNormal
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					4
				ypos					18
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_right_off"
				scaleImage				1
			}
		}

		MenuArrowChildGroupRightFocused
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					4
				ypos					18
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_right_on"
				scaleImage				1
			}
		}

		MenuArrowChildGroupUpNormal
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					10
				ypos					18
				zpos					10
				visible					1
				image					"../ui/menu/common/menu_arrow_up_off"
				scaleImage				1
			}
		}

		MenuArrowChildGroupUpFocused
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					10
				ypos					18
				zpos					10
				visible					1
				image					"../ui/menu/common/menu_arrow_up_on"
				scaleImage				1
			}
		}

		MenuArrowChildGroupDownNormal
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					10
				ypos					18
				zpos					10
				visible					1
				image					"../ui/menu/common/menu_arrow_down_off"
				scaleImage				1
			}
		}

		MenuArrowChildGroupDownFocused
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					10
				ypos					18
				zpos					10
				visible					1
				image					"../ui/menu/common/menu_arrow_down_on"
				scaleImage				1
			}
		}

		ChildGroupBurnCardPack_Normal
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					100
				tall					60
				xpos					0
				ypos					0
				zpos					100
				visible					1
				image					"../vgui/burncards/burncard_envelope"
				scaleImage				1
				drawColor				"255 255 255 105"
			}
		}

		ChildGroupBurnCardPack_Focused
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					100
				tall					60
				xpos					0
				ypos					0
				zpos					100
				visible					1
				image					"../vgui/burncards/burncard_envelope"
				scaleImage				1
				drawColor				"255 255 255 255"
			}
		}

		ChildGroupBurnCardPack_New
		{
			Arrow
			{
				ControlName				ImagePanel
				wide					100
				tall					60
				xpos					0
				ypos					0
				zpos					100
				visible					1
				image					"../vgui/burncards/burncard_envelope"
				scaleImage				1
				drawColor				"100 255 100 255"
			}
		}

		MenuArrowChildGroupRightNew
		{
			//New
			//{
			//	ControlName			Label
			//	visible				1
			//	ypos				-4
			//	xpos				-5
			//	wide				50
			//	zpos				5
			//	tall				30
			//	labelText			"(NEW)"
			//	font				DefaultButtonFont
			//	textAlignment		center
			//	fgcolor_override	"100 255 100 255"
			//}

			Arrow
			{
				ControlName				ImagePanel
				wide					21
				tall					21
				xpos					4
				ypos					18
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_right_on"
				scaleImage				1
				drawColor				"255 255 255 255"
			}

			Arrow
			{
				ControlName				ImagePanel
				wide					27
				tall					27
				xpos					3
				ypos					15
				zpos					10
				visible					1
				image					"../vgui/burncards/burncard_menu_arrow_right_on"
				scaleImage				1
				drawColor				"100 255 100 255"
			}
		}

		LoadoutLocked
		{
			LockImage
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/locked_icon"
				scaleImage				1
			}
		}

		BurnCardFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					3
				ypos					-3
				xpos					0
				ypos					0
				zpos					10
				wide					78 // 75
				tall					93 // 89 // 85
				visible					1
				image					"../vgui/burncards/burncard_select_outline"
				scaleImage				1
			}
		}

		FillBigVisible
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					100
				wide					1000
				tall					1000
				visible					1
				image					hud/white
				scaleImage				1
				drawColor				"155 55 255 50"
			}
		}

		DefaultButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					283
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}

		DefaultButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					283
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}
		DefaultButtonLockedGroup
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/locked_icon"
				scaleImage				1
			}
		}
		DefaultButtonNewGroup
		{
			NewIcon
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/newitemicon"
				scaleImage				1
			}
		}
		DefaultButtonSelectedGroup
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					283
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
				drawColor				"255 255 255 40"
			}
		}

		DefaultMessageButtonDisabledGroup
		{
			ButtonMessage
			{
				ControlName				Label
				xpos					55
				ypos					20
				wide					283
				tall					20
				font					LargeMessageButtonFont
				labelText 				""
				fgcolor_override		"214 121 49 255"
				visible					1
			}
		}

		CompactButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					283
				tall					18
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		CompactButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					283
				tall					18
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}
		CompactButtonLockedGroup
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/locked_icon"
				scaleImage				1
			}
		}
		CompactButtonNewGroup
		{
			NewIcon
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/newitemicon"
				scaleImage				1
			}
		}
		CompactButtonSelectedGroup
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					283
				tall					18
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
				drawColor				"255 255 255 40"
			}
		}

		ChallengeCategoryButtonSelectedGroup
		{
			TrackedIcon
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					0
				image					"../ui/menu/challenges/challengeTrackerIcon_big"
				scaleImage				1
			}
		}

		LargeButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					283
				tall					25
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		LargeButtonFocusGroup
		{
			FocusImage
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					283
				tall					25
				visible					1
				image					"../ui/menu/common/menu_hover_left_large"
				scaleImage				1
			}
		}

		LargeButtonLockedGroup
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					12
				ypos					2
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/locked_icon"
				scaleImage				1
			}
		}
		LargeButtonNewGroup
		{
			NewIcon
			{
				ControlName				ImagePanel
				xpos					12
				ypos					2
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/newitemicon"
				scaleImage				1
			}
		}
		LargeMessageButtonDisabledGroup
		{
			ButtonMessage
			{
				ControlName				Label
				xpos					55
				ypos					20
				wide					283
				tall					25
				font					LargeMessageButtonFont
				labelText 				""
				fgcolor_override		"214 121 49 255"
				visible					1
			}
		}

		WideButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					372
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		WideButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					372
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}

		DialogButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					347
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		DialogButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					347
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_center_controls"
				scaleImage				1
			}
		}

		CenterButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					200
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		CenterButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					200
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_center_controls"
				scaleImage				1
			}
		}

		DropDownMenuButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					300
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		DropDownMenuButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					300
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}

		FlyoutMenuButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					300
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		FlyoutMenuButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					300
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}

		PCFooterButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					-20
				ypos					0
				wide					300 //%100
				tall					16 //%100
				visible					1
				image					"../ui/menu/common/menu_hover_center_controls"
				scaleImage				1
			}
		}

		OldPCFooterButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					60 //%100
				tall					20 //%100
				visible					1
				image					"../ui/menu/common/menu_hover_center_controls"
				scaleImage				1
			}
		}

		KeyBindingsButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					140
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		KeyBindingsButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					140
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}

		KeyBindingsButtonNormalGroupSmall
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					80
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		KeyBindingsButtonFocusGroupSmall
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					80
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}

		LobbyPlayerNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					200
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}

		LobbyFriendlyAlwaysGroup
		{
			ImgBackground
			{
				ControlName				ImagePanel
				InheritProperties		LobbyFriendlyBackground
			}
			ImgBackgroundNeutral
			{
				ControlName				ImagePanel
				InheritProperties		LobbyNeutralBackground
			}
			ImgMic
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerMic
				pin_to_sibling			ImgBackground
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
			ColumnLineMic
			{
				ControlName				Label
				InheritProperties		LobbyColumnLine
				pin_to_sibling			ImgMic
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			ImgGen
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerGenImage
				pin_to_sibling			ColumnLineMic
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			ImgGenOverlay
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerGenOverlayImage
				pin_to_sibling			ImgGen
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
			LblGen
			{
				ControlName				Label
				InheritProperties		LobbyPlayerGenLabel
				pin_to_sibling			ImgGen
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
			LblLevel
			{
				ControlName				Label
				InheritProperties		LobbyPlayerLevel
				pin_to_sibling			ImgGen
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			CoopIcon
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerMic
				pin_to_sibling			ImgBackground
				pin_corner_to_sibling	1
				pin_to_sibling_corner	1
				visible					0
				enabled					0
			}
			ColumnLineLevel
			{
				ControlName				Label
				InheritProperties		LobbyColumnLine
				pin_to_sibling			LblLevel
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			ImgPartyLeader
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerPartyLeader
				pin_to_sibling			ColumnLineLevel
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
		}

		LobbyFriendlyFocusGroup
		{
			ImgFocused
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerFocus
			}
		}

		LobbyEnemyAlwaysGroup
		{
			ImgBackground
			{
				ControlName				ImagePanel
				InheritProperties		LobbyEnemyBackground
			}
			ImgBackgroundNeutral
			{
				ControlName				ImagePanel
				InheritProperties		LobbyNeutralBackground
			}
			ImgMic
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerMic
				pin_to_sibling			ImgBackground
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
			ColumnLineMic
			{
				ControlName				Label
				InheritProperties		LobbyColumnLine
				pin_to_sibling			ImgMic
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			ImgGen
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerGenImage
				pin_to_sibling			ColumnLineMic
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			ImgGenOverlay
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerGenOverlayImage
				pin_to_sibling			ImgGen
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
			LblGen
			{
				ControlName				Label
				InheritProperties		LobbyPlayerGenLabel
				pin_to_sibling			ImgGen
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
			LblLevel
			{
				ControlName				Label
				InheritProperties		LobbyPlayerLevel
				pin_to_sibling			ImgGen
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			ColumnLineLevel
			{
				ControlName				Label
				InheritProperties		LobbyColumnLine
				pin_to_sibling			LblLevel
				pin_corner_to_sibling	0
				pin_to_sibling_corner	1
			}
			ImgPartyLeader
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerPartyLeader
				pin_to_sibling			ColumnLineLevel
				pin_corner_to_sibling	0
				pin_to_sibling_corner	0
			}
		}

		LobbyEnemyFocusGroup
		{
			ImgFocused
			{
				ControlName				ImagePanel
				InheritProperties		LobbyPlayerFocus
			}
		}

		EOGScoreboardPlayerEmpty
		{

		}

		EOGScoreboardPlayerHover
		{
			ImgFocused
			{
				ControlName				ImagePanel
				zpos 					5
				wide					553
				tall					16
				visible					1
				image					"../ui/menu/lobby/player_hover"
				scaleImage				1
			}
		}

		EOGCoopPlayerButtonEmpty
		{

		}

		EOGCoopPlayerButtonHover
		{
			ImgFocused
			{
				ControlName				ImagePanel
				zpos 					5
				xpos					-22
				wide					180
				tall					16
				visible					1
				image					"../ui/menu/coop_eog_mission_summary/coop_eog_hover"
				scaleImage				1
			}
		}

		DataCenterButtonAlwaysGroup
		{
			Ping
			{
				ControlName				Label
				xpos 					177
				zpos					1
				wide 					80
				tall 					20
				labelText 				"temp_ping"
				font					DefaultButtonFont
				textAlignment			"east"
			}
		}
		DataCenterButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					283
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}
		DataCenterButtonSelectedGroup
		{
			Selected
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					283
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
				drawColor				"255 255 255 40"
			}
		}

		MapButtonAlwaysGroup
		{
			MapImage
			{
				ControlName				ImagePanel
				classname 				MapImageClass
				wide					158
				tall					89
				visible					1
				scaleImage				1
			}
		}
		MapButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				zpos 					1
				wide					158
				tall					89
				visible					1
				scaleImage				1
				image					"../ui/menu/campaign_menu/map_button_hover"
				drawColor				"255 255 255 0"
			}
		}
		MapButtonFocusGroup
		{
			MapNameBG
			{
				ControlName				ImagePanel
				xpos					1
				ypos					1
				zpos 					2
				wide					156
				tall					32
				visible					0
				scaleImage				1
				image					"../ui/menu/campaign_menu/map_name_background"
			}

			MapName
			{
				ControlName				Label
				ypos 					7
				zpos					3
				wide					158
				tall					89
				visible					0
				labelText				"Name"
				font 					MapButtonFont
				textAlignment			north
				allcaps					1
				fgcolor_override		"204 234 255 255"
			}

			Focus
			{
				ControlName				ImagePanel
				zpos 					1
				wide					158
				tall					89
				visible					1
				scaleImage				1
				image					"../ui/menu/campaign_menu/map_button_hover"
			}
		}
		MapButtonLockedGroup
		{
			DarkenOverlay
			{
				ControlName				ImagePanel
				wide					158
				tall					89
				visible					1
				scaleImage				1
				image					"../ui/menu/campaign_menu/map_button_darken_overlay"
			}
		}

		SubmenuButtonNormalGroup
		{
			FocusFade
			{
				ControlName				ImagePanel
				classname 				FocusFadeClass
				xpos					0
				ypos					0
				wide					240
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default_anim"
				scaleImage				1
				drawColor				"255 255 255 0"
			}
		}
		SubmenuButtonFocusGroup
		{
			Focus
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					240
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
			}
		}
		SubmenuButtonLockedGroup
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/locked_icon"
				scaleImage				1
			}
		}
		SubmenuButtonNewGroup
		{
			NewIcon
			{
				ControlName				ImagePanel
				xpos					12
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/common/newitemicon"
				scaleImage				1
			}
		}
		SubmenuButtonSelectedGroup
		{
			TestImage1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					240
				tall					20
				visible					1
				image					"../ui/menu/common/menu_hover_left_default"
				scaleImage				1
				drawColor				"255 255 255 40"
			}
		}

		BurnCardFocusGroup
		{
			CardPanel
			{
				ControlName				CNestedPanel
				zpos					3 // Needed or clicking on the background can hide this
				wide					180
				tall					180
				visible					1
				controlSettingsFile		"resource/UI/HudBurnCard.res"
			}
		}

		BurnCardDisplay
		{
			burnCard_frame
			{
				ControlName			ImagePanel
				xpos				0
				ypos				0
				zpos				100
				wide				133
				tall				100
				visible				1

				image				burncards/card_mask

				scaleImage			1
		//		drawColor			"0 30 85 255"
				drawColor			"255 255 255 255"

				pin_to_sibling				burnCard_background
				pin_corner_to_sibling		8
				pin_to_sibling_corner		8
			}

			burnCard_image
			{
				ControlName			ImagePanel
				xpos				0
				ypos				0
				zpos				99
				wide				126
				tall				95
				visible				1

				image				burncards/card_grunts

				scaleImage			1
				drawColor		"255 255 255 255"

				pin_to_sibling				burnCard_background
				pin_corner_to_sibling		8
				pin_to_sibling_corner		8
			}

			burnCard_buttonBackground
			{
				ControlName			ImagePanel
				xpos				0
				ypos				5
				visible				1
				zpos				140
				wide				80
				tall				40
				visible				0
				image				hud/white
				scaleImage			1
		//		drawColor			"0 0 0 60"
				drawColor			"0 0 0 200"


				pin_to_sibling				burnCard_image
				pin_corner_to_sibling		4
				pin_to_sibling_corner		6
			}

			burnCard_titleBackground
			{
				ControlName			ImagePanel
				xpos				0
				ypos				-8
				visible				0
				zpos				106
				wide				110
				tall				26
				visible				1
				image				hud/white
				scaleImage			1

				pin_to_sibling				burnCard_image
				pin_corner_to_sibling		8
				pin_to_sibling_corner		4
			}

			burnCard_titleBackgroundShadow
			{
				ControlName			ImagePanel
				xpos				5
				ypos				10
				visible				0
				zpos				105
				wide				110
				tall				30
				visible				1
				image				hud/white
				scaleImage			1
				drawColor			"0 0 0 145"

				pin_to_sibling				burnCard_titleBackground
				pin_corner_to_sibling		8
				pin_to_sibling_corner		8
			}

			burnCard_title
			{
				ControlName			Label
				xpos				0
				ypos				0
				visible				1
				zpos				107
				wide				110
				tall				40
				labelText			"#BURNCARD_1"
				font				HudFontMedBold
				textAlignment		center
				drawColor			"0 0 0 255"

				pin_to_sibling				burnCard_titleBackground
				pin_corner_to_sibling		8
				pin_to_sibling_corner		8
			}
		}

		EOGPageButtonNormalGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/eog/eog_indicator_frame"
				scaleImage				1
			}
		}

		EOGPageButtonFocusedGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/eog/eog_indicator_hover"
				scaleImage				1
			}
		}

		EOGPageButtonSelectedGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					20
				tall					20
				visible					1
				image					"../ui/menu/eog/eog_indicator_fill"
				scaleImage				1
			}
		}

		EOGXPBreakdownButtonNormalGroup
		{
			Line
			{
				ControlName				ImagePanel
				wide					405
				tall					2
				xpos 					0
				ypos					16
				zpos					101
				image					"../ui/menu/eog/xp_score_line"
				visible					1
				scaleImage				1
			}

			DescNormal
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineDesc
				labelText				"[DESCRIPTION]"
			}

			ValueNormal
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineValue
				labelText				"[0000 XP]"
			}
		}

		EOGXPBreakdownButtonFocusedGroup
		{
			Line
			{
				ControlName				ImagePanel
				wide					405
				tall					2
				xpos 					0
				ypos					16
				zpos					101
				image					"../ui/menu/eog/xp_score_line"
				visible					1
				scaleImage				1
			}

			Highlight
			{
				ControlName				ImagePanel
				xpos					-10
				ypos					0
				wide					425
				tall					40
				visible					1
				image					"../ui/menu/eog/xp_breakdown_button_hover"
				scaleImage				1
			}

			Arrow
			{
				ControlName				ImagePanel
				xpos					390
				ypos					2
				wide					15
				tall					15
				visible					1
				image					"../ui/menu/eog/xp_breakdown_arrow"
				scaleImage				1
			}

			DescFocused
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineDesc
				labelText				"[DESCRIPTION]"
			}

			ValueFocused
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineValue
				labelText				"[0000 XP]"
			}
		}

		EOGXPBreakdownButtonSelectedGroup
		{
			Line
			{
				ControlName				ImagePanel
				wide					405
				tall					2
				xpos 					0
				ypos					16
				zpos					101
				image					"../ui/menu/eog/xp_score_line"
				visible					1
				scaleImage				1
			}

			Highlight
			{
				ControlName				ImagePanel
				xpos					-10
				ypos					0
				wide					401
				tall					40
				visible					1
				image					"../ui/menu/eog/xp_breakdown_button_hover"
				scaleImage				1
			}

			Arrow
			{
				ControlName				ImagePanel
				xpos					385
				ypos					2
				wide					15
				tall					15
				visible					1
				image					"../ui/menu/eog/xp_breakdown_arrow"
				scaleImage				1
			}

			DescSelected
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineDesc
				labelText				"[DESCRIPTION]"
			}

			ValueSelected
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineValue
				labelText				"[0000 XP]"
			}
		}

		EOGXPBreakdownButtonDisabled
		{
			Line
			{
				ControlName				ImagePanel
				wide					405
				tall					2
				xpos 					0
				ypos					16
				zpos					101
				image					"../ui/menu/eog/xp_score_line"
				visible					1
				scaleImage				1
			}

			DescDisabled
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineDesc
				labelText				"[DESCRIPTION]"
				fgcolor_override		"100 100 100 255"
			}

			ValueDisabled
			{
				ControlName				Label
				InheritProperties		EOGXPEarnedLineValue
				labelText				"[0000 XP]"
				fgcolor_override		"100 100 100 255"
			}
		}

		TitanDecalButtonAlwaysGroup
		{
			BackgroundNormal
			{
				ControlName				ImagePanel
				wide					56
				tall					56
				xpos 					0
				ypos					0
				zpos					101
				image 					"../ui/menu/titanDecal_menu/decalSlot_default"
				visible					1
				scaleImage				1
			}

			DecalNormal
			{
				ControlName				ImagePanel
				wide					40
				tall					40
				xpos 					8
				ypos					8
				zpos					110
				image 					"../models/titans/custom_decals/decal_pack_01/wings_custom_decal_menu"
				visible					1
				scaleImage				1
			}
		}

		TitanDecalButtonFocusedGroup
		{
			BackgroundFocused
			{
				ControlName				ImagePanel
				wide					56
				tall					56
				xpos 					0
				ypos					0
				zpos					102
				image 					"../ui/menu/titanDecal_menu/decalSlot_hover"
				visible					1
				scaleImage				1
			}
		}

		TitanDecalButtonSelectedGroup
		{
			BackgroundSelected
			{
				ControlName				ImagePanel
				wide					56
				tall					56
				xpos 					0
				ypos					0
				zpos					103
				image 					"../ui/menu/titanDecal_menu/decalSlot_selected"
				visible					1
				scaleImage				1
			}
		}

		TitanDecalButtonLockedGroup
		{
			LockIcon
			{
				ControlName				ImagePanel
				wide					30
				tall					30
				xpos					0
				ypos					26
				zpos 					120
				image					"../ui/menu/common/locked_icon"
				visible					1
				scaleImage				1
			}
		}

		TitanDecalButtonNewGroup
		{
			NewIcon
			{
				ControlName				ImagePanel
				wide					26
				tall					26
				xpos					2
				ypos					28
				zpos 					119
				image					"../ui/menu/common/newitemicon"
				visible					1
				scaleImage				1
			}
		}

		CoopStoreButtonAlwaysGroup
		{
			BackgroundNormal
			{
				ControlName				ImagePanel
				wide					56
				tall					56
				xpos 					0
				ypos					0
				zpos					101
				image 					"../ui/menu/titanDecal_menu/decalSlot_default"
				visible					1
				scaleImage				1
			}

			UnlockNormal
			{
				ControlName				ImagePanel
				wide					40
				tall					40
				xpos 					8
				ypos					8
				zpos					110
				image 					"../models/titans/custom_decals/decal_pack_01/wings_custom_decal_menu"
				visible					1
				scaleImage				1
			}
		}

		CoopStoreButtonFocusedGroup
		{
			BackgroundFocused
			{
				ControlName				ImagePanel
				wide					56
				tall					56
				xpos 					0
				ypos					0
				zpos					102
				image 					"../ui/menu/titanDecal_menu/decalSlot_hover"
				visible					1
				scaleImage				1
			}
		}

		CoopStoreButtonSelectedGroup
		{
			BackgroundSelected
			{
				ControlName				ImagePanel
				wide					56
				tall					56
				xpos 					0
				ypos					0
				zpos					103
				image 					"../ui/menu/titanDecal_menu/decalSlot_selected"
				visible					1
				scaleImage				1
			}
		}

		CoopStoreButtonLockedGroup
		{
			LockIcon
			{
				ControlName				ImagePanel
				wide					30
				tall					30
				xpos					0
				ypos					26
				zpos 					120
				image					"../ui/menu/common/locked_icon"
				visible					1
				scaleImage				1
			}
		}

		CoopStoreButtonNewGroup
		{
			NewIcon
			{
				ControlName				ImagePanel
				wide					26
				tall					26
				xpos					2
				ypos					28
				zpos 					119
				image					"../ui/menu/coop_store/maxedItemIcon"
				visible					1
				scaleImage				1
			}
		}

		StatsWeaponListButtonNormalGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					10
				wide					120
				tall					40
				visible					1
				image					"../ui/menu/personal_stats/weapon_stats/ps_w_thumbnail_back"
				scaleImage				1
			}

			WeaponImageNormal
			{
				ControlName				ImagePanel
				xpos					0
				ypos					10
				wide					120
				tall					40
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}

			DimOverlay
			{
				ControlName				ImagePanel
				xpos					-2
				ypos					5
				wide					124
				tall					50
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}
		}

		StatsWeaponListButtonFocusedGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					10
				wide					120
				tall					40
				visible					1
				image					"../ui/menu/personal_stats/weapon_stats/ps_w_thumbnail_back"
				scaleImage				1
			}

			WeaponImageFocused
			{
				ControlName				ImagePanel
				xpos					0
				ypos					10
				wide					120
				tall					40
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}
		}

		StatsWeaponListButtonSelectedGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					140
				tall					60
				visible					1
				image					"../ui/menu/personal_stats/weapon_stats/ps_w_thumbnail_indicator"
				scaleImage				1
			}

			WeaponImageSelected
			{
				ControlName				ImagePanel
				xpos					0
				ypos					10
				wide					120
				tall					40
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}

			Arrow
			{
				ControlName				ImagePanel
				xpos					117
				ypos					15
				wide					20
				tall					30
				visible					1
				image 					"../ui/menu/personal_stats/weapon_stats/ps_w_main_arrow"
				scaleImage				1
			}
		}

		RankedSeasonListButtonAlwaysGroup
		{
			RankIcon
			{
				ControlName				ImagePanel
				xpos					16
				ypos					7
				zpos 					101
				wide					110
				tall					55
				image					"../ui/menu/rank_icons/tier_1_5"
				visible					1
				scaleImage				1
			}

			Division
			{
				ControlName				Label
				xpos					6
				ypos					-4
				zpos 					102
				textAlignment			west
				wide 					150
				tall					16
				visible					1
				font					RankedMenuMediumThin
				labelText				"[DIVISION NAME]"
				allcaps					1
				fgcolor_override		"245 245 245 255"
				pin_to_sibling			RankIcon
				pin_corner_to_sibling	0
				pin_to_sibling_corner	5
			}

			Tier
			{
				ControlName				Label
				xpos					0
				ypos					-3
				zpos 					102
				textAlignment			west
				wide 					150
				tall					16
				visible					1
				font					RankedMenuMediumThin
				labelText				"[TIER NAME]"
				allcaps					1
				fgcolor_override		"245 245 245 255"
				pin_to_sibling			Division
				pin_corner_to_sibling	0
				pin_to_sibling_corner	2
			}

			Season
			{
				ControlName				Label
				xpos					0
				ypos					-6
				zpos 					102
				textAlignment			west
				wide 					150
				tall					30
				visible					1
				font					RankedMenu20
				labelText				"[SEASON]"
				allcaps					1
				fgcolor_override		"204 234 255 255"
				pin_to_sibling			Division
				pin_corner_to_sibling	2
				pin_to_sibling_corner	0
			}
		}

		RankedSeasonListButtonNormalGroup
		{

		}

		RankedSeasonListButtonFocusedGroup
		{
			BackgroundFocused
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos 					100
				wide					249
				tall					69
				visible					1
				image 					"../ui/menu/rank_menus/ranked_FE_seasons_indicator"
				scaleImage				1
			}
		}

		RankedSeasonListButtonSelectedGroup
		{
			BackgroundSelected
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					249
				tall					69
				visible					1
				image 					"../ui/menu/rank_menus/ranked_FE_seasons_indicator"
				scaleImage				1
			}
		}

		BurnCardPackButtonAlwaysGroup
		{
			BurnCardRewardPanel
			{
				ControlName			CNestedPanel
				xpos				0
				ypos				0
				zpos				998
				wide				227
				tall				316
				visible				0
				controlSettingsFile	"scripts/screens/vgui_burn_card_medium.res"
				scaleImage			1
				drawColor			"255 255 255 255"
			}
		}

		BurnCardPackButtonFocusedGroup
		{
			Highlight
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					999
				wide					180
				tall					251
				visible					1
				image 					"../vgui/burncards/burncard_large_outline_highlight"
				scaleImage				1
				drawColor				"210 170 0 255"
			}
		}

		BurnCardPackButtonNormalGroup
		{
			DimOverlay
			{
				ControlName				ImagePanel
				xpos					1
				ypos					-25
				zpos 					999
				wide					179
				tall					302
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}
		}

		StatsLevelListButtonNormalGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					15
				ypos					10
				wide					90
				tall					40
				visible					1
				image					"../ui/menu/personal_stats/weapon_stats/ps_w_thumbnail_back"
				scaleImage				1
			}

			LevelImageNormal
			{
				ControlName				ImagePanel
				xpos					15
				ypos					10
				wide					90
				tall					40
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}

			DimOverlay
			{
				ControlName				ImagePanel
				xpos					14
				ypos					5
				wide					92
				tall					50
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}
		}

		StatsLevelListButtonFocusedGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					15
				ypos					10
				wide					90
				tall					40
				visible					1
				image					"../ui/menu/personal_stats/weapon_stats/ps_w_thumbnail_back"
				scaleImage				1
			}

			LevelImageFocused
			{
				ControlName				ImagePanel
				xpos					15
				ypos					10
				wide					90
				tall					40
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}
		}

		StatsLevelListButtonSelectedGroup
		{
			Image1
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				wide					140
				tall					60
				visible					1
				image					"../ui/menu/personal_stats/weapon_stats/ps_w_thumbnail_indicator"
				scaleImage				1
			}

			LevelImageSelected
			{
				ControlName				ImagePanel
				xpos					15
				ypos					10
				wide					90
				tall					40
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}

			Arrow
			{
				ControlName				ImagePanel
				xpos					117
				ypos					15
				wide					20
				tall					30
				visible					1
				image 					"../ui/menu/personal_stats/weapon_stats/ps_w_main_arrow"
				scaleImage				1
			}
		}

		EOGChallengeButtonEmpty
		{
		}

		ChallengeListButtonAlwaysGroup
		{
			TrackedIconAlways
			{
				ControlName				ImagePanel
				xpos					250
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					0
				scaleImage				1
				image 					"../ui/menu/challenges/challengeTrackerIcon_big"
			}

			DaysOldLabel
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide					282
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"X Days Old"
				textAlignment			east
				allcaps					1
				fgcolor_override		"230 161 23 255"
			}
		}
		ChallengeListButtonNormalGroup
		{
			BackgroundNormal
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					301
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box"
				scaleImage				1
			}

			IconNormal
			{
				ControlName				ImagePanel
				xpos					4
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					1
				scaleImage				1
				image 					"../ui/menu/challenge_icons/first_strike"
			}

			NameNormal
			{
				ControlName				Label
				xpos					42
				ypos					14
				zpos					303
				wide					234
				tall 					36
				visible					1
				font					ChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			BarFillNormal
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					304
				wide 					282
				tall 					14
				image 					"../ui/menu/eog/xp_bar"
				visible					1
				scaleImage				1
			}

			BarFillShadowNormal
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					305
				wide 					282
				tall 					15
				image 					"../ui/menu/eog/xp_bar_shadow"
				visible					1
				scaleImage				1
			}

			ProgressNormal
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide					282
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"[CHALLENGE PROGRESS]"
				textAlignment			west
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			DimOverlay
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					307
				wide					290
				tall					74
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}
		}

		ChallengeListButtonFocusedGroup
		{
			BackgroundFocused
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					301
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box"
				scaleImage				1
			}

			IconFocused
			{
				ControlName				ImagePanel
				xpos					4
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					1
				scaleImage				1
				image 					"../ui/menu/challenge_icons/first_strike"
			}

			NameFocused
			{
				ControlName				Label
				xpos					42
				ypos					14
				zpos					303
				wide					234
				tall 					36
				visible					1
				font					ChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			BarFillFocused
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					304
				wide 					282
				tall 					14
				image 					"../ui/menu/eog/xp_bar"
				visible					1
				scaleImage				1
			}

			BarFillShadowFocused
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					305
				wide 					282
				tall 					15
				image 					"../ui/menu/eog/xp_bar_shadow"
				visible					1
				scaleImage				1
			}

			ProgressFocused
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide					272
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"[CHALLENGE PROGRESS]"
				textAlignment			west
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}
		}

		ChallengeListButtonSelectedGroup
		{
			Highlight
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					300
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box_hover"
				scaleImage				1
			}

			BackgroundSelected
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					301
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box"
				scaleImage				1
			}

			IconSelected
			{
				ControlName				ImagePanel
				xpos					4
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					1
				scaleImage				1
				image 					"../ui/menu/challenge_icons/first_strike"
			}

			NameSelected
			{
				ControlName				Label
				xpos					42
				ypos					14
				zpos					303
				wide					234
				tall 					36
				visible					1
				font					ChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			BarFillSelected
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					304
				wide 					282
				tall 					14
				image 					"../ui/menu/eog/xp_bar"
				visible					1
				scaleImage				1
			}

			BarFillShadowSelected
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					305
				wide 					282
				tall 					15
				image 					"../ui/menu/eog/xp_bar_shadow"
				visible					1
				scaleImage				1
			}

			ProgressSelected
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide 					282
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"[CHALLENGE PROGRESS]"
				textAlignment			west
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}
		}

		DLCStoreButtonAlwaysGroup
		{
			Background
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					32
				wide					258
				tall					68
				visible					1
				scaleImage				1
				image 					""
				fgcolor_override		"220 220 220 255"
			}

			TitleLabel
			{
				ControlName				Label
				xpos					9
				ypos					6
				zpos					36
				auto_wide_tocontents	1
				tall 					14
				visible					1
				font					EOGUnlockItemHeaderMediumFont
				labelText				"XXXXXXXXXXX"
				textAlignment			west
				allcaps					0
				fgcolor_override		"230 230 230 255"
			}

			InstalledLabel
			{
				ControlName				Label
				xpos					-9
				ypos					-6
				zpos					36
				pin_to_sibling			Background
				pin_corner_to_sibling	3
				pin_to_sibling_corner	3
				tall 					14
				auto_wide_tocontents	1
				visible					1
				font					EOGUnlockItemHeaderMediumFont
				labelText				"XXXXXXXXXXX"
				textAlignment			east
				fgcolor_override		"230 161 23 255"
			}

			PartyDisabledImage
			{
				ControlName				ImagePanel
				zpos					36
				wide					258
				tall					68
				visible					1
				scaleImage				1
				image 					"../ui/menu/dlc_menu_grid/dlc_menu_grid_disabled"
				fgcolor_override		"255 255 255 127"
			}

			PartyDisabledLabel
			{
				ControlName				Label
				ypos					28
				zpos					37
				tall 					14
				wide					258
				visible					1
				font					RankedMenuSmallThin
				labelText				"#DLC_PARTY_WARNING"
				textAlignment			center
				allcaps					1
				fgcolor_override		"255 255 255 255"
			}

			PromoTextImage
			{
				ControlName				ImagePanel
				zpos					36
				wide					258
				tall					68
				visible					0
				scaleImage				1
				image 					"../ui/menu/dlc_menu_grid/dlc_menu_grid_promo"
				fgcolor_override		"255 255 255 127"
			}

			PromoTextLabel
			{
				ControlName				Label
				ypos					28
				zpos					37
				tall 					14
				wide					258
				visible					1
				font					RankedMenuSmallThin
				labelText				""
				textAlignment			center
				allcaps					1
				fgcolor_override		"255 255 255 255"
			}
		}

		DLCStoreButtonFocusedGroup
		{
			BackgroundFocused
			{
				ControlName				ImagePanel
				zpos					29
				wide					258
				tall					68
				visible					1
				scaleImage				1
				image 					"../ui/menu/dlc_menu_grid/dlc_menu_grid_hover"
				fgcolor_override		"255 255 255 255"
			}
		}

		TrackedChallengeListButtonAlwaysGroup
		{
			TrackedIconAlways
			{
				ControlName				ImagePanel
				xpos					250
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					0
				scaleImage				1
				image 					"../ui/menu/challenges/challengeTrackerIcon_big"
			}

			DaysOldLabel
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide					282
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"X Days Old"
				textAlignment			east
				allcaps					1
				fgcolor_override		"230 161 23 255"
			}
		}

		TrackedChallengeListButtonNormalGroup
		{
			BackgroundNormal
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					301
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box"
				scaleImage				1
			}

			IconNormal
			{
				ControlName				ImagePanel
				xpos					4
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					1
				scaleImage				1
				image 					"../ui/menu/challenge_icons/first_strike"
			}

			NameNormal
			{
				ControlName				Label
				xpos					42
				ypos					2//14
				zpos					303
				wide					200//234
				tall 					36
				visible					1
				font					TrackedChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			DescriptionNormal
			{
				ControlName				Label
				xpos					42
				ypos					22
				zpos					303
				wide					200//234
				tall 					36
				visible					1
				font					TrackedChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			BarFillNormal
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					304
				wide 					282
				tall 					14
				image 					"../ui/menu/eog/xp_bar"
				visible					1
				scaleImage				1
			}

			BarFillShadowNormal
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					305
				wide 					282
				tall 					15
				image 					"../ui/menu/eog/xp_bar_shadow"
				visible					1
				scaleImage				1
			}

			ProgressNormal
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide					282
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"[CHALLENGE PROGRESS]"
				textAlignment			west
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			DimOverlay
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					307
				wide					290
				tall					74
				visible					1
				image 					"../ui/menu/challenges/challenge_box_dim_overlay"
				scaleImage				1
			}
		}

		TrackedChallengeListButtonFocusedGroup
		{
			BackgroundFocused
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					301
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box"
				scaleImage				1
			}

			IconFocused
			{
				ControlName				ImagePanel
				xpos					4
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					1
				scaleImage				1
				image 					"../ui/menu/challenge_icons/first_strike"
			}

			NameFocused
			{
				ControlName				Label
				xpos					42
				ypos					2//14
				zpos					303
				wide					200//234
				tall 					36
				visible					1
				font					TrackedChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			DescriptionFocused
			{
				ControlName				Label
				xpos					42
				ypos					22
				zpos					303
				wide					200//234
				tall 					36
				visible					1
				font					TrackedChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			BarFillFocused
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					304
				wide 					282
				tall 					14
				image 					"../ui/menu/eog/xp_bar"
				visible					1
				scaleImage				1
			}

			BarFillShadowFocused
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					305
				wide 					282
				tall 					15
				image 					"../ui/menu/eog/xp_bar_shadow"
				visible					1
				scaleImage				1
			}

			ProgressFocused
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide					272
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"[CHALLENGE PROGRESS]"
				textAlignment			west
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}
		}

		TrackedChallengeListButtonSelectedGroup
		{
			Highlight
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					300
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box_hover"
				scaleImage				1
			}

			BackgroundSelected
			{
				ControlName				ImagePanel
				xpos					0
				ypos					0
				zpos					301
				wide					290
				tall					74
				visible					1
				image					"../ui/menu/challenges/challenge_box"
				scaleImage				1
			}

			IconSelected
			{
				ControlName				ImagePanel
				xpos					4
				ypos					9
				zpos					302
				wide					34
				tall					42
				visible					1
				scaleImage				1
				image 					"../ui/menu/challenge_icons/first_strike"
			}

			NameSelected
			{
				ControlName				Label
				xpos					42
				ypos					2//14
				zpos					303
				wide					200//234
				tall 					36
				visible					1
				font					TrackedChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			DescriptionSelected
			{
				ControlName				Label
				xpos					42
				ypos					22
				zpos					303
				wide					200//234
				tall 					36
				visible					1
				font					TrackedChallengeButtonNameFont
				labelText				"[CHALLENGE NAME]"
				textAlignment			middle
				wrap 					1
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}

			BarFillSelected
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					304
				wide 					282
				tall 					14
				image 					"../ui/menu/eog/xp_bar"
				visible					1
				scaleImage				1
			}

			BarFillShadowSelected
			{
				ControlName				ImagePanel
				xpos 					4
				ypos					52
				zpos					305
				wide 					282
				tall 					15
				image 					"../ui/menu/eog/xp_bar_shadow"
				visible					1
				scaleImage				1
			}

			ProgressSelected
			{
				ControlName				Label
				xpos					4
				ypos					52
				zpos					306
				wide 					282
				tall 					14
				visible					1
				font					ChallengeButtonProgressFont
				labelText				"[CHALLENGE PROGRESS]"
				textAlignment			west
				allcaps					1
				fgcolor_override		"220 220 220 255"
			}
		}
	}

	CustomFontFiles
	{
		1		"resource/ConduitITCPro-Medium.vfont"
		2		"resource/ConduitITCPro-Bold.vfont"
		3 		"resource/PFDinTextCondPro-Light.vfont"
		4 		"resource/PFDinTextCondPro-Medium.vfont"
		5 		"resource/arialuni.vfont" [$WINDOWS]
	}

	FontRemap
	{
		"ConduitITCPro-Medium"	"PFDinTextCondPro-Light" [$RUSSIAN]
		"ConduitITCPro-Bold"	"PFDinTextCondPro-Medium" [$RUSSIAN]
		"Titanfall"				"PFDinTextCondPro-Medium" [$RUSSIAN]

		"ConduitITCPro-Medium"	"arial unicode ms" [$JAPANESE || $KOREAN || $SCHINESE || $TCHINESE]
		"ConduitITCPro-Bold"	"arial unicode ms" [$JAPANESE || $KOREAN || $SCHINESE || $TCHINESE]
		"Titanfall"				"arial unicode ms" [$JAPANESE || $KOREAN || $SCHINESE || $TCHINESE]

		// Dev only fonts
		"Lucida Console"		"ConduitITCPro-Medium" [$GAMECONSOLE]
	}
}
