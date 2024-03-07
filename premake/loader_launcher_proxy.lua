os.chdir(_MAIN_SCRIPT_DIR)

project "loader_launcher_proxy"
kind "SharedLib"
language "C++"
copytodir "."

targetname "launcher"

links {
    "Shlwapi.lib", -- for PathRemoveFileSpecW
    "Imm32.lib", -- for ImmIsIME
}

pchheader "pch.h"
pchsource "./loader_launcher_proxy/pch.cpp"
forceincludes {"pch.h"}

files {"./loader_launcher_proxy/**.h", "./loader_launcher_proxy/**.cpp"}
includedirs {"./loader_launcher_proxy"}

libdirs {"./thirdparty/tier0"}
links {"tier0"}

linkoptions {
    "/CETCOMPAT", -- CET Shadow Stack Compatible
}
