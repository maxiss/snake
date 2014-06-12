#include "snake.h"

CGameMap::CGameMap( const int x, const int y )
   : maxX(x), maxY(y)
{
}

bool CGameMap::checkNext( TPoint &point )
{
   if ( point.x < 0 )
      point.x = maxX;
   if ( point.x > maxX )
      point.x = 0;
   if ( point.y < 0 )
      point.y = maxY;
   if ( point.y > maxY )
      point.y = 0;
   return true;
}

void CGameMap::step( const TPoint next )
{
   map[ next ] = TContent( true );
}

void CGameMap::step( const TPoint next, const TPoint prev )
{
   map[ next ] = TContent( true );
   map[ prev ] = TContent( false );
}

TGameMap* CGameMap::getMap()
{
   return &map;
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

TPoint CSnake::step( const TPoint point )
{
   TPoint retval = snake.front();
   snake.push( point );
   snake.pop();

   return retval;
}

CGame::CGame()
   : map( 20, 20 ), snake ( 10, 10 )
{
   map.step( TPoint( 10, 10 ) );
}

int CGame::step()
{
   int retval = OK;

   TPoint next = snake.getNext();
   if ( map.checkNext( next ) )
   {
      TPoint old = snake.step( next );
      map.step( next, old );
      visual.print( map.getMap() );
   }

   return retval;
}






