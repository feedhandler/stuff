// Demo of how Wrapper class can break

#include "Utils.h"
#include "SimpleAPI.h"
#include "Wrapper.h"

#include <log4cpp/Category.hh>

#include <chrono>
#include <thread>
#include <vector>

using namespace std;

void addWrapper(string name, vector<Wrapper>& wrappers)
{
  Wrapper wrapper(name);
  wrappers.emplace_back(std::move(wrapper));
}

int main(int argc, char* argv[])
{
  initializeLogging();

  auto& logger = log4cpp::Category::getInstance("main");

  
  vector<Wrapper> wrappers;
  addWrapper("alice", wrappers);
  addWrapper("bob", wrappers);
  
  
  
  logger.notice("start");
  simpleStart();
  
  this_thread::sleep_for(5s);
  
  logger.notice("stop");
  simpleStop();
  
  this_thread::sleep_for(2s);
  logger.notice("finished");
  
  // TODO check memory leaks
}
