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
#ifndef __FIRES_PROPERTY_GIDS_MANAGER__
#define __FIRES_PROPERTY_GIDS_MANAGER__

#include <map>
#include <limits>
#include <fires/api.h>
#include "error.h"
#include "Log.h"

#define FIRES_ANY std::string( "fires::any" )

namespace fires
{

  //! GID type for properties
  typedef unsigned short PropertyGID;

  /**
   * Class for linking property names to properties GIDs
   *
   */
  class PropertyGIDsManager
  {

  public:

    /**
     * Converts from property name to property GID. If the property has not been
     * used before a new GID is assigned. If the number of properties exceed
     * the maximum value possible an exception is reaised
     *
     * @param label Name of the property
     * @return GID of the property
     */
    FIRES_API static PropertyGID getPropertyGID( const std::string& label );

    /**
     * Converts from property property GID to property name.
     *
     * @param gid GID of the property
     * @return  Name of the property
     */
    FIRES_API static const std::string& getPropertyLabel( PropertyGID gid );

  protected:

    //! Next porperty ID to use
    static PropertyGID nextPropertyGID;

    //! Map to convert from name to GID
    static std::map< std::string, PropertyGID > _labelToGID;

    //! Map to convert from GID to name
    static std::map< PropertyGID, std::string > _GIDToLabel;


  };

}

#endif
