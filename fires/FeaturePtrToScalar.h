/**
 * @file    FeaturePtrToScalar.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_SCALAR_PTR_H__
#define __FIRES__FEATURE_SCALAR_PTR_H__


#include "FeaturePtr.h"

namespace fires
{

  /*! \class FeaturePtrToScalar
   \brief Feature class that has a pointer to a scalar value
   */
  template < typename TYPE > class FeaturePtrToScalar
    : public FeaturePtr< TYPE >
  {

  public:

    FeaturePtrToScalar( TYPE* pointer )
      : FeaturePtr< TYPE >( pointer )
    {
    }

    virtual FeaturePtrToScalar & operator +=( const Feature & rhs )
    {
      if ( this != & rhs )
      {
        const FeaturePtrToScalar< TYPE >* feat =
          static_cast< const FeaturePtrToScalar * >( & rhs );

        TYPE * rhsValue = feat->value( );
        ( * this->_value ) += ( * rhsValue );

      }
      return * this;
    }


    virtual FeaturePtrToScalar & operator /= ( const int & rhs )
    {
      ( * this->_value ) /=  rhs;
      return * this;

    }

    virtual Feature * newFeature( void ) const
    {
      return new FeaturePtrToScalar( new TYPE );
    }



  };


}


#endif
