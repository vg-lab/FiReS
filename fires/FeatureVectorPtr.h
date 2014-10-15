/**
 * @file    FeatureVectorPtr.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_VECTOR_PTR_H__
#define __FIRES__FEATURE_VECTOR_PTR_H__

#include <fires/config.h>

#if (FIRES_WITH_VMMLIB == 1)


#include "Feature.h"

#include <vmmlib/vector.hpp>

namespace fires
{

  /*! \class FeatureVectorPtr
   \brief Feature class that has a pointer to a float value
   */
  template< size_t M, typename T  >
  class FeatureVectorPtr 
    : public FeaturePtr< vmml::vector< M, T > >
  {

  public:

    FeatureVectorPtr( vmml::vector< M, T > * vectorPtr ) 
      : FeaturePtr< vmml::vector< M, T > >( vectorPtr )
    {
    }

  };





typedef vmml::vector< 2, float > Vec2f;
typedef FeatureVectorPtr< 2, float > FeatureVec2fPtr;
//typedef FeatureVectorPtr< 2, float * > FeatureVec2PtrfPtr;

typedef vmml::vector< 3, float > Vec3f;
typedef vmml::vector< 3, float * > Vec3ptrf;
typedef FeatureVectorPtr< 3, float > FeatureVec3fPtr;
typedef FeatureVectorPtr< 3, float * > FeatureVec3ptrfPtr;

typedef vmml::vector< 4, float > Vec4f;
typedef FeatureVectorPtr< 4, float > FeatureVec4fPtr;
//typedef FeatureVectorPtr< 4, float * > FeatureVec4PtrfPtr;


typedef vmml::vector< 2, int > Vec2i;
typedef FeatureVectorPtr< 2, int > FeatureVec2iPtr;
//typedef FeatureVectorPtr< 2, int * > FeaturePtrVec2PtriPtr;

typedef vmml::vector< 3, int > Vec3i;
typedef FeatureVectorPtr< 3, int > FeatureVec3iPtr;
//typedef FeatureVectorPtr< 3, int * > FeaturePtrVec3PtriPtr;

typedef vmml::vector< 4, int > Vec4i;
typedef FeatureVectorPtr< 4, int > FeatureVec4iPtr;
//typedef FeatureVectorPtr< 4, int * > FeaturePtrVec4PtriPtr;


} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)

#endif // __FIRES__FEATURE_VECTOR_PTR_H__

//EOF 

