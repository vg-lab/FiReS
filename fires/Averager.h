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
    // Altough this method should be const then feature constructed is
    // const dependent and breaks
    virtual Feature getFeature( void ) = 0;
  };


  template < typename T >
  class ScalarAverager : public Averager
  {
  public:

    FIRES_API
    ScalarAverager( ) : _accumValue( 0 )
    {
    }

    FIRES_API
    virtual ~ScalarAverager( )
    {
    }

    // FIRES_API
    // virtual Feature newFeature( void ) const
    // {
    //   return Feature( ( T ) 0 );
    // }

    virtual void accum( const Feature& feature )
    {
      _accumValue += feature.value< T >( );
    }

    virtual void divide( const unsigned int value )
    {
      _accumValue /= value;
    }

    virtual void reset( void )
    {
      _accumValue = 0;
    }

    virtual Feature getFeature( void )
    {
      return Feature( _accumValue );
    }

  protected:

    T _accumValue;

  };


  template < typename T >
  class ScalarPtrAverager
    : public ScalarAverager< T >
  {
  public:
    FIRES_API
    virtual ~ScalarPtrAverager( )
    {
    }

    virtual void accum( const Feature& feature )
    {
      this->_accumValue += *feature.value< T* >( );
    }


    virtual Feature getFeature( void )
    {
      return Feature( &this->_accumValue );
    }


  };



}


#endif
