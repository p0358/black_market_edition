#pragma once

#define BME_VERSION "1b4"

#ifdef _DEBUG
#define BME_CHANNEL "dev"
#else
#ifdef STAGING
#define BME_CHANNEL "staging"
#else
#define BME_CHANNEL "production"
#endif
#endif
