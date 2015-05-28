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

    virtual void deleteFeature( void ) const
    {
      return;
    };


    virtual Feature & operator +=( const Feature & rhs)
    {
      throw std::runtime_error(
        std::string( "Error: += operator not implemented for Feature." ) +
        std::string( " rhs address = " + std::to_string( long( & rhs ))));

      return *this;
    }

    virtual Feature & operator /= ( const int & rhs )
    {
      throw std::runtime_error(
        std::string( "Error: /= operator not implemented Feature ") +
        std::string( "( rhs = " ) + std::to_string( rhs ) +
        std::string( ")" ));

      return *this;
    }


    // virtual FeatureScalar<float>* asFloat( void )
    // {
    //   return nullptr;
    // }

    // virtual float asFloatValue( void )
    // {
    //   if ( this->asFloat( ) )
    //     return this->asFloat( )->value( );
    //   else
    //     0.0;
    // }
 };

}


#endif
