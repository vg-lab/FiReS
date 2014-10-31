

#include "../fires/fires.h"

#include <iostream>
#include <math.h>



class Test
{

public: 
  Test ( float attr1In, float attr2In )
    : attr1( attr1In )
    , attr2( attr2In )
  {
  }  

  float attr1, attr2;

};

class TestObject 
  : public Test
  , public fires::Object
{

public:

  TestObject ( float attr1In, float attr2In ) 
    : Test( attr1In, attr2In )
  {
    this->addFeature(std::string("feature1"), 
		     new fires::FeaturePtrToFloat(&this->attr1));
    this->addFeature(std::string("feature2"), 
		     new fires::FeaturePtrToFloat(&this->attr2));
  }
 
  // createFeatures();


};

#define NUM_OBJS 3000000

int main () 
{

  fires::System sys;

  srand(1);

  for ( int i = 0; i < NUM_OBJS; i++ )
  {
    
    float a1 = float( rand( ) ) / float ( RAND_MAX );
    float a2 = float( rand( ) ) / float ( RAND_MAX );

    TestObject * obj =  new TestObject( a1 , a2 );

    obj->label( ) = "OB" + std::to_string(i);

    sys.addObject( obj );

  }

  fires::FeaturePtrToFloatComparer comparer1( 0, 1.0f );
  fires::FeaturePtrToFloatComparer comparer2( 0, 1.0f );


  float a1 = rand() / RAND_MAX;
  float a2 = rand() / RAND_MAX;
  TestObject * queryObj =  new TestObject( a1 , a2 );
  sys.addQueryObject( queryObj );


  sys.addFeature( std::string( "feature1" ), 1.0, 
		  & comparer1, 0.0f, 4.1f );
  sys.addFeature( std::string( "feature2" ), 1.0, 
		  & comparer2, 0.0f, 4.3f );
  
  sys.query();

  // for (fires::System::Results::const_iterator it = sys.results().begin();
  //    it != sys.results().end(); it++)
  //   std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;

  // std::cout << std::endl;







}

