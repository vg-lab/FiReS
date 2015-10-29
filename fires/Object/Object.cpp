/**
 * @file    Object.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Object.h"
#include "../error.h"

#include <map>

#include <boost/any.hpp>

namespace fires
{
  namespace detail
  {

    class ObjectProperties
      : public std::map< std::string, Property >
    {

    public:

      ObjectProperties( void )
      {
      }

      void registerProperty( const std::string& label,
                            Property& property )
      {
        auto ret = this->insert( std::pair< std::string, Property& >
                                 ( label, property ));

        if ( !ret.second )
          ( *this )[ label ] = property;
      }

      bool unregisterProperty( const std::string& label )
      {
        ObjectProperties::const_iterator it = this->find( label );

        if ( it == this->end( ) )
          return false;

        this->erase( it );
        return true;
      }

      Property& get( const std::string& label )
      {
        ObjectProperties::iterator it = this->find( label );

          // if ( it == this->end( ) )
          // {
          //   std::cerr << "Fires::Object::getProperty: '" << label
          //             << "' not existing." << std::endl;
          //   return std::move( Property( ));
          // }

        FIRES_CHECK_THROW( it != this->end( ),
                           std::string( "non existing property '" ) +
                           label + std::string( "'" ))
        return ( *it ).second;
      }

      bool set( const std::string& label, const Property& property )
      {
        ObjectProperties::const_iterator it = this->find( label );

        if ( it == this->end( ))
          return false;

        ( * this )[label] = property;
        return true;
      }

    }; // class ObjectProperties


    class Object
    {

    public:

      Object( void )
        : _properties( )
        , _label( "" )
      {
      }

      Object( Object& object )
        : _properties( object._properties )
        , _label( object._label )
      {
      }

      void registerProperty( const std::string& propertyLabel, Property property )
      {
        _properties.registerProperty( propertyLabel, property );
      }

      Property& getProperty( const std::string& propertyLabel )
      {
        return _properties.get( propertyLabel );
      }

      bool setProperty( const std::string& propertyLabel,
                       const Property& property)
      {
        return _properties.set( propertyLabel, property );
      }

      bool unregisterProperty( const std::string& propertyLabel )
      {
        return _properties.unregisterProperty( propertyLabel );
      }

      void clearProperties( void )
      {
        _properties.clear( );
      }

      bool hasProperty( const std::string& label_ ) const
      {
        return _properties.find( label_ ) != _properties.end( );
      }

      ObjectProperties& properties( void )
      {
        return _properties;
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

      //! Set of properties of this object
      ObjectProperties _properties;

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


  void Object::registerProperty( const std::string& propertyLabel,
                                const Property& property )
  {
    _impl->registerProperty( propertyLabel, property );
  }

  bool Object::unregisterProperty( const std::string& propertyLabel )
  {
    return _impl->unregisterProperty( propertyLabel );
  }

  Property& Object::getProperty( const std::string& propertyLabel )
  {
    return _impl->getProperty( propertyLabel );
  }

  bool Object::setProperty( const std::string& propertyLabel,
                           const Property& property )
  {
    return _impl->setProperty( propertyLabel, property );
  }

  void Object::clearProperties( void )
  {
    return _impl->clearProperties( );
  }

  bool Object::hasProperty( const std::string& label_ ) const
  {
    return _impl->hasProperty( label_ );
  }

  std::map< std::string, Property >& Object::getProperties( void )
  {
    return _impl->properties( );
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
