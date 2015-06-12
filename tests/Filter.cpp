/**
 * @file    Filter.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_filter )
{

  fires::FilterScalarRange< float > fsr( 3.0f, 4.0f );

  BOOST_CHECK_EQUAL( fsr.min( ), 3.0f );
  BOOST_CHECK_EQUAL( fsr.max( ), 4.0f );
  BOOST_CHECK_EQUAL( fsr.minEndpoint( ), fires::FilterRange::OPENED_ENDPOINT );
  BOOST_CHECK_EQUAL( fsr.maxEndpoint( ), fires::FilterRange::OPENED_ENDPOINT );
  BOOST_CHECK_EQUAL( fsr.rangeInclusion( ), fires::FilterRange::INSIDE_RANGE );

  fires::Feature f1( 2.0f ), f2( 3.0f ), f3( 3.5f ), f4( 4.0f ), f5 ( 5.0f );

  BOOST_CHECK( !fsr.eval( f1 ));
  BOOST_CHECK( !fsr.eval( f2 ));
  BOOST_CHECK( fsr.eval( f3 ));
  BOOST_CHECK( !fsr.eval( f4 ));
  BOOST_CHECK( !fsr.eval( f5 ));

  fsr.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  BOOST_CHECK( fsr.eval( f1 ));
  BOOST_CHECK( fsr.eval( f2 ));
  BOOST_CHECK( !fsr.eval( f3 ));
  BOOST_CHECK( fsr.eval( f4 ));
  BOOST_CHECK( fsr.eval( f5 ));

  fsr.rangeInclusion( ) = fires::FilterRange::INSIDE_RANGE;
  fsr.minEndpoint( ) = fires::FilterRange::CLOSED_ENDPOINT;
  BOOST_CHECK( !fsr.eval( f1 ));
  BOOST_CHECK( fsr.eval( f2 ));
  BOOST_CHECK( fsr.eval( f3 ));
  BOOST_CHECK( !fsr.eval( f4 ));
  BOOST_CHECK( !fsr.eval( f5 ));

  fsr.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  BOOST_CHECK( fsr.eval( f1 ));
  BOOST_CHECK( !fsr.eval( f2 ));
  BOOST_CHECK( !fsr.eval( f3 ));
  BOOST_CHECK( fsr.eval( f4 ));
  BOOST_CHECK( fsr.eval( f5 ));

  fsr.rangeInclusion( ) = fires::FilterRange::INSIDE_RANGE;
  fsr.minEndpoint( ) = fires::FilterRange::OPENED_ENDPOINT;
  fsr.maxEndpoint( ) = fires::FilterRange::CLOSED_ENDPOINT;
  BOOST_CHECK( !fsr.eval( f1 ));
  BOOST_CHECK( !fsr.eval( f2 ));
  BOOST_CHECK( fsr.eval( f3 ));
  BOOST_CHECK( fsr.eval( f4 ));
  BOOST_CHECK( !fsr.eval( f5 ));

  fsr.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  BOOST_CHECK( fsr.eval( f1 ));
  BOOST_CHECK( fsr.eval( f2 ));
  BOOST_CHECK( !fsr.eval( f3 ));
  BOOST_CHECK( !fsr.eval( f4 ));
  BOOST_CHECK( fsr.eval( f5 ));

  fsr.rangeInclusion( ) = fires::FilterRange::INSIDE_RANGE;
  fsr.minEndpoint( ) = fires::FilterRange::CLOSED_ENDPOINT;
  fsr.maxEndpoint( ) = fires::FilterRange::CLOSED_ENDPOINT;
  BOOST_CHECK( !fsr.eval( f1 ));
  BOOST_CHECK( fsr.eval( f2 ));
  BOOST_CHECK( fsr.eval( f3 ));
  BOOST_CHECK( fsr.eval( f4 ));
  BOOST_CHECK( !fsr.eval( f5 ));

  fsr.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  BOOST_CHECK( fsr.eval( f1 ));
  BOOST_CHECK( !fsr.eval( f2 ));
  BOOST_CHECK( !fsr.eval( f3 ));
  BOOST_CHECK( !fsr.eval( f4 ));
  BOOST_CHECK( fsr.eval( f5 ));

}
