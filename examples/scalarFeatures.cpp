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
    fires::FeatureScalar< float >* fs =
      dynamic_cast< fires::FeatureScalar< float >* >(
        ( *obj )->getFeature( scoreLabel ));
    std::cout << ( *obj )->label( ) << ": "
              << fs->value( ) << std::endl;
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
    this->addFeature( std::string( "feature1" ),
                      new fires::FeaturePtrToScalar< float >( &this->attr1 ));
    this->addFeature( std::string( "feature2" ),
                      new fires::FeaturePtrToScalar< float >( &this->attr2 ));

    // Add a couple of non-pointer features, in this case one float
    // and one integer.
    this->addFeature( std::string( "feature3" ),
                      new fires::FeatureScalar< float >( ));
    this->addFeature( std::string( "feature4" ),
                      new fires::FeatureScalar< int >( ));

  }


};


class CustomFeaturePtrToFloatComparer
  : public fires::FeaturePtrToScalarComparer< float >
{

public:

  CustomFeaturePtrToFloatComparer(void)
  {
    factor = 1.0f;
  }

  float distance( fires::Feature* f1, fires::Feature* f2 ) const
  {
    return factor * FeaturePtrToScalarComparer::distance( f1, f2 );
  }

  float factor;

};


int main ()
{

  // Create objects and give value to their features
  TestObject obj1, obj2, obj3, obj4;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;
  fires::asFloat( obj1.getFeature( "feature3" ) )->value( 5.6f );
  fires::asInteger( obj1.getFeature( "feature4" ) )->value( 6 );

  obj2.attr1 = 3.2f;
  obj2.attr2 = 42.1f;
  fires::asFloat( obj2.getFeature( "feature3" ) )->value( 2.4 );
  fires::asInteger( obj2.getFeature( "feature4" ) )->value( 3 );

  obj3.attr1 = 1.4f;
  obj3.attr2 = 2.2f;
  fires::asFloat( obj3.getFeature( "feature3" ) )->value( 9.6f );
  fires::asInteger( obj3.getFeature( "feature4" ) )->value( 4 );

  obj4.attr1 = 4.1f;
  obj4.attr2 = 1.8f;
  fires::asFloat( obj4.getFeature( "feature3" ) )->value( 3.4f );
  fires::asInteger( obj4.getFeature( "feature4" ) )->value( 7 );


  // Label objects
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  // Create comparers
  fires::FeaturePtrToScalarComparer< float > comparer1( 0, 4.1f );
  CustomFeaturePtrToFloatComparer comparer2;
  comparer2.setMaxValue( 42.1 );
  fires::FeatureScalarComparer< float > comparer3;
  fires::FeatureScalarComparer< int > comparer4;

  // Instanciate fires' engine object
  fires::Engine engine;

  // Create the collection of target objects
  fires::Objects objects;
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );

  // Create the collection of query objects
  fires::Objects queryObjects;
  queryObjects.add( &obj1 );
  queryObjects.add( &obj2 );

  // Create the set of features to be used in the queries
  fires::QueryFeatures features;
  features.add( std::string("feature1"), &comparer1 );
  features.add( std::string("feature2"), &comparer2 );
  features.add( std::string("feature3"), &comparer3 );
  features.add( std::string("feature4"), &comparer4 );

  // Query the system and print results
  std::cout << "-- First query" << std::endl;
  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Change parameters of a custom comparer and query again
  // printing results afterwards and returning the parameter to
  // its original value
  std::cout << "-- Changing custom comparer parameter" << std::endl;
  comparer2.factor = 0.5f;
  engine.query( objects, queryObjects, features);
  printResults( objects, "fires::score" );
  comparer2.factor = 1.0f;
  std::cout << std::endl;

  // Change some attribute and due to the use of feature pointers
  // no need of an update step needed, query and print results.
  std::cout << "-- Changing attribute registered as pointer " << std::endl;
  obj1.attr2+= 1.3;
  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Take parameters to their original values and query again. Same
  // output as before should be obtained
  std::cout << "-- Changing back the same attribute " << std::endl;
  obj1.attr2-= 1.3;
  engine.query( objects, queryObjects, features,
             "fires::score",
             fires::Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Now query to the minimum object of the query set and print results.
  std::cout << "-- Use minimum distance " << std::endl;
  engine.query( objects, queryObjects, features, "fires::score",
             fires::Engine::MINIMUM_DISTANCE_TO_QUERY_OBJECTS );
  printResults( objects, "fires::score" );

  std::cout << std::endl;


  //TODO: delete dynamic memory


}
