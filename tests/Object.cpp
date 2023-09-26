/**
 * @file    Object.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) VG-Lab/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_object )
{

  fires::Object obj;
  fires::Property f1( 2 ), f2( 3.2f );

  // registerProperty and getProperty test
  obj.registerProperty( "property1", f1 );
  BOOST_CHECK( !obj.getProperty( "property1" ).empty( ));
  BOOST_CHECK( obj.getProperty( "property1" ).value< int >( ) ==
               f1.value< int >( ));
  BOOST_CHECK( f1.value< int >( ) == 2 );
  BOOST_REQUIRE_THROW( obj.getProperty( "property2" ), fires::exception );

  obj.registerProperty( std::string( "property2" ), f2 );
  BOOST_CHECK( !obj.getProperty( "property1" ).empty( ));
  BOOST_CHECK( obj.getProperty( "property1" ).value< int >( ) ==
               f1.value< int >( ));
  BOOST_CHECK( f1.value< int >( ) == 2 );
  BOOST_CHECK( !obj.getProperty( "property2" ).empty( ));
  BOOST_CHECK( obj.getProperty( "property2" ).value< float >( ) ==
               f2.value< float >( ));
  BOOST_CHECK( f2.value< float >( ) == 3.2f );

  // setProperty tests
  BOOST_CHECK( !obj.setProperty( "nonexistingproperty", f2 ));

  BOOST_CHECK( obj.setProperty( "property1", f2 ));
  BOOST_CHECK( !obj.getProperty( "property1" ).empty( ));
  BOOST_CHECK( obj.getProperty( "property1" ).value< float >( ) ==
               f2.value< float >( ));

  // clearProperties tests
  obj.clearProperties( );
  BOOST_REQUIRE_THROW( obj.getProperty( "property1" ), fires::exception );
  BOOST_REQUIRE_THROW( obj.getProperty( "property2" ), fires::exception );

  // label tests
  #define TEST_LABEL "testLabel"

  obj.label() = TEST_LABEL;
  BOOST_CHECK_EQUAL( obj.label(), TEST_LABEL );
  obj.label( ) = "";
  BOOST_CHECK( obj.label() != TEST_LABEL );
}

BOOST_AUTO_TEST_CASE( test_assignation )
{
  fires::Object o1, o2;

  o1.registerProperty( "p1", 3.0f );
  o1.registerProperty( "p2", std::string( "hello" ));

  BOOST_CHECK( o1.getProperty( "p1" ).value< float >( ) == 3.0f );
  BOOST_CHECK( o1.getProperty( "p2" ).value< std::string >( ) ==
               std::string( "hello" ));

  BOOST_REQUIRE_THROW( o2.getProperty( "p1" ), fires::exception );
  BOOST_REQUIRE_THROW( o2.getProperty( "p2" ), fires::exception );

  fires::Object o3( o1 );
  o2 = o1;

  o1.setProperty( "p1", 4.0f );
  o1.setProperty( "p2", std::string( "bye" ));

  BOOST_CHECK( o1.getProperty( "p1" ).value< float >( ) == 4.0f );
  BOOST_CHECK( o1.getProperty( "p2" ).value< std::string >( ) ==
               std::string( "bye" ));
  BOOST_CHECK( o2.getProperty( "p1" ).value< float >( ) == 3.0f );
  BOOST_CHECK( o2.getProperty( "p2" ).value< std::string >( ) ==
               std::string( "hello" ));
  BOOST_CHECK( o3.getProperty( "p1" ).value< float >( ) == 3.0f );
  BOOST_CHECK( o3.getProperty( "p2" ).value< std::string >( ) ==
               std::string( "hello" ));


}
