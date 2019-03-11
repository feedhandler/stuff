#include "Wrapper.h"
#include "SimpleAPI.h"
#include "spdlog/spdlog.h"

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
  : mName(name)
  , mImpl(make_unique<WrapperImpl>())
{
  mImpl->mParent=this;
  
  CallbackFuncInfo callbackFuncInfo;
  callbackFuncInfo.user_p = mImpl.get();
  callbackFuncInfo.callback_p = WrapperImpl::callbackFunc;
  
  sessionCreate(&callbackFuncInfo);
}

// move constructor
Wrapper::Wrapper(Wrapper&& other)
  : mName(std::move(other.mName))
  , mImpl(std::move(other.mImpl))
{
  // TODO google for PImpl reference to parent
  mImpl->mParent=this;
}

// move assignment
Wrapper& Wrapper::operator=(Wrapper&& other)
{
  if (this!=&other)
  {
    mImpl = std::move(other.mImpl);
    mName = std::move(other.mName);
    mImpl->mParent = this;
  }

  return *this;
}

void Wrapper::async_callback(int id)
{
  spdlog::info("{} got {}", mName, id);
}
