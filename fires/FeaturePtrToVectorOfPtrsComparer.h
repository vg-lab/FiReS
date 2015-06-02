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
  class FeaturePtrToVectorOfPtrsComparer
    : public FeatureVectorComparer
  {
  public:

    FeaturePtrToVectorOfPtrsComparer( void )
      : FeatureVectorComparer( )
    {
    }

    /**
     * Virtual method to compute distance between to vector pointers
     * @param f1 First feature to compare.
     * @param f2 Second feature to compare.
     * @return Distance between features
     */
    virtual float distance(Feature *f1, Feature *f2) const
    {

      FeaturePtrToVectorOfPtrs< M, T > * ffp1 =
        dynamic_cast< FeaturePtrToVectorOfPtrs< M, T > * >( f1 );
      FeaturePtrToVectorOfPtrs< M, T > * ffp2 =
        dynamic_cast< FeaturePtrToVectorOfPtrs< M, T > * >( f2 );

      if ( !ffp1 || !ffp2 )
      {
        std::cerr << "Error casting to FeaturePtrToVectorOfPtrs "
                  << "for distance computation"
                  << std::endl;
        return 0.0f;
      }

      // vmml::vector< M, T > * v1 = ffp1->value( );
      // vmml::vector< M, T > * v2 = ffp2->value( );

      // Convert to float to compute distances
      vmml::vector< M, float > v1f;
      for ( unsigned int i = 0; i < M ; i++ )
      {
        vmml::vector< M, T * > v = ( * ffp1->value( ));
        v1f( i ) = * v( i );
      }

      vmml::vector< M, float > v2f( * ( * ffp2->value( )));
      for ( unsigned int i = 0; i < M ; i++ )
      {
        vmml::vector< M, T * > v = ( * ffp2->value( ));
        v2f( i ) = * v( i );
      }


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


  typedef FeaturePtrToVectorOfPtrsComparer< 2, float >
  FeaturePtrToVec2pfComparer;
  typedef FeaturePtrToVectorOfPtrsComparer< 3, float >
  FeaturePtrToVec3pfComparer;
  typedef FeaturePtrToVectorOfPtrsComparer< 4, float >
  FeaturePtrToVec4pfComparer;

  typedef FeaturePtrToVectorOfPtrsComparer< 2, int >
  FeaturePtrToVec2piComparer;
  typedef FeaturePtrToVectorOfPtrsComparer< 3, int >
  FeaturePtrToVec3piComparer;
  typedef FeaturePtrToVectorOfPtrsComparer< 4, int >
  FeaturePtrToVec4piComparer;



} // namespace fires

#endif // (FIRES_WITH_VMMLIB == 1)


#endif
