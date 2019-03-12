#include "Wrapper.h"
#include "SimpleAPI.h"
#include "spdlog/spdlog.h"

using namespace std;

struct Wrapper::Impl
{
  Impl(Wrapper* wrapper)
    : mParent(wrapper)
    {}
  
  Wrapper* mParent;
};

void Wrapper::c_callback(int id, void *user_p)
{
  // get impl from closure
  auto& impl = *static_cast<Wrapper::Impl*>(user_p);
  
  // call the object's async callback function
  // Reminder: this will be on API's thread
  impl.mParent->async_callback(id);
}

// constructor
Wrapper::Wrapper(string name)
  : mName(name)
  , mImpl(make_unique<Wrapper::Impl>(this))
{
  CallbackFuncInfo callbackFuncInfo;
  callbackFuncInfo.user_p = mImpl.get();
  callbackFuncInfo.callback_p = Wrapper::c_callback;
  
  sessionCreate(&callbackFuncInfo);
}

// move constructor
Wrapper::Wrapper(Wrapper&& other)
  : mName(std::move(other.mName))
  , mImpl(std::move(other.mImpl))
{
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

// destructor must be in the cpp file, see Meyers Modern C++, item 22
Wrapper::~Wrapper() = default;

void Wrapper::async_callback(int id)
{
  spdlog::info("{} Got {}", mName, id);
}

