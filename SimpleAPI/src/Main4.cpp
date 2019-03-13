// This checks that Wrapper is unregistered when it is destroyed

#include "Utils.h"
#include "SimpleAPI.h"
#include "Wrapper.h"

#include "spdlog/spdlog.h"

#include <chrono>
#include <thread>

using namespace std;

int main()
{
  initializeLogging();

  Wrapper w1("w1");
  Wrapper* w2 = new Wrapper("w2");
  Wrapper w3("w3");
  
  spdlog::info("start");
  simple_start();
  
  this_thread::sleep_for(3s);
  
  delete w2;
  
  this_thread::sleep_for(3s);
  
  spdlog::info("stop");
  simple_stop();
  
  this_thread::sleep_for(1500ms);
  spdlog::info("finished");
}
