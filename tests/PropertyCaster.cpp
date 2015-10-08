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


BOOST_AUTO_TEST_CASE( test_property )
{

  fires::Property f1( 3.7f );
  fires::Property f2( 4.2f );

  fires::ScalarPropertyCaster< float > sfcf;
  fires::PropertyCaster* pfc = new fires::ScalarPropertyCaster< float >;

  std::cout << sfcf.toInt( f1 ) << std::endl;

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
