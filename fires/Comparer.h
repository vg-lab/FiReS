/**
 * @file    Comparer.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
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
  class Comparer 
  {
  public:

    /**
     * Virtual method to compute distance. 
       Has to be rewritten by the specific comparers.
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance(Feature *f1, Feature *f2);

  };


}


#endif
