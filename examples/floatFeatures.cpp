#include <fires/fires.h>

#include <iostream>
#include <math.h>


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
                     new fires::FeaturePtrToFloat(&this->attr1));
    this->addFeature(std::string("feature2"),
                     new fires::FeaturePtrToFloat(&this->attr2));
  }

  // createFeatures();


};


class CustomFeaturePtrToFloatComparer
  : public fires::FeaturePtrToFloatComparer
{

public:

  CustomFeaturePtrToFloatComparer(void)
  {
    factor = 1.0f;
  }


  float distance(fires::Feature *f1, fires::Feature *f2)
  {


    return factor * FeaturePtrToFloatComparer::distance( f1, f2 );

    // fires::FeaturePtrToFloat *ffp1 =
    //   static_cast<fires::FeaturePtrToFloat *>(f1);
    // fires::FeaturePtrToFloat *ffp2 =
    //   static_cast<fires::FeaturePtrToFloat *>(f2);

    // if (!ffp1 || !ffp2)
    //   {
    //         std::cerr << "Error casting to FeaturePtrToFloat "
    //                   << "for distance computation"
    //                   << std::endl;
    //         return 0.0f;
    //   }

    // return factor * fabs((*ffp1->value()) - (*ffp2->value()));

  }

  float factor;


};


int main ()
{

  TestObject obj1, obj2, obj3, obj4;

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

  fires::FeaturePtrToFloatComparer comparer1( 0, 4.1f );
  CustomFeaturePtrToFloatComparer comparer2;
  comparer2.setMaxValue( 42.1 );

  fires::System sys;

  fires::Objects objects;
  objects.add(&obj1);
  objects.add(&obj2);
  objects.add(&obj3);
  objects.add(&obj4);

  fires::Objects queryObjects;
  queryObjects.add(&obj1);
  queryObjects.add(&obj2);

  fires::QueryFeatures features;
  features.add( std::string("feature1"), &comparer1 );
  features.add( std::string("feature2"), &comparer2 );

  sys.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  std::cout << std::endl;


  // Change parameters of a custom comparer
  comparer2.factor = 0.5f;

  sys.query( objects, queryObjects, features);
  printResults( objects, "fires::score" );

  comparer2.factor = 1.0f;

  std::cout << std::endl;

  // Change some attribute and due to the use of feature pointers
  // no need of an update step needed
  obj1.attr2+= 1.3;

  sys.query( objects, queryObjects, features );
  printResults( objects, "fires::score" );

  std::cout << std::endl;


  // Take parameters to their original values
  obj1.attr2-= 1.3;

  sys.query( objects, queryObjects, features,
             "fires::score",
             fires::System::DISTANCE_TO_AVERAGE_QUERY_OBJECT );
  printResults( objects, "fires::score" );

  std::cout << std::endl;

  // Now query to the minimum object of the query set
  sys.query( objects, queryObjects, features, "fires::score",
             fires::System::MINIMUM_DISTANCE_TO_QUERY_OBJECTS );
  printResults( objects, "fires::score" );

  std::cout << std::endl;





}
