#include "SimpleAPI.h"

#include <chrono>
#include <thread>
#include <vector>

using namespace std;

// storage for handlers registered with the API
struct Handler
{
  SimpleAPI::Callback callback;
  void *closure;
};
vector<Handler> handlers;

void SimpleAPI::registerHandler(SimpleAPI::Callback callback, void* closure)
{
  handlers.push_back({callback, closure});
}

bool run = false;

void SimpleAPI::start()
{
  run = true;
  
  // to simulate event dispatching from a messaging API, we start a
  // thread here and iterate through the registered callback 
  // handlers, passing a different integer each time
  thread([](){
    int i=0;
    while(run)
    {
      for(auto& handler: handlers)
        handler.callback(++i, handler.closure);
      this_thread::sleep_for(1s);
    }
  }).detach();
}

void SimpleAPI::stop()
{
  run = false;
}
