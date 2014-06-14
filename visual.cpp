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
   ::move( point.y, point.x*2 );
   switch ( content.cont )
   {
      case CONT_NONE:
         ch = ' ';
      break;

      case CONT_SNAKE:
         ch = 'O';
      break;

      case CONT_HEAD:
         ch = '@';
      break;

      case CONT_TAIL:
         ch = 'o';
      break;

      case CONT_FOOD:
         ch = 'A';
      break;

      case CONT_COLLISION:
         ch = 'X';
      break;
   };

   ::addch( ch );
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

