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

  BOOST_CHECK( f1->newFeature( ) == nullptr );
  BOOST_CHECK( f2.newFeature( ) == nullptr );

  f1->deleteFeature( );
  f2.deleteFeature( );

  BOOST_REQUIRE_THROW( f2 += *f1, std::runtime_error );
  BOOST_REQUIRE_THROW( f2 /= 2.0f, std::runtime_error );
  BOOST_REQUIRE_THROW( *f1 /= 2.0f, std::runtime_error );

  delete f1;

}
