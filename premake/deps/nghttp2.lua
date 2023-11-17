nghttp2 = {
	source = path.join(dependencies.basePath, "nghttp2"),
}

function nghttp2.import()
	links {"nghttp2"}
	
	filter "toolset:msc*"
	links {}
	filter {}
	
	nghttp2.includes()
end

function nghttp2.includes()
filter "toolset:msc*"
	includedirs {
		path.join(nghttp2.source, "lib/includes"),
		path.join(dependencies.depsScriptsPath, "include"), -- to skip running autoconf script, we just add nghttp2ver.h there
	}

	defines {
		"NGHTTP2_STATICLIB",
	}

	filter {}
filter {}
end

function nghttp2.project()
	if not os.istarget("windows") then
		return
	end

	project "nghttp2"
    language "C"

    nghttp2.includes()

    defines {
		"_U_=",
		"_SSIZE_T_DEFINED=1",
		"ssize_t=__int64",
	}
    
    includedirs {
        path.join(nghttp2.source, "lib"),
    }
    
    files {
        path.join(nghttp2.source, "lib/*.h"),
        path.join(nghttp2.source, "lib/*.c"),
    }

    configure_ac = io.readfile(path.join(nghttp2.source, "configure.ac"))
	ac_init = configure_ac:sub(configure_ac:find("AC_INIT%([^%)]+%)"))
	version = ac_init:sub(ac_init:find("[0-9]+%.[0-9]+%.[0-9]+"))
	x = version:sub(version:find("^[0-9]+%."))
	y = version:sub(version:find("%.[0-9]+%.")):gsub("%.", "")
	z = version:sub(version:find("[0-9]+$"))
	vernum = string.format("0x%02x%02x%02x", x, y, z)

    nghttp2ver_h = io.readfile(path.join(nghttp2.source, "lib/includes/nghttp2/nghttp2ver.h.in"))
	nghttp2ver_h = nghttp2ver_h:gsub("@PACKAGE_VERSION@", version)
	nghttp2ver_h = nghttp2ver_h:gsub("@PACKAGE_VERSION_NUM@", vernum)
	io.writefile(path.join(dependencies.depsScriptsPath, "include/nghttp2/nghttp2ver.h"), nghttp2ver_h)
    
    filter "toolset:msc*"
    disablewarnings {
        "4702", -- unreachable code
    }

    filter {}

    warnings "Off"
    kind "StaticLib"
end

deps.nghttp2 = nghttp2
