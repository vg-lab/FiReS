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

#include <fires/api.h>

namespace fires
{

  /*! \class Feature
   \brief Feature generic class from which real features have to be derived
   */
  class Feature
  {

  public:

    FIRES_API
    Feature( void );

    FIRES_API
    virtual ~Feature( );

    FIRES_API
    virtual Feature* newFeature( void ) const;

    FIRES_API
    virtual void deleteFeature( void );

    FIRES_API
    virtual Feature& operator +=( const Feature& rhs);

    FIRES_API
    virtual Feature& operator /= ( const int& rhs );


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
