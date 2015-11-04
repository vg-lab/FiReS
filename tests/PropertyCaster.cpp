/**
 * @file    PropertyCaster.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( property_scalar_to_int )
{

  fires::Property f1( 3.7f );
  fires::Property f2( 4.2f );

  fires::ScalarPropertyCaster< float > sfcf;
  fires::PropertyCaster* pfc = new fires::ScalarPropertyCaster< float >;

  // default rounding
  BOOST_CHECK( sfcf.toInt( f1 ) == 4 );
  BOOST_CHECK( sfcf.toInt( f2 ) == 4 );
  BOOST_CHECK( pfc->toInt( f1 ) == 4 );
  BOOST_CHECK( pfc->toInt( f2 ) == 4 );

  // rounding
  BOOST_CHECK( sfcf.toInt( f1, fires::PropertyCaster::ROUND ) == 4 );
  BOOST_CHECK( sfcf.toInt( f2, fires::PropertyCaster::ROUND ) == 4 );
  BOOST_CHECK( pfc->toInt( f1, fires::PropertyCaster::ROUND ) == 4 );
  BOOST_CHECK( pfc->toInt( f2, fires::PropertyCaster::ROUND ) == 4 );

  // flooring
  BOOST_CHECK( sfcf.toInt( f1, fires::PropertyCaster::FLOOR ) == 3 );
  BOOST_CHECK( sfcf.toInt( f2, fires::PropertyCaster::FLOOR ) == 4 );
  BOOST_CHECK( pfc->toInt( f1, fires::PropertyCaster::FLOOR ) == 3 );
  BOOST_CHECK( pfc->toInt( f2, fires::PropertyCaster::FLOOR ) == 4 );

  // ceiling
  BOOST_CHECK( sfcf.toInt( f1, fires::PropertyCaster::CEIL ) == 4 );
  BOOST_CHECK( sfcf.toInt( f2, fires::PropertyCaster::CEIL ) == 5 );
  BOOST_CHECK( pfc->toInt( f1, fires::PropertyCaster::CEIL ) == 4 );
  BOOST_CHECK( pfc->toInt( f2, fires::PropertyCaster::CEIL ) == 5 );

  delete pfc;

}

BOOST_AUTO_TEST_CASE( property_scalar_to_string )
{

  fires::Property p1( 3.7f );
  fires::Property p2( 4.3434 );
  fires::Property p3( 5 );

  fires::ScalarPropertyCaster< float > spcf;
  fires::ScalarPropertyCaster< double > spcd;
  fires::ScalarPropertyCaster< int > spci;

  BOOST_CHECK( spcf.toString( p1 ) == std::string( "3.7" ));
  BOOST_CHECK( spcd.toString( p2 ) == std::string( "4.3434" ));
  BOOST_CHECK( spci.toString( p3 ) == std::string( "5" ));

}
