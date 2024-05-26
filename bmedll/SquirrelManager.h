#pragma once
#include "pch.h"
#include "Util.h"
#include "ConCommandManager.h"
#include "SigScanning.h"

#define SQ_SUCCEEDED(res) (res>=0)

#define SQTrue	(1)
#define SQFalse	(0)

typedef float SQFloat;
typedef long SQInteger;
typedef unsigned long SQUnsignedInteger;
typedef unsigned long SQHash;
typedef char SQChar;

typedef void* SQUserPointer;
typedef SQUnsignedInteger SQBool;
typedef SQInteger SQRESULT;

typedef struct SQVM* HSQUIRRELVM;
typedef void(*SQPRINTFUNCTION)(HSQUIRRELVM, const SQChar*, ...);
typedef SQInteger(*SQFUNCTION)(HSQUIRRELVM);

typedef SQInteger(*SQLEXREADFUNC)(SQUserPointer);

struct BufState {
	const SQChar* buf;
	SQInteger ptr;
	SQInteger size;
};

#pragma pack(push,1)
struct SQSharedState
{
	unsigned char unknownData[0x4158];
	SQPRINTFUNCTION _printfunc;
};

struct SQVM
{
	unsigned char unknownData[0xE8];
	SQSharedState* _sharedstate;
};
#pragma pack(pop)

#define _ss(_vm_) (_vm_)->_sharedstate

///////////////////////////////////////////////////////////////////////////////////////

typedef SQUnsignedInteger SQRawObjectVal;
#define SQ_OBJECT_RAWINIT()

#define SQOBJECT_REF_COUNTED	0x08000000
#define SQOBJECT_NUMERIC		0x04000000
#define SQOBJECT_DELEGABLE		0x02000000
#define SQOBJECT_CANBEFALSE		0x01000000

#define SQ_MATCHTYPEMASKSTRING (-99999)

#define _RT_MASK 0x00FFFFFF
#define _RAW_TYPE(type) (type&_RT_MASK)

#define _RT_NULL			0x00000001
#define _RT_INTEGER			0x00000002
#define _RT_FLOAT			0x00000004
#define _RT_BOOL			0x00000008
#define _RT_STRING			0x00000010
#define _RT_TABLE			0x00000020
#define _RT_ARRAY			0x00000040
#define _RT_USERDATA		0x00000080
#define _RT_CLOSURE			0x00000100
#define _RT_NATIVECLOSURE	0x00000200
#define _RT_GENERATOR		0x00000400
#define _RT_USERPOINTER		0x00000800
#define _RT_THREAD			0x00001000
#define _RT_FUNCPROTO		0x00002000
#define _RT_CLASS			0x00004000
#define _RT_INSTANCE		0x00008000
#define _RT_WEAKREF			0x00010000

#define ISREFCOUNTED(t) (t&SQOBJECT_REF_COUNTED)

