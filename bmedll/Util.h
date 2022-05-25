#pragma once
#include "pch.h"

//enum ExecutionContext
enum ClientServerExecutionContext
{
    CONTEXT_CLIENT,
    CONTEXT_SERVER
};

enum ScriptContext
{
    SCRIPT_CONTEXT_SERVER, // vm = server_local+0x108FFF0 // TODO_UPDATE
    SCRIPT_CONTEXT_CLIENT, // vm = client+0x16BBE78
    SCRIPT_CONTEXT_UI // vm = client+0x16C1FA8
};

template <typename T, T, typename U, U> struct MemberWrapper;
template<typename T, T& (*pObjGet)(), typename RT, typename... Args, RT(T::* pF)(Args...)>
struct MemberWrapper<RT(T::*)(Args...), pF, T& (*)(), pObjGet>
{
    /*static RT Call(Args&&... args)
    {
        return ((pObjGet()).*pF)(std::forward<Args>(args)...);
    }*/

    static RT Call(Args... args)
    {
        //if (&pObjGet() == nullptr /*|| ((pObjGet()).*pF) == nullptr*/) return NULL;
        return ((pObjGet()).*pF)(args...);
    }
};

/*template <typename T, T, typename U, U> struct MemberWrapper;
template<typename T, T& (*pObjGet)(), typename... Args, void(T::* pF)(Args...)>
struct MemberWrapper<void(T::*)(Args...), pF, T& (*)(), pObjGet>
{
    /*static RT Call(Args&&... args)
    {
        return ((pObjGet()).*pF)(std::forward<Args>(args)...);
    }* /

    static void Call(Args... args)
    {
        if (&pObjGet() == nullptr /*|| ((pObjGet()).*pF) == nullptr* /) return;
        return ((pObjGet()).*pF)(args...);
    }
};*/

namespace Util
{
    std::wstring Widen(const std::string& input);
    std::string Narrow(const std::wstring& input);
    std::string DataToHex(const char* input, size_t len);
    void SuspendAllOtherThreads();
    void ResumeAllOtherThreads();

    struct ThreadSuspender
    {
        ThreadSuspender();
        ~ThreadSuspender();
    };

    constexpr const char* GetContextName(ScriptContext context)
    {
        if (context == SCRIPT_CONTEXT_SERVER)
        {
            return "SERVER";
        }
        else if (context == SCRIPT_CONTEXT_CLIENT)
        {
            return "CLIENT";
        }
        else if (context == SCRIPT_CONTEXT_UI)
        {
            return "UI";
        }
        else
        {
            return "UNKNOWN";
        }
    }

    constexpr const char* GetContextName(ClientServerExecutionContext context)
    {
        if (context == CONTEXT_SERVER)
        {
            return "SERVER";
        }
        else if (context == CONTEXT_CLIENT)
        {
            return "CLIENT";
        }
        else
        {
            return "UNKNOWN";
        }
    }

    void FindAndReplaceAll(std::string& data, const std::string& search, const std::string& replace);
    HMODULE SafeGetModuleHandle(const std::string& moduleName);
    HMODULE GetModuleHandleOrThrow(const std::string& moduleName);
    MODULEINFO GetModuleInfo(const std::string& moduleName);
    DWORD64 GetModuleBaseAddress(const std::string& moduleName);
    DWORD64 GetModuleBaseAddressNoCache(const std::string& moduleName);
    void* ResolveLibraryExport(const std::string& moduleName, const std::string& exportName);
    void FixSlashes(char* pname, char separator);
    std::string ConcatStrings(const std::vector<std::string>& strings, const char* delim);
    HMODULE WaitForModuleHandle(const std::string& moduleName);
    std::string ReadFileToString(std::ifstream& f);
    std::vector<std::string> Split(const std::string& s, char delim);
    std::string RemoveChar(std::string str, char c);
    std::string GetLastErrorAsString();
    std::string vformat(const char* format, va_list args);
}