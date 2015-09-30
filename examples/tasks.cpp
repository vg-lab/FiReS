#include <fires/fires.h>

// Function to print out query results
void printResults( fires::Objects& objects, std::string scoreLabel )
{

  std::cout << objects.size( ) << " elements" << std::endl;
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  {
    std::cout << ( *obj )->label( ) << ": "
              << ( *obj )->getProperty( scoreLabel ).value< float >( )
              << std::endl;
  }
}


class TestObject :
  public fires::Object
{
public:
  TestObject( )
  {
    this->registerProperty( std::string( "property1" ), &this->attr1 );
    this->registerProperty( std::string( "property2" ), &this->attr2 );
  }

public:
  float attr1, attr2;

};

int main( void )
{

  // Create objects and give value to their propertys
  TestObject obj1, obj2, obj3, obj4;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;

  obj2.attr1 = 3.2f;
  obj2.attr2 = 42.1f;

  obj3.attr1 = 1.4f;
  obj3.attr2 = 2.2f;

  obj4.attr1 = 4.1f;
  obj4.attr2 = 1.8f;

  // Label objects
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  // Create comparers
  fires::ScalarComparer< float* > comparer;
  fires::ScalarAverager< float* > averager;
  fires::Search search;
  fires::SearchConfig sc;
  sc.add( std::string("property1"), &comparer, &averager );
  sc.add( std::string("property2"), &comparer, &averager );
  sc.queryObjects( ).add( &obj1 );
  sc.queryObjects( ).add( &obj2 );

  fires::Tasks tasks;
  tasks.push_back( fires::TasksConfig( &search, &sc ));


  fires::FilterSet fs;
  fires::FilterSetConfig fsc;
  fires::FilterScalarRange< float > fsrf( 10.0f, 20.0f );
  fsc.filters( ).push_back( std::make_pair( "fires::score", &fsrf ));
  tasks.push_back( fires::TasksConfig( &fs, &fsc));

  fires::Engine engine;

  fires::Objects objects;
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );


  auto objects1 = objects;
  engine.run( objects1, tasks );
  printResults( objects1, "fires::score" );
  std::cout << std::endl;

  sc.distanceToQueryType( ) =
    fires::SearchConfig::MINIMUM_DISTANCE_TO_QUERY_OBJECTS;

  fsrf.min( ) = 1.0f;
  fsrf.max( ) = 3.0f;

  engine.run( objects, tasks );
  printResults( objects, "fires::score" );


  return 0;
}
