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

  fires::Feature f1, f2;

  obj.addFeature( "feature1", &f1 );
  BOOST_CHECK( obj.getFeature( "feature1" ) != nullptr );
  BOOST_CHECK( obj.getFeature( "feature1" ) == &f1 );
  BOOST_CHECK( obj.getFeature( "feature2" ) == nullptr );

  obj.addFeature( std::string("feature2"), &f2 );
  BOOST_CHECK( obj.getFeature( "feature1" ) != nullptr );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature1" ), &f1 );
  BOOST_CHECK( obj.getFeature( "feature2" ) != nullptr );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature2" ), &f2 );

  obj.addFeature( std::string("feature1"), &f2 );
  BOOST_CHECK_EQUAL( obj.getFeature( std::string( "feature1" ) ), &f1 );

  obj.delFeature( std::string("feature2"));
  BOOST_CHECK( obj.getFeature( "feature2" ) == nullptr );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature1" ), &f1 );

  obj.addFeature( "feature2", &f2 );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature2" ), &f2 );


  obj.setFeature( "feature1", &f2 );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature1" ), &f2 );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature2" ), &f2 );

  obj.setFeature( "feature2", &f1 );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature1" ), &f2 );
  BOOST_CHECK_EQUAL( obj.getFeature( "feature2" ), &f1 );

  obj.clearFeatures( );
  BOOST_CHECK( obj.getFeature( "feature1" ) == nullptr );
  BOOST_CHECK( obj.getFeature( "feature2" ) == nullptr );

  #define TEST_LABEL "testLabel"

  obj.label() = TEST_LABEL;
  BOOST_CHECK_EQUAL( obj.label(), TEST_LABEL );
  obj.label( ) = "";
  BOOST_CHECK( obj.label() != TEST_LABEL );
}
