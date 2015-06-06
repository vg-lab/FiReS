/**
 * @file    Object.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Object.h"

#include <map>

#include <boost/any.hpp>

namespace fires
{
  namespace detail
  {

    // class ObjectFeatures
    //   : public std::map< std::string, Feature >
    // {
    // };

    class ObjectFeatures
      : public std::map< std::string, Feature >
    {

    public:

      ObjectFeatures( void )
      {
      }

      void registerFeature( const std::string& label,
                            const Feature& feature )
      {
        // std::cout << "ObjectFeatures::registerFeature" << std::endl;
        this->insert( std::pair< std::string, Feature >
                      ( label, feature ));
      }

      bool unregisterFeature( const std::string& label )
      {
        ObjectFeatures::const_iterator it = this->find( label );

        if ( it == this->end( ) )
          return false;

        this->erase( it );
        return true;
      }

      Feature get( const std::string& label ) const
      {
        ObjectFeatures::const_iterator it = this->find( label );

          if ( it == this->end( ) )
            std::cerr << "Feature '" << label << "' not existing." << std::endl;
          //   return Feature( );

          return ( *it ).second;
      }

      bool set( const std::string& label, Feature& feature )
      {
        ObjectFeatures::const_iterator it = this->find( label );

        if ( it == this->end( ) )
          return false;

        ( * this )[label] = feature;
        return true;
      }

    }; // class ObjectFeatures


    class Object
    {

    public:

      Object( void )
        : _features( )
        , _label( "" )
      {
      }

      Object( Object& object )
        : _features( object._features )
        , _label( object._label )
      {
      }

      void registerFeature( const std::string& featureLabel, Feature feature )
      {

        // std::cout << "detail::Object::registerFeature " << std::endl;
        // std::cout << *feature.value< int* >( ) << std::endl;

        _features.registerFeature( featureLabel, feature );

        // std::cout << *this->getFeature( "feature1" ).value< int* >( ) << std::endl;

      }

      Feature getFeature( const std::string& featureLabel )
      {
        return _features.get( featureLabel );
      }

      bool setFeature( const std::string& featureLabel, Feature& feature)
      {
        return _features.set( featureLabel, feature );
      }

      bool unregisterFeature( const std::string& featureLabel )
      {
        return _features.unregisterFeature( featureLabel );
      }

      void clearFeatures( void )
      {
        _features.clear( );
      }

      ObjectFeatures& features( void )
      {
        return _features;
      }

      std::string & label( void )
      {
        return _label;
      }

      std::string label( void ) const
      {
        return _label;
      }

    protected:

      //! Set of features of this object
      ObjectFeatures _features;

      //! Label of this object
      std::string _label;

    }; // class Object

  } // namespace detail


  Object::Object( )
    : _impl ( new detail::Object )
  {

  }

  Object::~Object( )
  {
    delete _impl;
  }

  Object::Object( Object& object )
    : _impl( new detail::Object( *object._impl ))
  {
  }


  void Object::registerFeature( const std::string& featureLabel,
                                const Feature& feature )
  {
    // std::cout << "::Object::registerFeature "; // << std::endl;
    // std::cout << *feature.value< int* >( ) << std::endl;
    // std::cout << *this->getFeature( "feature1" ).value< int* >( ) << std::endl;

    _impl->registerFeature( featureLabel, feature );
  }

  bool Object::unregisterFeature( const std::string& featureLabel )
  {
    return _impl->unregisterFeature( featureLabel );
  }

  Feature Object::getFeature( const std::string& featureLabel ) const
  {
    return _impl->getFeature( featureLabel );
  }

  bool Object::setFeature( const std::string& featureLabel, Feature& feature )
  {
    return _impl->setFeature( featureLabel, feature );
  }

  void Object::clearFeatures( void )
  {
    return _impl->clearFeatures( );
  }

  std::string& Object::label( void )
  {
    return _impl->label( );
  }

  std::string Object::label( void ) const
  {
    return _impl->label( );
  }

} // namespace fires

// EOF
