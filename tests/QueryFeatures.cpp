/**
 * @file    QueryFeatures.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_query_features )
{

  fires::Comparer c1;
  fires::Comparer c2;

  fires::QueryFeatureData qfd( &c1 );
  BOOST_CHECK( qfd.comparer( ) == &c1 );
  BOOST_CHECK( qfd.weight( ) == 1.0f );

  fires::QueryFeatureData qfd2( &c2, 2.3f );
  BOOST_CHECK( qfd2.comparer( ) == &c2 );
  BOOST_CHECK( qfd2.weight( ) == 2.3f );

  qfd.comparer( nullptr );
  BOOST_CHECK( qfd.comparer( ) == 0 );

  qfd.comparer( &c2 );
  BOOST_CHECK( qfd.comparer( ) == &c2 );

  qfd.weight( 5.6f );
  BOOST_CHECK( qfd.weight( ) == 5.6f );


  fires::QueryFeatures qf;

  qf.add( "test_label", &c1 );
  BOOST_CHECK( qf.find( "test_label" ) != qf.end( ));
  BOOST_CHECK(( *qf.find( "test_label" )).second.comparer( ) == &c1 );
  BOOST_CHECK(( *qf.find( "test_label" )).second.weight( ) == 1.0f);

  qf.add( "test_label2", &c2, 3.4f );
  BOOST_CHECK( qf.find( "test_label" ) != qf.end( ));
  BOOST_CHECK(( *qf.find( "test_label" )).second.comparer( ) == &c1 );
  BOOST_CHECK(( *qf.find( "test_label" )).second.weight( ) == 1.0f);
  BOOST_CHECK( qf.find( "test_label2" ) != qf.end( ));
  BOOST_CHECK(( *qf.find( "test_label2" )).second.comparer( ) == &c2 );
  BOOST_CHECK(( *qf.find( "test_label2" )).second.weight( ) == 3.4f);

  BOOST_CHECK( qf.find( "nonexistinglabel" ) == qf.end( ));

  qf.add( "test_label2", &c1, 6.7f );
  BOOST_CHECK( qf.find( "test_label2" ) != qf.end( ));
  BOOST_CHECK(( *qf.find( "test_label2" )).second.comparer( ) != &c1 );
  BOOST_CHECK(( *qf.find( "test_label2" )).second.weight( ) != 6.7f);


}
