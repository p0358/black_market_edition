os.chdir(_MAIN_SCRIPT_DIR)

project "bmedll"
kind "SharedLib"
language "C++"
copytodir "."

targetname "bme"

pchheader "pch.h"
pchsource "./bmedll/pch.cpp"
forceincludes {"pch.h"}
filter "files:**.c" --or files:**/pch_impl.cpp
	flags {"NoPCH"}
    forceincludes {";"}
filter {}

files {"./bmedll/**.h", "./bmedll/**.cpp", "%{dir}/bmedll/**.asm"}
includedirs {"./bmedll"}
libdirs {"./thirdparty/tier0"}

links {
    "tier0",
}

dependencies.imports()
