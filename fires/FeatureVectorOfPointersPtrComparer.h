/**
 * @file    FeatureVectorOfPointerPtrComparer.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_COMPARER_FEATURE_VECTOR_OF_POINTERS_PTR_H__
#define __FIRES_COMPARER_FEATURE_VECTOR_OF_POINTERS_PTR_H__

#if (FIRES_WITH_VMMLIB == 1)

#include "FeatureVectorComparer.h"
#include <vmmlib/util.hpp>

namespace fires
{

  template< size_t M, typename T  >
  class FeatureVectorOfPointersPtrComparer 
    : public FeatureVectorComparer
  {
  public:

    FeatureVectorOfPointersPtrComparer( void )
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
      vmml::vector< M, float > v1f( * ( * ffp1->value( )));
      vmml::vector< M, float > v2f( * ( * ffp2->value( )));

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
	  "FeatureVectorOfPointerPtrComparer: distance not supported");
      }
      
      return 0.0f;

    }

  }; 

  typedef FeatureVectorOfPointersPtrComparer< 2, float * > 
  FeatureVec2pfPtrComparer;
  typedef FeatureVectorOfPointersPtrComparer< 3, float * > 
  FeatureVec3pfPtrComparer;
  typedef FeatureVectorOfPointersPtrComparer< 4, float * > 
  FeatureVec4pfPtrComparer;

  typedef FeatureVectorOfPointersPtrComparer< 2, int * > 
  FeatureVec2piPtrComparer;
  typedef FeatureVectorOfPointersPtrComparer< 3, int * > 
  FeatureVec3piPtrComparer;
  typedef FeatureVectorOfPointersPtrComparer< 4, int * > 
  FeatureVec4piPtrComparer;

  
  
} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)


#endif

