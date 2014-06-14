#include "snake.h"
#include <curses.h>

CVisual::CVisual( const int width, const int height )
   : top(1), left(1), width( width ), height( height )
{
   ::initscr();
   ::clear();
   printBorder();
   ::refresh();
}

CVisual::~CVisual()
{
   ::endwin();
}

void CVisual::print( const TPoint point, const TContent content )
{
   char ch;
   ::move( top + point.y, left + point.x*2 );
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

void CVisual::printBorder()
{
   int i = 0;
   ::move( 0, 0 );
   for (i = 0; i <= width+3; i++)
   {
      addch( '#' );
   }

   ::move( height+2, 0 );
   for (i = 0; i <= width+3; i++)
   {
      addch( '#' );
   }

   for (i = 0; i <= height; i++)
   {
      ::move( i+1, 0 );
      addch( '#' );
   }

   for (i = 0; i <= height; i++)
   {
      ::move( i+1, width+3 );
      addch( '#' );
   }
}

