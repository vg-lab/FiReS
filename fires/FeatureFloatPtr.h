/**
 * @file    FeatureFloatPtr.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_FLOAT_PTR_H__
#define __FIRES__FEATURE_FLOAT_PTR_H__


#include "Feature.h"

namespace fires
{

  /*! \class FeatureFloatPtr
   \brief Feature class that has a pointer to a float value
   */
  class FeatureFloatPtr : public Feature
  {

  public:

    FeatureFloatPtr( float *floatPtr );

    float * value( void );

  protected:

    float * _value;

  };

}


#endif
