// example of how we can wrap the C API in a C++ class and
// give OO access to the callbacks

#pragma once

#include <memory>
#include <string>

class Wrapper
{
public:
  // Constructors
  Wrapper(std::string name);
  Wrapper(Wrapper&&);
  
  // No copy or assignment
  Wrapper(const Wrapper&) = delete;
  Wrapper& operator=(const Wrapper&) = delete;
  
  // Move assignment
  Wrapper& operator=(Wrapper&&);
  
  virtual ~Wrapper();

  // C++ callback
  virtual void async_callback(int id);
  
protected:
  std::string mName;

private:
  // the C callback function, it must match signature of SimpleAPI::callbackFunc_t
  static void c_callback(int id, void *closure);

  // The "bridge" between the c-callback and the C++ object
  struct Bridge;
  std::unique_ptr<Bridge> mBridge;
  // TODO could we do this? Maybe it is too confusing...
  std::unique_ptr<Wrapper*> mParent;
  // TODO check that it works with multiple inheritance
};
