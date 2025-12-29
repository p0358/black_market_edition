curl = {
	source = path.join(dependencies.basePath, "curl"),
}

function curl.import()
	links { "curl" }
	
	filter "toolset:msc*"
	links { "Crypt32.lib", "ws2_32.lib", "Secur32.lib" }
	filter {}
	
	curl.includes()
end

function curl.includes()
filter "toolset:msc*"
	includedirs {
		path.join(curl.source, "include"),
	}

	defines {
		"CURL_STRICTER",
		"CURL_STATICLIB",
		-- disable unused protocols
		"CURL_DISABLE_DICT",
		"CURL_DISABLE_FTP",
		"CURL_DISABLE_GOPHER",
		"CURL_DISABLE_IMAP",
		"CURL_DISABLE_LDAP",
		"CURL_DISABLE_LDAPS",
		"CURL_DISABLE_MQTT",
		"CURL_DISABLE_NETRC",
		"CURL_DISABLE_NTLM",
		"CURL_DISABLE_POP3",
		"CURL_DISABLE_RTSP",
		"CURL_DISABLE_SMB",
		"CURL_DISABLE_SMTP",
		"CURL_DISABLE_TELNET",
		"CURL_DISABLE_TFTP",
	}
filter {}
end

function curl.project()
	if not os.istarget("windows") then
		return
	end

	project "curl"
		language "C"

		curl.includes()
		
		includedirs {
			path.join(curl.source, "lib"),
		}
		
		--zlib.import()
		nghttp2.import()
		
		files {
			path.join(curl.source, "lib/**.c"),
			path.join(curl.source, "lib/**.h"),
		}

		defines {
			"BUILDING_LIBCURL",
			-- zlib
			--"HAVE_ZLIB",
			--"HAVE_ZLIB_H",
			--"HAVE_LIBZ",
			-- nghttp2
			"USE_NGHTTP2",
		}
		
		filter "toolset:msc*"
		defines {
			"USE_SCHANNEL",
			"USE_WINDOWS_SSPI",
			"USE_THREADS_WIN32",
		}

		filter "toolset:not msc*"
		defines {
			"USE_GNUTLS",
			"USE_THREADS_POSIX",
		}

		filter {}

		warnings "Off"
		kind "StaticLib"
end

deps.curl = curl
