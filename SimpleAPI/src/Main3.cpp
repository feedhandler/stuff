// Example showing how our Wrapper class can be std::move-d

#include "Utils.h"
#include "SimpleAPI.h"
#include "Wrapper.h"

#include "spdlog/spdlog.h"

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

  vector<Wrapper> wrappers;
  addWrapper("alice", wrappers);
  addWrapper("bob", wrappers);
  
  spdlog::info("start");
  SimpleAPI::start();
  
  this_thread::sleep_for(5s);
  
  spdlog::info("stop");
  SimpleAPI::stop();
  
  this_thread::sleep_for(2s);
  spdlog::info("finished");
}
