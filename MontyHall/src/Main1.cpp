// Monty Hall problem

#include "effolkronium/random.hpp"
#include "spdlog/spdlog.h"

#include <vector>

using namespace std;

enum class Prize
{
  Car,
  Goat
};

int main(int argc, char* argv[])
{
  unsigned NUM_PRIZES = 3;
  
  auto carIdx = Random::get(0, NUM_PRIZES);
  
  spdlog::info("num prizes = {}", NUM_PRIZES);
  spdlog::info("carIdx = {}", carIdx);

  
  // create prizes
  //~ vector<Prize> prizes;
  //~ for (int i=0; i<NUM_PRIZES; ++i)
    //~ prizes.push_back( i==carIdx ? Prize::Car : Prize::Goat );
      
  //~ // print doors
  //~ for (auto p: prizes)
    //~ spdlog::info("finished");
}
