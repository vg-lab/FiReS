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

namespace fires
{

  /*! \class Comparer
   \brief Parent comparer class that provides the distance computation
   virtual method.

   Parent comparer class that provides the distance computation
   virtual method. This method has to be rewritten by the actual comparer
   which have to be derived from this class.

   */

  // template < typename T >
  // float scalarDistance( Feature& f1, Feature &f2 )
  // {
  //   return ( float ) fabs( double( f1.value<T>( ) - f2.value<T>( )));
  // }

  // template < typename T >
  // float scalarPtrDistance( Feature& f1, Feature &f2 )
  // {
  //   return ( float ) fabs( double (*f1.value<T*>( ) - *f2.value<T*>( )));
  // }


//  typedef  float ( *Comparer ) ( Feature&, Feature& );

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



}


#endif
