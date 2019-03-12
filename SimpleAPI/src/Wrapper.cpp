#include "Wrapper.h"
#include "SimpleAPI.h"
#include "spdlog/spdlog.h"

using namespace std;

struct Wrapper::Bridge
{
  Bridge(Wrapper* wrapper)
    : mParent(wrapper)
    {}
  
  Wrapper* mParent;
};

void Wrapper::c_callback(int id, void *closure)
{
  // call the object's async callback function via the bridge
  // Reminder: this will be executed on the API's thread
  static_cast<Wrapper::Bridge*>(closure)->mParent->async_callback(id);
}

// constructor
Wrapper::Wrapper(string name)
  : mName(name)
  , mBridge(make_unique<Wrapper::Bridge>(this))
{
  // register a callback to the static c_callback function, and pass
  // the address of the Bridge object as the closure
  SimpleAPI::registerHandler(Wrapper::c_callback, mBridge.get());
}

// move constructor
Wrapper::Wrapper(Wrapper&& other)
  : mName(std::move(other.mName))
  , mBridge(std::move(other.mBridge))
{
  mBridge->mParent=this;
}

// move assignment
Wrapper& Wrapper::operator=(Wrapper&& other)
{
  if (this!=&other)
  {
    mBridge = std::move(other.mBridge);
    mName = std::move(other.mName);
    mBridge->mParent = this;
  }

  return *this;
}

// destructor must be in the cpp file, see Meyers Modern C++, item 22
Wrapper::~Wrapper() = default;

void Wrapper::async_callback(int id)
{
  spdlog::info("{} Got {}", mName, id);
}
