// This example shows two things how to convert a the C callback into a C++ callback

#include "Utils.h"
#include "SimpleAPI.h"
#include "Wrapper.h"

#include "spdlog/spdlog.h"

#include <chrono>
#include <thread>

using namespace std;

// the C callback function
static void c_callback(int id, void *user_p)
{
  spdlog::info("{} got {}", __FUNCTION__, id);
}

// derived classes, to make demonstrate that we call the overrides correctly
class FancyWrapper: public Wrapper
{
public:
  FancyWrapper(std::string name)
    : Wrapper(name)
    {}
    
  virtual void async_callback(int id) override
  {
    spdlog::info("{} GOt {}", mName, id);
  }
};

class SuperFancyWrapper: public FancyWrapper
{
public:
  SuperFancyWrapper(std::string name)
    : FancyWrapper(name)
    {}
    
  virtual void async_callback(int id) override
  {
    spdlog::info("{} GOT {}", mName, id);
  }
};


int main(int argc, char* argv[])
{
  initializeLogging();

  // C-style callback
  simple_register(c_callback, nullptr);
  
  // C++ callbacks
  Wrapper w1("wrapper");
  FancyWrapper w2("fancyWrapper");
  SuperFancyWrapper w3("superFancyWrapper");
  
  spdlog::info("start");
  simple_start();
  
  this_thread::sleep_for(5s);
  
  spdlog::info("stop");
  simple_stop();
  
  this_thread::sleep_for(1500ms);
  spdlog::info("finished");
}
