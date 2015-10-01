/**
 * @file    Engine.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */


#include "Engine.h"
#include "../Object/Objects.h"

namespace fires
{


  //
  // Engine methods
  //
  Engine::~Engine( )
  {
  }


  void Engine::run( Objects& objects, Tasks& tasks )
  {
    Objects& objs = objects;

    for ( auto t = tasks.begin( ); t != tasks.end( ); ++t )
      ( *t ).task( )->eval( objs, *(( *t ).config( )));

    return;

  }
} // namespace fires


//EOF
