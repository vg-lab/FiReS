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
#include <istream>
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
    DependenciesManager::updateProperty( this, propertyLabel );
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

  void Object::serialize( std::ostream& stream, bool minimizeStream,
    const std::string& linePrefix ) const
  {
    std::string endLine;
    std::string objectLabel;
    std::string properties;
    std::string label;
    std::string value;
    std::string continueBracket;

    if ( minimizeStream )
    {
      endLine = std::string( "" );
      objectLabel = std::string( "\"objectLabel\":\"" );
      properties = std::string( "\"properties\":[" );
      label = std::string( "{\"label\":\"" );
      value = std::string( "\"value\":\"" );
      continueBracket = std::string( "}," ) + label;
    }
    else
    {
      endLine = std::string( "\n" ) + linePrefix;
      objectLabel = endLine + std::string( "  \"objectLabel\": \"" );
      properties = endLine + std::string( "  \"properties\": [" );
      label = endLine + std::string( "    {" ) + endLine +
              std::string( "      \"label\": \"" );
      value = endLine + std::string( "      \"value\": \"" );
      continueBracket = std::string( "    }," ) + label;
      stream << linePrefix;
    }

    stream << "{" << objectLabel << this->_label << "\"," << properties;

    if( _properties.empty( ))
    {
      Log::log("Exporting object without properties.",LOG_LEVEL_WARNING );
    }
    else
    {
      auto prop = this->_properties.begin( );
      std::string propertyValue =
        PropertyManager::getPropertyCaster( prop->first )
        ->toString( prop->second );
      std::string propertyLabel =
        PropertyGIDsManager::getPropertyLabel( prop->first );


      stream << label << propertyLabel << "\"," << value
        << propertyValue << '"' << endLine;

      while ( ++prop != _properties.end( ))
      {
        propertyValue = PropertyManager::getPropertyCaster( prop->first )
          ->toString( prop->second );
        propertyLabel = PropertyGIDsManager::getPropertyLabel( prop->first );

        stream << continueBracket << propertyLabel << "\"," << value
          << propertyValue << '"' << endLine;
      }
      if( minimizeStream )
      {
        stream << "}";
      }
      else
      {
        stream << "    }" << endLine;
      }
    }
    if( minimizeStream )
    {
      stream << "]}";
    }
    else
    {
      stream << "  ]" << endLine << "}";
    }
  }

  void Object::deserialize( std::istream &stream )
  {
    boost::property_tree::ptree root;
    try
    {
      boost::property_tree::read_json( stream, root );
    }
    catch ( std::exception const& ex )
    {
      Log::log( "ERROR: reading JSON: " + std::string( ex.what( )),
        LOG_LEVEL_ERROR );
    };

    deserialize( root );
  }

  void Object::deserialize( const boost::property_tree::ptree &root )
  {
    if ( !root.empty( ))
    {
      Log::log( "ERROR: empty JSON file" ,
        LOG_LEVEL_ERROR );
    }
    try
    {
      std::string objectLabel = root.get< std::string >( "objectLabel" );
      this->_label = objectLabel;
    }
    catch ( std::exception const& ex )
    {
      Log::log( "ERROR: getting objectLabel from JSON: "
        + std::string( ex.what( )), LOG_LEVEL_ERROR );
    };

    boost::property_tree::ptree properties;
    try
    {
      properties = root.get_child( "properties" );
    }
    catch ( std::exception const& ex )
    {
      Log::log( "ERROR: getting properties Array from JSON: "
        + std::string( ex.what( )), LOG_LEVEL_ERROR );
      return;
    };

    for ( const auto& propertyJSON : properties )
    {
      try
      {
        const std::string propertyLabel =
          propertyJSON.second.get< std::string >( "label" );
        const std::string propertyValue =
          propertyJSON.second.get< std::string >( "value" );

        Property property;
        PropertyManager::getPropertyCaster( propertyLabel )
          ->fromString( property, propertyValue );
        this->registerProperty( propertyLabel,property );
      }
      catch ( std::exception const& ex )
      {
        Log::log( "ERROR: getting property from JSON: "
          +std::string( ex.what( )), LOG_LEVEL_ERROR );
      };
    }
  }

} // namespace fires

// EOF
