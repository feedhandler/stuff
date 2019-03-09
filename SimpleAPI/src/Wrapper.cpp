#include "Wrapper.h"

using namespace std;

void Wrapper::callbackFunc(int id, void *user_p)
{
  // cast closure to object
  auto& wrapper = *static_cast<Wrapper*>(user_p);
  
  // call the object's async callback function
  // (NB this will be on same thread as the C-callback)
  wrapper.async_callback(id);
}

// constructor
Wrapper::Wrapper(string name)
  : mLogger(log4cpp::Category::getInstance(name))
{
  CallbackFuncInfo callbackFuncInfo;
  callbackFuncInfo.user_p = this;
  callbackFuncInfo.callback_p = Wrapper::callbackFunc;
  
  sessionCreate(&callbackFuncInfo);
}

void Wrapper::async_callback(int id)
{
  mLogger.noticeStream() << " got " << id;
}
