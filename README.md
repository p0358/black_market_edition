# Black Market Edition

Black Market Edition is a multi-purpose community enhancement mod for Titanfall game, featuring various quality-of-life changes and improvements.

**NOTE:** It is NOT yet finished (but is getting very close there), there are a few chore tasks needed before so, but the work was again put on hold due to game servers being taken down by attackers. However it works as-is for the most part.

Open sourcing this for now regardless, because I slowly worked on it since 2019 and I am not sure if I will ever get a chance to finish it in the current situation.

## Installation

~~Just grab the latest version's installer from the [Releases](https://github.com/p0358/bme_solution/releases) page and run it in order to install BME.~~

Installers are built with Inno Setup using scripts from installer/ folder and they automatically detect game installation folder to which they can unpack the files.

## Features

* loadout editing mid-match
* **very** detailed Discord rich presence + basic invite/join support
* basic rich presence in Origin itself
* bigger max FOV scale in graphics settings; hovering FOV option will play a video that helps to see what difference does this setting make (in scale of 70 to 90)
* real-time synchronization of private match settings (apply and refresh instantly): no more people fighting and overriding each other's settings
* you can start pilot/titan training on any arbitrary stage
* private match settings preset for competetive CTF (PUG/tourney), set all settings in two clicks
* announcement alert made smaller to not obstruct the player view, but kept noticeable (after feedback from many players)
* "RETURN TO BATTLEFIELD" text removed, counter moved a bit away from the center of your screen to let you normally aim (remember to return to battlefield before the timer runs out though!)
* normally dead playlists (that is: not attrition, frontier defense or campaign) will have an exclamation mark on the left side if they happen to have any players, to easily notice this fact when viewing them
* fixes of various small bugs in scripts (that could result in you getting kicked out to main menu with an error)
* last used gamemode loadout will be correctly focused if one was used (instead of always selecting general loadout 1); last used loadout will be always focused, even if using keyboard (so you can confirm it with Enter key, just like you can with A on controller)
* enable in-game console accessible with `\`` key (enriched with output from Squirrel's print and svc_Print netmessages)
* execute Squirrel code with `script_client` and `script_ui` console commands
* when you're a party leader, change default in-game option for leaving from "Leave with Party" to "Leave Solo", to prevent accidentally pulling out your teammates with you when you want to leave alone
* see raw mouse sensivity value in mouse/keyboard settings
* start private matches alone by yourself
* see who's in a party with whom in public matchmaking
* hitch alerts to indicate various connection problems analogous to what Titanfall 2 and Apex have

### Known bugs

* pressing M to activate burn cards seems to activate the full screen map instead for some reason
* registering custom new Squirrel functions in native code doesn't work, but we don't really need it currently
* setting private match settings sliders to the edge unprecisely might apply a wrong setting (which will be shown within a second)

## Screenshots

Main menu:

![Main Menu](https://github.com/p0358/black_market_edition/raw/master/screenshots/main_menu.png)

Discord rich presence:

![Discord rich presence](https://github.com/p0358/black_market_edition/raw/master/screenshots/rich_presence.png)

FOV scale settings with extended range and background preview video:

![FOV scale settings with extended range and background preview video](https://github.com/p0358/black_market_edition/raw/master/screenshots/fov_settings.png)

In-game console during map loading (activate it with \`):

![In-game console during map loading](https://github.com/p0358/black_market_edition/raw/master/screenshots/map_loading_with_console.png)

Possibility to edit loadouts mid-match (either with Y on controller or right-click on the loadout with mouse):

![Possibility to edit loadouts mid-match](https://github.com/p0358/black_market_edition/raw/master/screenshots/loadout_editing_in_game_1.png)

Editing a pilot loadout mid-match:

![Editing a pilot loadout mid-match](https://github.com/p0358/black_market_edition/raw/master/screenshots/loadout_editing_in_game_2.png)

"RETURN TO BATTLEFIELD" text removed and counter moved to the side to not obstruct the aim view:

!["RETURN TO BATTLEFIELD" text removed and counter moved to the side to not obstruct the aim view](https://github.com/p0358/black_market_edition/raw/master/screenshots/return_to_battlefield.png)

Announcement text made smaller to make it less annoying and obtrusive:

![Announcement text made smaller to make it less annoying and obtrusive](https://github.com/p0358/black_market_edition/raw/master/screenshots/announcement_size.png)

"Invite friends" button opens a dialog that allows you to select a platform to invite your friends on:

!["Invite friends" dialog](https://github.com/p0358/black_market_edition/raw/master/screenshots/invite_button_platform_selection.png)

Presets in private match that allow to quickly change settings to a predetermined set (in this case for competetive CTF games):

![Private match presets](https://github.com/p0358/black_market_edition/raw/master/screenshots/private_match_presets.png)

Missing "Apply" button in private match settings, because the settings are now synchronized real-time, which prevents people from overriding each other's settings when they edit them at the same time:

![Private match settings](https://github.com/p0358/black_market_edition/raw/master/screenshots/private_match_settings.png)

Training can be played in whole or started from any arbitrary stage:

![Training dialog](https://github.com/p0358/black_market_edition/raw/master/screenshots/training_options_1.png)

Arbitrary training stage selection:

![Training dialog](https://github.com/p0358/black_market_edition/raw/master/screenshots/training_options_2.png)

Mouse sensitivity value visible in settings:

![Training dialog](https://github.com/p0358/black_market_edition/raw/master/screenshots/mouse_sensitivity.png)

## Compiling

Clone the repo with `git clone --resursive --depth 1 -j8 https://github.com/p0358/black_market_edition.git` and build the solution in VS 2022.

### Building an installer

To build an installer for full mod, you need to look into the file `installer/installer_simple2.iss` and copy the required files into `installer/source` dir manually.

Under `source/bme`, copy the compiled `bme.dll` and create an empty file `bme.log`. Also create `bme_channel.txt` with the value `release`. Get `bme.bsp` from latest release in the Releases section (this file contains the filesystem replacement contents, that is scripts and some UI elements, into PakFile as lump 40 in bsp format, which can be easily mounted in the engine). Copy the built `launcher.dll` into `source/bin/x64_retail/`.
Get [Discord GameSDK](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip) and place its x64 dll file into the root of `source` folder.

## Acknowledgements

Parts of code from [TTF2SDK by James Wilkinson and Will Donohoe](https://github.com/Titanfall-Mods/TTF2SDK/blob/master/LICENSE.md) were used.

Black Market Edition makes use of the following third-party libraries:

| Package Name  | URL                                                                  |
|---------------|----------------------------------------------------------------------|
| sentry-native | https://github.com/getsentry/sentry-native/blob/master/LICENSE       |
| crashpad      | https://chromium.googlesource.com/crashpad/crashpad/+/master/LICENSE |
| imgui         | https://github.com/ocornut/imgui/blob/master/LICENSE.txt             |
| MinHook       | https://github.com/TsudaKageyu/minhook/blob/master/LICENSE.txt       |
| rapidjson     | https://github.com/Tencent/rapidjson/blob/master/license.txt         |
| spdlog        | https://github.com/gabime/spdlog/blob/v1.x/LICENSE                   |

TITANFALL™ is a trademark of Respawn Entertainment, LLC.
