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
        const char* moduleName;
        const char* signature;
        const char* mask;
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

    T operator()(Args... args)
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
class HookedFunc : public SigScanFunc<T, Args...>
{
private:
    bool m_hooked = false;
    using SigScanFunc<T, Args...>::m_func;
    T(*m_hookedFunc)(Args...) = nullptr;

public:
    HookedFunc(const char* moduleName, const char* signature, const char* mask) : SigScanFunc<T, Args...>(moduleName, signature, mask)
    {

    }

    void Hook(T(*detourFunc)(Args...))
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
            logger->critical("MH_CreateHook returned {}", status);
            throw std::exception("Failed to hook function");
        }

        status = MH_EnableHook(m_hookedFunc);
        if (status != MH_OK)
        {
            logger->critical("MH_EnableHook returned {}", status);
            throw std::exception("Failed to enable hook");
        }

        m_hooked = true;
        logger->debug("Hooked function at {} - trampoline location: {}", (void*)m_hookedFunc, (void*)m_func);
    }

    ~HookedFunc()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedFunc);
        }
    }
};

template<typename T, typename... Args>
class HookedFuncStatic
{
public:
    bool m_hooked = false;
    T(*m_origFunc)(Args...) = nullptr;
    T(*m_hookedFunc)(Args...) = nullptr;

private:
    const char* moduleName;
    DWORD64 offset;

public:
    HookedFuncStatic(const char* moduleName, DWORD64 offset)
    {
        this->moduleName = moduleName;
        this->offset = offset;
    }

    void Hook(T(*detourFunc)(Args...))
    {
        if (m_hooked)
        {
            return;
        }

        auto logger = spdlog::get("logger");

        m_hookedFunc = /*(LPVOID)*/(T(__cdecl *)(Args...))(Util::GetModuleBaseAddress(moduleName) + offset);

        MH_STATUS status = MH_CreateHookEx(m_hookedFunc, detourFunc, &m_origFunc);
        if (status != MH_OK)
        {
            logger->critical("MH_CreateHook returned {}", status);
            throw std::exception("Failed to hook function");
        }

        status = MH_EnableHook(m_hookedFunc);
        if (status != MH_OK)
        {
            logger->critical("MH_EnableHook returned {}", status);
            throw std::exception("Failed to enable hook");
        }

        m_hooked = true;
        logger->debug("Hooked function at {} - trampoline location: {}", (void*)m_hookedFunc, (void*)m_origFunc);
    }

    ~HookedFuncStatic()
    {
        if (m_hooked)
        {
            MH_RemoveHook(m_hookedFunc);
        }
    }

    T operator()(Args... args)
    {
        return m_origFunc(args...);
    }
};

/*enum ExecutionContext
{
    CONTEXT_CLIENT,
    CONTEXT_SERVER
};*/

template<typename T>
class SharedFunc
{
    T m_clientFunc;
    T m_serverFunc;

public:
    SharedFunc(const char* signature, const char* mask) : m_clientFunc("client.dll", signature, mask), m_serverFunc("server.dll", signature, mask)
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

    template<ExecutionContext context>
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
class SharedSigFunc : public SharedFunc<SigScanFunc<T, Args...>>
{
public:
    SharedSigFunc(const char* signature, const char* mask) : SharedFunc<SigScanFunc<T, Args...>>(signature, mask)
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

    template<ExecutionContext context>
    T Call(Args... args)
    {
        return GetFuncForContext<context>()(args...);
    }
};

template<typename T, typename... Args>
class SharedHookedFunc : public SharedFunc<HookedFunc<T, Args...>>
{
public:
    SharedHookedFunc(const char* signature, const char* mask) : SharedFunc<HookedFunc<T, Args...>>(signature, mask)
    {

    }

    void Hook(T(*clientDetourFunc)(Args...), T(*serverDetourFunc)(Args...))
    {
        //GetClientFunc().Hook(clientDetourFunc);
        //GetServerFunc().Hook(serverDetourFunc);
    }

    T CallClient(Args... args)
    {
        return GetFuncForContext<CONTEXT_CLIENT>()(args...);
    }

    T CallServer(Args... args)
    {
        return GetFuncForContext<CONTEXT_SERVER>()(args...);
    }

    template<ExecutionContext context>
    T Call(Args... args)
    {
        return GetFuncForContext<context>()(args...);
    }
};