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

  ObjectProperties::ObjectProperties( void )
  {
  }

  void ObjectProperties::registerProperty( const std::string& label,
                                           const Property& property )
  {
//    Property p = property

    auto ret = this->insert( std::pair< std::string, Property >
                             ( label, property ));

    if ( !ret.second )
      ( *this )[ label ] = property;
  }

  bool ObjectProperties::unregisterProperty( const std::string& label )
  {
    ObjectProperties::const_iterator it = this->find( label );

    if ( it == this->end( ) )
      return false;

    this->erase( it );
    return true;
  }

  Property& ObjectProperties::get( const std::string& label )
  {
    ObjectProperties::iterator it = this->find( label );

    FIRES_CHECK_THROW( it != this->end( ),
                       std::string( "non existing property '" ) +
                       label + std::string( "'" ))
      return ( *it ).second;
  }

  const Property& ObjectProperties::get( const std::string& label ) const
  {
    ObjectProperties::const_iterator it = this->find( label );

    FIRES_CHECK_THROW( it != this->end( ),
                       std::string( "non existing property '" ) +
                       label + std::string( "'" ))
      return ( *it ).second;
  }

  bool ObjectProperties::set( const std::string& label,
                              const Property& property )
  {
    ObjectProperties::const_iterator it = this->find( label );

    if ( it == this->end( ))
      return false;

    ( * this )[label] = property;
    return true;
  }

  Object::Object( void )
    : _properties( )
    , _label( "" )
  {
  }

  Object::Object( Object& object )
    : _properties( object._properties )
    , _label( object._label )
  {
  }

  Object::~Object( void )
  {
  }


  void Object::registerProperty( const std::string& propertyLabel,
                                 const Property& property )
  {
    _properties.registerProperty( propertyLabel, property );
  }

  Property& Object::getProperty( const std::string& propertyLabel )
  {
    return _properties.get( propertyLabel );
  }

  const Property& Object::getProperty( const std::string& propertyLabel ) const
  {
    return _properties.get( propertyLabel );
  }

  bool Object::setProperty( const std::string& propertyLabel,
                            const Property& property)
  {
    return _properties.set( propertyLabel, property );
  }

  bool Object::unregisterProperty( const std::string& propertyLabel )
  {
    return _properties.unregisterProperty( propertyLabel );
  }

  void Object::clearProperties( void )
  {
    _properties.clear( );
  }

  bool Object::hasProperty( const std::string& label_ ) const
  {
    return _properties.find( label_ ) != _properties.end( );
  }

  ObjectProperties& Object::getProperties( void )
  {
    return _properties;
  }

  const ObjectProperties& Object::getProperties( void ) const
  {
    return _properties;
  }

  std::string& Object::label( void )
  {
    return _label;
  }

  std::string Object::label( void ) const
  {
    return _label;
  }

  Object& Object::operator= ( const Object& other )
  {
    this->_properties = other.getProperties( );
    _label = other.label( );
    return *this;
  }

 } // namespace fires

// EOF
