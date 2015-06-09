/**
 * @file    Feature.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_H__
#define __FIRES__FEATURE_H__


#include <fires/api.h>
#include <boost/any.hpp>
#include <iostream>

namespace fires
{


  class Feature
  {
  public:

    Feature( void )
      : _value( )
    {
    }

    virtual ~Feature( void )
    {
    }

    Feature& operator= ( const Feature& other )
    {
      this->_value = other._value;
      return *this;
    }

    template < class ValueType >
    Feature( ValueType value_ )
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
        std::cerr << "fires::Feature::value( ): can not cast, feature is empty "
                  << std::endl;

      try
      {
        v = boost::any_cast< ValueType >( _value );
      } catch( ... )
      {
        throw std::runtime_error(
          std::string( "fires::Feature::value( ): can not cast from " ) +
          _value.type( ).name( ) + std::string( " to " ) +
          typeid( ValueType ).name( ) );

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

  protected:
    boost::any _value;

  }; // class Feature

} // namespace fires


#endif
