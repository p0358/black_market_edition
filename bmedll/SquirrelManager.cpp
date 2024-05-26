#include "pch.h"
#include "TTFSDK.h"
#include "SigScanning.h"
#include "SquirrelManager.h"
#include "Tier0.h"

__forceinline SquirrelManager& SQManager()
{
    return SDK().GetSQManager();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&SquirrelManager::##name), &SquirrelManager::##name, decltype(&SQManager), &SQManager>::Call

HookedFuncStatic<SQInteger, HSQUIRRELVM> base_print("launcher.org.dll", 0x56B40);
FuncStatic<SQRESULT, HSQUIRRELVM, SQLEXREADFUNC, SQUserPointer, const SQChar*, SQBool> sq_compile("launcher.org.dll", 0x14970);
FuncStatic<SQRESULT, HSQUIRRELVM, const SQChar*, SQInteger, const SQChar*, SQBool> sq_compilebuffer("launcher.org.dll", 0x1A5E0);
FuncStatic<__int64 __fastcall, HSQUIRRELVM> base_getroottable("launcher.org.dll", 0x56440); // equivalent of sq_pushroottable
FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, SQBool, SQBool> sq_call("launcher.org.dll", 0x18C40);
HookedFuncStatic<void, HSQUIRRELVM, const SQChar*, const SQChar*, SQInteger, SQInteger> sqstd_compiler_error("launcher.org.dll", 0x3AB90); // should be
FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, SQBool> sq_newslot("launcher.org.dll", 0x17260);
FuncStatic<void, HSQUIRRELVM, SQInteger> SQVM_Pop("launcher.org.dll", 0x2BC60);
FuncStatic<void, HSQUIRRELVM, SQInteger> sq_push("launcher.org.dll", 0x165E0);
//FuncStatic<SQString*, HSQUIRRELVM, const SQObject&> SQVM_PrintObjVal("launcher.org.dll", 0x41300);
static auto SQVM_Raise_Error = (void(*)(HSQUIRRELVM, const SQChar*, ...))(Util::GetModuleBaseAddressNoCache("launcher.org.dll") + 0x411B0);
FuncStatic<SQChar* __fastcall, SQObjectType> IdType2Name("launcher.org.dll", 0x3C660);

FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, const SQChar**> sq_getstring("launcher.org.dll", 0x16880);
FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQInteger*> sq_getinteger("launcher.org.dll", 0xE740); // R1SquirrelVM* unused
FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQFloat*> sq_getfloat("launcher.org.dll", 0xE6F0); // R1SquirrelVM* unused
FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQBool*> sq_getbool("launcher.org.dll", 0xE6B0); // R1SquirrelVM* unused
FuncStatic<void, HSQUIRRELVM> sq_pushnull("launcher.org.dll", 0x14BD0);
FuncStatic<void, HSQUIRRELVM, const SQChar*, SQInteger> sq_pushstring("launcher.org.dll", 0x14C30);
FuncStatic<void, R1SquirrelVM*, HSQUIRRELVM, SQInteger> sq_pushinteger("launcher.org.dll", 0xEA10); // R1SquirrelVM* unused
FuncStatic<void, R1SquirrelVM*, HSQUIRRELVM, SQFloat> sq_pushfloat("launcher.org.dll", 0xE9B0); // R1SquirrelVM* unused
FuncStatic<void, R1SquirrelVM*, HSQUIRRELVM, SQBool> sq_pushbool("launcher.org.dll", 0xE930); // R1SquirrelVM* unused
FuncStatic<void, HSQUIRRELVM, SQInteger> sq_tostring("launcher.org.dll", 0x16690);
FuncStatic<SQInteger, R1SquirrelVM*, HSQUIRRELVM, SQInteger> sq_getsize("launcher.org.dll", 0xE790); // R1SquirrelVM* unused
//FuncStatic<SQObjectType, R1SquirrelVM*, HSQUIRRELVM, SQInteger> sq_gettype("launcher.org.dll", 0x2C310); // R1SquirrelVM* unused // TODO?? superseded below
FuncStatic<SQObjectType, HSQUIRRELVM, SQInteger> sq_gettype("launcher.org.dll", 0x16660); // "probably"
FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQObject*> sq_getstackobj("launcher.org.dll", 0xE7F0); // R1SquirrelVM* unused
FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_get("launcher.org.dll", 0x17F10); // "maybe"
FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_get_noerr("launcher.org.dll", 0x18150);
FuncStatic<SQInteger, R1SquirrelVM*, HSQUIRRELVM> sq_gettop("launcher.org.dll", 0xE830); // R1SquirrelVM* unused
FuncStatic<void, HSQUIRRELVM> sq_newtable("launcher.org.dll", 0x14F30);
FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_next("launcher.org.dll", 0x1A1B0);
FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, SQUserPointer*, SQUserPointer> sq_getinstanceup("launcher.org.dll", 0x6750);

FuncStatic<void, HSQUIRRELVM, SQInteger> sq_newarray("launcher.org.dll", 0x14FB0);
FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_arrayappend("launcher.org.dll", 0x152A0);

HookedFuncStatic<R1SquirrelVM*, int64_t, int, ScriptContext> CreateNewVM("launcher.org.dll", 0x1210);
//HookedFuncStatic<int64_t, int64_t> RunServerInitCallbacks("server_local.dll", 0x548710); // called multiple times // TODO
HookedFuncStatic<int64_t, int64_t> RunClientInitCallbacks("client.dll", 0x2BECF0); // called multiple times
HookedFuncStatic<char, __int64, __int64> RunUIInitCallbacks("client.dll", 0x2DAE30); // called multiple times (UI gets reinit on map change/server connect/level loading finished?)
FuncStatic<bool, R1SquirrelVM*, const char*> RunCallback("launcher.org.dll", 0x89A0);
//static auto ThrowClientScriptError = (void(*)(const char*, ...))(Util::GetModuleBaseAddressNoCache("client.dll") + 0x2C4FE0); // I guess // TODO: rethink this when we run in dedi without client.dll...
FuncStatic<__int64, R1SquirrelVM*, const char*, signed int> CSquirrelVM__RegisterGlobalConstantInt("launcher.org.dll", 0xA680); // example: (a1, "TRAINING_MOSH_PIT", 3i64)

FuncStatic<int64_t, R1SquirrelVM*, SQFuncRegistrationInternal*> AddSquirrelReg("launcher.org.dll", 0x8E50);

/*SQInteger buf_lexfeed(SQUserPointer file)
{
    BufState* buf = (BufState*)file;
    if (buf->size < (buf->ptr + 1))
        return 0;
    return buf->buf[buf->ptr++];
}

SQRESULT sq_compilebuffer(HSQUIRRELVM v, const SQChar* s, SQInteger size, const SQChar* sourcename, SQBool raiseerror) {
    BufState buf;
    buf.buf = s;
    buf.size = size;
    buf.ptr = 0;
    return sq_compile(v, buf_lexfeed, &buf, sourcename, raiseerror);
}*/

#define type(obj) ((obj)._type)
#define is_delegable(t) (type(t)&SQOBJECT_DELEGABLE)
#define raw_type(obj) _RAW_TYPE((obj)._type)

// TODO: d e l e t e, since these probably don't even work, I had crashes trying to use these
inline /*SQObjectPtr**/ /*void**/SQObject& stack_get(HSQUIRRELVM v, SQInteger idx) { // not sure if this works
    __int64 v3; // rbx
    __int64 v4; // rbx

    if (idx < 0)
        v3 = (unsigned int)(idx + *(_DWORD*)(v + 80));
    else
        v3 = (unsigned int)(*(_DWORD*)(v + 84) + idx - 1);
    v4 = *(_QWORD*)(v + 48) + 16 * v3;
    //return (void*)v4;
    return (SQObject&)v4;
}
bool sq_aux_gettypedarg(HSQUIRRELVM v, SQInteger idx, SQObjectType type, /*SQObjectPtr***/ /*void***/ SQObject** o)
{
    *o = &stack_get(v, idx);
    //*o = (SQObjectPtr*)stack_get(v, idx);
    //*o = stack_get(v, idx);
    //if (type(**((SQObject**)o)) != type) {
    if (type(**o) != type) {
        //if ((**((SQObjectType**)o)) != type) {
            //SQObjectPtr oval = SQVM_PrintObjVal(v, (const SQObjectPtr&)**o);
            ///////SQObject* oval = (SQObject*)SQVM_PrintObjVal(v, **((SQObject**)o)); // crashed here // we yeeted SQString type, oops
            //auto oval = SQVM_PrintObjVal(v, **((SQObject**)o));
            //SQVM_Raise_Error(v, "wrong argument type, expected '%s' got '%.50s'", IdType2Name(type), _stringval(oval));
            ///////SQVM_Raise_Error(v, "wrong argument type, expected '%s' got '%.50s'", IdType2Name(type), _stringval(*oval)); // we yeeted _stringval macro, oops
        return false;
    }
    return true;
}
#define _GETSAFE_OBJ(v,idx,type,o) { if(!sq_aux_gettypedarg(v,idx,type,&o)) return SQ_ERROR; }
#define _GETSAFE_OBJ_NULLABLE(v,idx,type,o) { if(!sq_aux_gettypedarg(v,idx,type,&o)) return NULL; }

// TODO: will we use this?
#define sq_aux_paramscheck(v,count) \
{ \
	if(sq_gettop(v) < count){ v->Raise_Error(_SC("not enough params in the stack")); return SQ_ERROR; }\
}

void sq_poptop(HSQUIRRELVM v)
{
    assert(*(_DWORD*)(v + 80) >= 1); // v->_top >= 1
    SQVM_Pop(v, 1);
}

__int64 __fastcall SQFuncBindingFn(__int64(__fastcall* a1)(_QWORD), __int64 a2, _QWORD* a3, __int64 a4, __int64 a5)
{
    __int64 result; // rax

    result = ((__int64(__fastcall*)(_QWORD, __int64))a1)(*a3, a2);
    *(unsigned __int16*)(a5 + 8) = 5;
    *(_DWORD*)a5 = result;
    return result;
}

HookedFuncStatic<bool, void*> FatalScriptError("launcher.org.dll", 0x39CD0);
bool __fastcall FatalScriptError_Hook(void* a1)
{
    static const char* script_error = (const char*)(Util::GetModuleBaseAddress("launcher.org.dll") + 0x117D40);
    if (IsSDKReady())
    {
        auto logger = spdlog::get("logger");
        logger->error("SCRIPT ERROR:\n{}\n\n", script_error);
    }
    else printf("\nSCRIPT ERROR:\n%s\n\n", script_error);
    return FatalScriptError(a1);
}

SquirrelManager::SquirrelManager()
{
    m_logger = spdlog::get("logger");

    //m_ppServerVM = (R1SquirrelVM**)(Util::GetModuleBaseAddress("server_local.dll") + 0x108FFF0); // TODO
    m_ppClientVM = (R1SquirrelVM**)(Util::GetModuleBaseAddress("client.dll") + 0x16BBE78);
    m_ppUIVM = (R1SquirrelVM**)(Util::GetModuleBaseAddress("client.dll") + 0x16C1FA8);

    base_print.Hook(WRAPPED_MEMBER(BasePrintHook));
    sqstd_compiler_error.Hook(WRAPPED_MEMBER(CompilerErrorHook));
    CreateNewVM.Hook(WRAPPED_MEMBER(CreateNewVMHook));
    //RunServerInitCallbacks.Hook(WRAPPED_MEMBER(RunServerInitCallbacksHook));
    if (IsClient()) RunClientInitCallbacks.Hook(WRAPPED_MEMBER(RunClientInitCallbacksHook));
    if (IsClient()) RunUIInitCallbacks.Hook(WRAPPED_MEMBER(RunUIInitCallbacksHook));
    FatalScriptError.Hook(FatalScriptError_Hook);

    // Add concommands to run server, client and UI code
    ConCommandManager& conCommandManager = SDK().GetConCommandManager();
    //conCommandManager.RegisterCommand("script_server", WRAPPED_MEMBER(RunServerCommand), "Execute Squirrel code in server context", 0);
    //conCommandManager.RegisterCommand("script", WRAPPED_MEMBER(RunServerCommand), "Execute Squirrel code in server context", 0); // this is what devmenu uses // TODO: think if we should leave that in
    if (IsClient()) conCommandManager.RegisterCommand("script_client", WRAPPED_MEMBER(RunClientCommand), "Execute Squirrel code in client context", 0);
    if (IsClient()) conCommandManager.RegisterCommand("script_ui", WRAPPED_MEMBER(RunUICommand), "Execute Squirrel code in UI context", 0);

    AddFuncRegistration(SCRIPT_CONTEXT_UI, "SquirrelNativeFunctionTest", WRAPPED_MEMBER(SquirrelNativeFunctionTest), ".sifb", 0, "string", "string text, int a2, float a3, bool a4", "Test registering and calling native function in Squirrel.");
    AddFuncRegistrationAllContexts("TraceLog_Internal", WRAPPED_MEMBER(TraceLog), ".s", 0, "void", "string text", "Log to trace log. Might not work in all compilations.");
    //AddFuncRegistrationAllContexts("IsDedi", WRAPPED_MEMBER(IsDedi_Script), ".", 0, "bool", "", "Is running a dedicated server.");
    //AddFuncRegistrationAllContexts("IsClient_Native", WRAPPED_MEMBER(IsClient_Script), ".", 0, "bool", "", "Is running in a client game rather than a dedicated server, regardless of script execution context.");
    AddFuncRegistration(SCRIPT_CONTEXT_CLIENT, "TranslateTokenToUTF8", WRAPPED_MEMBER(TranslateTokenToUTF8), ".s", 0, "string", "string text", "");
}

SQInteger SquirrelManager::BasePrintHook(HSQUIRRELVM v)
{
    static auto printFuncLambda = [](HSQUIRRELVM v, const SQChar* s, ...) {
        va_list vl;
        va_start(vl, s);
        ScriptContext context = (ScriptContext)-1;
        auto sqmg = SQManager();
        if (sqmg.m_ppClientVM != nullptr && *sqmg.m_ppClientVM != nullptr && (v == (*sqmg.m_ppClientVM)->sqvm || (_ss(v) == _ss((*sqmg.m_ppClientVM)->sqvm)))) context = SCRIPT_CONTEXT_CLIENT;
        else if (sqmg.m_ppUIVM != nullptr && *sqmg.m_ppUIVM != nullptr && (v == (*sqmg.m_ppUIVM)->sqvm || (_ss(v) == _ss((*sqmg.m_ppUIVM)->sqvm)))) context = SCRIPT_CONTEXT_UI;
        //else if (sqmg.m_ppServerVM != nullptr && *sqmg.m_ppServerVM != nullptr && (v == (*sqmg.m_ppServerVM)->sqvm || (_ss(v) == _ss((*sqmg.m_ppServerVM)->sqvm)))) context = SCRIPT_CONTEXT_SERVER;
        sqmg.PrintFunc(v, Util::GetContextName(context), s, vl);
        va_end(vl);
    };

    SQPRINTFUNCTION oldPrintFunc = _ss(v)->_printfunc;
    _ss(v)->_printfunc = printFuncLambda;
    base_print(v);
    _ss(v)->_printfunc = oldPrintFunc;
    SQInteger res = base_print(v);

    return res;
}

void SquirrelManager::PrintFunc(HSQUIRRELVM v, const SQChar* source, const SQChar* s, va_list args)
{
    SQChar buf[1024];

    int charactersWritten = _vsnprintf_s(buf, _TRUNCATE, s, args);
    if (charactersWritten > 0)
    {
        if (buf[charactersWritten - 1] == '\n')
        {
            buf[charactersWritten - 1] = 0;
        }

        m_logger->info("[sq] {}: {}", source, buf);
    }
}

HSQUIRRELVM SquirrelManager::GetServerSQVM()
{
    if (m_ppServerVM != nullptr && *m_ppServerVM != nullptr)
    {
        return (*m_ppServerVM)->sqvm;
    }

    return nullptr;
}

HSQUIRRELVM SquirrelManager::GetClientSQVM()
{
    if (m_ppClientVM != nullptr && *m_ppClientVM != nullptr)
    {
        return (*m_ppClientVM)->sqvm;
    }

    return nullptr;
}

HSQUIRRELVM SquirrelManager::GetUISQVM()
{
    if (m_ppUIVM != nullptr && *m_ppUIVM != nullptr)
    {
        return (*m_ppUIVM)->sqvm;
    }

    return nullptr;
}

const char* SquirrelManager::GetContextNameFromHSQUIRRELVMPointer(HSQUIRRELVM v)
{
    ScriptContext context = (ScriptContext)-1;
    if (m_ppClientVM != nullptr && *m_ppClientVM != nullptr && (v == (*m_ppClientVM)->sqvm || (_ss(v) == _ss((*m_ppClientVM)->sqvm)))) context = SCRIPT_CONTEXT_CLIENT;
    else if (m_ppUIVM != nullptr && *m_ppUIVM != nullptr && (v == (*m_ppUIVM)->sqvm || (_ss(v) == _ss((*m_ppUIVM)->sqvm)))) context = SCRIPT_CONTEXT_UI;
    //else if (m_ppServerVM != nullptr && *m_ppServerVM != nullptr && (v == (*m_ppServerVM)->sqvm || (_ss(v) == _ss((*m_ppServerVM)->sqvm)))) context = SCRIPT_CONTEXT_SERVER;
    return Util::GetContextName(context);
}

void SquirrelManager::CompilerErrorHook(HSQUIRRELVM v, const SQChar* sErr, const SQChar* sSource, SQInteger line, SQInteger column)
{
    m_logger->error("{} SCRIPT COMPILE ERROR", GetContextNameFromHSQUIRRELVMPointer(v));
    m_logger->error("{} line = ({}) column = ({}) error = {}", sSource, line, column, sErr);
    sqstd_compiler_error(v, sErr, sSource, line, column); // this will populate some buffers and report error to the engine (and that in turn disconnect from the server)
}

void SquirrelManager::RunServerCommand(const CCommand& args)
{
    ExecuteCode<SCRIPT_CONTEXT_SERVER>(args.ArgS());
}

void SquirrelManager::RunClientCommand(const CCommand& args)
{
    ExecuteCode<SCRIPT_CONTEXT_CLIENT>(args.ArgS());
}

void SquirrelManager::RunUICommand(const CCommand& args)
{
    ExecuteCode<SCRIPT_CONTEXT_UI>(args.ArgS());
}

void SquirrelManager::ExecuteServerCode(const char* code)
{
    ExecuteCode<SCRIPT_CONTEXT_SERVER>(code);
}

void SquirrelManager::ExecuteClientCode(const char* code)
{
    ExecuteCode<SCRIPT_CONTEXT_CLIENT>(code);
}

void SquirrelManager::ExecuteUICode(const char* code)
{
    ExecuteCode<SCRIPT_CONTEXT_UI>(code);
}

void SquirrelManager::AddFuncRegistration(
    ScriptContext context,
    const std::string& name,
    SQFUNCTION func,
    const std::string& szTypeMask,
    int nParamsCheck,
    const std::string& returnType,
    const std::string& argNames,
    const std::string& helpText
)
{
    m_funcsToRegister.emplace_back(context, name, func, szTypeMask, nParamsCheck, returnType, argNames, helpText);
}

void SquirrelManager::AddFuncRegistrationAllContexts(
    const std::string& name,
    SQFUNCTION func,
    const std::string& szTypeMask,
    int nParamsCheck,
    const std::string& returnType,
    const std::string& argNames,
    const std::string& helpText
)
{
    //AddFuncRegistration(SCRIPT_CONTEXT_SERVER, name, func, szTypeMask, nParamsCheck, returnType, argNames, helpText);
    AddFuncRegistration(SCRIPT_CONTEXT_CLIENT, name, func, szTypeMask, nParamsCheck, returnType, argNames, helpText);
    AddFuncRegistration(SCRIPT_CONTEXT_UI, name, func, szTypeMask, nParamsCheck, returnType, argNames, helpText);
}

/*int64_t SquirrelManager::RunServerInitCallbacksHook(int64_t a1)
{
    int64_t result = RunServerInitCallbacks(a1);
    SPDLOG_LOGGER_DEBUG(m_logger, "RunServerInitCallbacks called ({})", (void*)result);
    for (const auto& cb : m_serverCallbacks)
    {
        SPDLOG_LOGGER_DEBUG(m_logger, "Executing server callback {}", cb);
        //RunCallback.CallServer(*m_ppServerVM, cb.c_str());
        RunCallback(*m_ppServerVM, cb.c_str());
    }
    return result;
}*/

int64_t SquirrelManager::RunClientInitCallbacksHook(int64_t a1)
{
    int64_t result = RunClientInitCallbacks(a1);
    SPDLOG_LOGGER_DEBUG(m_logger, "RunClientInitCallbacks called ({})", (void*)result);
    for (const auto& cb : m_clientCallbacks)
    {
        SPDLOG_LOGGER_DEBUG(m_logger, "Executing client callback {}", cb);
        //RunCallback.CallClient(*m_ppClientVM, cb.c_str());
        RunCallback(*m_ppClientVM, cb.c_str());
    }
    return result;
}

char SquirrelManager::RunUIInitCallbacksHook(__int64 a1, __int64 a2)
{
    char result = RunUIInitCallbacks(a1, a2);
    SPDLOG_LOGGER_DEBUG(m_logger, "RunUIInitCallbacks called ({})", (void*)result);
    for (const auto& cb : m_uiCallbacks)
    {
        SPDLOG_LOGGER_DEBUG(m_logger, "Executing UI callback {}", cb);
        RunCallback(*m_ppUIVM, cb.c_str());
    }
    return result;
}

void SquirrelManager::AddServerCallback(const std::string& cb)
{
    m_serverCallbacks.push_back(cb);
}

void SquirrelManager::AddClientCallback(const std::string& cb)
{
    m_clientCallbacks.push_back(cb);
}

void SquirrelManager::AddUICallback(const std::string& cb)
{
    m_uiCallbacks.push_back(cb);
}

void SquirrelManager::ClearCallbacks()
{
    m_serverCallbacks.clear();
    m_clientCallbacks.clear();
    m_uiCallbacks.clear();
}

template<ScriptContext context>
void SquirrelManager::ExecuteCode(const char* code)
{
    if (!ThreadInMainThread())
    {
        m_logger->debug("Delaying execution into main thread: {}", code);
        std::string strCode(code);
        SDK().AddDelayedFunc([this, strCode]() {
            this->ExecuteCode<context>(strCode.c_str());
            }, 0);
        return;
    }

    HSQUIRRELVM v = nullptr;
    switch (context) {
    case SCRIPT_CONTEXT_SERVER: v = GetServerSQVM(); break;
    case SCRIPT_CONTEXT_CLIENT: v = GetClientSQVM(); break;
    case SCRIPT_CONTEXT_UI: v = GetUISQVM(); break;
    }

    if (v != nullptr)
    {
        std::string strCode(code);
        if (strCode.length() > INT_MAX)
        {
            m_logger->error("Code to execute too big (seriously who the fuck would execute something over 4 GB in size?)");
            return;
        }
        m_logger->info("Executing {} code: {}", Util::GetContextName(context), strCode);
        SQRESULT compileRes = sq_compilebuffer(v, strCode.c_str(), static_cast<SQInteger>(strCode.length()), "console", 1);
        SPDLOG_LOGGER_DEBUG(m_logger, "sq_compilebuffer returned {}", compileRes);
        if (SQ_SUCCEEDED(compileRes))
        {
            base_getroottable(v);
            SQRESULT callRes = sq_call(v, 1, SQFalse, SQFalse);
            SPDLOG_LOGGER_DEBUG(m_logger, "sq_call returned {}", callRes);
        }
    }
    else
    {
        m_logger->error("Cannot execute {} code, no handle to Squirrel VM for context", Util::GetContextName(context));
    }
}

void SquirrelManager::RegisterFunction(R1SquirrelVM* vm, SQFuncRegistration& reg)
{
    AddSquirrelReg(vm, reg.GetInternalReg());
}

R1SquirrelVM* SquirrelManager::CreateNewVMHook(int64_t a1, int always_2, ScriptContext context)
{
    R1SquirrelVM* vm = CreateNewVM(a1, always_2, context);
    SPDLOG_LOGGER_DEBUG(m_logger, "CreateNewVM ({}): {}", Util::GetContextName(context), (void*)vm);
    for (auto& reg : m_funcsToRegister)
    {
        if (reg.GetContext() == context)
        {
            RegisterFunction(vm, reg);
            SPDLOG_LOGGER_DEBUG(m_logger, "Registered {} in {} context", reg.GetName(), Util::GetContextName(context));
        }
    }
    return vm;
}

SQInteger SquirrelManager::SquirrelNativeFunctionTest(HSQUIRRELVM v)
{
    const SQChar* str;
    sq_getstring(v, 2, &str);
    SQInteger integer;
    sq_getinteger(NULL, v, 3, &integer);
    SQFloat fl;
    sq_getfloat(NULL, v, 4, &fl);
    SQBool bo;
    sq_getbool(NULL, v, 5, &bo);

    SPDLOG_LOGGER_TRACE(m_logger, "[sq] SquirrelNativeFunctionTest native: {} {} {} {}", str, integer, fl, bo);

    sq_pushstring(v, "from native", -1);
    return 1;
}

SQInteger SquirrelManager::TraceLog(HSQUIRRELVM v)
{
    const SQChar* str;
    sq_getstring(v, 2, &str);
    SPDLOG_LOGGER_TRACE(m_logger, "[sq] {}", str);
    return 1;
}

SQInteger SquirrelManager::IsDedi_Script(HSQUIRRELVM v)
{
    sq_pushbool(nullptr, v, IsDedi());
    return 1;
}

SQInteger SquirrelManager::IsClient_Script(HSQUIRRELVM v)
{
    sq_pushbool(nullptr, v, IsClient());
    return 1;
}

SQInteger SquirrelManager::TranslateTokenToUTF8(HSQUIRRELVM v)
{
    const SQChar* str;
    sq_getstring(v, 2, &str);
    auto sub_1802DBEA0 = reinterpret_cast<const char* (*)(const char*)>(Util::GetModuleBaseAddress("client.dll") + 0x2DBEA0);
    sq_pushstring(v, sub_1802DBEA0(str), -1);
    return 1;
}
