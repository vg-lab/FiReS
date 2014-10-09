

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
    this->addFeature(std::string("feature1"), new fires::FeatureFloatPtr(&this->attr1));
    this->addFeature(std::string("feature2"), new fires::FeatureFloatPtr(&this->attr2));
  }
 

};


class CustomFeatureFloatPtrComparer : public fires::Comparer
{
  
public:

  CustomFeatureFloatPtrComparer(void)
  {
    factor = 1.0f;
  }


  virtual float distance(fires::Feature *f1, fires::Feature *f2)
  {

    fires::FeatureFloatPtr *ffp1 = static_cast<fires::FeatureFloatPtr *>(f1);
    fires::FeatureFloatPtr *ffp2 = static_cast<fires::FeatureFloatPtr *>(f2);

    if (!ffp1 || !ffp2)
      {
	std::cerr << "Error casting to FeatureFloatPtr " 
		  << "for distance computation" 
		  << std::endl;
	return 0.0f;
      }


    //      std::cout << "Compare " << *ffp1->value() << " to " << *ffp2->value() << std::endl;


    return factor * fabs((*ffp1->value()) - (*ffp2->value()));

  }

  float factor;
  

}; 



int main () 
{

  TestObject obj1, obj2;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;
  obj2.attr1 = 3.2f;
  obj2.attr2 = 2.1f;

  obj1.label("Object 1");
  obj2.label("Object 2");
  
  fires::FeatureFloatPtrComparer comparer1;
  CustomFeatureFloatPtrComparer comparer2;
  fires::System sys;

  sys.addObject(&obj1);
  sys.addObject(&obj2);

  sys.addQueryObject(&obj1);

  sys.addFeature(std::string("feature1"), 1.0, &comparer1);
  sys.addFeature(std::string("feature2"), 1.0, &comparer2);
  
  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }

  std::cout << std::endl;

  comparer2.factor = 0.5f;

  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
  {
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  }


}

