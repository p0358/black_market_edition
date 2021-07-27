#pragma once
#include "pch.h"
#include "Util.h"

class BaseSigScanFunc
{
public:
    virtual void SetFuncPtr(void* funcPtr) = 0;
};

class SigScanFuncRegistry
{
private:
    struct RegistrationData
    {
        BaseSigScanFunc* func;
        /*const char* moduleName;
        const char* signature;
        const char* mask;*/
        std::string moduleName;
        std::string signature;
        std::string mask;
    };

    static const int MAX_SIG_SCAN_REGISTRATIONS = 100;

    RegistrationData m_registrations[MAX_SIG_SCAN_REGISTRATIONS];
    int m_numRegistrations;

public:
    static SigScanFuncRegistry& GetInstance();
    void AddSigScanFunc(BaseSigScanFunc& func, const char* moduleName, const char* signature, const char* mask);
    void ResolveAll();
};

template<typename T, typename... Args>
class SigScanFunc : public BaseSigScanFunc
{
protected:
    T(*m_func)(Args...) = nullptr;

public:
    SigScanFunc(const char* moduleName, const char* signature, const char* mask)
    {
        SigScanFuncRegistry::GetInstance().AddSigScanFunc(*this, moduleName, signature, mask);
    }

    void SetFuncPtr(void* ptr)
    {
        m_func = reinterpret_cast<T(*)(Args...)>(ptr);
    }

    void* GetFuncPtr()
    {
        return reinterpret_cast<void*>(m_func);
    }

    __forceinline T operator()(Args... args)
    {
        return m_func(args...);
    }
};

template <typename T>
inline MH_STATUS MH_CreateHookEx(LPVOID pTarget, LPVOID pDetour, T** ppOriginal)
{
    return MH_CreateHook(pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
}

template<typename T, typename... Args>
class HookedSigScanFunc : public SigScanFunc<T, Args...>
{
public:
    bool m_hooked = false;
    using SigScanFunc<T, Args...>::m_func;
    T(*m_hookedFunc)(Args...) = nullptr;

public:
    HookedSigScanFunc(const char* moduleName, const char* signature, const char* mask) : SigScanFunc<T, Args...>(moduleName, signature, mask)
    {

    }

    //void Hook(T(*detourFunc)(Args...))
    //void Hook(std::function<T(Args...)> detourFunc)
    void Hook(LPVOID detourFunc)
    {
        if (m_hooked)
        {
            return;
        }

        auto logger = spdlog::get("logger");

        m_hookedFunc = m_func;

        MH_STATUS status = MH_CreateHookEx(m_hookedFunc, detourFunc, &m_func);
        if (status != MH_OK)
        {
            //logger->critical("MH_CreateHook returned {} while trying to hook function in module {} of signature \"{}\" and mask \"{}\"", status, moduleName, signature, mask);
            logger->critical("MH_CreateHook returned {} while trying to hook a sigscan function");
            throw std::exception("Failed to hook function");
        }

        status = MH_EnableHook(m_hookedFunc);
        if (status != MH_OK)
        {
            logger->critical("MH_EnableHook returned {}", status);
            throw std::exception("Failed to enable hook");
        }

        m_hooked = true;
        SPDLOG_LOGGER_DEBUG(logger, "Hooked function at {} - trampoline location: {}", (void*)m_hookedFunc, (void*)m_func);
    }

    void Unhook()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedFunc);
        }
    }

    ~HookedSigScanFunc()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedFunc);
        }
    }
};

template<typename T, typename... Args>
class FuncStatic
{
protected:
    T(*m_func)(Args...) = nullptr;

public:
    FuncStatic(const char* moduleName, DWORD64 offset)
    {
        m_func = (T(/*__cdecl*/*)(Args...))(Util::GetModuleBaseAddressNoCache(moduleName) + offset); // if we inserted this DLL late before modules are loaded, then we'd need to create a static func registry analogous to sigscan one and resolve them when stuff is ready (also when calling check if func is ready and throw if it's not); but thankfully we don't :) just a comment for future reference
    }

    void SetFuncPtr(void* ptr)
    {
        m_func = reinterpret_cast<T(*)(Args...)>(ptr);
    }

    void* GetFuncPtr()
    {
        return reinterpret_cast<void*>(m_func);
    }

    __forceinline T operator()(Args... args)
    {
        return m_func(args...);
    }
};

template<typename T>
class FuncStaticWithType
{
protected:
    T m_func = nullptr;

public:
    FuncStaticWithType(const char* moduleName, DWORD64 offset)
    {
        m_func = (T)(Util::GetModuleBaseAddressNoCache(moduleName) + offset); // if we inserted this DLL late before modules are loaded, then we'd need to create a static func registry analogous to sigscan one and resolve them when stuff is ready (also when calling check if func is ready and throw if it's not); but thankfully we don't :) just a comment for future reference
    }

