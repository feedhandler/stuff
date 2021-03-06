#include "Wrapper.h"
#include "SimpleAPI.h"
#include "spdlog/spdlog.h"

using namespace std;

// The "bridge" between the c-callback and the C++ object
// Instead of a custom class we could just use 
//   std::unique_ptr<Wrapper*> mBridge;
// but I think it's confusing to mix smart and raw pointers
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
  , mHandle(-1)
  , mBridge(make_unique<Wrapper::Bridge>(this))
{
  // register a callback to the static c_callback function, and pass
  // the address of the Bridge object as the closure
  // Store the handle in a member variable
  mHandle = simple_register(Wrapper::c_callback, mBridge.get());
}

// move constructor
Wrapper::Wrapper(Wrapper&& other)
  : mName(std::move(other.mName))
  , mBridge(std::move(other.mBridge))
{
  mBridge->mParent=this;
}

// destructor must be in the cpp file, see Meyers Modern C++, item 22
Wrapper::~Wrapper()
{
  simple_unregister(mHandle);
}

void Wrapper::async_callback(int id)
{
  spdlog::info("{} handle {}, Got {}", mName, mHandle, id);
}
