/**
 * @file    FeaturePtrToFloat.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_FLOAT_PTR_H__
#define __FIRES__FEATURE_FLOAT_PTR_H__


#include "FeaturePtr.h"

namespace fires
{

  /*! \class FeaturePtrToFloat
   \brief Feature class that has a pointer to a float value
   */
  class FeaturePtrToFloat
    : public FeaturePtr< float >
  {

  public:

    FeaturePtrToFloat( float * pointer )
      : FeaturePtr( pointer )
    {
    }

    virtual FeaturePtrToFloat & operator +=( const Feature & rhs)
    {
      if ( this != & rhs )
      {
        const FeaturePtrToFloat * feat =
          static_cast< const FeaturePtrToFloat * >( & rhs );

        float * rhsValue = feat->value( );
        ( * this->_value ) += ( * rhsValue );

      }
      return * this;
    }


    virtual FeaturePtrToFloat & operator /= ( const int & rhs )
    {
      ( * this->_value ) /=  rhs;
      return * this;

    }

    virtual Feature * newFeature( void ) const
    {
      return new FeaturePtrToFloat( new float );
    }



  };

//  typedef FeaturePtr< float > FeaturePtrToFloat;

}


#endif
