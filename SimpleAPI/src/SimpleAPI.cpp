#include "SimpleAPI.h"

#include <chrono>
#include <thread>
#include <map>
#include <mutex>

using namespace std;

// storage for handlers registered with the API
struct Handler
{
  simple_callback callback;
  void *closure;
};
map<int,Handler> handlers;

int handle=-1;

std::mutex handlersMutex;

int simple_register(simple_callback callback, void* closure)
{
  std::lock_guard<std::mutex> lck(handlersMutex);

  handle++;
  handlers[handle]={callback, closure};
  return handle;
}

void simple_unregister(int handle)
{
  std::lock_guard<std::mutex> lck(handlersMutex);
  
  handlers.erase(handle);
}

bool run = false;

void simple_start()
{
  run = true;
  
  // to simulate event dispatching from a messaging API, we start a
  // thread here and iterate through the registered callback 
  // handlers, passing a different integer each time
  thread([](){
    int i=0;
    while(run)
    {
      {
        std::lock_guard<std::mutex> lck(handlersMutex);
        for(auto& kv: handlers)
        {
          auto& handler(kv.second);
          handler.callback(i, handler.closure);
        }
      }
      this_thread::sleep_for(1s);
      i++;
    }
  }).detach();
}

void simple_stop()
{
  run = false;
}
