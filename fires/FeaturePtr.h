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

    virtual TYPE * value( void )
    {
      return _value;      
    };

  protected:

    TYPE * _value;


  };

}


#endif
