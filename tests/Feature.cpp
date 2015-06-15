/**
 * @file    Feature.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_feature )
{

  fires::Feature *f1 = new fires::Feature;
  fires::Feature f2;
  BOOST_CHECK( f1->empty( ) == true );
  BOOST_CHECK( f2.empty( ) == true );
  BOOST_REQUIRE_THROW( f1->value< int >( ), boost::bad_any_cast);
  BOOST_REQUIRE_THROW( f2.value< int >( ), boost::bad_any_cast );
  
  *f1 = 3;
  f2 = 5.4f;
  BOOST_CHECK( f1->empty( ) == false );
  BOOST_CHECK( f2.empty( ) == false );
  BOOST_REQUIRE_THROW( f1->value< double >( ), boost::bad_any_cast );
  BOOST_REQUIRE_THROW( f2.value< double >( ), boost::bad_any_cast );
  BOOST_CHECK( f1->value< int >( ) == 3 );
  BOOST_CHECK( f2.value< float >( ) == 5.4f );
  BOOST_CHECK( typeid( int ).name( ) == f1->type( ));
  BOOST_CHECK( typeid( float ).name( ) == f2.type( ));


  *f1 = fires::Feature( );
  f2 = fires::Feature( );
  BOOST_CHECK( f1->empty( ) == true );
  BOOST_CHECK( f2.empty( ) == true );
  BOOST_REQUIRE_THROW( f1->value< int >( ), boost::bad_any_cast );
  BOOST_REQUIRE_THROW( f2.value< float >( ), boost::bad_any_cast );

  f1->set( 3.6 );
  f2.set( 5 );
  BOOST_CHECK( f1->empty( ) == false );
  BOOST_CHECK( f2.empty( ) == false );
  BOOST_REQUIRE_THROW( f1->value< int >( ), boost::bad_any_cast );
  BOOST_REQUIRE_THROW( f2.value< double >( ), boost::bad_any_cast );
  BOOST_CHECK( f1->value< double >( ) == 3.6 );
  BOOST_CHECK( f2.value< int >( ) == 5 );
  BOOST_CHECK( typeid( double ).name( ) == f1->type( ));
  BOOST_CHECK( typeid( int ).name( ) == f2.type( ));


  f1->set(( unsigned int ) 4 );
  f2.set( 4.5f );
  BOOST_CHECK( f1->empty( ) == false );
  BOOST_CHECK( f2.empty( ) == false );
  BOOST_REQUIRE_THROW( f1->value< int >( ), boost::bad_any_cast );
  BOOST_REQUIRE_THROW( f2.value< double >( ), boost::bad_any_cast );
  BOOST_CHECK( f1->value< unsigned int >( ) == 4 );
  BOOST_CHECK( f2.value< float >( ) == 4.5f );
  BOOST_CHECK( typeid( unsigned int ).name( ) == f1->type( ));
  BOOST_CHECK( typeid( float ).name( ) == f2.type( ));




  delete f1;

}
