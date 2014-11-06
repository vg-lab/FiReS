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
      throw std::runtime_error(
	std::string( "Error: += operator not implemented for FeaturePtr" ) 
	+ std::string( "rhs address = " + std::to_string( long( & rhs ))));

      return * this;
    }


    virtual FeaturePtr & operator /= ( const int & rhs ) 
    {
      throw std::runtime_error(
	std::string( "Error: /= operator not implemented FeaturePtr ") +
	std::string( "( rhs = " ) + std::to_string( rhs ) + 
	std::string( ")" ));

      return * this;
    }


  protected:

    TYPE * _value;


  };

}


#endif
