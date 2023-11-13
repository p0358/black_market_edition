spdlog = {
	source = path.join(dependencies.basePath, "spdlog"),
}

function spdlog.import()
    links {"spdlog"}

	defines {
		"SPDLOG_COMPILED_LIB",
		"SPDLOG_WCHAR_FILENAMES",
		"SPDLOG_WCHAR_TO_UTF8_SUPPORT",
	}

	filter "configurations:Release"
	--if _OPTIONS["ci-build"] then
		--defines {"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO"}
	--else
		defines {"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG"}
	--end
	filter {}
	filter "configurations:Debug"
	defines {"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE"}
	filter {}

	spdlog.includes()
end

function spdlog.includes()
	includedirs {
		path.join(spdlog.source, "include"),
	}
end

function spdlog.project()
	project "spdlog"
    language "C++"

    spdlog.includes()

    includedirs {
        path.join(spdlog.source, "src"),
    }

    files {
        path.join(spdlog.source, "src/*.cpp"),
    }

    defines {
        "SPDLOG_COMPILED_LIB",
        "SPDLOG_WCHAR_FILENAMES",
        "SPDLOG_WCHAR_TO_UTF8_SUPPORT",
        "SPDLOG_DISABLE_DEFAULT_LOGGER",
    }

    filter "configurations:Release"
    --if _OPTIONS["ci-build"] then
        --defines {"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO"}
    --else
        defines {"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG"}
    --end
    filter {}
    filter "configurations:Debug"
    defines {"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE"}
    filter {}

    warnings "Off"
    kind "StaticLib"
end

deps.spdlog = spdlog
