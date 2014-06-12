#include "snake.h"
#include <curses.h>

CVisual::CVisual()
{
   ::initscr();
   ::clear();
   ::refresh();
}

CVisual::~CVisual()
{
   ::endwin();
}

void CVisual::print( const TPoint point, const TContent content )
{
   char ch;
   ::move( point.x, point.y );
   if ( content.snake )
      ch = 'X';
   else
      ch = ' ';

   ::addch( ch );
}

void CVisual::refresh()
{
   ::refresh();
}

void CVisual::print( const TGameMap* gameMap )
{
   ::clear();
   for ( TGameMap::const_iterator it = gameMap->begin();
      it != gameMap->end(); ++it )
   {
      print( it->first, it->second );
   }
   ::refresh();
}

