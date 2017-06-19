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
#include <fires/fires.h>
#include <string>

int main( void )
{

  // Examples with scalars
  {
    fires::Object obj;
    obj.registerProperty( "p1", 3.5f );
    obj.registerProperty( "p2", int( 2 ));

    fires::ScalarPropertyCaster< float > spcf;
    fires::ScalarPropertyCaster< int > spci;

    std::string str;

    str = spcf.toString(( obj.getProperty( "p1" )));
    std::cout << str << std::endl;

    str = spci.toString(( obj.getProperty( "p2" )));
    std::cout << str << std::endl;

    // Seting values from strings
    spcf.fromString( obj.getProperty( "p1" ), "7.6" );
    std::cout << obj.getProperty( "p1" ).value< float >( )  << std::endl;

    spci.fromString( obj.getProperty( "p2" ), "6" );
    std::cout << obj.getProperty( "p2" ).value< int >( )  << std::endl;
  }


  // Examples with enums
  {
    fires::Object obj;
    enum class TEnum { ONE = 0, TWO, THREE };
    obj.registerProperty( "enumProp", TEnum::TWO );

    fires::EnumPropertyCaster< TEnum > enumCaster(
      {{ TEnum::ONE, "ONE" }, { TEnum::TWO, "TWO" }, { TEnum::THREE, "THREE" }} );

    std::cout << enumCaster.toInt( obj.getProperty( "enumProp" )) << std::endl;
    std::cout << enumCaster.toString( obj.getProperty( "enumProp" )) << std::endl;

    // Seting the value from string
    enumCaster.fromString( obj.getProperty( "enumProp" ), "THREE" );

    std::cout << enumCaster.toInt( obj.getProperty( "enumProp" )) << std::endl;
    std::cout << enumCaster.toString( obj.getProperty( "enumProp" )) << std::endl;
  }


  // Examples with PropertyManager
  {
    fires::Object obj;
    fires::PropertyManager::registerProperty( &obj, "p1", int( 3 ));

    enum class  TEnum { A = 0, B, C };
    fires::PropertyManager::registerProperty(
      &obj, "p2", TEnum::B,
      {{ TEnum::A, "A" }, { TEnum::B, "B" }, { TEnum::C, "C" }} );

    enum class TVehicle { CAR = 0, BUS, BIKE };
    fires::PropertyManager::registerProperty(
      &obj, "p3", TVehicle::BIKE,
      {{ TVehicle::CAR, "CAR" }, { TVehicle::BUS, "BUS" },
       { TVehicle::BIKE, "BIKE" }} );

    // Now convertig a set of properties to string is homogeneous
    for ( const auto prop : { "p1", "p2", "p3" } )
    {
      std::string str =
        fires::PropertyManager::getPropertyCaster( prop )->toString(
          obj.getProperty( prop ));
      std::cout << str << std::endl;
    }

    // Get posible values of an enum property
    for ( const auto prop : { "p1", "p2", "p3" } )
    {
      auto caster =
        fires::PropertyManager::getPropertyCaster( prop );
      const auto& categories = caster->categories( );
      if ( categories.size( ) > 0 )
      {
        std::cout << prop << ": ";
        for ( const auto value : categories )
          std::cout << value << " ";
        std::cout << std::endl;
      }
    }

  }
}
