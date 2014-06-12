#include <iostream>
#include "snake.h"
#include <thread>
#include <chrono>

using namespace std;

int main()
{
   CGame game;

   for (int i = 0; i<30; i++)
   {
      game.step();
      std::this_thread::sleep_for( std::chrono::milliseconds(300) );
   }

   return 0;
}
