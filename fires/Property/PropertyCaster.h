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
#ifndef __FIRES__PROPERTYCASTER_H__
#define __FIRES__PROPERTYCASTER_H__

#include "Property.h"
#include <sstream>
#include <math.h>

namespace fires
{

  class PropertyCaster
  {
  public:

    virtual ~PropertyCaster( void )
    {
    }

    typedef enum
    {
      ROUND = 0,
      CEIL,
      FLOOR
    } TIntCasting;

    virtual int toInt( const Property&, TIntCasting casting = ROUND ) = 0;
    virtual std::string toString( const Property& property ) = 0;

  };

  template < typename T >
  class ScalarPropertyCaster : public PropertyCaster
  {
  public:

    virtual ~ScalarPropertyCaster( void )
    {
    }

    virtual int toInt( const Property& property, TIntCasting casting = ROUND )
    {
      switch ( casting )
      {
      case ROUND:
        return int( round( property.value< T >( )));
        break;
      case CEIL:
        return int( ceil( property.value< T >( )));
        break;
      case FLOOR:
        return int( floor( property.value< T >( )));
        break;
      default:
        throw std::runtime_error( "Invalid casting type" );
      }
    }

    virtual std::string toString( const Property& property )
    {
      std::ostringstream iss;
// Avoiding choose int over unsigned int for enum types
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-promo"
      iss << (( T ) property.value< T >( ));
#pragma GCC diagnostic pop
      return std::string( iss.str( ));
    }
  };

} // namespace fires

#endif
