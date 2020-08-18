// Demonstration of the Monty Hall problem

#include "effolkronium/random.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <vector>

using namespace std;

using Random = effolkronium::random_static;

enum class Prize
{
  Car,
  Goat
};

template<typename OStream>
OStream& operator<<(OStream &os, const Prize& p)
{
  switch (p) 
  {
    case Prize::Car:  os << "Car";  break;
    case Prize::Goat: os << "Goat"; break;
  }
  
  return os;    
}

// play the game, change your choice according to the parameter
// numDoors is the number of doors (3, in the classic version of the problem)
// return your prize
Prize play(const int numDoors, bool change)
{
  // behind each door is a prize. So we just create a vector of
  // prizes, it's basically the same. We create a convenience
  // variable here to make the code clearer
  const int numPrizes = numDoors;

  // fill with goats
  vector<Prize> prizes(numPrizes, Prize::Goat);
  
  // set one of the prizes as the car
  *Random::get(prizes) = Prize::Car;

  int x=0;
  spdlog::debug("-----------------------------");
  for (auto p: prizes)
    spdlog::debug("{}: {}", x++, p);
      
  // choose a prize  
  auto iFirstChoice = Random::get(0, numPrizes-1);

  spdlog::debug("First choice: {}", iFirstChoice);
  
  // Monty picks a door
  int iMontyChoice=0;
  while(true)
  {
    iMontyChoice = Random::get(0, numPrizes-1);
    
    // monty must pick different door to the contestant
    if (iMontyChoice==iFirstChoice)
      continue;
      
    // monty can't pick a car
    if (prizes[iMontyChoice]==Prize::Car)
      continue;
      
    break;
  }
  
  spdlog::debug("Monty's choice: {}", iMontyChoice);

  Prize prize;
  if (change)
  {
    // change your choice
    int iSecondChoice=0;
    while(true)
    {
      iSecondChoice = Random::get(0, numPrizes-1);
      
      // must pick different door to first choice
      if (iSecondChoice==iFirstChoice)
        continue;
      
      // must pick different door to monty
      if (iSecondChoice==iMontyChoice)
        continue;
        
      break;
    }
    
    spdlog::debug("Changed choice: {}", iSecondChoice);
    
    prize = prizes[iSecondChoice];
  }
  else
  {
    prize = prizes[iFirstChoice];
  }
  
  spdlog::debug("Prize: {}", prize);
  
  return prize;
}

void doIt(int numDoors, int numGames, bool change)
{
  int cars = 0;
  int goats = 0;
  for (int j=0; j<numGames; ++j)
  {
    if (Prize::Car == play(numDoors, change))
      cars++;
    else
      goats++;
  }

  spdlog::info("===================");
  spdlog::info("numDoors   {:>8}", numDoors);
  spdlog::info("numGames   {:>8}", numGames);
  spdlog::info("change     {:>8}", change);
  spdlog::info("cars won   {:>8}", cars);
  spdlog::info("goats won  {:>8}", goats);
}

int main(int argc, char* argv[])
{
  //~ spdlog::set_level(spdlog::level::debug);
    
  int numDoors = 3, numGames=1000;
  
  doIt(numDoors, numGames, true);
  doIt(numDoors, numGames, false);
}
