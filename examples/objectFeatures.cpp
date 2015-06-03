#include <iostream>
#include <fires/fires.h>


class ComplexFeature : public fires::Feature
{

public:

  int i;
  float j;

};


int main( void )
{

  fires::Object obj;

  int i = 3;

  fires::Feature f1 = i;
  fires::Feature f2;

  obj.registerFeature( "feature1", f1 );
  f2 = obj.getFeature( "feature1" );

  std::cout << boost::any_cast< int >( f1 ) << std::endl;
  std::cout << boost::any_cast< int >( f2 ) << std::endl;

  i = 5;

  std::cout << boost::any_cast< int >( f1 ) << std::endl;
  std::cout << boost::any_cast< int >( f2 ) << std::endl;


  fires::Feature fp1 = &i;
  fires::Feature fp2;

  obj.registerFeature( "feature2", fp1 );
  fp2 = obj.getFeature( "feature2" );

  i = 3;

  std::cout << *boost::any_cast< int* >( fp1 ) << std::endl;
  std::cout << *boost::any_cast< int* >( fp2 ) << std::endl;

  i = 5;

  std::cout << *boost::any_cast< int* >( fp1 ) << std::endl;
  std::cout << *boost::any_cast< int* >( fp2 ) << std::endl;

  // Class feature based example
  ComplexFeature cf1, cf2;
  cf1.i = 3;
  cf1.j = 4.5f;

  f1 = cf1;
  obj.registerFeature( "feature3", cf1 );
  f2 = obj.getFeature( "feature3" );

  cf2 = boost::any_cast< ComplexFeature >( f2 );

  std::cout << "(" << cf2.i << "," << cf2.j << ")" << std::endl;


  ComplexFeature *cfp1 = new ComplexFeature;
  ComplexFeature *cfp2;

  fp1 = cfp1;

  cfp1->i = 3;
  cfp1->j = 4.5f;

  obj.registerFeature( "feature4", fp1 );
  f2 = obj.getFeature( "feature4" );

  cfp2 = boost::any_cast< ComplexFeature* >( f2 );

  std::cout << "(" << cfp2->i << "," << cfp2->j << ")" << std::endl;

  cfp1->i = 4;
  cfp1->j = 5.6f;

  std::cout << "(" << cfp2->i << "," << cfp2->j << ")" << std::endl;


}
