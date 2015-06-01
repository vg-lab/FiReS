/**
 * @file    FeaturePtrToScalar.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_ptr_to_scalar )
{

  double d1 = 3.4, d2 = 5.6;
  float f1 = 3.4f, f2 = 5.6f;
  int i1 = 3, i2 = 4;

  fires::FeaturePtrToScalar< double > fd1( &d1 );
  fires::FeaturePtrToScalar< float > ff1( &f1 );
  fires::FeaturePtrToScalar< int > fi1( &i1 );

  fires::FeaturePtrToScalar< double > fd2( &d2 );
  fires::FeaturePtrToScalar< float > ff2( &f2 );
  fires::FeaturePtrToScalar< int > fi2( &i2 );

  BOOST_CHECK_EQUAL( fd1.value( ), &d1 );
  BOOST_CHECK_EQUAL( ff1.value( ), &f1 );
  BOOST_CHECK_EQUAL( fi1.value( ), &i1 );

  BOOST_CHECK_EQUAL( fd2.value( ), &d2 );
  BOOST_CHECK_EQUAL( ff2.value( ), &f2 );
  BOOST_CHECK_EQUAL( fi2.value( ), &i2 );

  BOOST_CHECK_EQUAL( *fd1.value( ), 3.4 );
  BOOST_CHECK_EQUAL( *ff1.value( ), 3.4f );
  BOOST_CHECK_EQUAL( *fi1.value( ), 3 );

  BOOST_CHECK_EQUAL( *fd2.value( ), 5.6 );
  BOOST_CHECK_EQUAL( *ff2.value( ), 5.6f );
  BOOST_CHECK_EQUAL( *fi2.value( ), 4 );

  BOOST_CHECK( fd1.value( ) != fd2.value( ));
  BOOST_CHECK( ff1.value( ) != ff2.value( ));
  BOOST_CHECK( fi1.value( ) != fi2.value( ));

  fd2.value( &d1 );
  ff2.value( &f1 );
  fi2.value( &i1 );

  BOOST_CHECK_EQUAL( fd1.value( ), fd2.value( ));
  BOOST_CHECK_EQUAL( ff1.value( ), ff2.value( ));
  BOOST_CHECK_EQUAL( fi1.value( ), fi2.value( ));

  fd2.value( &d2 );
  ff2.value( &f2 );
  fi2.value( &i2 );

  BOOST_CHECK_EQUAL( fd1.value( ), fd1.value( ));
  BOOST_CHECK_EQUAL( ff1.value( ), ff1.value( ));
  BOOST_CHECK_EQUAL( fi1.value( ), fi1.value( ));


  // Testing newFeature and deleteFeature
  fires::Feature* feature;

  feature = fd1.newFeature( );
  BOOST_CHECK( feature != 0 );
  fires::FeaturePtrToScalar< double >* fd3 =
    dynamic_cast< fires::FeaturePtrToScalar< double >* >( feature );
  BOOST_CHECK( fd3 != 0 );
  BOOST_CHECK( fd3->value( ) != 0 );

  fd3->deleteFeature( );
  BOOST_CHECK( fd3->value( ) == 0 );

  delete feature;

  // Testing += and /= operators
  fd1 += fd2;
  ff1 += ff2;
  fi1 += fi2;

  BOOST_CHECK_EQUAL( *fd1.value( ), 3.4 + 5.6 );
  BOOST_CHECK_EQUAL( *ff1.value( ), 3.4f + 5.6f );
  BOOST_CHECK_EQUAL( *fi1.value( ), 3 + 4 );

  fires::Feature feature2;
  BOOST_REQUIRE_THROW( fd1 += feature2, std::runtime_error );

  fd1 /= 3.0;
  ff1 /= 3.0f;
  fi1 /= 3;

  BOOST_CHECK_EQUAL( *fd1.value( ), ( 3.4 + 5.6 ) / 3.0 );
  BOOST_CHECK_EQUAL( *ff1.value( ), ( 3.4f + 5.6f ) / 3.0f );
  BOOST_CHECK_EQUAL( *fi1.value( ), ( 3 + 4 ) / 3 );


}
