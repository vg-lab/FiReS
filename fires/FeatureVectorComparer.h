/**
 * @file    FeatureVectorOfPointerPtrComparer.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_FEATURE_VECTOR_COMPARER_H__
#define __FIRES_FEATURE_VECTOR_COMPARER_H__


#include "Comparer.h"

namespace fires
{

  class FeatureVectorComparer
    : public Comparer
  {

  public:

    FeatureVectorComparer( void )
      : _type( EUCLIDEAN )
    {
    }

    typedef enum
    {
      EUCLIDEAN,
      MANHATTAN
    } TVectorDistance;

    TVectorDistance & distanceType( void )
    {
      return _type;
    }

  protected:
    TVectorDistance _type;

  };


}

#endif
