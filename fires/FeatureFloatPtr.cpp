/**
 * @file    FeatureFloatPtr.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "FeatureFloatPtr.h"

namespace fires
{

  FeatureFloatPtr::FeatureFloatPtr( float *floatPtr )
  {
    _value = floatPtr;
  }
  
  float * FeatureFloatPtr::value( void )
  {
    return _value;
  }
 

}

