/*
 * Copyright (c) 2014-2016 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/vg-lab/FiReS>
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
#include "PropertyGIDsManager.h"

namespace fires
{
  PropertyGID PropertyGIDsManager::nextPropertyGID = 0;

  std::map< std::string, unsigned short > PropertyGIDsManager::_labelToGID =
    std::map< std::string, unsigned short >( );

  std::map< PropertyGID, std::string > PropertyGIDsManager::_GIDToLabel =
    std::map< PropertyGID, std::string >( );

  PropertyGID PropertyGIDsManager::getPropertyGID( const std::string& label )
  {
    auto gid = _labelToGID.find( label );
    if ( gid == _labelToGID.end( ))
    {
      _labelToGID[ label ] = nextPropertyGID;
      _GIDToLabel[ nextPropertyGID ] = label;
      nextPropertyGID++;
      FIRES_DEBUG_CHECK( nextPropertyGID !=
                         std::numeric_limits< PropertyGID >::max( ),
                         "Number of properties exceeded maximum GID value" );
    }
    return _labelToGID[ label ];
  }

  const std::string& PropertyGIDsManager::getPropertyLabel( PropertyGID gid )
  {
    return _GIDToLabel.at( gid );
  }

}
