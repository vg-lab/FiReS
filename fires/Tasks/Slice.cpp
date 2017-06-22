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
#include "../Property/Property.h"
#include "Slice.h"
#include "../Object/Objects.h"

namespace fires
{


  Objects& Slice::eval( Objects& objs, TaskConfig& /* config */ )
  {
    assert( false );
    return objs;
  }

  void Slice::eval( GroupsOfObjects &groups, TaskConfig &config )
  {
    SliceConfig* sliceConfig = static_cast< SliceConfig* >( &config );
    FIRES_DEBUG_CHECK( sliceConfig, "error casting to SliceConfig" );

    auto categoriesSlices = sliceConfig->config( ).categoriesIdxs.size( );
    auto numericSlices = sliceConfig->config( ).cuts.size( );

    FIRES_DEBUG_CHECK(( categoriesSlices != 0 && numericSlices != 0 ) &&
                      ( categoriesSlices > 1 || numericSlices > 0 ),
                       "error categorical slices and numerical slices both or "
                       "none defined" );

    if ( categoriesSlices > 0 )
    {
      GroupsOfObjects slicedObjs;
      slicedObjs.reserve( categoriesSlices );
      for ( const auto& obj : groups[0] )
      {
        const auto& prop = obj->getProperty( sliceConfig->config( ).label );
        ( void ) prop;
      }
    }
    else if ( numericSlices > 0 )
    {
    }


  }

} // namespace fires
