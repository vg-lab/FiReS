/**
 * @file    Comparer.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_COMPARER_H__
#define __FIRES_COMPARER_H__

#include "Feature.h"
#include "Definitions.h"

#include <math.h>

#ifdef FIRES_USE_VMMLIB
#include <vmmlib/vmmlib.hpp>
#include <vmmlib/util.hpp>
#endif

namespace fires
{

  /*! \class Comparer
   \brief Parent comparer class that provides the distance computation
   virtual method.

   Parent comparer class that provides the distance computation
   virtual method. This method has to be rewritten by the actual comparer
   which have to be derived from this class.

   */
  class Comparer
  {
  public:
    FIRES_API
    virtual ~Comparer( )
    {
    }

    /**
     * Virtual method to compute distance.
       Has to be rewritten by the specific comparers.
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    FIRES_API
    virtual float distance( const Feature& /* f1 */,
                            const Feature& /* f2 */ ) const
    {
      FIRES_LOG( "No valid Comparer registered. Returning 0." );
      return 0.0f;
    }

  };


  template < typename T >
  class ScalarComparer : public Comparer
  {
  public:

    virtual ~ScalarComparer( )
    {
    }

    /**
     * Virtual method to compute distance.
       Has to be rewritten by the specific comparers.
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      return _distance( f1.value< T >( ), f2.value< T >( ));
    }

  protected:

    template< typename TYPE >
    float _distance( const TYPE f1, const TYPE f2  ) const
    {
      // std::cout << f1 << " " << f2 << std::endl;
      return fabsf( float( f1 ) - float( f2 ));
    }

  };

  template < typename T >
  class ScalarComparer< T* > : public ScalarComparer< T >
  {
  public:
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      // std::cout  << "Scalar Comparer * " << *f1.value< T* >( ) << " "
      //            << *f2.value< T* >( ) << std::endl;
      return  ScalarComparer< T >::_distance( *f1.value< T* >( ),
                                              *f2.value< T* >( ));
    }
  };


  #ifdef FIRES_USE_VMMLIB

  typedef enum
  {
    EUCLIDEAN_DIST = 0,
    MANHATTAN_DIST
  } TVectorDistance;

  template < class V, size_t M, typename T >
  class VectorComparer : public Comparer
  {
  public:

    VectorComparer( void )
      : _type( EUCLIDEAN_DIST )
    {
    }

    TVectorDistance& distanceType( void )
    {
      return _type;
    }

    virtual ~VectorComparer( )
    {
    }

    /**
     * Virtual method to compute distance.
       Has to be rewritten by the specific comparers.
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      return _vectorDistance( f1.value< vector<M ,T>>( ),
                              f2.value< vector<M ,T> >( ));
    }

  protected:

    virtual float _vectorDistance( const vector<M ,T>& f1,
                                   const vector<M ,T>& f2 ) const
    {
      switch ( _type )
      {
      case MANHATTAN_DIST:
        return float( vmml::manhattan( f1 - f2 ));
        break;
      case EUCLIDEAN_DIST:
        return float(( f1 - f2 ).length( ));
        break;
      default:
        throw std::runtime_error(
          "fires::VectorComparer: distance not supported" );
      }

      return 0.0f;
    }


    TVectorDistance _type;

  };


  template < class V, size_t M, typename T >
  class VectorComparer< V*, M, T >
    : public VectorComparer< V, M, T >
  {
  public:
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      return VectorComparer< V, M, T >::_vectorDistance(
        *f1.value< vector< M, T >* >( ),
        *f2.value< vector< M, T >* >( ));
    }
  };

  template < class V, size_t M, typename T >
  class VectorComparer< V, M, T* >
    : public VectorComparer< V, M, T >
  {
  public:
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      vector< M, T > v1;
      vector< M, T * > vp = f1.value< vector< M, T* >>( );
      for ( unsigned int i = 0; i < M ; i++ )
        v1( i ) = *vp( i );

      vector< M, T > v2;
      vp = f2.value< vector< M, T* >>( );
      for ( unsigned int i = 0; i < M ; i++ )
        v2( i ) = *vp( i );

      return VectorComparer< V, M, T >::_vectorDistance( v1, v2 );
    }
  };


  template < class V, size_t M, typename T >
  class VectorComparer< V*, M, T* >
    : public VectorComparer< V, M, T >
  {
  public:
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      vector< M, T > v1;
      vector< M, T * > vp = *f1.value< vector< M, T* >* >( );
      for ( unsigned int i = 0; i < M ; i++ )
        v1( i ) = *vp( i );

      vector< M, T > v2;
      vp = *f2.value< vector< M, T* >* >( );
      for ( unsigned int i = 0; i < M ; i++ )
        v2( i ) = *vp( i );

      return VectorComparer< V, M, T >::_vectorDistance( v1, v2 );
    }
  };

#endif

}


#endif
