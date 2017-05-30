/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/gmrvvis/FiReS>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#include "Object.h"
#include "../error.h"
#include "../DependenciesManager.h"
#include "../PropertyManager.h"
#include "../ObserverManager.h"

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
    auto propertyGID = PropertyGIDsManager::getPropertyGID( label );

    auto ret = this->insert( std::pair< PropertyGID, Property >
                             ( propertyGID, property ));

    if ( !ret.second )
      ( *this )[ propertyGID ] = property;

    // PropertyManager::registerProperty( label, property );
  }

  bool ObjectProperties::unregisterProperty( const std::string& label )
  {
    auto propertyGID = PropertyGIDsManager::getPropertyGID( label );

    const auto it = this->find( propertyGID );

    if ( it == this->end( ) )
      return false;

    this->erase( it );
    return true;
  }

  Property& ObjectProperties::get( const std::string& label )
  {
    auto propertyGID = PropertyGIDsManager::getPropertyGID( label );

    ObjectProperties::iterator it = this->find( propertyGID );

    FIRES_CHECK_THROW( it != this->end( ),
                       std::string( "non existing property '" ) +
                       label + std::string( "'" ));
    return ( *it ).second;
  }

  const Property& ObjectProperties::get( const std::string& label ) const
  {
    auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
    ObjectProperties::const_iterator it = this->find( propertyGID );

    FIRES_CHECK_THROW( it != this->end( ),
                       std::string( "non existing property '" ) +
                       label + std::string( "'" ));
    return ( *it ).second;
  }

  bool ObjectProperties::set( const std::string& label,
                              const Property& property )
  {
    auto propertyGID = PropertyGIDsManager::getPropertyGID( label );

    ObjectProperties::const_iterator it = this->find( propertyGID );

    if ( it == this->end( ))
      return false;

    ( * this )[ propertyGID ] = property;
    return true;
  }

  Object::Object( void )
    : _properties( )
    , _label( "" )
  {
  }

  Object::Object( const Object& object )
    : _properties( object._properties )
    , _label( object._label )
  {
  }

  Object::~Object( void )
  {
    ObserverManager::removeObserver( this );
    ObserverManager::removeNotifier( this );
    DependenciesManager::removeObject( this );
  }


  void Object::registerProperty( const std::string& propertyLabel,
                                 const Property& property )
  {
    _properties.registerProperty( propertyLabel, property );
  }

  Property& Object::getProperty( const std::string& propertyLabel )
  {
    DependenciesManager::updateProperty( this, propertyLabel );
    return _properties.get( propertyLabel );
  }

  const Property& Object::getProperty( const std::string& propertyLabel ) const
  {
    //WAR to have a const getter
    Object* nonConstObj = const_cast< Object* >( this );

    DependenciesManager::updateProperty( nonConstObj, propertyLabel );
    return _properties.get( propertyLabel );
  }

  Property& Object::operator[]( const std::string& propertyLabel )
  {
    DependenciesManager::updateProperty( this, propertyLabel );
    return this->getProperty( propertyLabel );
  }

  bool Object::setProperty( const std::string& propertyLabel,
                            const Property& property)
  {
    auto ret = _properties.set( propertyLabel, property );
    ObserverManager::trigger( this, propertyLabel );
    ObserverManager::trigger( this, FIRES_ANY );
    DependenciesManager::setDependentsDirty( this, propertyLabel );
    return ret;
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
    return _properties.find( PropertyGIDsManager::getPropertyGID( label_ )) !=
                             _properties.end( );
  }

  ObjectProperties& Object::properties( void )
  {
    return _properties;
  }

  const ObjectProperties& Object::properties( void ) const
  {
    return _properties;
  }

  std::string& Object::label( void )
  {
    return _label;
  }

  const std::string& Object::label( void ) const
  {
    return _label;
  }

  Object& Object::operator= ( const Object& other )
  {
    this->_properties = other.properties( );
    _label = other.label( );
    return *this;
  }

 } // namespace fires

// EOF
