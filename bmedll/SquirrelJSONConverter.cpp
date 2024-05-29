#include "pch.h"
#include "SquirrelManager.h"
#include "SquirrelJSONConverter.h"

SQRESULT SquirrelJSONConverter::PullSquirrelValue(HSQUIRRELVM v, SQInteger i, rapidjson::Value& target, rapidjson::Document::AllocatorType& alloc)
{
    auto type = sq_gettype(v, i);
    switch (type)
    {
    case OT_NULL:
    {
        target.SetNull();
        return SQ_OK;
    }
    case OT_BOOL:
    {
        SQBool p;
        if (!SQ_SUCCEEDED(sq_getbool(nullptr, v, i, &p)))
            break;
        target.SetBool(p);
        return SQ_OK;
    }
    case OT_INTEGER:
    {
        SQInteger sqint;
        if (!SQ_SUCCEEDED(sq_getinteger(nullptr, v, i, &sqint)))
            break;
        target.SetInt(sqint);
        return SQ_OK;
    }
    case OT_FLOAT:
    {
        SQFloat sqfl;
        if (!SQ_SUCCEEDED(sq_getfloat(nullptr, v, i, &sqfl)))
            break;
        target.SetFloat(sqfl);
        return SQ_OK;
    }
    case OT_STRING:
    {
        const SQChar* sqstr;
        if (!SQ_SUCCEEDED(sq_getstring(v, i, &sqstr)))
            break;
        SQInteger allocated = sq_getsize(nullptr, v, i);
        target.SetString(sqstr, allocated, alloc);
        return SQ_OK;
    }
    case OT_ARRAY:
    {
        target.SetArray();
        sq_pushnull(v); // null iterator
        while (SQ_SUCCEEDED(sq_next(v, i < 0 ? i - 1 : i)))
        {
            rapidjson::Value elem;

            // here -1 is the value and -2 is the key
            // we ignore the key, since that is just the index in an array
            if (!SQ_SUCCEEDED(PullSquirrelValue(v, -1, elem, alloc)))
                return SQ_ERROR;

            target.PushBack(elem.Move(), alloc);
            SQVM_Pop(v, 2); // pops key and val before the next iteration
        }
        sq_poptop(v); // pops the iterator
        return SQ_OK;
    }
    case OT_TABLE:
    {
        target.SetObject();
        sq_pushnull(v); // null iterator
        while (SQ_SUCCEEDED(sq_next(v, i < 0 ? i - 1 : i)))
        {
            rapidjson::Value elem;

            // here -1 is the value and -2 is the key

            // key
            const SQChar* sqstr;
            if (!SQ_SUCCEEDED(sq_getstring(v, -2, &sqstr)))
            {
                target.SetNull();
                spdlog::error("failed getting squirrel key for object in table (key type {})", IdType2Name(sq_gettype(v, -2)));
                SQVM_Raise_Error(v, "failed getting squirrel key for object in table (key type %s)", IdType2Name(sq_gettype(v, -2))); // TODO
                return SQ_ERROR;
            }
            SQInteger allocated = sq_getsize(nullptr, v, -2);
            rapidjson::Value obj_key{ sqstr, static_cast<rapidjson::SizeType>(allocated), alloc };

            // value
            rapidjson::Value obj_value;
            PullSquirrelValue(v, -1, obj_value, alloc);

            target.AddMember(obj_key.Move(), obj_value.Move(), alloc);
            SQVM_Pop(v, 2); // pops key and val before the next iteration
        }
        sq_poptop(v); // pops the iterator
        return SQ_OK;
    }
    case OT_USERDATA:
    case OT_INSTANCE:
    {
        const SQChar* sqstr;
        if (SQ_SUCCEEDED(sq_getstring(v, i, &sqstr)))
        {
            SQInteger allocated = sq_getsize(nullptr, v, i);
            target.SetString(sqstr, allocated, alloc);
            return SQ_OK;
        }
        [[fallthrough]]; // could not be represented as a string (no tostring metamethod was defined)
    }
    default:
        target.SetNull();
        spdlog::warn("[SquirrelJSONConverter::PushSquirrelValue] Unsupported Squirrel value type that cannot be represented in JSON: {}", IdType2Name(type));
        return SQ_OK;
    }
    target.SetNull();
    spdlog::error("[SquirrelJSONConverter::PushSquirrelValue] failed getting squirrel value (type {})", IdType2Name(type));
    SQVM_Raise_Error(v, "failed getting squirrel value (type %s)", IdType2Name(type));
    return SQ_ERROR;
}

SQRESULT ToJSON_Script(HSQUIRRELVM v)
{
    // example: script print(ToJSON({ bbb = [1,2,"yy", { aaaau = "1524" , b=[], c={}, d=1,e=null}, {}, [], null], aaaa = "fdsf"}))

    if (sq_gettop(nullptr, v) != 2)
    {
        SQVM_Raise_Error(v, "wrong number of parameters");
        return SQ_ERROR;
    }

    rapidjson::Document document;
    SquirrelJSONConverter::PullSquirrelValue(v, -1, document, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    sq_pushstring(v, buffer.GetString(), static_cast<SQInteger>(buffer.GetLength()));

    return 1;
}

void SquirrelJSONConverter::RegisterFunctions(SquirrelManager& sqManager)
{
    sqManager.AddFuncRegistrationAllContexts("ToJSON", ToJSON_Script, "..", 0, "string", "void input", "Convert to Squirrel object to JSON string.");
}
