// example of how we can wrap the C-API in a C++ class and
// give OO access to the async callbacks

#pragma once

#include "SimpleAPI.h"
#include "log4cpp/Category.hh"
#include <string>

class Wrapper
{
public:
  Wrapper(std::string name);
  
  virtual void async_callback(int id);
  
protected:
  log4cpp::Category& mLogger;
  
private:
  // the C callback function
  static void callbackFunc(int id, void *user_p);
};
