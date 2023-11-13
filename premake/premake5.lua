-- Note: loaded scripts will change the current directory due to the code below:
-- https://github.com/premake/premake-core/blob/5b6289407d24fd48d5d8066119295a9c89947c4c/src/host/lua_auxlib.c#L153
-- for this reason we have to change directory manually back at the beginning on each script to avoid major pain!
os.chdir(_MAIN_SCRIPT_DIR)

newoption {
	trigger = "copy-to",
	description = "Optional, copy the EXE to a custom folder after build, define the path here if wanted.",
	value = "PATH"
}

function copytodir(subdir)
	if _OPTIONS["copy-to"] then
		postbuildcommands {"copy /y \"$(TargetPath)\" \"" .. path.join(_OPTIONS["copy-to"], subdir) .. "\""}
	end
end

newoption {
	trigger = "ci-build",
	description = "Enable CI builds of the client."
}

require("premake/utils")

dependencies = {
	basePath = path.join(_MAIN_SCRIPT_DIR, "thirdparty"),
	depsScriptsPath = path.join(_MAIN_SCRIPT_DIR, "premake/deps"),
}

deps = {} -- actual projects are here

function dependencies.load()
	local dir = path.join(dependencies.depsScriptsPath, "*.lua")
	local deps = os.matchfiles(dir)

	for i, dep in pairs(deps) do
		local dep = dep:gsub(".lua", "")
		require(dep)
	end
end

function dependencies.imports()
	for name, proj in pairs(deps) do
		proj.import()
	end
end

function dependencies.projects()
	for name, proj in pairs(deps) do
		proj.project()
	end
end

dependencies.load()

workspace "bme"
startproject "bmedll"
location "./build"
objdir "%{wks.location}/obj"
targetdir "%{wks.location}/bin/%{cfg.platform}-%{cfg.buildcfg}"
libdirs {"%{wks.location}/bin/%{cfg.platform}-%{cfg.buildcfg}"}

solutionitems {
	"./README.md",
	"./.gitignore",
	"./.github/workflows/build.yaml",
	"./.github/dependabot.yaml",
	["Premake"] = {
		"./premake/*.lua",
		["Deps"] = {
			"./premake/deps/**.lua"
		}
	},
}

configurations {"Release", "Staging", "Debug"}

language "C++"
cppdialect "C++20"
toolset "msc"

architecture "x86_64"
platforms "x64"

systemversion "latest"
symbols "On"
staticruntime "Off"
editandcontinue "Off"
--warnings "Extra"
characterset "ASCII"

flags {"MultiProcessorCompile", "No64BitChecks"}

defines {"_WINDOWS", "WIN32", "NOMINMAX"}

disablewarnings {"26812"} -- prefer `enum class` over `enum`
disablewarnings {"6255"} -- _alloca indicates failure by raising a stack overflow exception. Consider using _malloca instead

buildoptions {"/utf-8"}
linkoptions {}

filter "configurations:Release or configurations:Staging"
	optimize "Speed"
	buildoptions {
		--"/GL", -- Whole Program Optimization (requires LTCG)
		--"/guard:cf", -- Control Flow Guard (commented out because it was failing on us calling function pointer from GetProcAddress)
		--"/guard:ehcont", -- Enable EH Continuation Metadata (commented out because requires all .lib's to be recompiled)
	}
	linkoptions {
		--"/LTCG", -- Link Time Code Generation (required for whole program optimization)
		--"/guard:cf", -- Control Flow Guard
		--"/guard:ehcont", -- Enable EH Continuation Metadata
	}
	defines {"NDEBUG"}
	flags {--[["FatalCompileWarnings",]] "LinkTimeOptimization"}
filter {}

filter "configurations:Staging"
	defines {"STAGING"}
filter {}

filter "configurations:Debug"
	optimize "Debug"
	defines {"DEBUG", "_DEBUG"}
filter {}

files {"shared.manifest"}
includedirs {"./thirdparty"}
libdirs {"./thirdparty"}

require("premake/bmedll")
require("premake/loader_launcher_exe")
require("premake/loader_launcher_proxy")

group "Dependencies"
dependencies.projects()
