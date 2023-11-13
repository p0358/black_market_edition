discord = {
	source = path.join(dependencies.basePath, "discord-rpc"),
}

function discord.import()
    links {"discord-rpc"}

	discord.includes()

	rapidjson.import()
end

function discord.includes()
	includedirs {
		path.join(discord.source, "include"),
	}

	rapidjson.includes()
end

function discord.project()
	project "discord-rpc"
    language "C++"

	discord.includes()

	files {
		path.join(discord.source, "include/*.h"),
		path.join(discord.source, "src/*.h"),
		path.join(discord.source, "src/*.cpp"),
	}

	removefiles {
        path.join(discord.source, "src/*_unix.cpp"),
        path.join(discord.source, "src/*_linux.cpp"),
        path.join(discord.source, "src/*_osx.cpp"),
    }

	warnings "Off"
    kind "StaticLib"
end

deps.discord = discord
