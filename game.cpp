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
   snake.stepOn( TPoint(10, 10) );
   snake.stepOn( TPoint(10, 11) );
   snake.stepOn( TPoint(10, 12) );

   map.changeMap( TPoint(10, 10), TContent(CONT_TAIL) );
   map.changeMap( TPoint(10, 11), TContent(CONT_SNAKE) );
   map.changeMap( TPoint(10, 12), TContent(CONT_HEAD) );

   map.decEmptyPoints( 3 );

   map.addFood();
   visual.print( map.getMapChanges() );
   map.commit();
}

int CGame::step()
{
   int retval = OK;

   TPoint next = snake.getNext();
   if ( map.checkNext( next ) )
   {
      if ( map.checkFood( next ) )
      {
         TPoint head = snake.getHead();
         snake.stepOn( next );
         map.snakeStepOn( next, head );
         map.addFood();
      }
      else
      {
         TPoint head = snake.getHead();
         snake.stepOn( next );
         TPoint out = snake.stepOut();
         TPoint tail = snake.getTail();
         map.snakeStepOut( out, tail );
         map.snakeStepOn( next, head );
      }
   }
   else
   {
      TPoint head = snake.getHead();
      snake.stepOn( next );
      TPoint out = snake.stepOut();
      TPoint tail = snake.getTail();
      map.snakeStepOut( out, tail );
      map.changeMap( head, TContent( CONT_SNAKE ) );
      map.changeMap( next, TContent( CONT_COLLISION ) );
      loop = false;
   }
   visual.print( map.getMapChanges() );
   map.commit();

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

