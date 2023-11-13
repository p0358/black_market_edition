os.chdir(_MAIN_SCRIPT_DIR)

project "loader_launcher_exe"
kind "WindowedApp"
language "C++"
copytodir "."

targetname "Titanfall_alt"

links {
    "Shlwapi.lib", -- for PathRemoveFileSpecW
    "Imm32.lib", -- for ImmIsIME
}

files {
    "./loader_launcher_exe/**.h",
    "./loader_launcher_exe/**.cpp",
    "./loader_launcher_exe/Titanfall_101.ico",
    "./loader_launcher_exe/loader_launcher_exe.rc",
}

includedirs {"./loader_launcher_exe"}

buildoptions {
    "/F8000000", -- stack
}

linkoptions {
    "/STACK:8000000", -- StackReserveSize
    "/CETCOMPAT", -- CET Shadow Stack Compatible
}
