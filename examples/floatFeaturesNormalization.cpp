

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
		     new fires::FeaturePtrToFloat(&this->attr1));
    this->addFeature(std::string("feature2"), 
		     new fires::FeaturePtrToFloat(&this->attr2));
  }
 
  // createFeatures();


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

  
  fires::FeaturePtrToFloatComparer comparer1( 0, 4.1f );
  fires::FeaturePtrToFloatComparer comparer2( 0, 42.1f );

  fires::System sys;

  sys.addObject( & objMin );
  sys.addObject( & objMax );
  sys.addObject( & obj1 );
  sys.addObject( & obj2 );
  sys.addObject( & obj3 );
  sys.addObject( & obj4 );

  sys.addQueryObject( & objMax );

  sys.addFeature( std::string( "feature1" ), 1.0, 
		  & comparer1 );

  sys.addFeature( std::string( "feature2" ), 1.0, 
		  & comparer2 );
  
  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;

  std::cout << std::endl;







}

