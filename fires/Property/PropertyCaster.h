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
#include <map>
#include <vector>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/lexical_cast.hpp>

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
    } TIntRounding;

    virtual int toInt( const Property&, TIntRounding rounding = ROUND ) = 0;
    virtual std::string toString( const Property& property ) = 0;
    virtual void fromString(
      Property& property, const std::string& str ) = 0;

    virtual std::vector< std::string > categories( void )
    {
      return std::vector< std::string >( );
    }
  };

  template < typename T,  class Enable = void >
  class StringPropertyCaster
    : public PropertyCaster
  {
  };

  template < typename T >
  class StringPropertyCaster
    < T, typename std::enable_if< boost::spirit::traits::is_string < T >::value >::type >
    : public PropertyCaster
  {
    public:

    virtual ~StringPropertyCaster( void )
    {
    }

    virtual int toInt( const Property& property, TIntRounding rounding = ROUND )
    {
      float value = boost::lexical_cast<float> ( ( std::string ) property.value<T>( ));
      switch ( rounding )
      {
        case ROUND:
          return int( round( value ));
          break;
        case CEIL:
          return int( ceil(value ));
          break;
        case FLOOR:
          return int( floor( value ));
          break;
        default:
          throw std::runtime_error( "Invalid rounding type" );
      }
    }

    virtual std::string toString( const Property& property )
    {
      return std::string( ( T ) property.value< T >( ) );
    }

    virtual void fromString( Property& property, const std::string& str )
    {
      property.set( str );
    }

  };

  template < typename T,  class Enable = void >
  class ScalarPropertyCaster
    : public PropertyCaster
  {
  };

  template < typename T >
  class ScalarPropertyCaster
  < T, typename std::enable_if< std::is_arithmetic< T >::value >::type >
    : public PropertyCaster
  {
  public:

    virtual ~ScalarPropertyCaster( void )
    {
    }

    virtual int toInt( const Property& property, TIntRounding rounding = ROUND )
    {
      switch ( rounding )
      {
      case ROUND:
        return int( round( double( property.value< T >( ))));
        break;
      case CEIL:
        return int( ceil( double( property.value< T >( ))));
        break;
      case FLOOR:
        return int( floor( double( property.value< T >( ))));
        break;
      default:
        throw std::runtime_error( "Invalid rounding type" );
      }
    }

    virtual std::string toString( const Property& property )
    {
      std::ostringstream iss;
// Avoiding choose int over unsigned int for enum types
#ifdef __GNUC__
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wsign-promo"
#endif
      iss << (( T ) property.value< T >( ));
#ifdef __GNUC__
      #pragma GCC diagnostic pop
#endif
      return std::string( iss.str( ));
    }

    virtual void fromString( Property& property, const std::string& str )
    {
      property.set( ( T ) std::stod( str ));
    }

  };

  template < typename T,  class Enable = void >
  class EnumPropertyCaster
  {
  };

  template < typename T >
  class EnumPropertyCaster
  < T, typename std::enable_if< std::is_enum< T >::value >::type >
    : public PropertyCaster
  {
  public:

    EnumPropertyCaster( const std::map< T, std::string >& scalarToString_ )
    {
      _scalarToString = scalarToString_;
      for ( const auto pair : _scalarToString )
        _stringToScalar[ pair.second ] = pair.first;
    }
    virtual ~EnumPropertyCaster( void )
    {
    }

    virtual int toInt( const Property& property, TIntRounding rounding = ROUND )
    {
      switch ( rounding )
      {
      case ROUND:
        return int( round( double( property.value< T >( ))));
        break;
      case CEIL:
        return int( ceil( double( property.value< T >( ))));
        break;
      case FLOOR:
        return int( floor( double( property.value< T >( ))));
        break;
      default:
        throw std::runtime_error( "Invalid rounding type" );
      }
    }

    virtual std::string toString( const Property& property )
    {
      return _scalarToString.at( property.value< T >( ));
    }

    virtual void fromString( Property& property, const std::string& str )
    {
      property.set( ( T ) _stringToScalar.at( str ));
    }

    virtual std::vector< std::string > categories( void ) final
    {
      std::vector< std::string > categories_;
      categories_.reserve( _scalarToString.size( ));
      for ( const auto catPair : _scalarToString )
        categories_.push_back( catPair.second );
      return categories_;
    }

    const std::map< T, std::string>& scalarToString( void )
    {
      return _scalarToString;
    }

  protected:

    std::map< T, std::string > _scalarToString;
    std::map< std::string, T > _stringToScalar;
  };


} // namespace fires

#endif
