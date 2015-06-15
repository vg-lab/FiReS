/**
 * @file    Averager.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"

#define F1 3.4f
#define F2 4.5f
#define F3 5.6f
#define ADD_F1_F2 ( F1 + F2 )
#define ADD_F1_F2_F3 ( F1 + F2 + F3 )
#define AVG_F1_F2 ADD_F1_F2 / 2.0f
#define AVG_F1_F2_F3 ADD_F1_F2_F3 / 3.0f

BOOST_AUTO_TEST_CASE( test_scalar_averager )
{

  fires::Feature f1( F1 ), f2( F2 ), f3( F3 );

  fires::ScalarAverager< float > av;

  av.reset( );
  BOOST_CHECK_EQUAL( av.feature( ).value< float >( ), 0 );
  av.accum( f1 );
  BOOST_CHECK_EQUAL( av.feature( ).value< float >( ), F1 );
  av.accum( f2 );
  BOOST_CHECK_EQUAL( av.feature( ).value< float >( ), ADD_F1_F2 );
  av.accum( f3 );
  BOOST_CHECK_EQUAL( av.feature( ).value< float >( ), ADD_F1_F2_F3 );

  av.divide( 3 );
  BOOST_CHECK_EQUAL( av.feature( ).value< float >( ), AVG_F1_F2_F3 );

}


BOOST_AUTO_TEST_CASE( test_scalar_ptr_averager )
{

  float v1( F1 ), v2( F2 ), v3( F3 );
  fires::Feature f1( &v1 ), f2( &v2 ), f3( &v3 );

  fires::ScalarAverager< float* > av;

  av.reset( );
  BOOST_CHECK_EQUAL( *av.feature( ).value< float* >( ), 0 );
  av.accum( f1 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< float* >( ), F1 );
  av.accum( f2 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< float* >( ), ADD_F1_F2 );
  av.accum( f3 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< float* >( ), ADD_F1_F2_F3 );

  av.divide( 3 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< float* >( ), AVG_F1_F2_F3 );

}



#ifdef FIRES_WITH_VMMLIB

#define V11 1.2f
#define V12 2.3f
#define V13 3.4f
#define V21 4.5f
#define V22 5.6f
#define V23 6.7f
#define V31 7.8f
#define V32 8.9f
#define V33 9.1f
#define V1 fires::Vec3f( V11, V12, V13 )
#define V2 fires::Vec3f( V21, V22, V23 )
#define V3 fires::Vec3f( V31, V32, V33 )
#define ADD_V1_V2 ( V1 + V2 )
#define ADD_V1_V2_V3 ( V1 + V2 + V3 )
#define AVG_V1_V2 ADD_V1_V2 / 2.0f
#define AVG_V1_V2_V3 ADD_V1_V2_V3 / 3.0f


BOOST_AUTO_TEST_CASE( test_vector_averager )
{
  fires::Feature f1( V1 ), f2( V2 ), f3( V3 );
  fires::VectorAverager< fires::vector<>, 3, float > av;

  av.reset( );
  BOOST_CHECK_EQUAL( av.feature( ).value< fires::Vec3f >( ),
                     fires::Vec3f::ZERO );
  av.accum( f1 );
  BOOST_CHECK_EQUAL( av.feature( ).value< fires::Vec3f >( ), V1 );
  av.accum( f2 );
  BOOST_CHECK_EQUAL( av.feature( ).value< fires::Vec3f >( ), ADD_V1_V2 );
  av.accum( f3 );
  BOOST_CHECK_EQUAL( av.feature( ).value< fires::Vec3f >( ), ADD_V1_V2_V3 );
  av.divide( 3 );
  BOOST_CHECK_EQUAL( av.feature( ).value< fires::Vec3f >( ), AVG_V1_V2_V3 );

}

BOOST_AUTO_TEST_CASE( test_vector_ptr_averager )
{
  fires::Vec3f v1( V1 ), v2( V2 ), v3( V3 );
  fires::Feature f1( &v1 ), f2( &v2 ), f3( &v3 );

  fires::VectorAverager< fires::vector<>*, 3, float > av;

  av.reset( );
  BOOST_CHECK_EQUAL( *av.feature( ).value< fires::Vec3f* >( ),
                     fires::Vec3f::ZERO );
  av.accum( f1 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< fires::Vec3f* >( ), V1 );
  av.accum( f2 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< fires::Vec3f* >( ), ADD_V1_V2 );
  av.accum( f3 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< fires::Vec3f* >( ), ADD_V1_V2_V3 );
  av.divide( 3 );
  BOOST_CHECK_EQUAL( *av.feature( ).value< fires::Vec3f* >( ), AVG_V1_V2_V3 );

}

BOOST_AUTO_TEST_CASE( test_vector_of_ptrs_averager )
{
  float v11 = V11, v12 = V12, v13 = V13;
  float v21 = V21, v22 = V22, v23 = V23;
  float v31 = V31, v32 = V32, v33 = V33;

  fires::Vec3pf v1( &v11, &v12, &v13 ), v2( &v21, &v22, &v23 ),
    v3( &v31, &v32, &v33 );

  fires::Feature f1( v1 ), f2( v2 ), f3( v3 );

  fires::VectorAverager< fires::vector<>, 3, float* > av;

  av.reset( );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *( av.feature( ).value< fires::Vec3pf >( )( 0 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 1 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 2 ))),
    fires::Vec3f::ZERO );
  av.accum( f1 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *( av.feature( ).value< fires::Vec3pf >( )( 0 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 1 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 2 ))), V1 );

  av.accum( f2 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *( av.feature( ).value< fires::Vec3pf >( )( 0 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 1 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 2 ))),
    ADD_V1_V2 );

  av.accum( f3 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *( av.feature( ).value< fires::Vec3pf >( )( 0 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 1 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 2 ))),
    ADD_V1_V2_V3 );

  av.divide( 3 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *( av.feature( ).value< fires::Vec3pf >( )( 0 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 1 )),
                  *( av.feature( ).value< fires::Vec3pf >( )( 2 ))),
    AVG_V1_V2_V3 );

}



BOOST_AUTO_TEST_CASE( test_vector_ptr_of_ptrs_averager )
{
  float v11 = V11, v12 = V12, v13 = V13;
  float v21 = V21, v22 = V22, v23 = V23;
  float v31 = V31, v32 = V32, v33 = V33;

  fires::Vec3pf v1( &v11, &v12, &v13 ), v2( &v21, &v22, &v23 ),
    v3( &v31, &v32, &v33 );

  fires::Feature f1( &v1 ), f2( &v2 ), f3( &v3 );

  fires::VectorAverager< fires::vector<>*, 3, float* > av;

  av.reset( );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *(( *av.feature( ).value< fires::Vec3pf* >( ))( 0 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 1 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 2 ))),
    fires::Vec3f::ZERO );
  av.accum( f1 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *(( *av.feature( ).value< fires::Vec3pf* >( ))( 0 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 1 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 2 ))), V1 );

  av.accum( f2 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *(( *av.feature( ).value< fires::Vec3pf* >( ))( 0 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 1 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 2 ))),
    ADD_V1_V2 );

  av.accum( f3 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *(( *av.feature( ).value< fires::Vec3pf* >( ))( 0 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 1 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 2 ))),
    ADD_V1_V2_V3 );

  av.divide( 3 );
  BOOST_CHECK_EQUAL(
    fires::Vec3f( *(( *av.feature( ).value< fires::Vec3pf* >( ))( 0 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 1 )),
                  *(( *av.feature( ).value< fires::Vec3pf* >( ))( 2 ))),
    AVG_V1_V2_V3 );

}

#endif
