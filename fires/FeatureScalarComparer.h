/**
 * @file    FeatureScalarComparer.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_SCALAR_COMPARER_H__
#define __FIRES_SCALAR_COMPARER_H__

#include "Feature.h"

namespace fires
{

  /*! \class Comparer
   \brief Comparer for FeatureScalar


   */
  template < typename TYPE > class FeatureScalarComparer
    : public Comparer
  {
  public:

    virtual ~FeatureScalarComparer( void )
    {
    }

    /**
     * Virtual method to compute distance.
       Has to be rewritten by the specific comparers.
     * @param f1 First feature to compare.
     * @param f Second feature to compare.
     * @return Distance between features
     */
    virtual float distance( Feature* f1, Feature* f2 ) const
    {
      FeatureScalar< TYPE >* fsp1 =
        dynamic_cast< FeatureScalar< TYPE >* >( f1 );
      FeatureScalar< TYPE >* fsp2 =
        dynamic_cast< FeatureScalar< TYPE >* >( f2 );

      if ( !fsp1 || !fsp2 )
      {
        std::cerr << "Error casting to FeaturePtrToFloat "
                  << "for distance computation"
                  << std::endl;
        return 0.0f;
      }

      float dist = ( float ) fabs(( fsp1->value( ) ) -
                                  ( fsp2->value( )));

      // if ( ( _maxValue - _minValue ) != 0 )
      //   dist *= _invMaxMinDiff;

      return dist;
    }

  };


}


#endif
