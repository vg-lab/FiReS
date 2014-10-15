/**
 * @file    FeatureVectorPtrComparer.h
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
#include <vmmlib/util.hpp>

namespace fires
{

  /*! \class FeatureVectortPtrComparer
    \brief Comparer specific to compute distance between two 
    FeatureVectorPtr features

  */
  template< size_t M, typename T  >
  class FeatureVectorPtrComparer 
    : public FeatureVectorComparer
  {
  public:

    FeatureVectorPtrComparer( void )
      : FeatureVectorComparer( )
    {
    }

    /**
     * Virtual method to compute distance between to vector pointers 
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance(Feature *f1, Feature *f2)
    {

      FeatureVectorPtr< M, T > * ffp1 = 
	dynamic_cast< FeatureVectorPtr< M, T > * >( f1 );
      FeatureVectorPtr< M, T > * ffp2 = 
	dynamic_cast< FeatureVectorPtr< M, T > * >( f2 );
      
      if ( !ffp1 || !ffp2 )
      {
	std::cerr << "Error casting to FeatureVectorPtr " 
		  << "for distance computation" 
		<< std::endl;
	return 0.0f;
      }
      
      // vmml::vector< M, T > * v1 = ffp1->value( );
      // vmml::vector< M, T > * v2 = ffp2->value( );

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
	  "FeatureVectorPtrComparer: distance not supported");
      }
      
      return 0.0f;

    }


  }; 


  typedef FeatureVectorPtrComparer< 2, float > FeatureVec2fPtrComparer;
  typedef FeatureVectorPtrComparer< 3, float > FeatureVec3fPtrComparer;
  typedef FeatureVectorPtrComparer< 4, float > FeatureVec4fPtrComparer;
  
  typedef FeatureVectorPtrComparer< 2, int > FeatureVec2iPtrComparer;
  typedef FeatureVectorPtrComparer< 3, int > FeatureVec3iPtrComparer;
  typedef FeatureVectorPtrComparer< 4, int > FeatureVec4iPtrComparer;
  
  
} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)


#endif

