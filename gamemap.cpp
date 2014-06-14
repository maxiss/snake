#include "snake.h"

CGameMap::CGameMap( const int x, const int y )
   : maxX(x), maxY(y)
{
   map.resize( maxX * maxY );
}

TContent& CGameMap::getContent( const int x, const int y )
{
   int index = y * maxX + x;
   return map[ index ];
}

TContent& CGameMap::getContent( const TPoint point )
{
   return getContent( point.x, point.y );
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

bool CGameMap::checkFood( const TPoint point )
{
   bool retval = false;
   if ( getContent( point ).cont == CONT_FOOD )
      retval = true;

   return retval;
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
      getContent( it->first ) = it->second;
   }
   mapChanges.clear();
}

void CGameMap::snakeStep( const TPoint next )
{
   changeMap( next, TContent(CONT_SNAKE) );
}

void CGameMap::snakeStep( const TPoint next, const TPoint prev )
{
   changeMap( next, TContent(CONT_SNAKE) );
   changeMap( prev, TContent(CONT_NONE) );
}

void CGameMap::addFood( const int x, const int y )
{
   changeMap( TPoint(x, y), TContent( CONT_FOOD ) );
}

TGameMap* CGameMap::getMapChanges()
{
   return &mapChanges;
}
