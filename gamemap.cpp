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
