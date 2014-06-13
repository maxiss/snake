#include <map>
#include <queue>

#define OK 0
#define NO_OK -1

enum TDirection
{
   D_UP = 0
  ,D_DOWN
  ,D_LEFT
  ,D_RIGHT
};

enum TKey
{
   K_W = 119
  ,K_A = 97
  ,K_S = 115
  ,K_D = 100
};

enum EContent
{
   CONT_NONE = 0
  ,CONT_SNAKE
  ,CONT_FOOD
};

struct TPoint
{
   int x, y;
   TPoint( const int x, const int y ) : x(x), y(y) {};
};

struct TContent
{
   EContent cont;
   TContent() : cont(CONT_NONE) {};
   TContent( const EContent val ) : cont(val) {};
};

struct TPointComparer
   : std::binary_function< TPoint, TPoint, bool >
{
   bool operator()( const TPoint& arg1, const TPoint& arg2 )
   {
      if ( arg1.y == arg2.y )
         return ( arg1.x < arg2.x );
      else
         return ( arg1.y < arg2.y );
   }
};

typedef std::map< TPoint, TContent, TPointComparer > TGameMap;
typedef std::queue< TPoint > TSnake;

class CGameMap
{
public:
   CGameMap( const int x, const int y );
   bool checkNext( TPoint &point );
   bool checkFood( const TPoint point );
   void changeMap( const TPoint point, const TContent content );
   void commit();
   void snakeStep( const TPoint next );
   void snakeStep( const TPoint next, const TPoint prev );
   void addFood( const int x, const int y );
   TGameMap* getMapChanges();

private:
   const int maxX;
   const int maxY;
   TGameMap map;
   TGameMap mapChanges;

};

class CSnake
{
public:
   CSnake();
   CSnake( const int x, const int y );
   TPoint getNext();
   TPoint step( const TPoint point );
   void stepAhead( const TPoint point );
   void turn( int ch );

private:
   TDirection direct;
   TSnake snake;
   bool turned;

};

class CVisual
{
public:
   CVisual();
   ~CVisual();
   void print( const TPoint point, const TContent content );
   void refresh();
   void print( const TGameMap* gameMap );

private:

};

class CGame
{
public:
   CGame();
   int step();
   void start();
   bool loop;

private:
   CGameMap map;
   CSnake snake;
   CVisual visual;

};








