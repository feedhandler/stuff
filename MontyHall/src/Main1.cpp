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
// NUM_PRIZES is the number of prizes (3, in the classic version of the problem)
// return a bool indicating whether you won or lost
bool play(int NUM_PRIZES, bool change)
{
  // fill with goats
  vector<Prize> prizes(NUM_PRIZES, Prize::Goat);
  
  // set one of the prizes as the car
  *Random::get(prizes) = Prize::Car;

  int x=0;
  spdlog::debug("-----------------------------");
  for (auto p: prizes)
    spdlog::debug("{}: {}", x++, p);
      
  // choose a prize  
  auto iFirstChoice = Random::get(0, NUM_PRIZES-1);

  spdlog::debug("First choice: {}", iFirstChoice);
  
  // Monty picks a door
  int iMontyChoice=0;
  while(true)
  {
    iMontyChoice = Random::get(0, NUM_PRIZES-1);
    
    // monty must pick different door to the contestant
    if (iMontyChoice==iFirstChoice)
      continue;
      
    // monty can't pick a car
    if (prizes[iMontyChoice]==Prize::Car)
      continue;
      
    break;
  }
  
  spdlog::debug("Monty's choice: {}", iMontyChoice);

  bool win=false;
  if (change)
  {
    // change your choice
    int iSecondChoice=0;
    while(true)
    {
      iSecondChoice = Random::get(0, NUM_PRIZES-1);
      
      // must pick different door to first choice
      if (iSecondChoice==iFirstChoice)
        continue;
      
      // must pick different door to monty
      if (iSecondChoice==iMontyChoice)
        continue;
        
      break;
    }
    
    spdlog::debug("Changed choice: {}", iSecondChoice);
    
    // did you win?
    win = prizes[iSecondChoice]==Prize::Car;
  }
  else
  {
    // did you win?
    win = prizes[iFirstChoice]==Prize::Car;
  }
  
  spdlog::debug("Won: {}", win);
  
  return win;
}

int main(int argc, char* argv[])
{
  //~ spdlog::set_level(spdlog::level::debug);
    
  int numPrizes = 3, numGames=1000;
  
  int wonChanged = 0;
  for (int j=0; j<numGames; ++j)
    if (play(numPrizes, true))
      wonChanged++;

  int wonStayed = 0;
  for (int j=0; j<numGames; ++j)
    if (play(numPrizes, false))
      wonStayed++;
      
  spdlog::info("numDoors   {: 8}",   numPrizes);
  spdlog::info("numGames   {: 8}",   numGames);
  spdlog::info("wonChanged {: 8}", wonChanged);
  spdlog::info("wonStayed  {: 8}",  wonStayed);
}
