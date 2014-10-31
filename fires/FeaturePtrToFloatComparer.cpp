/**
 * @file    ComparerFeaturePtrToFloat.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "FeaturePtrToFloat.h"
#include "FeaturePtrToFloatComparer.h"

#include <iostream>
#include <math.h>

namespace fires
{

  FeaturePtrToFloatComparer::FeaturePtrToFloatComparer( 
    float minValue, float maxValue )
    : Comparer( )
    , _minValue( minValue )
    , _maxValue( maxValue )
    , _invMaxMinDiff( 0.0f )
  {

    if ( ( _maxValue - _minValue )  != 0 )
      _invMaxMinDiff = 1.0f / ( _maxValue - _minValue );

  }


  void FeaturePtrToFloatComparer::setMaxValue( const float maxValue )
  {
    _maxValue = maxValue;

    if ( ( _maxValue - _minValue )  != 0 )
      _invMaxMinDiff = 1.0f / ( _maxValue - _minValue );
  }

  void FeaturePtrToFloatComparer::setMinValue( const float minValue )
  {
    _minValue = minValue;

    if ( ( _maxValue - _minValue )  != 0 )
      _invMaxMinDiff = 1.0f / ( _maxValue - _minValue );

  }

  float FeaturePtrToFloatComparer::distance( Feature *f1, Feature *f2 )
  {
    FeaturePtrToFloat *ffp1 = dynamic_cast< FeaturePtrToFloat * >( f1 );
    FeaturePtrToFloat *ffp2 = dynamic_cast< FeaturePtrToFloat * >( f2 );

    if ( !ffp1 || !ffp2 )
    {
      std::cerr << "Error casting to FeaturePtrToFloat " 
		<< "for distance computation" 
		<< std::endl;
      return 0.0f;
    }

    float distance = fabs( ( *ffp1->value( ) ) - ( *ffp2->value( )));

    if ( ( _maxValue - _minValue ) != 0 )
      distance *= _invMaxMinDiff;

    return distance;

  }

} // namespace fires

// EOF
