#pragma once
#include "SquirrelManager.h"

namespace SquirrelJSONConverter
{
    SQRESULT PullSquirrelValue(HSQUIRRELVM v, SQInteger i, rapidjson::Value& target, rapidjson::Document::AllocatorType& alloc);

    void RegisterFunctions(SquirrelManager& sqManager);
}
