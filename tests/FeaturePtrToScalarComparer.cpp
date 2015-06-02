/**
 * @file    FeaturePtrToScalarComparer.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_feature_scalar_comparer )
{


  double double1 = 3.5, double2 = 4.7;
  float float1 = 3.5f, float2 = 4.7f;
  int int1 = 3, int2 = 4;

  fires::Feature f1, f2;

  fires::FeaturePtrToScalar< double > fd1( &double1 );
  fires::FeaturePtrToScalar< float > ff1( &float1 );
  fires::FeaturePtrToScalar< int > fi1( &int1 );

  fires::FeaturePtrToScalar< double > fd2( &double2 );
  fires::FeaturePtrToScalar< float > ff2( &float2 );
  fires::FeaturePtrToScalar< int > fi2( &int2 );

  fires::FeaturePtrToScalarComparer < double > comparerD;
  fires::FeaturePtrToScalarComparer < float > comparerF;
  fires::FeaturePtrToScalarComparer < int > comparerI;

  // Double
  // If types are not consistent then 0 should be returned
  BOOST_CHECK_EQUAL( comparerD.distance( &f1, &f2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerD.distance( &ff1, &ff2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerD.distance( &fi1, &fi2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerD.distance( &f1, &fd2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerD.distance( &fd1, &f2 ), 0.0f );

  BOOST_CHECK_EQUAL( comparerD.distance( &fd1, &fd2 ),
                     ( float ) fabs( 3.5 - 4.7 ));
  BOOST_CHECK_EQUAL( comparerD.distance( &fd1, &fd2 ),
                     comparerD.distance( &fd2, &fd1 ));


  fires::Comparer* comparer = &comparerD;

  BOOST_CHECK_EQUAL( comparer->distance( &fd1, &fd2 ),
                     ( float ) fabs( 3.5 - 4.7 ));
  BOOST_CHECK_EQUAL( comparer->distance( &fd1, &fd2 ),
                     comparer->distance( &fd2, &fd1 ));


  // Float
  // If types are not consistent then 0 should be returned
  BOOST_CHECK_EQUAL( comparerF.distance( &f1, &f2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerF.distance( &fd1, &fd2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerF.distance( &fi1, &fi2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerF.distance( &f1, &ff2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerF.distance( &ff1, &f2 ), 0.0f );

  BOOST_CHECK_EQUAL( comparerF.distance( &ff1, &ff2 ),
                     ( float ) fabs( 3.5f - 4.7f ));
  BOOST_CHECK_EQUAL( comparerF.distance( &ff1, &ff2 ),
                     comparerF.distance( &ff2, &ff1 ));


  comparer = &comparerF;

  BOOST_CHECK_EQUAL( comparer->distance( &ff1, &ff2 ),
                     ( float ) fabs( 3.5f - 4.7f ));
  BOOST_CHECK_EQUAL( comparer->distance( &ff1, &ff2 ),
                     comparer->distance( &ff2, &ff1 ));


  // Int
  // If types are not consistent then 0 should be returned
  BOOST_CHECK_EQUAL( comparerI.distance( &f1, &f2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerI.distance( &fd1, &fd2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerI.distance( &ff1, &ff2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerI.distance( &f1, &fi2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparerI.distance( &fi1, &f2 ), 0.0f );

  BOOST_CHECK_EQUAL( comparerI.distance( &fi1, &fi2 ),
                     ( float ) fabs( float( 3 - 4 )));
  BOOST_CHECK_EQUAL( comparerI.distance( &fi1, &fi2 ),
                     comparerI.distance( &fi2, &fi1 ));


  comparer = &comparerI;

  BOOST_CHECK_EQUAL( comparer->distance( &fi1, &fi2 ),
                     ( float ) fabs( float( 3 - 4 )));
  BOOST_CHECK_EQUAL( comparer->distance( &fi1, &fi2 ),
                     comparer->distance( &fi2, &fi1 ));




}
