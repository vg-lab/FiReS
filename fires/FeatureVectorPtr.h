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
  typedef vmml::vector< 2, float * > Vec2pf;
  typedef FeatureVectorPtr< 2, float > FeatureVec2fPtr;
  typedef FeatureVectorPtr< 2, float * > FeatureVec2pfPtr;

  typedef vmml::vector< 3, float > Vec3f;
  typedef vmml::vector< 3, float * > Vec3pf;
  typedef FeatureVectorPtr< 3, float > FeatureVec3fPtr;
  typedef FeatureVectorPtr< 3, float * > FeatureVec3pfPtr;

  typedef vmml::vector< 4, float > Vec4f;
  typedef vmml::vector< 4, float * > Vec4pf;
  typedef FeatureVectorPtr< 4, float > FeatureVec4fPtr;
  typedef FeatureVectorPtr< 4, float * > FeatureVec4pfPtr;


  typedef vmml::vector< 2, int > Vec2i;
  typedef vmml::vector< 2, int * > Vec2pi;
  typedef FeatureVectorPtr< 2, int > FeatureVec2iPtr;
  typedef FeatureVectorPtr< 2, int * > FeaturePtrVec2piPtr;

  typedef vmml::vector< 3, int > Vec3i;
  typedef vmml::vector< 3, int * > Vec3pi;
  typedef FeatureVectorPtr< 3, int > FeatureVec3iPtr;
  typedef FeatureVectorPtr< 3, int * > FeaturePtrVec3piPtr;

  typedef vmml::vector< 4, int > Vec4i;
  typedef vmml::vector< 4, int * > Vec4pi;
  typedef FeatureVectorPtr< 4, int > FeatureVec4iPtr;
  typedef FeatureVectorPtr< 4, int * > FeaturePtrVec4piPtr;


} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)

#endif // __FIRES__FEATURE_VECTOR_PTR_H__

//EOF 

