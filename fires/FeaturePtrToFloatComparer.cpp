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

    return fabs( ( *ffp1->value( ) ) - ( *ffp2->value( )));

  }

} // namespace fires

// EOF
