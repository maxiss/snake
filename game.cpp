#include "snake.h"
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>

struct termSaver
{
   termios oldt;
   termSaver()
   {
      tcgetattr( STDIN_FILENO, &oldt );
      termios newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr( STDIN_FILENO, TCSANOW, &newt );
   };
   ~termSaver()
   {
      tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
   };
};

CGame::CGame()
   : map( 20, 20 )
{
   snake.stepAhead( TPoint(10, 10) );
   snake.stepAhead( TPoint(10, 11) );
   snake.stepAhead( TPoint(10, 12) );

   map.snakeStep( TPoint( 10, 10 ) );
   map.snakeStep( TPoint( 10, 11 ) );
   map.snakeStep( TPoint( 10, 12 ) );

   map.decEmptyPoints( 3 );

   map.addFood();
}

int CGame::step()
{
   int retval = OK;

   TPoint next = snake.getNext();
   if ( map.checkNext( next ) )
   {
      if ( map.checkFood( next ) )
      {
         snake.stepAhead( next );
         map.snakeStep( next );
         map.addFood();
      }
      else
      {
         TPoint old = snake.step( next );
         map.snakeStep( next, old );
      }
      visual.print( map.getMapChanges() );
      map.commit();
   }

   return retval;
}

static void gameStep( CGame* game )
{
   while ( game->loop )
   {
      game->step();
      std::this_thread::sleep_for( std::chrono::milliseconds(200) );
   }
}

void CGame::start() {
   termSaver saver;
   loop = true;
   std::thread gameThread( gameStep, this );
   int ch = 0;
   do
   {
      ch = getchar();
      snake.turn( ch );
   } while ( ch != 27 );
   loop = false;
   gameThread.join();
}

