-- cmake -B build -DSENTRY_BUILD_SHARED_LIBS=OFF
-- cmake --build build --parallel --config Release
-- cmake --install build --prefix install --config Release

sentry = {
	source = path.join(dependencies.basePath, "sentry"),
}

function sentry.import()
    links {
        "sentry.lib",
        "crashpad_client.lib",
        "crashpad_util.lib",
        "mini_chromium.lib",

        "Winhttp",
        "DbgHelp",
        "Version",
    }

    libdirs {
		path.join(sentry.source, "lib"),
	}

	sentry.includes()
end

function sentry.includes()
	includedirs {
		path.join(sentry.source, "include"),
	}
end

function sentry.project()

end

deps.sentry = sentry
