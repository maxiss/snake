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

void CGameMap::changeMap( const TPoint point, const TContent content )
{
   mapChanges[ point ] = content;
}

void CGameMap::commit()
{
   for ( TGameMap::const_iterator it = mapChanges.begin();
      it != mapChanges.end(); ++it )
   {
      map[ it->first ] = it->second;
   }
   mapChanges.clear();
}

void CGameMap::snakeStep( const TPoint next )
{
   changeMap( next, TContent(true) );
}

void CGameMap::snakeStep( const TPoint next, const TPoint prev )
{
   changeMap( next, TContent(true) );
   changeMap( prev, TContent(false) );
}

TGameMap* CGameMap::getMapChanges()
{
   return &mapChanges;
}

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






