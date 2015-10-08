/**
 * @file    example2.cpp
 * @brief   This example show how to use vector-based properties
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include <fires/fires.h>

#include <iostream>
#include <math.h>


// This example requires fires compiled with vmmlib
#ifdef FIRES_WITH_VMMLIB

// Function to print out query results
void printResults( fires::Objects& objects, std::string scoreLabel )
{
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  {
    fires::Property f = ( *obj )->getProperty( scoreLabel );

    std::cout << ( *obj )->label( ) << ": ";
    if ( !f.empty( ) )
      std::cout << f.value< float >( );
    else
      std::cout << "empty";

    std::cout << std::endl;
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
  fires::Vec3pf vector3;
//  fires::Vec3pf vector3;

//  fires::Property* f1, * f2, * f3, * f4;

  TestObject ()
  {

    // Vectors of scalars are initilized to zero (optional)
    vector1 = fires::Vec2f::ZERO;
    vector2 = fires::Vec3i::ZERO;

    vector3 = fires::Vec3pf( &attr31, &attr32, &attr33 );

    // Create the properties
    // f1 = new fires::PropertyPtrToVec2f( &vector1 );
    // f2 = new fires::PropertyPtrToVec3i( & vector2 );
    // f3 = new fires::PropertyPtrToVec3pf( & vector3 );
    // f4 = new fires::PropertyPtrToScalar< float >( & this->attr1);

    // Add the different properties of different types, giving a name
    // and the property itself
    this->registerProperty( "property1", fires::Property( &vector1 ));
    this->registerProperty( "property2", fires::Property( &vector2 ));
    this->registerProperty( "property3", fires::Property( &vector3 ));
    this->registerProperty( "property4", fires::Property( &this->attr1 ));
    this->registerProperty( "property5", fires::Property( fires::Vec3f::ZERO ));

  }

  ~TestObject ()
  {

    // delete f1;
    // delete f2;
    // delete f3;
    // delete f4;

  }

};


int main( void )
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
  obj1.attr31 = 4.4f;
  obj1.attr32 = 1.2f;
  obj1.attr33 = 2.6f;

  obj2.attr1 = 2.3f;
  obj2.attr11 = 2.4f;
  obj2.attr12 = 2.5f;
  obj2.attr21 = 4;
  obj2.attr22 = 1;
  obj2.attr23 = 2;
  obj2.attr31 = 2.2f;
  obj2.attr32 = 2.4f;
  obj2.attr33 = 3.1f;

  obj3.attr1 = 2.1f;
  obj3.attr11 = 5.1f;
  obj3.attr12 = 3.3f;
  obj3.attr21 = 4;
  obj3.attr22 = 5;
  obj3.attr23 = 1;
  obj3.attr31 = 2.1f;
  obj3.attr32 = 2.6f;
  obj3.attr33 = 2.3f;

  obj4.attr1 = 2.6f;
  obj4.attr11 = 5.8f;
  obj4.attr12 = 4.6f;
  obj4.attr21 = 6;
  obj4.attr22 = 2;
  obj4.attr23 = 1;
  obj4.attr31 = 1.2f;
  obj4.attr32 = 2.3f;
  obj4.attr33 = 3.8f;


  // In case of using pointers to vectors of scalars their values
  // have to be updated
  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );
  obj1.vector2 = fires::Vec3i( obj1.attr21, obj1.attr22, obj1.attr23 );
  obj1.getProperty( "property5" ).set( fires::Vec3f( 1.1f, 3.4f, 5.3f ));

  obj2.vector1 = fires::Vec2f( obj2.attr11, obj2.attr12 );
  obj2.vector2 = fires::Vec3i( obj2.attr21, obj2.attr22, obj2.attr23 );
  obj2.getProperty( "property5" ).set( fires::Vec3f( 6.3f, 4.2f, 2.1f ));

  obj3.vector1 = fires::Vec2f( obj3.attr11, obj3.attr12 );
  obj3.vector2 = fires::Vec3i( obj3.attr21, obj3.attr22, obj3.attr23 );
  obj3.getProperty( "property5" ).set( fires::Vec3f( 4.6f, 5.7f, 6.9f ));

  obj4.vector1 = fires::Vec2f( obj4.attr11, obj4.attr12 );
  obj4.vector2 = fires::Vec3i( obj4.attr21, obj4.attr22, obj4.attr23 );
  obj4.getProperty( "property5" ).set( fires::Vec3f( 7.3f, 5.2f, 6.2f ));

  // Asign labels
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";


  // Set-up comparers
  // fires::PropertyPtrToVec2fComparer comparer1;
  // fires::PropertyPtrToVec3iComparer comparer2;
  // fires::PropertyPtrToVec3pfComparer comparer3;
  // fires::PropertyPtrToScalarComparer< float > comparer4;

  // fires::VectorComparer< fires::vector<>*, 2, float > comp1;
  // fires::VectorComparer< fires::vector<>*, 3, int > comp2;
  // fires::VectorComparer< fires::vector<>*, 3, float* > comp3;
  // fires::ScalarComparer< float* > comp4;

  // fires::VectorAverager< fires::vector<>*, 2, float > avg1;
  // fires::VectorAverager< fires::vector<>*, 3, int > avg2;
  // fires::VectorAverager< fires::vector<>*, 3, float* > avg3;
  // fires::ScalarAverager< float* > avg4;

  fires::VectorComparer< fires::vector<>, 3, float > vc3f;
  fires::VectorAverager< fires::vector<>, 3, float > va3f;
  fires::VectorNormalizer< fires::vector<>, 3, float > vn3f;

  fires::VectorComparer< fires::vector<>*, 2, float > pvc2f;
  fires::VectorAverager< fires::vector<>*, 2, float > pva2f;
  fires::VectorNormalizer< fires::vector<>*, 2, float > pvn2f;

  fires::VectorComparer< fires::vector<>*, 3, int > pvc3i;
  fires::VectorAverager< fires::vector<>*, 3, int > pva3i;
  fires::VectorNormalizer< fires::vector<>*, 3, int > pvn3i;

  fires::VectorComparer< fires::vector<>*, 3, float > pvc3f;
  fires::VectorAverager< fires::vector<>*, 3, float > pva3f;
  fires::VectorNormalizer< fires::vector<>*, 3, float > pvn3f;

  fires::VectorComparer< fires::vector<>*, 3, float* > pvc3pf;
  fires::VectorAverager< fires::vector<>*, 3, float* > pva3pf;
  fires::VectorNormalizer< fires::vector<>*, 3, float* > pvn3pf;

  fires::ScalarComparer< float* > scpf;
  fires::ScalarAverager< float* > sapf;
  fires::ScalarNormalizer< float* > snpf;

  // Set-up system
  fires::Search search;

  // Add objects
  fires::Objects objects;
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );

  // Add query objects
  // fires::Objects queryObjects;

  // Add the properties to the system
  fires::SearchConfig sc;

  sc.add( "property1", &pvc2f, &pva2f, &pvn2f );
  sc.add( "property2", &pvc3i, &pva3i, &pvn3i );
  sc.add( "property3", &pvc3pf, &pva3pf, &pvn3pf );
  sc.add( "property4", &scpf, &sapf, &snpf );
  sc.add( "property5", &vc3f, &va3f, &vn3f );

  sc.queryObjects( ).add( &obj1 );
  sc.queryObjects( ).add( &obj2 );

  // Perform a query
  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Now show that comparer parameters can be changed. In this case the
  // type of distance is changed from default euclidean to manhattan
  pvc2f.distanceType( ) = fires::MANHATTAN_DIST;
  pvc3i.distanceType( ) = fires::MANHATTAN_DIST;
  pvc3pf.distanceType( ) = fires::MANHATTAN_DIST;
  vc3f.distanceType( ) = fires::MANHATTAN_DIST;
  // comp1.distanceType( ) = fires::MANHATTAN_DIST;
  // comp2.distanceType( ) = fires::MANHATTAN_DIST;
  // comp3.distanceType( ) = fires::MANHATTAN_DIST;

  // Query again and print results
  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Return the the distances to euclidean and print results. They
  // should be the same as the first query
  pvc2f.distanceType( ) = fires::EUCLIDEAN_DIST;
  pvc3i.distanceType( ) = fires::EUCLIDEAN_DIST;
  pvc3pf.distanceType( ) = fires::EUCLIDEAN_DIST;
  vc3f.distanceType( ) = fires::EUCLIDEAN_DIST;

  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Now change an atribute of an object which is used in a vector of
  // scalars. In this case the vector is not affected and the result
  // of the query should be the same.
  //
  obj1.attr11 = 13.4f;

  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // Now update the vector and the result now is correctly computed
  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );

  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  // If we use vectors of pointers to scalars in this case changing the
  // value of an attribute affects the result of the query
  obj1.attr31 = 20.0f;
  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  sc.distanceToQueryType( ) =
    fires::SearchConfig::DISTANCE_TO_AVERAGE_QUERY_OBJECT;
  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  sc.distanceToQueryType( ) =
    fires::SearchConfig::MINIMUM_DISTANCE_TO_QUERY_OBJECTS;

  search.eval( objects, sc );
  printResults( objects, "fires::score" );
  std::cout << std::endl;


  return 0;


}

#else


int main ( void )
{

  std::cerr << "This example need vmmlib" << std::endl;

  return -1;

}

#endif
