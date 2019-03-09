#include "SimpleAPI.h"

#include <chrono>
#include <thread>
#include <vector>

using namespace std;

// storage for the callback handlers
vector<CallbackFuncInfo> callbackFuncInfos;

bool stop = false;

void sessionCreate(CallbackFuncInfo* funcInfo_p)
{
  callbackFuncInfos.push_back(*funcInfo_p);
}

void simpleStart()
{
  stop = false;
  
  // to simulate event dispatching from a messaging API, we start a
  // thread here and iterate through the registered callback 
  // handlers, passing a different integer each time
  thread([](){
    int i=0;
    while(!stop)
    {
      for(auto& cfi: callbackFuncInfos)
        cfi.callback_p(++i, cfi.user_p);
      this_thread::sleep_for(1s);
    }
  }).detach();
}

void simpleStop()
{
  stop = true;
}
