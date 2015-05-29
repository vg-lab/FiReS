/**
 * @file    FeatureScalar.cpp
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

  fires::FeatureScalar< double > fd1;
  fires::FeatureScalar< float > ff1;
  fires::FeatureScalar< int > fi1;

  fires::Feature* f;

  f = fd1.newFeature( );
  BOOST_CHECK( f != 0 );
  fires::FeatureScalar< double >* fd2 =
  dynamic_cast< fires::FeatureScalar< double >* >( f );
  BOOST_CHECK( fd2 != 0 );

  f = ff1.newFeature( );
  BOOST_CHECK( f != 0 );
  fires::FeatureScalar< float >* ff2 =
  dynamic_cast< fires::FeatureScalar< float >* >( f );
  BOOST_CHECK( ff2 != 0 );

  f = fi1.newFeature( );
  BOOST_CHECK( f != 0 );
  fires::FeatureScalar< int >* fi2 =
  dynamic_cast< fires::FeatureScalar< int >* >( f );
  BOOST_CHECK( fi2 != 0 );

  fd1.value( 3.4 );
  ff1.value( 3.4f );
  fi1.value( 3 );

  BOOST_CHECK( fd1.value( ) == 3.4 );
  BOOST_CHECK( ff1.value( ) == 3.4f );
  BOOST_CHECK( fi1.value( ) == 3 );

  fd2->value( 4.5 );
  ff2->value( 4.5f );
  fi2->value( 4 );

  BOOST_CHECK( fd2->value( ) == 4.5 );
  BOOST_CHECK( ff2->value( ) == 4.5f );
  BOOST_CHECK( fi2->value( ) == 4 );

  BOOST_CHECK( fd1.value( ) != fd2->value( ));
  BOOST_CHECK( ff1.value( ) != ff2->value( ));
  BOOST_CHECK( fi1.value( ) != fi2->value( ));

  // Delete feature should't do anything
  fd1.deleteFeature( );
  ff1.deleteFeature( );
  fi1.deleteFeature( );
  fd2->deleteFeature( );
  ff2->deleteFeature( );
  fi2->deleteFeature( );

  BOOST_CHECK( fd2->value( ) == 4.5 );
  BOOST_CHECK( ff2->value( ) == 4.5f );
  BOOST_CHECK( fi2->value( ) == 4 );

  fd1 += *fd2;
  ff1 += *ff2;
  fi1 += *fi2;

  BOOST_CHECK( fd1.value( ) == 3.4 + 4.5 );
  BOOST_CHECK( ff1.value( ) == 3.4f + 4.5f );
  BOOST_CHECK( fi1.value( ) == 3 + 4 );

  fires::Feature f2;

  BOOST_REQUIRE_THROW( fd1 += f2, std::runtime_error );

  fd1 /= 3.0;
  ff1 /= 3.0f;
  fi1 /= 3;

  BOOST_CHECK( fd1.value( ) == ( 3.4 + 4.5 ) / 3.0 );
  BOOST_CHECK( ff1.value( ) == ( 3.4f + 4.5f ) / 3.0f );
  BOOST_CHECK( fi1.value( ) == ( 3 + 4 ) / 3 );

  delete fd2;
  delete ff2;
  delete fi2;


}
