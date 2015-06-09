/**
 * @file    Averager.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_AVERAGER_H__
#define __FIRES_AVERAGER_H__

#include "Feature.h"

#ifdef FIRES_WITH_VMMLIB
#include <vmmlib/vmmlib.hpp>
#endif

namespace fires
{

  /*! \class Averager

   */

  class Averager
  {
  public:
    FIRES_API
    virtual ~Averager( )
    {
    }

    FIRES_API
    // virtual Feature newFeature( void ) const = 0;
    // virtual Feature deleteFeature( void ) const
    // {
    // }
    virtual void accum( const Feature& /* f1 */ ) = 0;
    virtual void divide( const unsigned int /* f1 */ ) = 0;
    virtual void reset( void ) = 0;
    // Altough this method should be const then feature constructed as
    // const and breaks
    virtual Feature feature( void ) = 0;
  };


  template < typename T >
  class ScalarAverager : public Averager
  {
  public:

    FIRES_API
    ScalarAverager( T resetValue_ = ( T ) 0 )
      : _resetValue( resetValue_ )
    {
    }

    FIRES_API
    virtual ~ScalarAverager( )
    {
    }

    virtual void accum( const Feature& feature_ )
    {
      _accumValue += feature_.value< T >( );
    }

    virtual void divide( const unsigned int value )
    {
      _accumValue /= value;
    }

    virtual void reset( void )
    {
      _accumValue = _resetValue;
    }

    virtual Feature feature( void )
    {
      return Feature( _accumValue );
    }

  protected:

    T _resetValue;
    T _accumValue;

  };


  template < typename T >
  class ScalarPtrAverager
    : public ScalarAverager< T >
  {
  public:

    FIRES_API
    ScalarPtrAverager( T resetValue_ = ( T ) 0 )
      : ScalarAverager< T >( resetValue_ )
    {
    }


    FIRES_API
    virtual ~ScalarPtrAverager( )
    {
    }

    virtual void accum( const Feature& feature_ )
    {
      this->_accumValue += *feature_.value< T* >( );
    }


    virtual Feature feature( void )
    {
      return Feature( &this->_accumValue );
    }


  };

  #ifdef FIRES_WITH_VMMLIB

  template < size_t M, typename T >
  class VectorAverager
    : public ScalarAverager< vmml::vector< M, T >>
  {
  public:
    VectorAverager( )
      : ScalarAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
    {
    }

  };

  template < size_t M, typename T >
  class VectorPtrAverager
    : public ScalarPtrAverager< vmml::vector< M, T >>
  {
  public:
    VectorPtrAverager( )
      : ScalarPtrAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
    {
    }

  };

 #endif

}


#endif
