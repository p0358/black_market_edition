#pragma once

#define SENTRY_BUILD_STATIC 1
#include "sentry.h"

bool SetupCrashHandler(std::wstring BasePath);
void UpdateSETranslator();