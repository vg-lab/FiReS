/**
 * @file    FeaturePtrToVector.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_VECTOR_PTR_H__
#define __FIRES__FEATURE_VECTOR_PTR_H__

#include <fires/defines.h>

#if (FIRES_WITH_VMMLIB == 1)

#include "FeaturePtr.h"

#include <vmmlib/vector.hpp>

namespace fires
{

  /*! \class FeatureVectorPtr
   \brief Feature class that has a pointer to a float value
   */
  template< size_t M, typename T  >
  class FeaturePtrToVector
    : public FeaturePtr< vmml::vector< M, T > >
  {

  public:

    FeaturePtrToVector( vmml::vector< M, T > * vectorPtr );

    virtual FeaturePtrToVector & operator +=( const Feature & rhs );

    virtual FeaturePtrToVector & operator /= ( const int & rhs );

    virtual Feature * newFeature( void ) const;


  };


  // Define standard types
  typedef vmml::vector< 2, float > Vec2f;
  typedef vmml::vector< 2, float * > Vec2pf;
  typedef FeaturePtrToVector< 2, float > FeaturePtrToVec2f;

  typedef vmml::vector< 3, float > Vec3f;
  typedef vmml::vector< 3, float * > Vec3pf;
  typedef FeaturePtrToVector< 3, float > FeaturePtrToVec3f;

  typedef vmml::vector< 4, float > Vec4f;
  typedef vmml::vector< 4, float * > Vec4pf;
  typedef FeaturePtrToVector< 4, float > FeaturePtrToVec4f;

  typedef vmml::vector< 2, int > Vec2i;
  typedef vmml::vector< 2, int * > Vec2pi;
  typedef FeaturePtrToVector< 2, int > FeaturePtrToVec2i;

  typedef vmml::vector< 3, int > Vec3i;
  typedef vmml::vector< 3, int * > Vec3pi;
  typedef FeaturePtrToVector< 3, int > FeaturePtrToVec3i;

  typedef vmml::vector< 4, int > Vec4i;
  typedef vmml::vector< 4, int * > Vec4pi;
  typedef FeaturePtrToVector< 4, int > FeaturePtrToVec4i;


  template< size_t M, typename T  >
  FeaturePtrToVector< M, T>::FeaturePtrToVector(
    vmml::vector< M, T > * vectorPtr )
    : FeaturePtr< vmml::vector< M, T > >( vectorPtr )
  {
  }

  template< size_t M, typename T  > FeaturePtrToVector< M, T > &
  FeaturePtrToVector< M, T>::operator +=( const Feature & rhs )
  {
    const FeaturePtrToVector< M, T > * feat =
      static_cast< const FeaturePtrToVector< M, T > * >( & rhs );

    vmml::vector< M, T > * rhsValue =  feat->value( );
    ( * this->_value ) += ( * rhsValue );

    return * this;
  }

  template< size_t M, typename T  > FeaturePtrToVector< M, T > &
  FeaturePtrToVector< M, T>::operator /= ( const int & rhs )
  {
    ( * this->_value ) /= rhs;
    return * this;

  }

  template< size_t M, typename T  > Feature *
  FeaturePtrToVector< M, T>::newFeature( void ) const
  {
    return new FeaturePtrToVector( new vmml::vector< M, T >(T(0)) );
  }



} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)

#endif // __FIRES__FEATURE_VECTOR_PTR_H__

//EOF
