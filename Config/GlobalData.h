#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "SystemConfig.h"

static SystemConfig global_system_config;
SystemConfig& GetSystemConfig();


#endif // GLOBALDATA_H
