/**
 * @file    Comparer.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_comparer )
{

  fires::Feature f1, f2;

  fires::Comparer* comparer1 = new fires::Comparer;
  fires::Comparer comparer2;

  BOOST_CHECK_EQUAL( comparer1->distance( &f1, &f2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparer2.distance( &f1, &f2 ), 0.0f );

}
