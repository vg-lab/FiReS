/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Iago Calvo Lista <i.calvol@alumnos.urjc.es>
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
#include <fires/fires.h>
#include <iostream>
#include <fstream>

class ExampleObject
{
public:
  ExampleObject( ){
  }
  ExampleObject(std::string value_ )
    : _value( value_)
  {
  }
  std::string value( )
  {
    return _value;
  }

private:
  std::string _value;
};

class FiresTestObject :
  public fires::Object
{
public:
  FiresTestObject( )
  {
  }
};

class MyPropertyCaster : public fires::PropertyCaster
{
public:

  virtual ~MyPropertyCaster( void )
  {
  }


  int toInt( const fires::Property&, TIntRounding  ) override
  {
    return 1;
  };
  std::string toString( const fires::Property& prop) override
  {
    return prop.value< ExampleObject >( ).value( );
  };
  void fromString(
    fires::Property& property, const std::string& value_ ) override
  {
    ExampleObject newObject( value_ );
    property.set( newObject );
  };

  std::vector< std::string > categories( void ) override
  {
    return std::vector< std::string >( );
  }
};



int main( void ){


  typedef enum {A = 0, B} TEnum;

  FiresTestObject originalObject;

  originalObject.label( ) = "object1";

  //Register the original properties
  fires::PropertyManager::registerProperty(
    &originalObject, "floatProperty", 3.1f );
  fires::PropertyManager::registerProperty(
    &originalObject, "doubleProperty", 4.1 );
  fires::PropertyManager::registerProperty(
    &originalObject, "u_intProperty", ( unsigned int ) 1 );
  fires::PropertyManager::registerProperty(
    &originalObject, "intProperty", 1 );
  fires::PropertyManager::registerProperty(
    &originalObject, "stringProperty", std::string("stringValueExample"));

  //Enum Registration
  fires::PropertyManager::registerProperty(
    &originalObject, "enum1", TEnum::B,
    {{ TEnum::A, "enum-A" }, { TEnum::B, "enum-B" }} );

  //Register property with a custom caster
  fires::PropertyManager::setPropertyTypeCaster( typeid( ExampleObject ),
    new MyPropertyCaster( ));
  fires::PropertyManager::registerProperty( &originalObject, "objectProperty",
    ExampleObject( "Example Object using custom caster" ) );

  //Serialization of first object and showing it by console
  std::stringstream stream;
  originalObject.serialize( stream );
  std::cout << "Original object: " << std::endl << stream.str( ) << std::endl;

  //Clear the property manager to start over
  fires::PropertyManager::clear( );

  //Sets the custom properties
  fires::PropertyManager::setPropertyTypeCaster(
    typeid( ExampleObject ), new MyPropertyCaster( ));
  fires::PropertyManager::setPropertyTypeCaster( typeid( TEnum ),
    new fires::EnumPropertyCaster<TEnum>(
    {{ TEnum::A, "enum-A" }, { TEnum::B, "enum-B" }}  ));
  fires::PropertyManager::addBasicTypes( );

  //Creates a new object from the old object serialization
  FiresTestObject newObject;
  newObject.deserialize( stream );

  //Shows the newObject from console
  std::stringstream newStream;
  newObject.serialize( newStream );
  std::cout << "New imported object: "<<std::endl
    << newStream.str( ) << std::endl;

}