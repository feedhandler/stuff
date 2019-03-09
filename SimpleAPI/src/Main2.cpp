// Convert a C callback into a C++ callback

#include "Utils.h"
#include "SimpleAPI.h"
#include "Wrapper.h"

#include <log4cpp/Category.hh>

#include <chrono>
#include <thread>

using namespace std;

// the C callback function
static void c_callback(int id, void *user_p)
{
  log4cpp::Category::getInstance(__FUNCTION__).noticeStream() << "Got " << id;
}

// derived class, to make demonstrate that we call the override correctly
class FancyWrapper: public Wrapper
{
public:
  FancyWrapper(std::string name)
    : Wrapper(name)
    {}
    
  virtual void async_callback(int id) override
  {
    mLogger.noticeStream() << " GOT " << id;
  }
};

int main(int argc, char* argv[])
{
  initializeLogging();

  auto& logger = log4cpp::Category::getInstance("main");

  // C-style callback
  CallbackFuncInfo callbackFuncInfo;
  callbackFuncInfo.user_p = nullptr;
  callbackFuncInfo.callback_p = c_callback;
  sessionCreate(&callbackFuncInfo);
  
  // C++ callbacks
  Wrapper wrapper("alice");
  FancyWrapper fancyWrapper("bob");
  
  logger.notice("start");
  simpleStart();
  
  this_thread::sleep_for(10s);
  
  logger.notice("stop");
  simpleStop();
  
  this_thread::sleep_for(1500ms);
  logger.notice("finished");
}
