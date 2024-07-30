// pch.h: wstępnie skompilowany plik nagłówka.
// Wymienione poniżej pliki są kompilowane tylko raz, co poprawia wydajność kompilacji dla przyszłych kompilacji.
// Ma to także wpływ na wydajność funkcji IntelliSense, w tym uzupełnianie kodu i wiele funkcji przeglądania kodu.
// Jednak WSZYSTKIE wymienione tutaj pliki będą ponownie kompilowane, jeśli którykolwiek z nich zostanie zaktualizowany między kompilacjami.
// Nie dodawaj tutaj plików, które będziesz często aktualizować (obniża to korzystny wpływ na wydajność).

#ifndef PCH_H
#define PCH_H

typedef unsigned __int64 _QWORD;
typedef unsigned int _DWORD;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <TlHelp32.h>
#include <stdint.h>
#include <psapi.h>
#include <stdio.h>
#include <tchar.h>
#include <bcrypt.h>
#include <winioctl.h>

#include <algorithm>
#include <functional>
#include <shared_mutex>
#include <unordered_set>
#include <filesystem>
namespace fs = std::filesystem;
#include <locale>
#include <numeric>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <mutex>
#include <sstream>
#include <map>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
#ifdef STAGING
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/wincolor_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/fmt/bundled/printf.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
//#include <rapidjson/schema.h>
//#include <rapidjson/filereadstream.h>

//#define D3D11_NO_HELPERS
//#define CINTERFACE
#define INITGUID
#include <d3d11.h>
#include <DXGI.h>
#undef INITGUID
//#undef CINTERFACE

#include <d3dcompiler.h>

// imgui
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include <imgui/backends/imgui_impl_win32.h>

#include <MinHook.h>

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/system.h>

template <class F>
struct lambda_traits : lambda_traits<decltype(&F::operator())> {};

template <typename F, typename R, typename... Args>
struct lambda_traits<R(F::*)(Args...)> : lambda_traits<R(F::*)(Args...) const> {};

template <class F, class R, class... Args>
struct lambda_traits<R(F::*)(Args...) const>
{
	using pointer = typename std::add_pointer<R(Args...)>::type;

	static pointer to_ptr(F&& f)
	{
		static F fn = std::forward<F>(f);
		return [](Args... args)
			{
				return fn(std::forward<Args>(args)...);
			};
	}
};

template <class F>
inline typename lambda_traits<F>::pointer lambda_to_ptr(F&& f)
{
	return lambda_traits<F>::to_ptr(std::forward<F>(f));
}

#endif //PCH_H
