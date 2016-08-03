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
#ifndef __FIRES__PROPERTY_H__
#define __FIRES__PROPERTY_H__

#include <fires/api.h>
#include <boost/any.hpp>
#include <iostream>

#include "../error.h"
#include "../Log.h"

namespace fires
{
  class Property
  {
  public:

    FIRES_API
    Property( void );

    FIRES_API
    virtual ~Property( void );

    Property& operator= ( const Property& other )
    {
      this->_value = other._value;
      return *this;
    }

    template < class ValueType >
    Property( ValueType value_ )
    {
      _value = value_;
    }

    template < class ValueType >
    void set( ValueType value_ )
    {
      _value = value_;
    }

    template < typename ValueType >
    ValueType value( void ) const
    {
#ifdef NDEBUG
      return boost::any_cast< ValueType >( _value );
#else
      ValueType v;

      if ( _value.empty( ))
        std::cerr << "fires::Property::value( ): property value is empty "
                  << std::endl;

      try
      {
        v = boost::any_cast< ValueType >( _value );
      }
      catch( ... )
      {
        Log::log(
          std::string( "fires::Property::value( ), can not cast from " ) +
          _value.type( ).name( ) + std::string( " to " ) +
          typeid( ValueType ).name( ), LOG_LEVEL_ERROR );
        throw boost::bad_any_cast( );
      }
      return v;
#endif
    }

    template < typename ValueType >
    ValueType* valuePtr( void )
    {
#ifdef NDEBUG
      return boost::any_cast< ValueType >( &_value );
#else
      ValueType* v;

      if ( _value.empty( ))
        std::cerr << "fires::Property::value( ): property value is empty "
                  << std::endl;

      try
      {
        v = boost::any_cast< ValueType >( &_value );
      }
      catch( ... )
      {
        Log::log(
          std::string( "fires::Property::value( ), can not cast from " ) +
          _value.type( ).name( ) + std::string( " to " ) +
          typeid( ValueType ).name( ), LOG_LEVEL_ERROR );
        throw boost::bad_any_cast( );
      }
      return v;
#endif
    }


    FIRES_API
    std::string type( void ) const;

    FIRES_API
    bool empty( void ) const;

  protected:
    boost::any _value;

  }; // class Property


} // namespace fires


#endif
