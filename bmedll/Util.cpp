#include "pch.h"
#include "Util.h"
#include "TTFSDK.h"

std::unordered_map<std::string, DWORD64> baseModuleAddressCache;

HANDLE GetVolumeHandleForFile(const wchar_t* filePath)
{
    wchar_t volume_path[MAX_PATH];
    if (!GetVolumePathNameW(filePath, volume_path, ARRAYSIZE(volume_path)))
        return nullptr;

    wchar_t volume_name[MAX_PATH];
    if (!GetVolumeNameForVolumeMountPointW(volume_path, volume_name, ARRAYSIZE(volume_name)))
        return nullptr;

    auto length = wcslen(volume_name);
    if (length && volume_name[length - 1] == L'\\')
        volume_name[length - 1] = L'\0';

    return CreateFileW(volume_name, 0, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
}

namespace Util
{
    // Taken from https://stackoverflow.com/a/18374698
    std::wstring Widen(const std::string& input)
    {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;
        return converterX.from_bytes(input);
    }

    // Taken from https://stackoverflow.com/a/18374698
    std::string Narrow(const std::wstring& input)
    {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;
        return converterX.to_bytes(input);
    }

    // This will convert some data like "Hello World" to "48 65 6C 6C 6F 20 57 6F 72 6C 64"
    // Taken mostly from https://stackoverflow.com/a/3382894
    std::string DataToHex(const char* input, size_t len)
    {
        static const char* const lut = "0123456789ABCDEF";

        std::string output;
        output.reserve(2 * len);
        for (size_t i = 0; i < len; i++)
        {
            const unsigned char c = input[i];
            output.push_back(lut[c >> 4]);
            output.push_back(lut[c & 15]);
        }

        return output;
    }

    void FindAndReplaceAll(std::string& data, const std::string& search, const std::string& replace)
    {
        size_t pos = data.find(search);
        while (pos != std::string::npos)
        {
            data.replace(pos, search.size(), replace);
            pos = data.find(search, pos + replace.size());
        }
    }

    HMODULE SafeGetModuleHandle(const std::string& moduleName) {
        HMODULE hModule;
        for (hModule = nullptr; hModule == nullptr; Sleep(1))
        {
            hModule = GetModuleHandleA(moduleName.c_str());
        }
        return hModule;
    }

    HMODULE GetModuleHandleOrThrow(const std::string& moduleName)
    {
        HMODULE hModule = GetModuleHandleA(moduleName.c_str());
        if (!hModule)
        {
            auto err = fmt::sprintf("GetModuleHandle failed for %s (Error = 0x%X)", moduleName, GetLastError());
            if (IsSDKReady()) spdlog::critical(err);
            else fprintf(stderr, "%s\n", err.c_str());
            if (IsClient()) MessageBoxA(NULL, err.c_str(), "Critical BME Error", MB_ICONERROR);
            throw std::runtime_error(err);
        }
        return hModule;
    }

    MODULEINFO GetModuleInfo(const std::string& moduleName)
    {
        MODULEINFO modinfo = { 0 };
        //HMODULE hModule = SafeGetModuleHandle(moduleName);
        HMODULE hModule = GetModuleHandleOrThrow(moduleName);
        GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
        return modinfo;
    }

    DWORD64 GetModuleBaseAddress(const std::string& moduleName)
    {
        DWORD64 lpBaseOfDll = baseModuleAddressCache[moduleName];
        if (!lpBaseOfDll)
        {
            lpBaseOfDll = (DWORD64)GetModuleInfo(moduleName).lpBaseOfDll;
            baseModuleAddressCache[moduleName] = lpBaseOfDll;
        }
        return lpBaseOfDll;
    }

    DWORD64 GetModuleBaseAddressNoCache(const std::string& moduleName)
    {
        return (DWORD64)GetModuleInfo(moduleName).lpBaseOfDll;
    }

    void* ResolveLibraryExport(const std::string& moduleName, const std::string& exportName)
    {
        HMODULE hModule = GetModuleHandleA(moduleName.c_str());
        if (!hModule)
        {
            throw std::runtime_error(fmt::sprintf("GetModuleHandle failed for %s (Error = 0x%X)", moduleName, GetLastError()));
        }

        void* exportPtr = GetProcAddress(hModule, exportName.c_str());
        if (!exportPtr)
        {
            throw std::runtime_error(fmt::sprintf("GetProcAddress failed for %s (Error = 0x%X)", exportName, GetLastError()));
        }

        return exportPtr;
    }

    void FixSlashes(char* pname, char separator)
    {
        while (*pname)
        {
            if (*pname == '\\' || *pname == '/')
            {
                *pname = separator;
            }
            pname++;
        }
    }

    std::string ConcatStrings(const std::vector<std::string>& strings, const char* delim)
    {
        std::ostringstream imploded;
        std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(imploded, delim));
        return imploded.str();
    }

    HMODULE WaitForModuleHandle(const std::string& moduleName)
    {
        HMODULE m = GetModuleHandleA(moduleName.c_str());
        while (m == nullptr)
        {
            //Sleep(1);
            YieldProcessor();
            m = GetModuleHandleA(moduleName.c_str());
        }
        return m;
    }

    std::string ReadFileToString(std::ifstream& f)
    {
        std::string fileData;
        f.seekg(0, std::ios::end);
        fileData.reserve(f.tellg());
        f.seekg(0, std::ios::beg);

        fileData.assign((std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>());
        return fileData;
    }

    // Taken from https://stackoverflow.com/a/9435385
    std::vector<std::string> Split(const std::string& s, char delim)
    {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> elems;
        while (std::getline(ss, item, delim))
        {
            elems.push_back(std::move(item));
        }
        return elems;
    }

    std::string RemoveChar(std::string str, char c)
    {
        std::string result;
        for (size_t i = 0; i < str.size(); i++)
        {
            char currentChar = str[i];
            if (currentChar != c)
                result += currentChar;
        }
        return result;
    }

    std::string GetLastErrorAsString()
    {
        //Get the error message, if any.
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0)
            return std::string(); //No error message has been recorded

        LPSTR messageBuffer = nullptr;
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        std::string message(messageBuffer, size);

        //Free the buffer.
        LocalFree(messageBuffer);

        return message;
    }

    std::string vformat(const char* format, va_list args)
    {
        va_list copy;
        va_copy(copy, args);
        int len = std::vsnprintf(nullptr, 0, format, copy);
        va_end(copy);

        if (len >= 0) [[likely]]
        {
            std::string s(std::size_t(len) + 1, '\0');
            std::vsnprintf(&s[0], s.size(), format, args);
            s.resize(len);
            return s;
        }

        const auto err = errno;
        const auto ec = std::error_code(err, std::generic_category());
        throw std::system_error(ec);
    }

    const char* GetProcessorNameString()
    {
        static char CPUBrandString[0x41];
        static std::once_flag flag;
        std::call_once(flag, [&]()
        {
            int cpuInfo[4] = { -1 };
            memset(CPUBrandString, 0, sizeof(CPUBrandString));

            __cpuid(cpuInfo, 0x80000002);
            memcpy(CPUBrandString, cpuInfo, sizeof(cpuInfo));

            __cpuid(cpuInfo, 0x80000003);
            memcpy(CPUBrandString + 16, cpuInfo, sizeof(cpuInfo));

            __cpuid(cpuInfo, 0x80000004);
            memcpy(CPUBrandString + 32, cpuInfo, sizeof(cpuInfo));

            CPUBrandString[0x40] = '\0';
        });

        // example: Intel(R) Core(TM) i5-6600 CPU @ 3.30GHz
        // example: AMD Ryzen 5 3600 6-Core Processor
        return CPUBrandString;
    }

    bool DoesStorageDeviceIncurSeekPenaltyAtPath(const wchar_t* file_path) // is HDD
    {
        bool incursSeekPenalty = false;
        HANDLE volume = GetVolumeHandleForFile(file_path);
        if (volume == INVALID_HANDLE_VALUE)
            return false;

        STORAGE_PROPERTY_QUERY query{};
        query.PropertyId = StorageDeviceSeekPenaltyProperty;
        query.QueryType = PropertyStandardQuery;

        DWORD count;
        DEVICE_SEEK_PENALTY_DESCRIPTOR result{};
        if (DeviceIoControl(volume, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query), &result, sizeof(result), &count, nullptr))
            incursSeekPenalty = result.IncursSeekPenalty;

        CloseHandle(volume);
        return incursSeekPenalty;
    }

}