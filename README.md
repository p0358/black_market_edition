# Black Market Edition

Black Market Edition is a client-side multi-purpose community enhancement mod for Titanfall game, featuring various tons of quality-of-life changes and improvements.

Note that this mod is meant for playing on vanilla game and does not include game servers.

## Installation

Just grab the latest version's installer from the [Releases](https://github.com/p0358/bme_solution/releases) page and run it in order to install BME.

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
* enable in-game console accessible with <code>\`</code> key (enriched with output from Squirrel's print and svc_Print netmessages)
* execute Squirrel code with `script_client` and `script_ui` console commands
* when you're a party leader, change default in-game option for leaving from "Leave with Party" to "Leave Solo", to prevent accidentally pulling out your teammates with you when you want to leave alone
* see raw mouse sensivity value in mouse/keyboard settings
* remove minimum mouse sensitivity limitation
* start private matches alone by yourself
* see who's in a party with whom in public matchmaking
* hitch alerts to indicate various connection problems analogous to what Titanfall 2 and Apex have (for example: "OUT OF SNAPSHOTS", "NET CHOKED") (needs `cl_showfps` enabled)
* separate launcher exe that alleviates issues when Origin acts up and refuses to launch the game otherwise
* enable Unicode input in text chat (so you can type non-English characters; note: font used for some game locales cannot display many non-Latin characters)
* fix "XSS" in game invites (malicious join secrets could execute arbitrary client commands)
* fix various other security issues in the game
* unlocks `fps_max` cvar and allows default detected monitor refresh rate to be higher than 144 Hz
	* `fps_max -1` (default) defaults to monitor's refresh rate limit
	* `fps_max 0` uncaps the frame rate to unlimited (not recommended, will have adverse effects on network upload and will cause your client to lag and experience various glitches)
	* `fps_max <value>` caps the framerate to specified value
* mitigate performance issue that caused the game to drop FPS by wasting too much time in CPU (and leaving GPU idle) by warping HUD by overriding `hudwarp_chopsize` from `60` to `120`
	* **performance penalty can be entirely avoided with minimal loss of visual quality to the HUD by setting `hudwarp_use_gpu 1` which will make the warp effect run on the GPU instead of CPU**
	* further performance improvement can be achieved by increasing that cvar value even higher
	* **the best performance can be achieved by setting `hudwarp_disable 1`**, but this has adverse effect of not warping the HUD visually at all anymore
* allow to go on DLC playlists despite not having DLCs (by adding Ignore button to the playlist dialog)
	* this allows you to play the game (more-less) even if you couldn't obtain Deluxe Edition or Season Pass keys
	* as soon as a DLC map comes up in the rotation, you will be kicked out of the lobby upon its launch: still, that's better than not getting to play on the playlist at all
* make the game follow the default sound output device automatically (such as when connecting a Bluetooth headset; might not always work due to some engine bug though and then you still gotta restart the game)
* add custom playlist player counts sourced from [titanfall.p0358.net](https://titanfall.p0358.net) if the in-game counters are broken (the fallback BME counters are displayed in green, while original game ones from Stryder in amber)
* for switch-sides-based gamemodes, show in HUD whether you're playing first or second half
* allow replacing VPK files without making patched VPK files, by putting your modded files into `r1_mod` directory under your game installation dir
	* use concommand `fs_replacements_cache_refresh` to refresh the file list without restarting the game
* allow auto-saving of game scoreboards to JSON files after the match was concluded
	* use cvar `bme_cl_save_scoreboards 1` to enable the feature
	* the files will be saved into `<game dir>/bme/saved_scoreboards` directory, with name in format like `2024-05-28_11_40_04-private_match-ctf-mp_relic-5v5.json` (time is UTC)
	* you can enable automatic remote uploading of said files by `bme_cl_save_scoreboards_upload_url <URL>` to upload them to your custom endpoint via HTTP POST

### Known bugs

* pressing M to activate burn cards seems to activate the full screen map instead for some reason
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

Fallback playlist player counters:

![BME playlist counts](https://github.com/p0358/black_market_edition/raw/master/screenshots/player_counts.png)

Showing whether you're playing first or second half in switch-sides-based gamemodes such as CTF:

![Playing first half of the game](https://github.com/p0358/black_market_edition/raw/master/screenshots/first_half.png)

## Compiling

1. Clone the repo with `git clone --recursive --depth 1 https://github.com/p0358/black_market_edition.git`
2. Run `generate.bat` to generate Visual Studio project files
3. Run `copy_scripts_to_r1_modsrc.bat` to copy needed files from `bme_scripts` into `r1_modsrc`.
4. Run `build_assets.bat` to package `r1_modsrc` dir contents into `installer/source/bme/bme.bsp` and generate file list header file
5. Build the solution (`./build/bme.sln`) in VS 2022 (alternatively run `msbuild build\bme.sln -m`).
6. Look at `installer/installer_simple2.iss` to figure out which files go where (copy `bme.dll` and `Titanfall_alt.exe` most importantly).
7. Optionally build the installer (instructions below).

Note: if you add/remove files in `r1_modsrc`, you need to re-compile the DLL too (as that includes the list of available files).

### Building an installer

To build an installer for full mod, after doing the steps above, you need to look into the file `installer/installer_simple2.iss` and copy the required files into `installer/source` dir manually.

1. Under `installer/source/bme/`, copy the compiled `bme.dll` (from `build/x64-<CHANNEL>/bin/bme.dll`).
2. Also create `bme_channel.txt` with the value `staging` (or `release`).
3. `bme.bsp` should already be there after step #4 of compiling above (this file contains the filesystem replacement contents, that is scripts and some UI elements, into PakFile as lump 40 in bsp format, which can be easily mounted in the engine).
4. Copy the built `launcher.dll` into `installer/source/bin/x64_retail/` and `Titanfall_alt.exe` into `installer/source/`.
5. With Inno Setup compile out `installer/installer_simple2.iss` (or use `build_installer.bat` script if you have `iscc` in your path). The resulting installer will be in `installer/bme_installer.exe`.

## Acknowledgements

Parts of code from [TTF2SDK by James Wilkinson and Will Donohoe](https://github.com/Titanfall-Mods/TTF2SDK/blob/master/LICENSE.md) were used.

Black Market Edition makes use of the following third-party libraries:

| Package Name            | URL                                                                        |
|-------------------------|----------------------------------------------------------------------------|
| crashpad                | https://chromium.googlesource.com/crashpad/crashpad/+/master/LICENSE       |
| curl                    | https://curl.se/docs/copyright.html                                        |
| discord-rpc             | https://github.com/harmonytf/discord-rpc/blob/master/LICENSE               |
| imgui                   | https://github.com/ocornut/imgui/blob/master/LICENSE.txt                   |
| InnoDependencyInstaller | https://github.com/DomGries/InnoDependencyInstaller/blob/master/LICENSE.md |
| MinHook                 | https://github.com/TFORevive/minhook/blob/master/LICENSE.txt               |
| nghttp2                 | https://github.com/nghttp2/nghttp2/blob/master/COPYING                     |
| sentry-native           | https://github.com/getsentry/sentry-native/blob/master/LICENSE             |
| spdlog                  | https://github.com/gabime/spdlog/blob/v1.x/LICENSE                         |
| rapidjson               | https://github.com/Tencent/rapidjson/blob/master/license.txt               |

TITANFALL™ is a trademark of Respawn Entertainment, LLC.
