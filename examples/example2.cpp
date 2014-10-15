
#include "../fires/fires.h"

#include <iostream>
#include <math.h>


#if (FIRES_WITH_VMMLIB == 1)


class Test
{
  
public:
  float attr11, attr12;
  int attr21, attr22, attr23;
  float attr31, attr32, attr33;
  
};

class TestObject 
  : public Test
  , public fires::Object
{
  
public:
  
  fires::Vec2f vector1;
  fires::Vec3i vector2;
  fires::Vec3ptrf vector3;
  
  TestObject () 
  {
    vector1 = fires::Vec2f::ZERO;
    vector2 = fires::Vec3i::ZERO;
    vector3 = fires::Vec3ptrf( & attr31, & attr32, & attr33 );

    this->addFeature(std::string("feature1"), 
		     new fires::FeatureVec2fPtr( & vector1 ));

    this->addFeature(std::string("feature2"), 
    		     new fires::FeatureVec3iPtr( & vector2 ));

    this->addFeature(std::string("feature3"), 
    		     new fires::FeatureVec3ptrfPtr( & vector3 ));
  }     

};



int main ( )
{

  TestObject obj1, obj2;

  obj1.attr11 = 3.4f;
  obj1.attr12 = 4.3f;

  obj1.attr21 = 3;
  obj1.attr22 = 2;
  obj1.attr23 = 2;

  obj2.attr11 = 2.4f;
  obj2.attr12 = 2.5f;

  obj2.attr21 = 4;
  obj2.attr22 = 1;
  obj2.attr23 = 2;

  obj1.attr31 = 4.4;
  obj1.attr32 = 1.2;
  obj1.attr33 = 2.6;

  obj2.attr31 = 2.2;
  obj2.attr32 = 2.4;
  obj2.attr33 = 3.1;

  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );
  obj1.vector2 = fires::Vec3i( obj1.attr21, obj1.attr22, obj1.attr23 );

  obj2.vector1 = fires::Vec2f( obj2.attr11, obj2.attr12 );
  obj2.vector2 = fires::Vec3i( obj2.attr21, obj2.attr22, obj2.attr23 );


  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  
  fires::FeatureVec2fPtrComparer comparer1;
  fires::FeatureVec3iPtrComparer comparer2;
  fires::FeatureVec3pfPtrComparer comparer3;

  fires::System sys;

  sys.addObject(&obj1);
  sys.addObject(&obj2);

  sys.addQueryObject(&obj1);

  sys.addFeature(std::string("feature1"), 1.0, &comparer1);
  sys.addFeature(std::string("feature2"), 1.0, &comparer2);
  sys.addFeature(std::string("feature3"), 1.0, &comparer3);
  
  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }

  std::cout << std::endl;

  comparer1.distanceType() = fires::FeatureVec2fPtrComparer::MANHATTAN;
  comparer2.distanceType() = fires::FeatureVec3iPtrComparer::MANHATTAN;


  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }


  std::cout << std::endl;

  comparer1.distanceType() = fires::FeatureVec2fPtrComparer::EUCLIDEAN;
  comparer2.distanceType() = fires::FeatureVec3iPtrComparer::EUCLIDEAN;

  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }


  obj1.attr11 = 13.4f;

  sys.query();

  std::cout << std::endl;
  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }


  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );


  sys.query();

  std::cout << std::endl;
  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }


  obj1.attr31 = 20.0f;
  sys.query();

  std::cout << std::endl;
  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }


  return 0;


}

#else 


int main ( void )
{

  std::cerr << "This example need vmmlib" << std::endl;

  return -1;

}

#endif 
