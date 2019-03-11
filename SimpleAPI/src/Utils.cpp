
#include "Utils.h"

#include "spdlog/spdlog.h"

void initializeLogging()
{
  spdlog::set_pattern("%H:%M:%S.%e %t %v");
}
