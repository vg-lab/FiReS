/**
 * @file    FeaturePtrToVectorComparer.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_COMPARER_FEATURE_VECTOR_PTR_H__
#define __FIRES_COMPARER_FEATURE_VECTOR_PTR_H__

#if (FIRES_WITH_VMMLIB == 1)

#include "FeatureVectorComparer.h"

#include <vmmlib/util.hpp> // manhattan

namespace fires
{

  /*! \class FeatureVectortPtrComparer
    \brief Comparer specific to compute distance between two 
    FeaturePtrToVector features

  */

  template< size_t M, typename T  >
  class FeaturePtrToVectorComparer 
    : public FeatureVectorComparer
  {
  public:

    FeaturePtrToVectorComparer( void );

    /**
     * Virtual method to compute distance between to vector pointers 
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance(Feature *f1, Feature *f2);


  }; 


  typedef FeaturePtrToVectorComparer< 2, float > FeaturePtrToVec2fComparer;
  typedef FeaturePtrToVectorComparer< 3, float > FeaturePtrToVec3fComparer;
  typedef FeaturePtrToVectorComparer< 4, float > FeaturePtrToVec4fComparer;
  
  typedef FeaturePtrToVectorComparer< 2, int > FeaturePtrToVec2iComparer;
  typedef FeaturePtrToVectorComparer< 3, int > FeaturePtrToVec3iComparer;
  typedef FeaturePtrToVectorComparer< 4, int > FeaturePtrToVec4iComparer;

  
  template< size_t M, typename T  >
  FeaturePtrToVectorComparer< M, T>::FeaturePtrToVectorComparer( void )
    : FeatureVectorComparer( )
  {
  }

  template< size_t M, typename T  > float 
  FeaturePtrToVectorComparer< M, T >::distance( Feature *f1, Feature *f2 )
  {

    FeaturePtrToVector< M, T > * ffp1 = 
      dynamic_cast< FeaturePtrToVector< M, T > * >( f1 );
    FeaturePtrToVector< M, T > * ffp2 = 
      dynamic_cast< FeaturePtrToVector< M, T > * >( f2 );
      
    if ( !ffp1 || !ffp2 )
    {
      std::cerr << "Error casting to FeaturePtrToVector " 
		<< "for distance computation" 
		<< std::endl;
      return 0.0f;
    }
      
    // Convert to float to compute distances
    vmml::vector< M, float > v1f( * ffp1->value( ));
    vmml::vector< M, float > v2f( * ffp2->value( ));

    switch ( _type )
    {
    case MANHATTAN:
      return vmml::manhattan( v2f - v1f );
      break;
    case EUCLIDEAN:
      return ( v1f - v2f ).length( );
      break;
    default:
      throw std::runtime_error(
	"FeaturePtrToVectorComparer: distance not supported");
    }
      
    return 0.0f;

  }


  
} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)


#endif