    void SetFuncPtr(void* ptr)
    {
        m_func = reinterpret_cast<T>(ptr);
    }

    void* GetFuncPtr()
    {
        return reinterpret_cast<void*>(m_func);
    }

    /*__forceinline T operator()(Args... args)
    {
        return m_func(args...);
    }*/

    template<typename... Args> __forceinline auto operator()(Args... args)
    {
        return m_func(args...);
    }
};

//template<typename T, typename... Args>
template<typename T>
class HookedFuncStaticWithType
{
public:
    bool m_hooked = false;
    //T(*m_origFunc)(Args...) = nullptr;
    //T(*m_hookedFunc)(Args...) = nullptr;
    T m_origFunc = nullptr;
    T m_hookedFunc = nullptr;

private:
    const char* moduleName;
    DWORD64 offset;

public:
    HookedFuncStaticWithType(const char* moduleName, DWORD64 offset)
    {
        this->moduleName = moduleName;
        this->offset = offset;
    }

    //void Hook(T(*detourFunc)(Args...))
    void Hook(T detourFunc)
    {
        if (m_hooked)
        {
            return;
        }

        auto logger = spdlog::get("logger");

        //m_hookedFunc = /*(LPVOID)*/(T(__cdecl*)(Args...))(Util::GetModuleBaseAddress(moduleName) + offset);
        m_hookedFunc = /*(LPVOID)*/(T)(Util::GetModuleBaseAddress(moduleName) + offset);

        MH_STATUS status = MH_CreateHookEx(m_hookedFunc, detourFunc, &m_origFunc);
        if (status != MH_OK)
        {
            logger->critical("MH_CreateHook returned {} while trying to hook function in module {} with offset {}", status, moduleName, (void*)offset);
            throw std::exception("Failed to hook function");
        }

        status = MH_EnableHook(m_hookedFunc);
        if (status != MH_OK)
        {
            logger->critical("MH_EnableHook returned {}", status);
            throw std::exception("Failed to enable hook");
        }

        m_hooked = true;
        SPDLOG_LOGGER_DEBUG(logger, "Hooked function at {} - trampoline location: {}", (void*)m_hookedFunc, (void*)m_origFunc);
    }

    void Unhook()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedFunc);
        }
    }

    ~HookedFuncStaticWithType()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedFunc);
        }
    }

    /*__forceinline T operator()(Args... args)
    {
        return m_origFunc(args...);
    }*/

    template<typename... Args> __forceinline auto operator()(Args... args)
    {
        return m_origFunc(args...);
    }
};

template<typename ReturnType, typename... Args>
class HookedFuncStatic : public HookedFuncStaticWithType<ReturnType(*)(Args...)>
{
public:
    HookedFuncStatic(const char* moduleName, DWORD64 offset) : HookedFuncStaticWithType<ReturnType(*)(Args...)>(moduleName, offset)
    {}

    __forceinline ReturnType operator()(Args... args)
    {
        return this->m_origFunc(args...);
    }
};

/*enum ClientServerExecutionContext // moved to Util.h
{
    CONTEXT_SERVER,
    CONTEXT_CLIENT
};*/

template<typename T>
class SharedClientServerFunc
{
    T m_clientFunc;
    T m_serverFunc;

public:
    SharedClientServerFunc(const char* signature, const char* mask) : m_clientFunc("client.dll", signature, mask), m_serverFunc("server.dll", signature, mask)
    {

    }

    T& GetClientFunc()
    {
        return m_clientFunc;
    }

    T& GetServerFunc()
    {
        return m_serverFunc;
    }

    template<ClientServerExecutionContext context>
    T& GetFuncForContext() = delete;

    template<>
    T& GetFuncForContext<CONTEXT_CLIENT>()
    {
        return m_clientFunc;
    }

    template<>
    T& GetFuncForContext<CONTEXT_SERVER>()
    {
        return m_serverFunc;
    }
};

template<typename T, typename... Args>
class SharedClientServerSigFunc : public SharedClientServerFunc<SigScanFunc<T, Args...>>
{
public:
    SharedClientServerSigFunc(const char* signature, const char* mask) : SharedClientServerFunc<SigScanFunc<T, Args...>>(signature, mask)
    {

    }

    T CallClient(Args... args)
    {
        return GetFuncForContext<CONTEXT_CLIENT>()(args...);
    }

    T CallServer(Args... args)
    {
        return GetFuncForContext<CONTEXT_SERVER>()(args...);
    }

    template<ClientServerExecutionContext context>
    T Call(Args... args)
    {
        return GetFuncForContext<context>()(args...);
    }
};

