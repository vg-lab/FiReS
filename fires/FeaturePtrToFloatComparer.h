/**
 * @file    ComparerFeaturePtrToFloat.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_COMPARER_FEATURE_FLOAT_PTR_H__
#define __FIRES_COMPARER_FEATURE_FLOAT_PTR_H__

#include "Comparer.h"

namespace fires
{

  /*! \class FeaturePtrToFloatComparer
    \brief Comparer specific to compute distance between two 
    FeaturePtrToFloat features

  */
  class FeaturePtrToFloatComparer : public Comparer
  {
  public:

    /**
     * Virtual method to compute distance between to float pointers 
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance(Feature *f1, Feature *f2);

  }; 

}

#endif
