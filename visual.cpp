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
   ::move( point.y, point.x );
   if ( content.snake )
      ch = 'X';
   else
      ch = ' ';

   ::addch( ch );
}

void CVisual::refresh()
{
   ::move( ::LINES-1, ::COLS-1 );
   ::refresh();
}

void CVisual::print( const TGameMap* gameMap )
{
   for ( TGameMap::const_iterator it = gameMap->begin();
      it != gameMap->end(); ++it )
   {
      print( it->first, it->second );
   }
   refresh();
}

