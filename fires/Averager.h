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
#include "Definitions.h"

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
    virtual void accum( const Feature& /* f1 */ ) = 0;

    FIRES_API
    virtual void divide( const unsigned int /* f1 */ ) = 0;

    FIRES_API
    virtual void reset( void ) = 0;

    // Altough this method should be const then feature constructed as
    // const and breaks
    FIRES_API
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

    FIRES_API
    virtual void accum( const Feature& feature_ )
    {
      _accumValue += feature_.value< T >( );
    }

    FIRES_API
    virtual void divide( const unsigned int value )
    {
//      std::cout << _accumValue << " " << value << " " << _accumValue / value << std::endl;;
      _accumValue /= value;
    }

    FIRES_API
    virtual void reset( void )
    {
      _accumValue = _resetValue;
    }

    FIRES_API
    virtual Feature feature( void )
    {
      return Feature( _accumValue );
    }

  protected:

    T _resetValue;
    T _accumValue;

  };


  template < typename T >
  class ScalarAverager< T* >
    : public ScalarAverager< T >
  {
  public:

    FIRES_API
    ScalarAverager( T resetValue_ = ( T ) 0 )
      : ScalarAverager< T >( resetValue_ )
    {
    }

    FIRES_API
    virtual ~ScalarAverager( )
    {
    }

    FIRES_API
    virtual void accum( const Feature& feature_ )
    {
      this->_accumValue += *feature_.value< T* >( );
    }

    FIRES_API
    virtual Feature feature( void )
    {
      return Feature( &this->_accumValue );
    }


  };

  #ifdef FIRES_WITH_VMMLIB

  template < class V, size_t M, typename T >
  class VectorAverager
    : public ScalarAverager< vmml::vector< M, T >>
  {
  public:
    VectorAverager( )
      : ScalarAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
    {
    }

  };

  template < class V, size_t M, typename T >
  class VectorAverager< V*, M, T >
    : public ScalarAverager< vmml::vector< M, T >* >
  {
  public:
    VectorAverager( )
      : ScalarAverager< vmml::vector< M, T >* >( vmml::vector< M, T >::ZERO )
    {
    }

  };



  template < class V, size_t M, typename T >
  class VectorAverager< V, M, T* >
    : public ScalarAverager< vmml::vector< M, T >>
  {
  public:
    VectorAverager( )
      : ScalarAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
    {
    }

    FIRES_API
    virtual void accum( const Feature& feature_ )
    {
      vector< M, T > v;
      vector< M, T * > vp = feature_.value< vector< M, T* >>( );
      for ( unsigned int i = 0; i < M ; i++ )
        v( i ) = *vp( i );

      this->_accumValue += v;
    }

    FIRES_API
    virtual Feature feature( void )
    {

      vector<M, T* > _vector;

      for ( unsigned int i = 0; i < M ; i++ )
      {
        _vectorValues[ i ] = this->_accumValue( i );
        _vector( i ) = &_vectorValues[ i ];
      }

      return Feature( _vector );
    }

  protected:

    T _vectorValues[ M ];


  };

  template < class V, size_t M, typename T >
  class VectorAverager< V*, M, T* >
    : public ScalarAverager< vmml::vector< M, T >>
  {
  public:
    VectorAverager( )
      : ScalarAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
    {
    }

    FIRES_API
    virtual void accum( const Feature& feature_ )
    {

      feature_.value< vector< M, T* >* >( );
      vector< M, T > v;
      vector< M, T* > vp = *( feature_.value< vector< M, T* >* >( ));
      for ( unsigned int i = 0; i < M ; i++ )
        v( i ) = *vp( i );

      this->_accumValue += v;
    }

    FIRES_API
    virtual Feature feature( void )
    {
      for ( unsigned int i = 0; i < M ; i++ )
      {
        _vectorValues[ i ] = this->_accumValue( i );
        _vector( i ) = &_vectorValues[ i ];
      }

      return Feature( &_vector );
    }

  protected:

    T _vectorValues[ M ];
    vector<M, T* > _vector;

  };



#endif

}


#endif
