/**
 * @file    floatFeatures.cpp
 * @brief   This example shows a simple use case for using fires with different
 *          types of scalar features.
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include <fires/fires.h>
#include <iostream>
#include <math.h>


// Function to print out query results
void printResults( fires::Objects& objects, std::string scoreLabel )
{
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  {
    std::cout << ( *obj )->getFeature( scoreLabel ).value< float >( )
              << std::endl;
  }
}


// Parent object to be used for constructing fires objects
class Test
{

public:
  float attr1, attr2;

};

// Derived object from Test and fires::Object. Its constructor
// creates the features (but could be created afterwards).
class TestObject
  : public Test
  , public fires::Object
{

public:

  TestObject( void )
    : Test( )
  {
    // Add a couple of features which hold pointer to already existing
    // float attributes
    this->registerFeature( std::string( "feature1" ), &this->attr1 );
    this->registerFeature( std::string( "feature2" ), &this->attr2 );

    // Add a couple of non-pointer features, in this case one float
    // and one integer.
    this->registerFeature( std::string( "feature3" ), float( 0.0f ) );
    this->registerFeature( std::string( "feature4" ), int( 0 ) );
  }


};


template < typename T >
class CustomScalarComparer
  : public fires::ScalarComparer< T >
{

public:

  CustomScalarComparer( void )
  {
    factor = 1.0f;
  }

  float distance( const fires::Feature& f1, const fires::Feature& f2 ) const
  {
    return factor * fires::ScalarComparer< T >::distance( f1, f2 );
  }


  float factor;

};


int main ()
{

  // Create objects and give value to their features
  TestObject obj1, obj2, obj3, obj4;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;
  obj1.getFeature( "feature3" ).set( 5.6f );
  obj1.getFeature( "feature4" ).set( 6 );

  obj2.attr1 = 3.2f;
  obj2.attr2 = 42.1f;
  obj2.getFeature( "feature3" ).set( 2.4f );
  obj2.getFeature( "feature4" ).set( 3 );

  obj3.attr1 = 1.4f;
  obj3.attr2 = 2.2f;
  obj3.getFeature( "feature3" ).set( 9.6f );
  obj3.getFeature( "feature4" ).set( 4 );

  obj4.attr1 = 4.1f;
  obj4.attr2 = 1.8f;
  obj4.getFeature( "feature3" ).set( 2.1f );
  obj4.getFeature( "feature4" ).set( 7 );


  // Label objects
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  // Create comparers
  fires::ScalarComparer< float* > comparer1;
  CustomScalarComparer< float* > comparer2;
  fires::ScalarComparer< float > comparer3;
  fires::ScalarComparer< int > comparer4;

  fires::ScalarAverager< int > sai;
  fires::ScalarAverager< float > saf;
  fires::ScalarAverager< int* > sapi;
  fires::ScalarAverager< float* > sapf;

  // Instanciate fires' search object
  fires::Search search;

  // Create the collection of target objects
  fires::Objects objects;
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );

  // // Create the collection of query objects
  // fires::Objects queryObjects;

  // Create the set of features to be used in the queries
  fires::SearchConfig sc;
  sc.add( std::string("feature1"), &comparer1, &sapf );
  sc.add( std::string("feature2"), &comparer2, &sapf );
  sc.add( std::string("feature3"), &comparer3, &saf );
  sc.add( std::string("feature4"), &comparer4, &sai );

  sc.queryObjects( ).add( &obj1 );
  sc.queryObjects( ).add( &obj2 );


  // Query the system and print results
  std::cout << "-- First query" << std::endl;
  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Change parameters of a custom comparer and query again
  // printing results afterwards and returning the parameter to
  // its original value
  std::cout << "-- Changing custom comparer parameter" << std::endl;
  comparer2.factor = 0.5f;
  search.eval( objects, sc );
  // search.query( objects, queryObjects, features);
  printResults( objects, "fires::score" );
  comparer2.factor = 1.0f;
  std::cout << std::endl;

  // Change some attribute and due to the use of feature pointers
  // no need of an update step needed, query and print results.
  std::cout << "-- Changing attribute registered as pointer " << std::endl;
  obj1.attr2+= 1.3f;
  search.eval( objects, sc );
 // search.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Take parameters to their original values and query again. Same
  // output as before should be obtained
  std::cout << "-- Changing back the same attribute " << std::endl;
  obj1.attr2-= 1.3f;
  search.eval( objects, sc );
  // search.query( objects, queryObjects, features,
  //            "fires::score",
  //            fires::SearchConfig::DISTANCE_TO_AVERAGE_QUERY_OBJECT );
  sc.distanceToQueryType( ) =
    fires::SearchConfig::DISTANCE_TO_AVERAGE_QUERY_OBJECT;
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Now query to the minimum object of the query set and print results.
  std::cout << "-- Use minimum distance " << std::endl;
  sc.distanceToQueryType( ) =
    fires::SearchConfig::MINIMUM_DISTANCE_TO_QUERY_OBJECTS;
  search.eval( objects, sc );
  // search.query( objects, queryObjects, features, "fires::score",
  //            fires::SearchConfig::MINIMUM_DISTANCE_TO_QUERY_OBJECTS );
  printResults( objects, "fires::score" );

  std::cout << std::endl;


  //TODO: delete dynamic memory


}
