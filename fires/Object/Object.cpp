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

  void Object::serialize( std::ostream& stream )
  {
    FIRES_CHECK_THROW( !this-> _properties.empty( ),
      "ERROR: Exporting object without properties." );
    stream << "{" << std::endl
      << "  \"objectLabel\": \""<< this->_label << "\"," << std::endl
      << "  \"properties\":"<< std::endl << "    [" << std::endl;
    //std::cout << "Num Properties: "<<this->_properties.size()<<std::endl;
    auto prop = this-> _properties.begin( );
    std::string propertyValue = PropertyManager::getPropertyCaster(
      prop->first )->toString( prop->second );

    stream << "      {" << std::endl
       << "        \"label\": \""
       << PropertyGIDsManager::getPropertyLabel( prop->first )
       << "\"," << std::endl
       << "        \"type\": \"" << prop->second.type( ) << "\"," << std::endl
       << "        \"value\": \"" << propertyValue << '"' << std::endl;
    prop++;
    while (prop != _properties.end( )){
      propertyValue = PropertyManager::getPropertyCaster(
        prop->first )->toString( prop->second );
      stream << "      }," << std::endl << "      {" << std::endl
        << "        \"label\": \""
        << PropertyGIDsManager::getPropertyLabel( prop->first )
        << "\"," << std::endl
        << "        \"type\": \"" << prop->second.type( ) << "\"," << std::endl
        << "        \"value\": \"" << propertyValue << '"' << std::endl;
      prop++;
    }
    stream << "      }" << std::endl << "    ]" << std::endl << "}";
  }

  void Object::deserialize( std::istream &stream )
  {
    //Parsing first line: {
    std::string line;
    FIRES_CHECK_THROW( std::getline( stream, line ),
      "ERROR parsing object: Empty File." );

    auto firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );

    FIRES_CHECK_THROW( line[ firstNotWhiteSpace ] == '{',
      "ERROR parsing object: First line must be a '{' for start the JSONobject,"
      " instead does: \"" + line + "\"." );
    FIRES_CHECK_THROW( firstNotWhiteSpace == line.find_last_not_of( "  \r\t" ),
      "ERROR parsing object: in line \"" + line +
      "\" nothing must come after '{'." );

    FIRES_CHECK_THROW( std::getline( stream, line ),
       "ERROR parsing object: next line after initial '{' must"
       " specify the objectLabel but it doesn't exist" );


    //Parsing second line, objectLabe declartion: "objectLabel": "exampleValue",
    std::string labelString = std::string( "\"objectLabel\": \"" );

    firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );
    FIRES_CHECK_THROW( firstNotWhiteSpace == line.find( labelString ),
       "\"ERROR parsing object: next line after initial '{'"
       " must specify the objectLabel, instead does: " +
                       line );
    auto startString = firstNotWhiteSpace + labelString.size( );
    auto endString = line.rfind( "\"," );

    FIRES_CHECK_THROW( line.find_last_not_of( "  \r\t" ) - 1 == endString,
      "ERROR parsing object: line: \"" + line +
      "\", it must end in: '\",'." );
    std::string objectLabel =
      line.substr( startString, endString - startString );

    this->_label=objectLabel;

    //Parsing third line, properties declartion: "properties":
    FIRES_CHECK_THROW( std::getline( stream, line ),
      "ERROR parsing object: next line after the declaration of objectLabel "
      "must declare the properties, but it doesn't exist" );

    labelString = std::string( "\"properties\":" );

    firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );

    FIRES_CHECK_THROW( firstNotWhiteSpace == line.find( labelString ),
      "\"ERROR parsing object: next line after the declaration of "
      "objectLabel must declare the properties, instead does: " + line );

    FIRES_CHECK_THROW( line.find_last_not_of( "  \r\t" ) +1  ==
                         firstNotWhiteSpace + labelString.size( ),
                       "ERROR parsing object: line: \"" + line +
                       "\", it must end in: '\"properties\":'." );

     //Parsing fourth line, properties array declartion: [
    FIRES_CHECK_THROW( std::getline( stream, line ),
      "ERROR parsing object: Next line after the declaration of properties must"
      " declare the  JSONarray of the properties, instead it doesn't exit." );

    firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );

    FIRES_CHECK_THROW( line[ firstNotWhiteSpace ] == '[',
      "ERROR parsing object: Next line after the declaration of properties must"
      " declare the  JSONarray of the properties, instead does: \""
      + line + "\"." );
    FIRES_CHECK_THROW( firstNotWhiteSpace == line.find_last_not_of( "  \r\t" ),
      "ERROR parsing object: in line \"" + line +
      "\" nothing must come after '['." );


    //Properties parse bucle
    while( std::getline(stream,line) )
    {
      //Parsing property first line: {
      firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );
      FIRES_CHECK_THROW( line[ firstNotWhiteSpace ] == '{',
        "ERROR parsing object: this line must be a '{' for start the JSONobject"
        " of the property, instead does: \"" + line + "\"." );
      FIRES_CHECK_THROW( firstNotWhiteSpace ==
        line.find_last_not_of( "  \r\t" ),
        "ERROR parsing object: in line \"" + line +
        "\" nothing must come after '{'." );

      //Property second line, label declaration: "label": "exampleLabel",
      FIRES_CHECK_THROW( std::getline(stream,line ),
        "\"ERROR parsing object: next line after the property '{'"
        " must specify the label, instead it doesn't exit.");
      labelString = std::string( "\"label\": \"" );
      firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );
      FIRES_CHECK_THROW( firstNotWhiteSpace == line.find( labelString ),
        "\"ERROR parsing object: this line must specify the label,"
        " instead it does: " + line );
      startString = firstNotWhiteSpace + labelString.size( );
      endString = line.rfind( "\"," );

      FIRES_CHECK_THROW( line.find_last_not_of( "  \r\t" ) - 1 == endString,
                         "ERROR parsing object: line: \"" + line +
                         "\", it must end in: '\",'." );
      std::string propertyLabel =
        line.substr( startString, endString - startString );


      //Parsing property third line, type declaration: "type": "c++ExampleType",
      FIRES_CHECK_THROW( std::getline(stream,line ),
        "\"ERROR parsing object: next line after the declaration fo the label"
        " must specify the type, instead it doesn't exit.");
      labelString = std::string( "\"type\": \"" );
      firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );
      FIRES_CHECK_THROW( firstNotWhiteSpace == line.find( labelString ),
         "\"ERROR parsing object: this line must specify the type,"
         " instead it does: " + line );
      startString = firstNotWhiteSpace + labelString.size( );
      endString = line.rfind( "\"," );

      FIRES_CHECK_THROW( line.find_last_not_of( "  \r\t" ) - 1 == endString,
        "ERROR parsing object: line: \"" + line +
        "\", it must end in: '\",'." );
      std::string typeLabel =
        line.substr( startString, endString - startString );

      //Parsing property fourth line, value declaration: "value": "casterValue",
      FIRES_CHECK_THROW( std::getline(stream,line ),
        "\"ERROR parsing object: next line after the declaration fo the type "
        "must specify the value, instead it doesn't exit.");
      labelString = std::string( "\"value\": \"" );
      firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );
      FIRES_CHECK_THROW( firstNotWhiteSpace == line.find( labelString ),
        "\"ERROR parsing object: this line must specify the value,"
        " instead it does: " + line );
      startString = firstNotWhiteSpace + labelString.size( );
      endString = line.rfind( "\"" );

      FIRES_CHECK_THROW( line.find_last_not_of( "  \r\t" ) == endString,
        "ERROR parsing object: line: \"" + line + "\", it must end in: '\"'." );
      std::string valueLabel =
        line.substr( startString, endString - startString );


      Property property;
      std::type_index* serializeInfo =
        PropertyManager::getSerializeIndex(typeLabel);
      auto caster = PropertyManager::getTypeCaster(*serializeInfo);

      caster->fromString(property,valueLabel);
      this->registerProperty(propertyLabel,property);
      PropertyManager::registerProperty(propertyLabel,*serializeInfo, caster,
        PropertyManager::getTypeAggregator(*serializeInfo),
        PropertyManager::getTypeSorter(*serializeInfo), nullptr);

      //std::cout << "label: " << propertyLabel << " type: " << typeLabel
      //  << " value: " << valueLabel << std::endl;

      //Parsing property final line, close JSONObject
      FIRES_CHECK_THROW( std::getline(stream,line ),
         "\"ERROR parsing object: next line after the declaration fo the value"
         " must close the property JSONObject, instead it doesn't exit.");

      firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );
      FIRES_CHECK_THROW( line[ firstNotWhiteSpace ] == '}',
        "ERROR parsing object: this line must close the JSONobject "
        "of the property, instead does: \"" + line + "\"." );
      if( line[ firstNotWhiteSpace + 1 ] == ',' ){
        FIRES_CHECK_THROW(
          firstNotWhiteSpace + 1 == line.find_last_not_of( "  \r\t" ),
          "ERROR parsing object: in line \"" + line +
          "\" nothing must come after '},'." );
      }else
      {
        FIRES_CHECK_THROW(
          firstNotWhiteSpace == line.find_last_not_of( "  \r\t" ),
          "ERROR parsing object: in line \"" + line +
          "\" nothing must come after '}'." );
        break;
      }
    }
    FIRES_CHECK_THROW( std::getline( stream, line ),
      "ERROR parsing object: this line must close the JSONArray"
      " but instead it doesn't exit" );

    firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );

    FIRES_CHECK_THROW( line[ firstNotWhiteSpace ] == ']',
      "ERROR parsing object: this line must be a ']' for close the JSONArray,"
      " instead does: \"" + line + "\"." );
    FIRES_CHECK_THROW( firstNotWhiteSpace == line.find_last_not_of( "  \r\t" ),
      "ERROR parsing object: in line \"" + line
      +  "\" nothing must come after ']'." );

    FIRES_CHECK_THROW( std::getline( stream, line ),
       "ERROR parsing object: this line must close the JSONObject"
       " but instead it doesn't exit" );

    firstNotWhiteSpace = line.find_first_not_of( "  \r\t" );

    FIRES_CHECK_THROW( line[ firstNotWhiteSpace ] == '}',
      "ERROR parsing object: this line must be a '}' for close the JSONArray"
      ", instead does: \"" + line + "\"." );
    FIRES_CHECK_THROW( firstNotWhiteSpace == line.find_last_not_of( "  \r\t" ),
       "ERROR parsing object: in line \"" + line +
       "\" nothing must come after '}'." );
  }

 } // namespace fires

// EOF