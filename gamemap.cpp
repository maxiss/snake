#include "snake.h"
#include <stdlib.h>

CGameMap::CGameMap( const int x, const int y )
   : maxX(x), maxY(y), emptyPoints(x * y)
{
   map.resize( (maxX + 1) * (maxY + 1) );
}

TContent& CGameMap::getContent( const int x, const int y )
{
   int index = y * (maxX + 1) + x;
   return map[ index ];
}

TContent& CGameMap::getContent_ext( const int x, const int y )
{
   TGameMap::iterator it = mapChanges.find( TPoint(x, y) );
   if (it != mapChanges.end())
      return it->second;
   else
      return getContent( x, y );
}

TContent& CGameMap::getContent( const TPoint point )
{
   return getContent( point.x, point.y );
}

bool CGameMap::checkCollision( const TPoint point )
{
   bool retval = false;
   if ( getContent( point ).cont == CONT_SNAKE )
      retval = true;

   return retval;
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
   return !checkCollision( point );
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

void CGameMap::snakeStepOn( const TPoint next, const TPoint head )
{
   changeMap( next, TContent(CONT_HEAD) );
   changeMap( head, TContent(CONT_SNAKE) );
}

void CGameMap::snakeStepOut( const TPoint out, const TPoint tail )
{
   changeMap( out,  TContent(CONT_NONE) );
   changeMap( tail, TContent(CONT_TAIL) );
}

void CGameMap::addFood( const int x, const int y )
{
   changeMap( TPoint(x, y), TContent( CONT_FOOD ) );
   emptyPoints--;
}

void CGameMap::addFood()
{
   int r = rand() % emptyPoints;
   int i = 0;
   for (int x = 0; x <= maxX; x++)
   {
      for (int y = 0; y <= maxY; y++)
      {
         if (getContent_ext(x, y).cont == CONT_NONE)
         {
            if (i == r)
            {
               addFood( x, y );
               return;
            }
            else
               i++;
         }
      }
   }
}

void CGameMap::decEmptyPoints( const int cnt )
{
   emptyPoints -= cnt;
}

TGameMap* CGameMap::getMapChanges()
{
   return &mapChanges;
}
