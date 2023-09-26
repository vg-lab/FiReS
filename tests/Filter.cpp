/**
 * @file    Filter.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) VG-Lab/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include "firesTests.h"


BOOST_AUTO_TEST_CASE( test_filter_scalar_range )
{

  fires::FilterScalarRange< float > fsr( 3.0f, 4.0f );

  BOOST_CHECK_EQUAL( fsr.min( ), 3.0f );
  BOOST_CHECK_EQUAL( fsr.max( ), 4.0f );
  BOOST_CHECK_EQUAL( fsr.minEndpoint( ), fires::FilterRange::OPENED_ENDPOINT );
  BOOST_CHECK_EQUAL( fsr.maxEndpoint( ), fires::FilterRange::OPENED_ENDPOINT );
  BOOST_CHECK_EQUAL( fsr.rangeInclusion( ), fires::FilterRange::INSIDE_RANGE );

  fires::Property f1( 2.0f ), f2( 3.0f ), f3( 3.5f ), f4( 4.0f ), f5 ( 5.0f );

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

BOOST_AUTO_TEST_CASE( test_filter_set )
{

  fires::Object obj1, obj2, obj3, obj4;

  obj1.registerProperty( "p2", 4 );
  obj1.registerProperty( "p3", 2.3f );

  obj2.registerProperty( "p2", 10 );
  obj2.registerProperty( "p3", 3.4f );

  obj3.registerProperty( "p2", 2 );
  obj3.registerProperty( "p3", 4.5f );

  obj4.registerProperty( "p2", 1 );
  obj4.registerProperty( "p3", 5.6f );

  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  fires::Objects objs;
  {
    objs.addList( { &obj1, &obj2, &obj3, &obj4 } );
    fires::FilterSet fs0;
    fires::FilterSetConfig fsc0;
    fires::FilterMinValue< float > ff10( 5.0f );

    fsc0.filters( ).push_back( std::make_pair( "p3", &ff10 ));
    fs0.eval( objs, fsc0 );
    BOOST_CHECK( objs.size( ) == 1);
  }
  {
    objs.addList( { &obj1, &obj2, &obj3, &obj4 } );
    fires::FilterSet fs0;
    fires::FilterSetConfig fsc0;
    fires::FilterMaxValue< float > ff10( 5.0f );

    fsc0.filters( ).push_back( std::make_pair( "p3", &ff10 ));
    fs0.eval( objs, fsc0 );
    BOOST_CHECK( objs.size( ) == 3);
  }
  objs.addList( { &obj1, &obj2, &obj3, &obj4 } );

  fires::FilterSet fs;
  fires::FilterSetConfig fsc;
  fires::FilterScalarRange< float > ff1( 3.0f, 5.0f );
  fires::FilterScalarRange< int > fi1( 0, 9 );

  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj1 ) != objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj2 ) != objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj3 ) != objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj4 ) != objs.end( ));

  fsc.filters( ).push_back( std::make_pair( "p3", &ff1 ));
  fs.eval( objs, fsc );
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj1 ) == objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj2 ) != objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj3 ) != objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj4 ) == objs.end( ));

  ff1.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  fs.eval( objs, fsc );
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj1 ) == objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj2 ) == objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj3 ) == objs.end( ));
  BOOST_CHECK( std::find( objs.begin( ), objs.end( ), &obj4 ) == objs.end( ));

  objs.add( &obj1 );
  objs.add( &obj2 );
  objs.add( &obj3 );
  objs.add( &obj4 );

  fsc.filters( ).push_back( std::make_pair( "p2", &fi1 ));
  fs.eval( objs, fsc );

  objs.clear( );
  objs.add( &obj1 );
  objs.add( &obj2 );
  objs.add( &obj3 );
  objs.add( &obj4 );

  ff1.rangeInclusion( ) = fires::FilterRange::INSIDE_RANGE;
  fsc.filterPropertyLabel( ) = std::string( "fires::filter" );
  fs.eval( objs, fsc );
  BOOST_CHECK( !obj1.getProperty( "fires::filter" ).value< bool >( ));
  BOOST_CHECK( !obj2.getProperty( "fires::filter" ).value< bool >( ));
  BOOST_CHECK( obj3.getProperty( "fires::filter" ).value< bool >( ));
  BOOST_CHECK( !obj4.getProperty( "fires::filter" ).value< bool >( ));

  ff1.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  fs.eval( objs, fsc );
  BOOST_CHECK( obj1.getProperty( "fires::filter" ).value< bool >( ));
  BOOST_CHECK( !obj2.getProperty( "fires::filter" ).value< bool >( ));
  BOOST_CHECK( !obj3.getProperty( "fires::filter" ).value< bool >( ));
  BOOST_CHECK( obj4.getProperty( "fires::filter" ).value< bool >( ));

}
