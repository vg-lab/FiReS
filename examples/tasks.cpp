#include <fires/fires.h>


int main( void )
{


  fires::Tasks tasks;
  fires::Engine engine;
  fires::Objects objects;

  engine.eval( objects, tasks );


  return 0;
}
