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
   switch ( content.cont )
   {
      case CONT_NONE:
         ch = ' ';
      break;

      case CONT_SNAKE:
         ch = 'X';
      break;

      case CONT_FOOD:
         ch = 'O';
      break;
   };

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

