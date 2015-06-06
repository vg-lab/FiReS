/**
 * @file    example2.cpp
 * @brief   This example show how to use vector-based features
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include <fires/fires.h>

#include <iostream>
#include <math.h>


// This example requires fires compiled with vmmlib
#if (FIRES_WITH_VMMLIB == 1)

// Function to print out query results
void printResults( fires::Objects& objects, std::string scoreLabel )
{
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  {
    // fires::FeatureScalar< float >* fs =
    //   dynamic_cast< fires::FeatureScalar< float >* >(
    std::cout << ( *obj )->getFeature( scoreLabel ).value< float >( )
              << std::endl;
  }
}


// Original test class which has some attributes
// of different types
class Test
{

public:

  float attr1;

  float attr11, attr12;
  int attr21, attr22, attr23;
  float attr31, attr32, attr33;

};

// Class derived from original class and fires::Object
class TestObject
  : public Test
  , public fires::Object
{

public:

  // If we are going to use pointers to vectors then this
  // vectors have to be created.

  // vector1 and vector2 are made of scalars, thus their changes
  // on the original attributes are not reflected automatically
  // in the vector. It has to be manually upadated
  fires::Vec2f vector1;
  fires::Vec3i vector2;

  // vector3 is made od pointers to scalars. Thus, any change on
  // the original values are directly reflected on the vector
  fires::Vec3f vector3;
//  fires::Vec3pf vector3;

//  fires::Feature* f1, * f2, * f3, * f4;

  TestObject ()
  {

    // Vectors of scalars are initilized to zero (optional)
    vector1 = fires::Vec2f::ZERO;
    vector2 = fires::Vec3i::ZERO;

    vector3 = fires::Vec3f( attr31, attr32, attr33 );

    // Create the features
    // f1 = new fires::FeaturePtrToVec2f( &vector1 );
    // f2 = new fires::FeaturePtrToVec3i( & vector2 );
    // f3 = new fires::FeaturePtrToVec3pf( & vector3 );
    // f4 = new fires::FeaturePtrToScalar< float >( & this->attr1);

    // Add the different features of different types, giving a name
    // and the feature itself
    this->registerFeature( "feature1", fires::Feature( &vector1 ));
    this->registerFeature( "feature2", fires::Feature( &vector2 ));
    this->registerFeature( "feature3", fires::Feature( &vector2 ));
    this->registerFeature( "feature4", fires::Feature( &this->attr1 ));

  }

  ~TestObject ()
  {

    // delete f1;
    // delete f2;
    // delete f3;
    // delete f4;

  }

};



int main ( )
{

  // Two test objects
  TestObject obj1, obj2, obj3, obj4;

  // Set values to their attributes
  obj1.attr1 = 1.2f;
  obj1.attr11 = 3.4f;
  obj1.attr12 = 4.3f;
  obj1.attr21 = 3;
  obj1.attr22 = 2;
  obj1.attr23 = 2;
  obj1.attr31 = 4.4;
  obj1.attr32 = 1.2;
  obj1.attr33 = 2.6;

  obj2.attr1 = 2.3f;
  obj2.attr11 = 2.4f;
  obj2.attr12 = 2.5f;
  obj2.attr21 = 4;
  obj2.attr22 = 1;
  obj2.attr23 = 2;
  obj2.attr31 = 2.2;
  obj2.attr32 = 2.4;
  obj2.attr33 = 3.1;

  obj3.attr1 = 2.1f;
  obj3.attr11 = 5.1f;
  obj3.attr12 = 3.3f;
  obj3.attr21 = 4;
  obj3.attr22 = 5;
  obj3.attr23 = 1;
  obj3.attr31 = 2.1;
  obj3.attr32 = 2.6;
  obj3.attr33 = 2.3;

  obj4.attr1 = 2.6f;
  obj4.attr11 = 5.8f;
  obj4.attr12 = 4.6f;
  obj4.attr21 = 6;
  obj4.attr22 = 2;
  obj4.attr23 = 1;
  obj4.attr31 = 1.2;
  obj4.attr32 = 2.3;
  obj4.attr33 = 3.8;


  // In case of using pointers to vectors of scalars their values
  // have to be updated
  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );
  obj1.vector2 = fires::Vec3i( obj1.attr21, obj1.attr22, obj1.attr23 );

  obj2.vector1 = fires::Vec2f( obj2.attr11, obj2.attr12 );
  obj2.vector2 = fires::Vec3i( obj2.attr21, obj2.attr22, obj2.attr23 );

  obj3.vector1 = fires::Vec2f( obj3.attr11, obj3.attr12 );
  obj3.vector2 = fires::Vec3i( obj3.attr21, obj3.attr22, obj3.attr23 );

  obj4.vector1 = fires::Vec2f( obj4.attr11, obj4.attr12 );
  obj4.vector2 = fires::Vec3i( obj4.attr21, obj4.attr22, obj4.attr23 );


  // Asign labels
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";


  // Set-up comparers
  // fires::FeaturePtrToVec2fComparer comparer1;
  // fires::FeaturePtrToVec3iComparer comparer2;
  // fires::FeaturePtrToVec3pfComparer comparer3;
  // fires::FeaturePtrToScalarComparer< float > comparer4;

  fires::VectorComparer< 2, float > comp1;
  fires::VectorComparer< 3, int > comp2;
  fires::VectorComparer< 3, int > comp3;
  fires::ScalarPtrComparer< float > comp4;

  fires::VectorAverager< 2, float > avg1;
  fires::VectorAverager< 3, int > avg2;
  fires::VectorAverager< 3, int > avg3;
  fires::ScalarPtrAverager< float > avg4;


  // Set-up system
  fires::Engine engine;

  // Add objects
  fires::Objects objects;
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );

  // Add query objects
  fires::Objects queryObjects;
  queryObjects.add( &obj1 );
  queryObjects.add( &obj2 );

  // Add the features to the system
  fires::QueryFeatures features;

  features.add( "feature1", &comp1, &avg1 );
  features.add( "feature2", &comp2, &avg1 );
  features.add( "feature3", &comp3, &avg1 );
  features.add( "feature4", &comp4, &avg1 );

  // Perform a query
  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  // Now show that comparer parameters can be changed. In this case the
  // type of distance is changed from default euclidean to manhattan
  comp1.distanceType( ) = fires::MANHATTAN_DIST;
  comp2.distanceType( ) = fires::MANHATTAN_DIST;
  comp3.distanceType( ) = fires::MANHATTAN_DIST;

  // Query again and print results
  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  // Return the the distances to euclidean and print results. They
  // should be the same as the first query
  comp1.distanceType() = fires::EUCLIDEAN_DIST;
  comp2.distanceType() = fires::EUCLIDEAN_DIST;

  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  // Now change an atribute of an object which is used in a vector of
  // scalars. In this case the vector is not affected and the result
  // of the query should be the same.
  //
  obj1.attr11 = 13.4f;

  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  // Now update the vector and the result now is correctly computed
  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );

  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  // If we use vectors of pointers to scalars in this case changing the
  // value of an attribute affects the result of the query
  obj1.attr31 = 20.0f;
  engine.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  engine.query( objects, queryObjects, features, "fires::score",
             fires::Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT );
  printResults( objects, "fires::score" );


  engine.query( objects, queryObjects, features, "fires::score",
             fires::Engine::MINIMUM_DISTANCE_TO_QUERY_OBJECTS );
  printResults( objects, "fires::score" );


  return 0;


}

#else


int main ( void )
{

  std::cerr << "This example need vmmlib" << std::endl;

  return -1;

}

#endif
