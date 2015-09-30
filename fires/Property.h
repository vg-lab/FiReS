/**
 * @file    Property.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__PROPERTY_H__
#define __FIRES__PROPERTY_H__


#include <fires/api.h>
#include <boost/any.hpp>
#include <iostream>

#include "error.h"

namespace fires
{


  class Property
  {
  public:

    Property( void )
      : _value( )
    {
    }

    virtual ~Property( void )
    {
    }

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
	std::cerr << "fires::Property::value( ): can not cast, property is empty "
		  << std::endl;

      try
      {
	v = boost::any_cast< ValueType >( _value );
      }
      catch( ... )
      {
	FIRES_LOG(
		  std::string( "fires::Property::value( ), can not cast from " ) +
		  _value.type( ).name( ) + std::string( " to " ) +
		  typeid( ValueType ).name( ));
	throw boost::bad_any_cast( );
      }
      return v;
      #endif
    }

    std::string type( void ) const
    {
      return _value.type( ).name( );
    }

    bool empty( void ) const
    {
      return _value.empty( );
    }

    // boost::any value( ) const
    // {
    //   return _value;
    // }

  protected:
    boost::any _value;

  }; // class Property


  // inline bool operator==( const Property& lhs, const Property& rhs )
  // {
  //   return ( lhs.value( ) == rhs.value( ));
  // }
  // inline bool operator!=( const Property& lhs, const Property& rhs )
  // {
  //   return !( lhs == rhs );
  // }


} // namespace fires


#endif
