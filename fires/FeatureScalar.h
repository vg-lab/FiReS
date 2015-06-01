/**
 * @file    FeatureScalar.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_SCALAR_H__
#define __FIRES__FEATURE_SCALAR_H__


#include "Feature.h"

#include <iostream>

namespace fires
{

  /*! \class FeaturePtr
   */
  template< typename TYPE > class FeatureScalar
    : public Feature
  {

  public:
    FIRES_API
    FeatureScalar( TYPE value_ = ( TYPE ) 0 )
    {
      _value = value_;
    };

    FIRES_API
    virtual ~FeatureScalar( void ) {};

    FIRES_API
    virtual void value( const TYPE value_ )
    {
      _value = value_;
    };

    FIRES_API
    virtual TYPE value( void ) const
    {
      return _value;
    };

    FIRES_API
    virtual Feature* newFeature( void ) const
    {
      return new FeatureScalar( );
    }

    FIRES_API
    virtual FeatureScalar & operator +=( const Feature& rhs)
    {
      if ( this != & rhs )
      {
        const FeatureScalar* rhsFeatureScalar =
          dynamic_cast< const FeatureScalar* >( &rhs );

        if ( !rhsFeatureScalar )
          throw std::runtime_error(
            std::string( "Error: FeatureScalar operator += right " ) +
            std::string( "hand side type not valid" ));
        else
          this->_value += rhsFeatureScalar->value( );
      }
      return * this;
    }


    FIRES_API
    virtual FeatureScalar & operator /= ( const int& rhs )
    {
      this->_value /=  ( TYPE ) rhs;
      return * this;
    }

    // Feature* asloat( )
    // {
    //   return this;
    // }

  protected:

    TYPE _value;


  }; // class FeatureScalar

} // namespace fires


#endif