template<typename T, typename... Args>
class SharedClientServerHookedFunc : public SharedClientServerFunc<HookedSigScanFunc<T, Args...>>
{
public:
    SharedClientServerHookedFunc(const char* signature, const char* mask) : SharedClientServerFunc<HookedSigScanFunc<T, Args...>>(signature, mask)
    {

    }

    void Hook(T(*clientDetourFunc)(Args...), T(*serverDetourFunc)(Args...))
    {
        this.GetClientFunc().Hook(clientDetourFunc);
        this.GetServerFunc().Hook(serverDetourFunc);
    }

    T CallClient(Args... args)
    {
        return GetFuncForContext<CONTEXT_CLIENT>()(args...);
    }

    T CallServer(Args... args)
    {
        return GetFuncForContext<CONTEXT_SERVER>()(args...);
    }

    template<ClientServerExecutionContext context>
    T Call(Args... args)
    {
        return GetFuncForContext<context>()(args...);
    }
};

// SHARED SCRIPT FUNCS (server, client, client-ui)

/*enum ScriptContext // moved to Util.h
{
    SCRIPT_CONTEXT_SERVER, // vm = server_local+0x108FFF0 // TODO_UPDATE
    SCRIPT_CONTEXT_CLIENT, // vm = client+0x16BBE78
    SCRIPT_CONTEXT_UI // vm = client+0x16C1FA8
};*/

//SharedScriptHookedStaticFunc

//template<typename T>
template<typename T, typename... Args>
class SharedScriptStaticFunc
{
public:
    //T m_serverFunc;
    //T m_clientFunc;
    //T m_uiFunc;
    T(*m_serverFunc)(Args...); //= nullptr;
    T(*m_clientFunc)(Args...);
    T(*m_uiFunc)(Args...);

public:
    SharedScriptStaticFunc(DWORD64 serverOffset, DWORD64 clientOffset, DWORD64 uiOffset)
    {
        m_serverFunc = (T(/*__cdecl*/*)(Args...))(Util::GetModuleBaseAddressNoCache("server.dll") + serverOffset);
        m_clientFunc = (T(/*__cdecl*/*)(Args...))(Util::GetModuleBaseAddressNoCache("client.dll") + clientOffset);
        m_uiFunc = (T(/*__cdecl*/*)(Args...))(Util::GetModuleBaseAddressNoCache("client.dll") + uiOffset);
    }

    __forceinline auto& GetServerFunc()
    {
        return m_serverFunc;
    }

    __forceinline auto& GetClientFunc()
    {
        return m_clientFunc;
    }

    __forceinline auto& GetUIFunc()
    {
        return m_uiFunc;
    }

    template<ScriptContext context>
    auto& GetFuncForContext() = delete;

    template<>
    __forceinline auto& GetFuncForContext<SCRIPT_CONTEXT_SERVER>()
    {
        return m_serverFunc;
    }

    template<>
    __forceinline auto& GetFuncForContext<SCRIPT_CONTEXT_CLIENT>()
    {
        return m_clientFunc;
    }

    template<>
    __forceinline auto& GetFuncForContext<SCRIPT_CONTEXT_UI>()
    {
        return m_uiFunc;
    }

    __forceinline T CallServer(Args... args)
    {
        return GetFuncForContext<SCRIPT_CONTEXT_SERVER>()(args...);
    }

    __forceinline T CallClient(Args... args)
    {
        return GetFuncForContext<SCRIPT_CONTEXT_CLIENT>()(args...);
    }

    __forceinline T CallUI(Args... args)
    {
        return GetFuncForContext<SCRIPT_CONTEXT_UI>()(args...);
    }

    template<ScriptContext context>
    __forceinline T Call(Args... args)
    {
        return GetFuncForContext<context>()(args...);
    }
};

/*
template<typename T, typename... Args>
class HookedSigScanFunc : public SigScanFunc<T, Args...>
{
public:
    bool m_hooked = false;
    using SigScanFunc<T, Args...>::m_func;
    T(*m_hookedFunc)(Args...) = nullptr;
*/

template<typename T, typename... Args>
class SharedScriptHookedStaticFunc : SharedScriptStaticFunc<T, Args...>
{
public:
    bool m_hooked = false;
    //T(*m_origFunc)(Args...) = nullptr;
    //T(*m_hookedFunc)(Args...) = nullptr;
    using SharedScriptStaticFunc<T, Args...>::m_serverFunc;
    using SharedScriptStaticFunc<T, Args...>::m_clientFunc;
    using SharedScriptStaticFunc<T, Args...>::m_uiFunc;
    T(*m_hookedServerFunc)(Args...) = nullptr;
    T(*m_hookedClientFunc)(Args...) = nullptr;
    T(*m_hookedUIFunc)(Args...) = nullptr;

private:
    //const char* moduleName;
    //DWORD64 offset;

public:
    SharedScriptHookedStaticFunc(DWORD64 serverOffset, DWORD64 clientOffset, DWORD64 uiOffset) : SharedScriptStaticFunc(serverOffset, clientOffset, uiOffset)
    {

    }

