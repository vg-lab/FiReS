/**
 * @file    FeaturePtr.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_feature_ptr )
{

  float f1 = 3.5f;
  float f2 = 4.6;

  fires::FeaturePtr< float >* ff1 = new fires::FeaturePtr< float >( &f1 );
  fires::FeaturePtr< float > ff2( &f2 );

  BOOST_CHECK( ff1->value( ) == &f1 );
  BOOST_CHECK( ff2.value( ) == &f2 );

  fires::Feature* f;

  f = ff1->newFeature( );
  BOOST_CHECK( f != 0 );
  fires::FeaturePtr< float >* ff3 =
    dynamic_cast< fires::FeaturePtr< float >* >( f );
  BOOST_CHECK( ff3 != 0 );

  BOOST_REQUIRE_THROW( ff2 += *ff1, std::runtime_error );
  BOOST_REQUIRE_THROW( ff2 /= 2.0f, std::runtime_error );

}
