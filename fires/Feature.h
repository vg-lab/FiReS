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


#include <fires/api.h>
#include <boost/any.hpp>
#include <iostream>

namespace fires
{


  class Feature
  {
  public:

    Feature( void )
      : _value( )
    {
    }

    virtual ~Feature( void )
    {
    }

    Feature& operator= ( const Feature& other )
    {
      this->_value = other._value;
      return *this;
    }

    template < class ValueType >
    Feature( const ValueType value_ )
    {
      _value = value_;
      // std::cout << "Feature( ) " << typeid( value_ ).name( ) << " "
      //           << _value.type( ).name( ) << std::endl;
    }

    template < class ValueType >
    void set( ValueType value_ )
    {
      _value = value_;
    }

    template < typename ValueType >
    ValueType value( void ) const
    {
      // std::cout << "Feature::Value " << _value.type( ).name( ) << std::endl;
      return boost::any_cast< ValueType >( _value );
    }

    std::string type( void ) const
    {
      return _value.type( ).name( );
    }

    virtual Feature& operator += ( const Feature& rhs )
    {

      if ( this->_value.type( ).name( ) == typeid( int ).name( ))
      {
        int accum = this->value< int >( ) +
          rhs.value< int >( );
        this->set< int >( accum );
      }
      else if ( this->_value.type( ).name( ) == typeid( float ).name( ))
      {
        float accum = this->value< float >( ) +
          rhs.value< float >( );
        this->set< float >( accum );
      }
      else if ( this->_value.type( ).name( ) == typeid( double ).name( ))
      {
        double accum = this->value< double >( ) +
          rhs.value< double >( );
        this->set< double >( accum );
      }
      else
        std::cerr << "Operator += for type " << this->_value.type( ).name( )
                  << " not implemented" << std::endl;

      return *this;

    }

  protected:
    boost::any _value;

  };



 //  /*! \Class Feature
 //   \brief Feature generic class from which real features have to be derived
 //   */
 //  class Feature
 //  {

 //  public:

 //    FIRES_API
 //    Feature( void );

 //    FIRES_API
 //    virtual ~Feature( );

 //    FIRES_API
 //    virtual Feature* newFeature( void ) const;

 //    FIRES_API
 //    virtual void deleteFeature( void );

 //    FIRES_API
 //    virtual Feature& operator +=( const Feature& rhs);

 //    FIRES_API
 //    virtual Feature& operator /= ( const int& rhs );


 //    // virtual FeatureScalar<float>* asFloat( void )
 //    // {
 //    //   return nullptr;
 //    // }

 //    // virtual float asFloatValue( void )
 //    // {
 //    //   if ( this->asFloat( ) )
 //    //     return this->asFloat( )->value( );
 //    //   else
 //    //     0.0;
 //    // }
 // };

}


#endif
