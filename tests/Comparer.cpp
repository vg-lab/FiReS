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

  BOOST_CHECK_EQUAL( comparer1->distance( f1, f2 ), 0.0f );
  BOOST_CHECK_EQUAL( comparer2.distance( f1, f2 ), 0.0f );

  delete comparer1;

}

#define F1 3.3f
#define F2 5.3f
#define DISTANCE_F1_F2 ( float ) fabs( F1 - F2 )

BOOST_AUTO_TEST_CASE( test_scalar_comparer )
{
  fires::Feature f1( 3.3f ), f2( 5.3f );
  fires::ScalarComparer< float > c;
  BOOST_CHECK_EQUAL( c.distance( f1, f2 ), DISTANCE_F1_F2 );
}


BOOST_AUTO_TEST_CASE( test_scalar_ptr_comparer )
{
  float v1 = F1, v2 = F2;

  fires::Feature f1( &v1 ), f2( &v2 );
  fires::ScalarComparer< float* > c;
  BOOST_CHECK_EQUAL( c.distance( f1, f2 ), DISTANCE_F1_F2 );
  BOOST_CHECK_EQUAL( c.distance( f1, f1 ), 0.0f );
  BOOST_CHECK_EQUAL( c.distance( f2, f2 ), 0.0f );
}

#ifdef FIRES_WITH_VMMLIB


#define V11 1.2f
#define V12 2.3f
#define V13 3.4f
#define V21 4.5f
#define V22 5.6f
#define V23 6.7f

#define V1 fires::Vec3f( V11, V12, V13 )
#define V2 fires::Vec3f( V21, V22, V23 )
#define EUCLIDEAN_DISTANCE_V1_V2 ( V1 - V2 ).length( )

BOOST_AUTO_TEST_CASE( test_vector_comparer )
{
  fires::Feature f1( V1 ), f2( V2 );
  fires::VectorComparer< fires::vector<>, 3, float  > c;
  BOOST_CHECK_EQUAL( c.distance( f1, f2 ), EUCLIDEAN_DISTANCE_V1_V2 );
}

BOOST_AUTO_TEST_CASE( test_vector_ptr_comparer )
{
  fires::Vec3f v1( V1 ), v2( V2 );
  fires::Feature f1( &v1 ), f2( &v2 );
  fires::VectorComparer< fires::vector<>*, 3, float  > c;
  BOOST_CHECK_EQUAL( c.distance( f1, f2 ), EUCLIDEAN_DISTANCE_V1_V2 );
}

BOOST_AUTO_TEST_CASE( test_vector_of_ptrs_comparer )
{
  float v11 = V11, v12 = V12, v13 = V13;
  float v21 = V21, v22 = V22, v23 = V23;

  fires::Vec3pf v1( &v11, &v12, &v13 ), v2( &v21, &v22, &v23 );

  fires::Feature f1( v1 ), f2( v2 );
  fires::VectorComparer< fires::vector<>, 3, float*  > c;
  BOOST_CHECK_EQUAL( c.distance( f1, f2 ), EUCLIDEAN_DISTANCE_V1_V2 );
}

BOOST_AUTO_TEST_CASE( test_vector_ptr_of_ptrs_comparer )
{
  float v11 = V11, v12 = V12, v13 = V13;
  float v21 = V21, v22 = V22, v23 = V23;

  fires::Vec3pf v1( &v11, &v12, &v13 ), v2( &v21, &v22, &v23 );

  fires::Feature f1( &v1 ), f2( &v2 );
  fires::VectorComparer< fires::vector<>*, 3, float*  > c;
  BOOST_CHECK_EQUAL( c.distance( f1, f2 ), EUCLIDEAN_DISTANCE_V1_V2 );
}


#endif
