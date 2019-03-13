// Test multiple inhertiance

#include "Utils.h"
#include "SimpleAPI.h"
#include "Wrapper.h"

#include "spdlog/spdlog.h"

#include <chrono>
#include <thread>

using namespace std;

class Printer
{
public:
  void print(string name, int id)
  {
    spdlog::info("{} GOt {}", name, id);
  }
};

class FancyWrapper
  : public Printer
  , public Wrapper
{
public:
  FancyWrapper(std::string name)
    : Wrapper(name)
    {}
    
  virtual void async_callback(int id) override
  {
    print(mName, id);
  }
};


int main()
{
  initializeLogging();

  FancyWrapper fw("fancyWrapper");
  
  spdlog::info("start");
  simple_start();
  
  this_thread::sleep_for(4s);
  
  spdlog::info("stop");
  simple_stop();
  
  this_thread::sleep_for(1500ms);
  spdlog::info("finished");
}
