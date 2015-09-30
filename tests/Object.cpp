/**
 * @file    Object.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
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
