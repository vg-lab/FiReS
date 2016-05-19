/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/gmrvvis/FiReS>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
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
