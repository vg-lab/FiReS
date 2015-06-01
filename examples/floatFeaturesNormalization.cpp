#include <fires/fires.h>

#include <iostream>
#include <math.h>



class Test
{

public:
  float attr1, attr2;

};

class TestObject
  : public Test
  , public fires::Object
{

public:

  TestObject ()
  {
    this->addFeature(std::string("feature1"),
                     new fires::FeaturePtrToScalar< float >(&this->attr1));
    this->addFeature(std::string("feature2"),
                     new fires::FeaturePtrToScalar< float >(&this->attr2));
  }


};


int main ()
{

  TestObject objMin, objMax;

  TestObject obj1, obj2, obj3, obj4;

  objMin.attr1 = 0.0f;
  objMin.attr2 = 0.0f;

  objMax.attr1 = 4.1f;
  objMax.attr2 = 42.1f;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;

  obj2.attr1 = 3.2f;
  obj2.attr2 = 42.1f;

  obj3.attr1 = 1.4f;
  obj3.attr2 = 2.2f;

  obj4.attr1 = 4.1f;
  obj4.attr2 = 1.8f;

  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  objMin.label( ) = "Object Min";
  objMax.label( ) = "Object Max";


  fires::FeaturePtrToScalarComparer< float > comparer1( 0, 4.1f );
  fires::FeaturePtrToScalarComparer< float > comparer2( 0, 42.1f );

  fires::Engine engine;

  fires::Objects objects;
  objects.add( & objMin );
  objects.add( & objMax );
  objects.add( & obj1 );
  objects.add( & obj2 );
  objects.add( & obj3 );
  objects.add( & obj4 );

  fires::Objects queryObjects;
  queryObjects.add( & objMax );

  fires::QueryFeatures features;
  features.add( std::string( "feature1" ),
           &comparer1 );

  features.add( std::string( "feature2" ),
                &comparer2 );

  engine.query( objects, queryObjects, features );

  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
    std::cout << ( *obj )->label( ) << ": "
              << ( *obj )->getFeature( "fires::score" );

  std::cout << std::endl;







}
