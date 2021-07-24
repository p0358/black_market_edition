// pch.h: wstępnie skompilowany plik nagłówka.
// Wymienione poniżej pliki są kompilowane tylko raz, co poprawia wydajność kompilacji dla przyszłych kompilacji.
// Ma to także wpływ na wydajność funkcji IntelliSense, w tym uzupełnianie kodu i wiele funkcji przeglądania kodu.
// Jednak WSZYSTKIE wymienione tutaj pliki będą ponownie kompilowane, jeśli którykolwiek z nich zostanie zaktualizowany między kompilacjami.
// Nie dodawaj tutaj plików, które będziesz często aktualizować (obniża to korzystny wpływ na wydajność).

#ifndef PCH_H
#define PCH_H

// w tym miejscu dodaj nagłówki, które mają być wstępnie kompilowane
#include "framework.h"

#include <TlHelp32.h>
#include <stdint.h>
#include <psapi.h>
#include <stdio.h>
#include <tchar.h>
#include <bcrypt.h>

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
#include <spdlog/fmt/bundled/printf.h>

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

#include "Memory.h"
#include "tier0.h"
#include <algorithm>
#include <functional>
#include <shared_mutex>
#include <unordered_set>
#include <filesystem>
namespace fs = std::filesystem;
#include <locale>
#include <codecvt>
#include <numeric>
#include <string>
#include <fstream>
#include <regex>
#include <mutex>
#include <sstream>
#include <map>
#include <MinHook/MinHook.h>
#include <xorstr.hpp>
#define _(str) xorstr_(str)

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/system.h>

#endif //PCH_H
