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

#include <math.h>

#ifdef FIRES_WITH_VMMLIB
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
      std::cerr << "No valid Comparer registered. Returning 0." << std::endl;
      return 0.0f;
    }

  };


  template < typename T >
  class ScalarComparer : public Comparer
  {
  public:
    FIRES_API
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
    FIRES_API
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      return ( float ) fabs( double ( f1.value< T >( ) - f2.value< T >( )));
    }

  };


  template < typename T >
  class ScalarPtrComparer : public Comparer
  {
  public:
    FIRES_API
    virtual ~ScalarPtrComparer( )
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
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      return ( float ) fabs( double ( *f1.value<T*>( ) - *f2.value<T*>( )));
    }

  };


  #ifdef FIRES_WITH_VMMLIB

  typedef enum
  {
    EUCLIDEAN_DIST = 0,
    MANHATTAN_DIST
  } TVectorDistance;


  template < size_t M, typename T >
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

    FIRES_API
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

    FIRES_API
    virtual float vectorDistance( const vmml::vector< M, T >& f1,
                                  const vmml::vector< M, T >& f2 ) const
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

    FIRES_API
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      return distance( f1.value< vmml::vector< M, T >>( ),
                       f2.value< vmml::vector< M, T >>( ));
    }

  protected:
    TVectorDistance _type;

  };


  template < size_t M, typename T >
  class VectorPtrComparer : public VectorComparer< M, T >
  {
  public:

    FIRES_API
    virtual float distance( const Feature& f1, const Feature& f2 ) const
    {
      return VectorComparer< M, T >::vectorDistance(
        *f1.value< vmml::vector< M, T >* >( ),
        *f2.value< vmml::vector< M, T >* >( ));
    }
  };

#endif
  
}


#endif
