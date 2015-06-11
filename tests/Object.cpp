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
  fires::Feature f1( 2 ), f2( 3.2f );

  // registerFeature and getFeature test
  obj.registerFeature( "feature1", f1 );
  BOOST_CHECK( !obj.getFeature( "feature1" ).empty( ));
  BOOST_CHECK( obj.getFeature( "feature1" ).value< int >( ) ==
               f1.value< int >( ));
  BOOST_CHECK( f1.value< int >( ) == 2 );
  BOOST_REQUIRE_THROW( obj.getFeature( "feature2" ), fires::exception );

  obj.registerFeature( std::string( "feature2" ), f2 );
  BOOST_CHECK( !obj.getFeature( "feature1" ).empty( ));
  BOOST_CHECK( obj.getFeature( "feature1" ).value< int >( ) ==
               f1.value< int >( ));
  BOOST_CHECK( f1.value< int >( ) == 2 );
  BOOST_CHECK( !obj.getFeature( "feature2" ).empty( ));
  BOOST_CHECK( obj.getFeature( "feature2" ).value< float >( ) ==
               f2.value< float >( ));
  BOOST_CHECK( f2.value< float >( ) == 3.2f );

  // setFeature tests
  BOOST_CHECK( !obj.setFeature( "nonexistingfeature", f2 ));

  BOOST_CHECK( obj.setFeature( "feature1", f2 ));
  BOOST_CHECK( !obj.getFeature( "feature1" ).empty( ));
  BOOST_CHECK( obj.getFeature( "feature1" ).value< float >( ) ==
               f2.value< float >( ));

  // clearFeatures tests
  obj.clearFeatures( );
  BOOST_REQUIRE_THROW( obj.getFeature( "feature1" ), fires::exception );
  BOOST_REQUIRE_THROW( obj.getFeature( "feature2" ), fires::exception );

  // label tests
  #define TEST_LABEL "testLabel"

  obj.label() = TEST_LABEL;
  BOOST_CHECK_EQUAL( obj.label(), TEST_LABEL );
  obj.label( ) = "";
  BOOST_CHECK( obj.label() != TEST_LABEL );
}
