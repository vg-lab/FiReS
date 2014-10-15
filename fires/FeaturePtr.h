/**
 * @file    Feature.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_PTR_H__
#define __FIRES__FEATURE_PTR_H__


#include "Feature.h"

#include <iostream>

namespace fires
{

  /*! \class FeaturePtr
   */
  template< typename TYPE > class FeaturePtr
    : public Feature
  {

  public:
    FeaturePtr( TYPE * pointer )
    { 
      _value = pointer;
    };

    virtual ~FeaturePtr( ) {};

    virtual TYPE * value( void ) const
    {
      return _value;      
    };

    virtual Feature * newFeature( void ) const
    {
      return new FeaturePtr( new TYPE );
    }


    virtual FeaturePtr & operator +=( const Feature & rhs) 
    {
      if ( this != & rhs ) 
      {	
	const FeaturePtr< TYPE > * feat = 
	  static_cast< const FeaturePtr< TYPE > * >( & rhs );

	TYPE * rhsValue = feat->value( );
	( * this->_value ) += ( * rhsValue );

      }
      return * this;
    }


    virtual FeaturePtr & operator /= ( const int & rhs ) 
    {
      ( * this->_value ) /= rhs;
      return * this;

    }


  protected:

    TYPE * _value;


  };

}


#endif
