/**
 * @file    FeaturePtrToVectorOfPtrs.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_PTR_TO_VECTOR_OF_PTRS_H__ 
#define __FIRES__FEATURE_PTR_TO_VECTOR_OF_PTRS_H__

#include <fires/defines.h>

#if (FIRES_WITH_VMMLIB == 1)


#include "FeaturePtr.h"
#include "FeaturePtrToVector.h" // vmmlib typedefs

namespace fires
{

  template< size_t M, typename T  >
  class FeaturePtrToVectorOfPtrs
    : public FeaturePtr< vmml::vector< M, T * > >
  {

  public:

    FeaturePtrToVectorOfPtrs( vmml::vector< M, T * > * vectorPtr );

    virtual FeaturePtrToVectorOfPtrs & operator +=( const Feature & rhs ); 

    virtual FeaturePtrToVectorOfPtrs & operator /= ( const int & rhs ); 

    virtual Feature * newFeature( void ) const;
    virtual void deleteFeature( void ) const;


  };


  typedef FeaturePtrToVectorOfPtrs< 2, float > FeaturePtrToVec2pf;
  typedef FeaturePtrToVectorOfPtrs< 3, float > FeaturePtrToVec3pf;
  typedef FeaturePtrToVectorOfPtrs< 4, float > FeaturePtrToVec4pf;

  typedef FeaturePtrToVectorOfPtrs< 2, int > FeaturePtrToVec2pi;
  typedef FeaturePtrToVectorOfPtrs< 3, int > FeaturePtrOfVec3pi;
  typedef FeaturePtrToVectorOfPtrs< 4, int > FeaturePtrToVec4pi;


  template< size_t M, typename T  >
  FeaturePtrToVectorOfPtrs< M, T >::FeaturePtrToVectorOfPtrs( 
    vmml::vector< M, T * > * vectorPtr ) 
    : FeaturePtr< vmml::vector< M, T * > >( vectorPtr )
  {
  }

  template< size_t M, typename T  > FeaturePtrToVectorOfPtrs< M, T > &
  FeaturePtrToVectorOfPtrs< M, T >::operator +=( const Feature & rhs ) 
  {

    const FeaturePtrToVectorOfPtrs< M, T > * feat = 
      static_cast< const FeaturePtrToVectorOfPtrs< M, T > * >( & rhs );

    assert( feat );

    vmml::vector< M, T > lhsValues;
    for ( int i = 0; i < M ; i++ )
      lhsValues(i) = * ( ( * this->_value )(i) );

    vmml::vector< M, T > rhsValues;
    for ( int i = 0; i < M ; i++ )
      rhsValues[i] =  * ( ( * feat->value() )[i] );

    lhsValues += rhsValues;
    for ( int i = 0; i < M ; i++ )
      * ( ( * this->_value )[i] ) =  lhsValues[i];

    return * this;
  }

  template< size_t M, typename T  > FeaturePtrToVectorOfPtrs< M, T > & 
  FeaturePtrToVectorOfPtrs< M, T >::operator /= ( const int & rhs ) 
  {

    vmml::vector< M, T > lhsValues;     
    for ( int i = 0; i < M ; i++ )
      lhsValues(i) = * ( ( * this->_value )(i) );
      
    lhsValues /= rhs;

    for ( int i = 0; i < M ; i++ )
      * ( ( * this->_value )[i] ) =  lhsValues[i];
        
    return * this;
      
  }

  template< size_t M, typename T  > Feature * 
  FeaturePtrToVectorOfPtrs< M, T >::newFeature( void ) const
  {
    auto f = new FeaturePtrToVectorOfPtrs( new vmml::vector< M, T * > );
    for ( int i = 0 ; i < M ; i++ )
      (* f->_value )(i) = new T(0);
    return f;
  }

  template< size_t M, typename T  > void 
  FeaturePtrToVectorOfPtrs< M, T >::deleteFeature( void ) const
  {      
    for ( int i = 0 ; i < M ; i++ )
      delete (* this->_value )(i);
  }



} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)

#endif // __FIRES__FEATURE_PTR_TO_VECTOR_OF_PTRS_H__

//EOF 

