#include "snake.h"

CGame::CGame()
   : map( 20, 20 ), snake ( 10, 10 )
{
   map.snakeStep( TPoint( 10, 10 ) );
}

int CGame::step()
{
   int retval = OK;

   TPoint next = snake.getNext();
   if ( map.checkNext( next ) )
   {
      TPoint old = snake.step( next );
      map.snakeStep( next, old );
      visual.print( map.getMapChanges() );
      map.commit();
   }

   return retval;
}
