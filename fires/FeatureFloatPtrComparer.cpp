/**
 * @file    ComparerFeatureFloatPtr.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "FeatureFloatPtr.h"
#include "FeatureFloatPtrComparer.h"

#include <iostream>
#include <math.h>

namespace fires
{

  float FeatureFloatPtrComparer::distance( Feature *f1, Feature *f2 )
  {
    FeatureFloatPtr *ffp1 = dynamic_cast< FeatureFloatPtr * >( f1 );
    FeatureFloatPtr *ffp2 = dynamic_cast< FeatureFloatPtr * >( f2 );

    if ( !ffp1 || !ffp2 )
    {
      std::cerr << "Error casting to FeatureFloatPtr " 
		<< "for distance computation" 
		<< std::endl;
      return 0.0f;
    }

    return fabs( ( *ffp1->value( ) ) - ( *ffp2->value( )));

  }

} // namespace fires

// EOF