typedef enum tagSQObjectType {
	OT_NULL = (_RT_NULL | SQOBJECT_CANBEFALSE),
	OT_INTEGER = (_RT_INTEGER | SQOBJECT_NUMERIC | SQOBJECT_CANBEFALSE),
	OT_FLOAT = (_RT_FLOAT | SQOBJECT_NUMERIC | SQOBJECT_CANBEFALSE),
	OT_BOOL = (_RT_BOOL | SQOBJECT_CANBEFALSE),
	OT_STRING = (_RT_STRING | SQOBJECT_REF_COUNTED),
	OT_TABLE = (_RT_TABLE | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
	OT_ARRAY = (_RT_ARRAY | SQOBJECT_REF_COUNTED),
	OT_USERDATA = (_RT_USERDATA | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
	OT_CLOSURE = (_RT_CLOSURE | SQOBJECT_REF_COUNTED),
	OT_NATIVECLOSURE = (_RT_NATIVECLOSURE | SQOBJECT_REF_COUNTED),
	OT_GENERATOR = (_RT_GENERATOR | SQOBJECT_REF_COUNTED),
	OT_USERPOINTER = _RT_USERPOINTER,
	OT_THREAD = (_RT_THREAD | SQOBJECT_REF_COUNTED),
	OT_FUNCPROTO = (_RT_FUNCPROTO | SQOBJECT_REF_COUNTED), //internal usage only
	OT_CLASS = (_RT_CLASS | SQOBJECT_REF_COUNTED),
	OT_INSTANCE = (_RT_INSTANCE | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
	OT_WEAKREF = (_RT_WEAKREF | SQOBJECT_REF_COUNTED)
} SQObjectType;

typedef union tagSQObjectValue // dunno?
{
	struct SQTable* pTable;
	struct SQArray* pArray;
	struct SQClosure* pClosure;
	struct SQGenerator* pGenerator;
	struct SQNativeClosure* pNativeClosure;
	struct SQString* pString;
	struct SQUserData* pUserData;
	SQInteger nInteger;
	SQFloat fFloat;
	SQUserPointer pUserPointer;
	struct SQFunctionProto* pFunctionProto;
	struct SQRefCounted* pRefCounted;
	struct SQDelegable* pDelegable;
	struct SQVM* pThread;
	struct SQClass* pClass;
	struct SQInstance* pInstance;
	struct SQWeakRef* pWeakRef;
	SQRawObjectVal raw;
} SQObjectValue;
//typedef tagSQObjectValue SQObjectValue; // not sure if we need this

typedef struct tagSQObject
{
	SQObjectType _type;
	SQObjectValue _unVal;
} SQObject;

typedef tagSQObject SQObject;

// TODO: do we need this? if not, delet
/*struct SQRefCounted
{
	SQRefCounted() { _uiRef = 0; _weakref = NULL; }
	virtual ~SQRefCounted();
	SQWeakRef* GetWeakRef(SQObjectType type);
	SQUnsignedInteger _uiRef;
	struct SQWeakRef* _weakref;
	virtual void Release() = 0;
};
struct SQWeakRef : SQRefCounted
{
	void Release();
	SQObject _obj;
};*/

////

// UTILITY MACRO
#define sq_isnumeric(o) ((o)._type&SQOBJECT_NUMERIC)
#define sq_istable(o) ((o)._type==OT_TABLE)
#define sq_isarray(o) ((o)._type==OT_ARRAY)
#define sq_isfunction(o) ((o)._type==OT_FUNCPROTO)
#define sq_isclosure(o) ((o)._type==OT_CLOSURE)
#define sq_isgenerator(o) ((o)._type==OT_GENERATOR)
#define sq_isnativeclosure(o) ((o)._type==OT_NATIVECLOSURE)
#define sq_isstring(o) ((o)._type==OT_STRING)
#define sq_isinteger(o) ((o)._type==OT_INTEGER)
#define sq_isfloat(o) ((o)._type==OT_FLOAT)
#define sq_isuserpointer(o) ((o)._type==OT_USERPOINTER)
#define sq_isuserdata(o) ((o)._type==OT_USERDATA)
#define sq_isthread(o) ((o)._type==OT_THREAD)
#define sq_isnull(o) ((o)._type==OT_NULL)
#define sq_isclass(o) ((o)._type==OT_CLASS)
#define sq_isinstance(o) ((o)._type==OT_INSTANCE)
#define sq_isbool(o) ((o)._type==OT_BOOL)
#define sq_isweakref(o) ((o)._type==OT_WEAKREF)
#define sq_type(o) ((o)._type)

#define SQ_OK (0)
#define SQ_ERROR (-1)

#define SQ_FAILED(res) (res<0)
#define SQ_SUCCEEDED(res) (res>=0)

///////////////////////////////////////////////////////////////////////////////////////

struct R1SquirrelVM
{
	unsigned char vtbl[8];
	HSQUIRRELVM sqvm;
};

struct SQFuncRegistrationInternal {
	const char* squirrelFuncName; //0x0000 
	const char* cppFuncName; //0x0008 
	const char* helpText; //0x0010 

	// stuff for flags&2
	// first parameter here is "this", params counter includes it
	// nparamscheck 0 = don't check params, number = check for exact number of params, -number = check for at least abs(number) params
	// . = any; o = null (?); i = integer; f = float; n = integer or float; s = string; t = table; a = array; u = userdata; c = closure/nativeclosure; g = generator; p = userpointer; v = thread; x = class instance; y = class; b = bool
	// at least those are supported for sure: nxbs. (number, instance, boolean, string, any)
	// [untested] #define SQ_MATCHTYPEMASKSTRING (-99999) = If SQ_MATCHTYPEMASKSTRING is passed instead of the number of parameters, the function will automatically extrapolate the number of parameters to check from the typemask(eg. if the typemask is ”.sn” is like passing 3).
	const char* szTypeMask; //0x0018 can be: .s, .ss., .., ..  
	__int64 nparamscheck_probably; //0x0020 can be: 2, -3, 2, 0  

	const char* returnValueTypeText; //0x0028 
	const char* argNamesText; //0x0030 

	__int64 UnkSeemsToAlwaysBe32; //0x0038 
	char pad_0x0040[0x20]; //0x0040 // CUtlVector of parameter types, can't be arsed to reverse this
	void* pfnBinding; //0x0068 
	void* pFunction; //0x0070 
	__int64 flags; //0x0078 // if it's 2, then the CUtlVector mentioned above will not be used

	SQFuncRegistrationInternal()
	{
		memset(this, 0, sizeof(SQFuncRegistrationInternal));
		this->UnkSeemsToAlwaysBe32 = 32;
	}
};

__int64 __fastcall SQFuncBindingFn(__int64(__fastcall* a1)(_QWORD), __int64 a2, _QWORD* a3, __int64 a4, __int64 a5);

class SQFuncRegistration
{
public:
	SQFuncRegistration(
		ScriptContext context,
		const std::string& name,
		SQFUNCTION funcPtr,
		const std::string& szTypeMask,
		int nParamsCheck,
		const std::string& returnType,
		const std::string& argNames,
		const std::string& helpText
	) :
		m_context(context),
		m_funcName(name),
		m_szTypeMask(szTypeMask),
		m_retValueType(returnType),
		m_argNames(argNames),
		m_helpText(helpText)
	{
		m_internalReg.squirrelFuncName = m_internalReg.cppFuncName = m_funcName.c_str();
		m_internalReg.helpText = m_helpText.c_str();
		m_internalReg.szTypeMask = m_szTypeMask.c_str();
		m_internalReg.nparamscheck_probably = nParamsCheck;
		m_internalReg.returnValueTypeText = m_retValueType.c_str();
		m_internalReg.argNamesText = m_argNames.c_str();
		m_internalReg.pfnBinding = SQFuncBindingFn;
		m_internalReg.pFunction = funcPtr;
		m_internalReg.flags = 2;
	}

	ScriptContext GetContext() const
	{
		return m_context;
	}

	SQFuncRegistrationInternal* GetInternalReg()
	{
		return &m_internalReg;
	}

	const std::string& GetName() const
	{
		return m_funcName;
	}

private:
	ScriptContext m_context;
	std::string m_funcName;
	std::string m_helpText;
	std::string m_szTypeMask;
	std::string m_retValueType;
	std::string m_argNames;
	SQFuncRegistrationInternal m_internalReg;
};

class SquirrelManager
{
public:
	R1SquirrelVM** m_ppServerVM = nullptr;
	R1SquirrelVM** m_ppClientVM = nullptr;
	R1SquirrelVM** m_ppUIVM = nullptr;
private:
	std::shared_ptr<spdlog::logger> m_logger;
	std::list<SQFuncRegistration> m_funcsToRegister;
	std::vector<std::string> m_serverCallbacks;
	std::vector<std::string> m_clientCallbacks;
	std::vector<std::string> m_uiCallbacks;

public:
	SquirrelManager();

	SQInteger BasePrintHook(HSQUIRRELVM v);
	void PrintFunc(HSQUIRRELVM v, const SQChar* source, const SQChar* s, va_list args);

	HSQUIRRELVM GetServerSQVM();
	HSQUIRRELVM GetClientSQVM();
	HSQUIRRELVM GetUISQVM();

	const char* GetContextNameFromHSQUIRRELVMPointer(HSQUIRRELVM v);
	void CompilerErrorHook(HSQUIRRELVM v, const SQChar* sErr, const SQChar* sSource, SQInteger line, SQInteger column);

	void RunServerCommand(const CCommand& args);
	void RunClientCommand(const CCommand& args);
	void RunUICommand(const CCommand& args);

	template<ScriptContext context>
	void ExecuteCode(const char* code);
	void ExecuteServerCode(const char* code);
	void ExecuteClientCode(const char* code);
	void ExecuteUICode(const char* code);

	void RegisterFunction(R1SquirrelVM* vm, SQFuncRegistration& reg);

	void AddFuncRegistration(
		ScriptContext context,
		const std::string& name,
		SQFUNCTION func,
		const std::string& szTypeMask,
		int nParamsCheck,
		const std::string& returnType,
		const std::string& argNames,
		const std::string& helpText
	);
	void AddFuncRegistrationAllContexts(
		const std::string& name,
		SQFUNCTION func,
		const std::string& szTypeMask,
		int nParamsCheck,
		const std::string& returnType,
		const std::string& argNames,
		const std::string& helpText
	);

	R1SquirrelVM* CreateNewVMHook(int64_t a1, int always_2, ScriptContext context);

	//int64_t RunServerInitCallbacksHook(int64_t a1);
	int64_t RunClientInitCallbacksHook(int64_t a1);
	char RunUIInitCallbacksHook(__int64 a1, __int64 a2);

	void AddServerCallback(const std::string& cb);
	void AddClientCallback(const std::string& cb);
	void AddUICallback(const std::string& cb);
	void ClearCallbacks();

	SQInteger SquirrelNativeFunctionTest(HSQUIRRELVM v);
	SQInteger TraceLog(HSQUIRRELVM v);
	SQInteger IsDedi_Script(HSQUIRRELVM v);
	SQInteger IsClient_Script(HSQUIRRELVM v);
	SQInteger TranslateTokenToUTF8(HSQUIRRELVM v);
};

extern FuncStatic<SQRESULT, HSQUIRRELVM, SQLEXREADFUNC, SQUserPointer, const SQChar*, SQBool> sq_compile;
extern FuncStatic<__int64 __fastcall, HSQUIRRELVM> base_getroottable; // equivalent of sq_pushroottable
extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, SQBool, SQBool> sq_call;
extern HookedFuncStatic<void, HSQUIRRELVM, const SQChar*, const SQChar*, SQInteger, SQInteger> sqstd_compiler_error;
extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, SQBool> sq_newslot;
extern FuncStatic<void, HSQUIRRELVM, SQInteger> SQVM_Pop;
extern FuncStatic<void, HSQUIRRELVM, SQInteger> SQVM_Push;
extern FuncStatic<SQChar* __fastcall, SQObjectType> IdType2Name;

extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, const SQChar**> sq_getstring;
extern FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQInteger*> sq_getinteger; // R1SquirrelVM* unused
extern FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQFloat*> sq_getfloat; // R1SquirrelVM* unused
extern FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQBool*> sq_getbool; // R1SquirrelVM* unused
extern FuncStatic<void, HSQUIRRELVM> sq_pushnull;
extern FuncStatic<void, HSQUIRRELVM, const SQChar*, SQInteger> sq_pushstring;
extern FuncStatic<void, R1SquirrelVM*, HSQUIRRELVM, SQInteger> sq_pushinteger; // R1SquirrelVM* unused
extern FuncStatic<void, R1SquirrelVM*, HSQUIRRELVM, SQFloat> sq_pushfloat; // R1SquirrelVM* unused
extern FuncStatic<void, R1SquirrelVM*, HSQUIRRELVM, SQBool> sq_pushbool; // R1SquirrelVM* unused
extern FuncStatic<void, HSQUIRRELVM, SQInteger> sq_tostring;
extern FuncStatic<SQInteger, R1SquirrelVM*, HSQUIRRELVM, SQInteger> sq_getsize; // R1SquirrelVM* unused
//extern FuncStatic<SQObjectType, R1SquirrelVM*, HSQUIRRELVM, SQInteger> sq_gettype; // R1SquirrelVM* unused
extern FuncStatic<SQObjectType, HSQUIRRELVM, SQInteger> sq_gettype;
extern FuncStatic<SQRESULT, R1SquirrelVM*, HSQUIRRELVM, SQInteger, SQObject*> sq_getstackobj; // R1SquirrelVM* unused
extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_get;
extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_get_noerr;
extern FuncStatic<SQInteger, R1SquirrelVM*, HSQUIRRELVM> sq_gettop; // R1SquirrelVM* unused
extern FuncStatic<void, HSQUIRRELVM> sq_newtable;
extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_next;
extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger, SQUserPointer*, SQUserPointer> sq_getinstanceup;

extern FuncStatic<void, HSQUIRRELVM, SQInteger> sq_newarray;
extern FuncStatic<SQRESULT, HSQUIRRELVM, SQInteger> sq_arrayappend;
