// Example of using the SimpleAPI with C callbacks

#include "Utils.h"
#include "SimpleAPI.h"

#include "spdlog/spdlog.h"

#include <chrono>
#include <thread>

using namespace std;

// C callback functions
static void c_1(int id, void *user_p)
{
  spdlog::info("{} got {}", __FUNCTION__, id);
}

static void c_2(int id, void *user_p)
{
  spdlog::info("{} got {}", __FUNCTION__, id);
}

int main(int argc, char* argv[])
{
  initializeLogging();

  // C-style callbacks
  simple_register(c_1, nullptr);
  simple_register(c_2, nullptr);
  
  spdlog::info("start");
  simple_start();
  
  this_thread::sleep_for(10s);
  
  spdlog::info("stop");
  simple_stop();
  
  this_thread::sleep_for(2s);
  spdlog::info("finished");
}
