#include "snake.h"
#include <curses.h>

CVisual::CVisual()
{
   initscr();
   ::clear();
   refresh();
}

CVisual::~CVisual()
{
   endwin();
}

void CVisual::print( const TPoint point, const TContent content )
{
   char ch;
   move( point.x, point.y );
   if ( content.snake )
      ch = 'X';
   else
      ch = ' ';

   addch( ch );
}

