rapidjson = {
	source = path.join(dependencies.basePath, "rapidjson"),
}

function rapidjson.import()
	defines {
		"RAPIDJSON_HAS_STDSTRING=1",
		"RAPIDJSON_SSE2",
	}

	rapidjson.includes()
end

function rapidjson.includes()
	includedirs {
		path.join(rapidjson.source, "include"),
	}
end

function rapidjson.project()

end

deps.rapidjson = rapidjson