    void Hook(T(*serverDetourFunc)(Args...), T(*clientDetourFunc)(Args...), T(*uiDetourFunc)(Args...))
    {
        if (m_hooked)
            return;
        //GetServerFunc().Hook(serverDetourFunc);
        //GetClientFunc().Hook(clientDetourFunc);
        /*m_serverFunc = _Hook(GetServerFunc(), serverDetourFunc);
        m_clientFunc = _Hook(GetClientFunc(), clientDetourFunc);
        m_uiFunc = _Hook(GetUIFunc(), uiDetourFunc);*/
        m_hookedServerFunc = m_serverFunc;
        m_hookedClientFunc = m_clientFunc;
        m_hookedUIFunc = m_uiFunc;
        _Hook<SCRIPT_CONTEXT_SERVER>(serverDetourFunc);
        _Hook<SCRIPT_CONTEXT_CLIENT>(clientDetourFunc);
        _Hook<SCRIPT_CONTEXT_UI>(uiDetourFunc);
        m_hooked = true;
    }

    template<ScriptContext context>
    void _Hook(/*T(*targetFunc)(Args...),*/ T(*detourFunc)(Args...))
    {
        if (m_hooked)
            return;

        auto logger = spdlog::get("logger");

        //m_hookedFunc = /*(LPVOID)*/(T(__cdecl*)(Args...))(Util::GetModuleBaseAddress(moduleName) + offset);
        //auto hookedFunc = targetFunc;
        //auto origFunc = targetFunc;
        //m_hookedServerFunc = m_serverFunc;

        //MH_STATUS status = MH_CreateHookEx(m_hookedFunc, detourFunc, &m_origFunc);
        //MH_STATUS status = MH_CreateHookEx(hookedFunc, detourFunc, &origFunc);

        MH_STATUS status = MH_OK;
        if (context == SCRIPT_CONTEXT_SERVER)
            status = MH_CreateHookEx(m_hookedServerFunc, detourFunc, &m_serverFunc);
        else if (context == SCRIPT_CONTEXT_CLIENT)
            status = MH_CreateHookEx(m_hookedClientFunc, detourFunc, &m_clientFunc);
        else if (context == SCRIPT_CONTEXT_UI)
            status = MH_CreateHookEx(m_hookedUIFunc, detourFunc, &m_uiFunc);
        else
            throw std::runtime_error("Unknown execution context when trying to hook function");

        if (status != MH_OK)
        {
            logger->critical("MH_CreateHook returned in SharedScriptHookedStaticFunc");
            throw std::exception("Failed to hook function");
        }

        status = MH_OK;
        if (context == SCRIPT_CONTEXT_SERVER)
            status = MH_EnableHook(m_hookedServerFunc);
        else if (context == SCRIPT_CONTEXT_CLIENT)
            status = MH_EnableHook(m_hookedClientFunc);
        else if (context == SCRIPT_CONTEXT_UI)
            status = MH_EnableHook(m_hookedUIFunc);
        else
            throw std::runtime_error("Unknown execution context when trying to hook function");
        if (status != MH_OK)
        {
            logger->critical("MH_EnableHook returned {}", status);
            throw std::exception("Failed to enable hook");
        }

        //SPDLOG_LOGGER_DEBUG(logger, "Hooked function at {} - trampoline location: {}", (void*)m_hookedFunc, (void*)m_origFunc);
        if (context == SCRIPT_CONTEXT_SERVER)
            SPDLOG_LOGGER_DEBUG(logger, "Hooked shared script-server function at {} - trampoline location: {}", (void*)m_hookedServerFunc, (void*)m_serverFunc);
        else if (context == SCRIPT_CONTEXT_CLIENT)
            SPDLOG_LOGGER_DEBUG(logger, "Hooked shared script-client function at {} - trampoline location: {}", (void*)m_hookedClientFunc, (void*)m_clientFunc);
        else if (context == SCRIPT_CONTEXT_UI)
            SPDLOG_LOGGER_DEBUG(logger, "Hooked shared script-client-ui function at {} - trampoline location: {}", (void*)m_hookedUIFunc, (void*)m_uiFunc);
        //return origFunc; // ?
    }

    void Unhook()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedServerFunc);
            MH_RemoveHook(m_hookedClientFunc);
            MH_RemoveHook(m_hookedUIFunc);
            m_hooked = false;
        }
    }

    ~SharedScriptHookedStaticFunc()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedServerFunc);
            MH_RemoveHook(m_hookedClientFunc);
            MH_RemoveHook(m_hookedUIFunc);
            m_hooked = false;
        }
    }
};