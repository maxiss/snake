#include "snake.h"

CSnake::CSnake()
   : direct( D_RIGHT )
{
}

CSnake::CSnake( const int x, const int y )
   : direct( D_LEFT )
{
   snake.push( TPoint( x, y ) );
   snake.push( TPoint( x, y+1 ) );
   snake.push( TPoint( x, y+2) );
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

void CSnake::stepOn( const TPoint point )
{
   snake.push( point );
   turned = false;
}

TPoint CSnake::stepOut()
{
   TPoint retval = snake.front();
   snake.pop();
   return retval;
}

TPoint CSnake::getHead()
{
   return snake.back();
}

TPoint CSnake::getTail()
{
   return snake.front();
}

void CSnake::turn( const int ch )
{
   if (!turned)
   {
      switch (ch)
      {
      case K_W:
         if ( (direct != D_UP) && (direct != D_DOWN) )
         {
            direct = D_DOWN;
            turned = true;
         }
      break;

      case K_A:
         if ( (direct != D_LEFT) && (direct != D_RIGHT) )
         {
            direct = D_LEFT;
            turned = true;
         }
      break;

      case K_S:
         if ( (direct != D_UP) && (direct != D_DOWN) )
         {
            direct = D_UP;
            turned = true;
         }
      break;

      case K_D:
         if ( (direct != D_LEFT) && (direct != D_RIGHT) )
         {
            direct = D_RIGHT;
            turned = true;
         }
      break;
      }
   }
}

