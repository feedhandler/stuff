#include "Wrapper.h"

using namespace std;

void WrapperImpl::callbackFunc(int id, void *user_p)
{
  // cast closure to object
  auto& wrapperImpl = *static_cast<WrapperImpl*>(user_p);
  
  // call the object's async callback function
  // This will be on same thread as the C-callback
  wrapperImpl.mParent->async_callback(id);
}

// constructor
Wrapper::Wrapper(string name)
  : mLogger(log4cpp::Category::getInstance(name))
  , mImpl(new WrapperImpl)
{
  mImpl->mParent=this;
  
  CallbackFuncInfo callbackFuncInfo;
  callbackFuncInfo.user_p = mImpl;
  callbackFuncInfo.callback_p = WrapperImpl::callbackFunc;
  
  sessionCreate(&callbackFuncInfo);
}

// move constructor
Wrapper::Wrapper(Wrapper&& other)
  : mLogger(other.mLogger)
  , mImpl(other.mImpl)
{
  mImpl->mParent=this;
  
  other.mImpl = nullptr;
}

// TODO move assignment

Wrapper::~Wrapper()
{
  if (mImpl)
  {
    delete mImpl;
    mImpl = nullptr;
  }
}

void Wrapper::async_callback(int id)
{
  mLogger.noticeStream() << " got " << id;
}
