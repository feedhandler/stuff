// example of how we can wrap the C-API in a C++ class and
// give OO access to the async callbacks

#pragma once

#include "SimpleAPI.h"
#include "log4cpp/Category.hh"

#include <memory>
#include <string>

class Wrapper;

struct WrapperImpl
{
  // the C callback function
  static void callbackFunc(int id, void *user_p);
  Wrapper* mParent;
};

class Wrapper
{
public:
  Wrapper(std::string name);
  
  // No copy or assignment
  Wrapper(const Wrapper&) = delete;
  Wrapper& operator=(const Wrapper&) = delete;
  
  Wrapper(Wrapper&&);
  Wrapper& operator=(Wrapper&&);
  
  virtual ~Wrapper();
  
  virtual void async_callback(int id);
  
protected:
  log4cpp::Category& mLogger;
  
private:
  std::unique_ptr<WrapperImpl> mImpl;
};
