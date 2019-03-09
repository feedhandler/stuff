// using the API will C callbacks

#include "Utils.h"
#include "SimpleAPI.h"

#include <log4cpp/Category.hh>

#include <chrono>
#include <thread>

using namespace std;

// C callback functions
static void c_1(int id, void *user_p)
{
  int delta = 1;
  log4cpp::Category::getInstance(__FUNCTION__).noticeStream() << id << " plus " << delta << " = " << (id + delta);
}

static void c_2(int id, void *user_p)
{
  int delta = 2;
  log4cpp::Category::getInstance(__FUNCTION__).noticeStream() << id << " plus " << delta << " = " << (id + delta);
}

int main(int argc, char* argv[])
{
  initializeLogging();

  auto& logger = log4cpp::Category::getInstance("main");

  // C-style callback
  CallbackFuncInfo callbackFuncInfo;
  callbackFuncInfo.user_p = nullptr;

  callbackFuncInfo.callback_p = c_1;
  sessionCreate(&callbackFuncInfo);
  
  callbackFuncInfo.callback_p = c_2;
  sessionCreate(&callbackFuncInfo);
  
  logger.notice("start");
  simpleStart();
  
  this_thread::sleep_for(10s);
  
  logger.notice("stop");
  simpleStop();
  
  this_thread::sleep_for(2s);
  logger.notice("finished");
}
