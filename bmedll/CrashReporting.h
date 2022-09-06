#pragma once

#ifdef NDEBUG
#define SENTRY_BUILD_STATIC 1
#include "sentry.h"
#endif

bool SetupCrashHandler(std::wstring BasePath);
void UpdateSETranslator();