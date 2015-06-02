/**
 * @file    ComparerFeaturePtrToScalar.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_COMPARER_FEATURE_SCALAR_PTR_H__
#define __FIRES_COMPARER_FEATURE_SCALAR_PTR_H__

#include "Comparer.h"

namespace fires
{

  /*! \class FeaturePtrToScalarComparer
    \brief Comparer specific to compute distance between two
    FeaturePtrToScalar features

  */
  template < typename TYPE > class FeaturePtrToScalarComparer
    : public Comparer
  {

  public:

    FeaturePtrToScalarComparer( TYPE minValue = 0, TYPE maxValue = 0)
      : Comparer( )
      , _minValue( minValue )
      , _maxValue( maxValue )
      , _invMaxMinDiff( 0.0f )
    {
      if ( ( _maxValue - _minValue )  != 0 )
        _invMaxMinDiff = 1.0f / ( _maxValue - _minValue );
    }

    void setMaxValue( const TYPE maxValue )
    {
      _maxValue = maxValue;

      if ( ( _maxValue - _minValue )  != 0 )
        _invMaxMinDiff = 1.0f / ( _maxValue - _minValue );
    }

    void setMinValue( const float minValue )
    {
      _minValue = minValue;

      if ( ( _maxValue - _minValue )  != 0 )
        _invMaxMinDiff = 1.0f / ( _maxValue - _minValue );
    }

    /**
     * Virtual method to compute distance between to Scalar pointers
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance( Feature* f1, Feature* f2 ) const
    {
      FeaturePtrToScalar< TYPE >* fps1 =
        dynamic_cast< FeaturePtrToScalar< TYPE >* >( f1 );
      FeaturePtrToScalar< TYPE >* fps2 =
        dynamic_cast< FeaturePtrToScalar< TYPE >* >( f2 );

      if ( !fps1 || !fps2 )
      {
        std::cerr << "Error casting to FeaturePtrToScalar "
                  << "for distance computation"
                  << std::endl;
        return 0.0f;
      }

      float dist = float( fabs(( *fps1->value( )) - ( *fps2->value( ))));

      if (( _maxValue - _minValue ) != 0 )
        dist *= float( _invMaxMinDiff );

      return dist;

    }

  protected:

    //! Minimum possible value (used to normalize)
    TYPE _minValue;

    //! Maximum possible value (used to normalize)
    TYPE _maxValue;

    //! Value cached to speed up a bunch of distances coputations
    TYPE _invMaxMinDiff;


  };

}

#endif
