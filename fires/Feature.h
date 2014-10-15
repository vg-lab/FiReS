/**
 * @file    Feature.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURE_H__
#define __FIRES__FEATURE_H__

#include <stdexcept> // runtime_error


namespace fires
{

  /*! \class Feature
   \brief Feature class from which real features have to be derived
   */
  class Feature 
  {

  public:
    virtual ~Feature( ) {};

    virtual Feature * newFeature( void ) const 
    { 
      return nullptr;
    };


    virtual Feature & operator +=( const Feature & rhs) 
    {
      throw std::runtime_error("Error: += operator not implemented");
    }

    virtual Feature & operator /= ( const int & rhs ) 
    {
      throw std::runtime_error("Error: += operator not implemented");
    }


  };

}


#endif
