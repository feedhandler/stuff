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
  Wrapper& operator=(Wrapper&&) = delete;
  
  virtual ~Wrapper();

  // C++ callback
  virtual void async_callback(int id);

protected:
  std::string mName;
  int mHandle;

private:
  // the C callback function, it must match signature of the callback function in the SimpleAPI
  static void c_callback(int id, void *closure);

  // The "bridge" between the c-callback and the C++ object
  struct Bridge;
  std::unique_ptr<Bridge> mBridge;
};
