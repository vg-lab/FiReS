/**
 * @file    Engine.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

// #ifdef FIRES_USE_OPENMP
// #include <omp.h>
// #endif
// #include <stdio.h>
// #include <stdlib.h>


#include "Engine.h"

namespace fires
{


  //
  // Engine methods
  //
  Engine::~Engine( )
  {
  }


  virtual void Engine::run( Objects& objects, Tasks& tasks )
  {
    Objects& objs = objects;

    for ( auto t = tasks.begin( ); t != tasks.end( ); ++t )
      ( *t ).task( )->eval( objs, *(( *t ).config( )));

    return;

  }
} // namespace fires


//EOF
