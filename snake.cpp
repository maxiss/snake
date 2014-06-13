#include "snake.h"

CSnake::CSnake( const int x, const int y )
   : direct( D_LEFT )
{
   snake.push( TPoint( x, y ) );
   snake.push( TPoint( x+1, y+1 ) );
   snake.push( TPoint( x+3, y+2) );
}

TPoint CSnake::getNext()
{
   TPoint retval = snake.back();
   switch ( direct )
   {
   case D_UP:
      retval.y++;
   break;

   case D_DOWN:
      retval.y--;
   break;

   case D_LEFT:
      retval.x--;
   break;

   case D_RIGHT:
      retval.x++;
   break;
   }

   return retval;
}

TPoint CSnake::step( const TPoint point )
{
   TPoint retval = snake.front();
   snake.push( point );
   snake.pop();

   return retval;
}

