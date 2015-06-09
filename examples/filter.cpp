#include <fires/fires.h>

// Function to print out query results
void printObjects( fires::Objects& objects )
{
  std::cout << "[ ";
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  {
    std::cout << ( *obj )->label( ) << " ";
  }
  std::cout << "] " << std::endl;
}



class TestObject :
  public fires::Object
{
public:
  TestObject( )
  {
    this->registerFeature( std::string( "feature1" ), &this->attr1 );
    this->registerFeature( std::string( "feature2" ), &this->attr2 );
    this->registerFeature( std::string( "feature3" ), 1.0f );
  }

public:
  float attr1, attr2;

};

int main( void )
{

  // Create objects and give value to their features
  TestObject obj1, obj2, obj3, obj4;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;
  obj1.getFeature( "feature3" ).set( 2.3f );

  obj2.attr1 = 3.2f;
  obj2.attr2 = 42.1f;
  obj2.getFeature( "feature3" ).set< float >( 3.4f );

  obj3.attr1 = 1.4f;
  obj3.attr2 = 2.2f;
  obj3.getFeature( "feature3" ).set< float >( 4.5f );

  obj4.attr1 = 4.1f;
  obj4.attr2 = 1.8f;
  obj4.getFeature( "feature3" ).set< float >( 5.6f );

  // Label objects
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  fires::Objects objects;
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );

  fires::FilterSet fs;
  fires::FilterSetConfig fsc;
  fires::FilterScalarRange< float > ff1( 3.0f, 5.0f );

  printObjects( objects );

  fsc.filters( ).push_back( std::make_pair( "feature3", &ff1 ));
  fs.eval( objects, fsc );
  printObjects( objects );

  ff1.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  fs.eval( objects, fsc );
  printObjects( objects );

}
