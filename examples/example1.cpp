

#include "../fires/fires.h"

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
		     new fires::FeaturePtrToFloat(&this->attr1));
    this->addFeature(std::string("feature2"), 
		     new fires::FeaturePtrToFloat(&this->attr2));
  }
 
  // createFeatures();


};


class CustomFeaturePtrToFloatComparer : public fires::Comparer
{
  
public:

  CustomFeaturePtrToFloatComparer(void)
  {
    factor = 1.0f;
  }


  virtual float distance(fires::Feature *f1, fires::Feature *f2)
  {

    fires::FeaturePtrToFloat *ffp1 = 
      static_cast<fires::FeaturePtrToFloat *>(f1);
    fires::FeaturePtrToFloat *ffp2 = 
      static_cast<fires::FeaturePtrToFloat *>(f2);

    if (!ffp1 || !ffp2)
      {
	std::cerr << "Error casting to FeaturePtrToFloat " 
		  << "for distance computation" 
		  << std::endl;
	return 0.0f;
      }

    return factor * fabs((*ffp1->value()) - (*ffp2->value()));

  }

  float factor;
  

}; 



int main () 
{

  TestObject obj1, obj2, obj3, obj4;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;

  obj2.attr1 = 3.2f;
  obj2.attr2 = 2.1f;

  obj3.attr1 = 1.4f;
  obj3.attr2 = 2.2f;

  obj4.attr1 = 4.1f;
  obj4.attr2 = 1.8f;


  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";
  
  fires::FeaturePtrToFloatComparer comparer1;
  CustomFeaturePtrToFloatComparer comparer2;
  fires::System sys;

  sys.addObject(&obj1);
  sys.addObject(&obj2);
  sys.addObject(&obj3);
  sys.addObject(&obj4);

  sys.addQueryObject(&obj1);
  sys.addQueryObject(&obj2);

  sys.addFeature(std::string("feature1"), 1.0, &comparer1);
  sys.addFeature(std::string("feature2"), 1.0, &comparer2);
  
  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }

  std::cout << std::endl;


  // Change parameters of a custom comparer
  comparer2.factor = 0.5f;

  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }

  comparer2.factor = 1.0f;

  std::cout << std::endl;


  // Change some attribute and due to the use of feature pointers 
  // no need of an update step needed 
  obj1.attr2+= 1.3;

  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }

  std::cout << std::endl;


  // Take parameters to their original values
  obj1.attr2-= 1.3;

  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }

  std::cout << std::endl;





}

