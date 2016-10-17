#include <fires/fires.h>

// Function to print out query results
void printObjects( fires::Objects& objects,
                   const std::string& filterLabel = "" )
{
  std::cout << "[ ";
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  {
    std::cout << ( *obj )->label( ) << " ";
    if ( filterLabel != "" )
      std::cout << std::boolalpha << "("
                << ( *obj )->getProperty( filterLabel ).value< bool >( )
                << ") ";
  }
  std::cout << "] " << std::endl;
}



class TestObject :
  public fires::Object
{
public:
  TestObject( )
  {
    this->registerProperty( std::string( "property1" ), &this->attr1 );
    this->registerProperty( std::string( "property2" ), &this->attr2 );
    this->registerProperty( std::string( "property3" ), 0.0f );
    this->registerProperty( std::string( "property4" ), 0 );
  }

public:
  float attr1;
  int attr2;

};

int main( void )
{

  // Create objects and give value to their propertiess
  TestObject obj1, obj2, obj3, obj4;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4;
  obj1.getProperty( "property3" ).set( 2.3f );
  obj1.getProperty( "property4" ).set( 4 );

  obj2.attr1 = 3.2f;
  obj2.attr2 = 10;
  obj2["property3"].set( 3.4f );
  obj2.getProperty( "property4" ).set( 10 );

  obj3.attr1 = 1.4f;
  obj3.attr2 = 3;
  obj3.getProperty( "property3" ).set( 4.5f );
  obj3.getProperty( "property4" ).set( 3 );

  obj4.attr1 = 4.1f;
  obj4.attr2 = 5;
  obj4.getProperty( "property3" ).set( 5.6f );
  obj4.getProperty( "property4" ).set( 5 );

  // Label objects
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  fires::Objects objects;

  {
    objects.addList( { &obj1, &obj2, &obj3, &obj4 } );
    fires::FilterSet fs0;
    fires::FilterSetConfig fsc0;
    fires::FilterMinValue< float > ff10( 5.0f );

    fsc0.filters( ).push_back( std::make_pair( "property3", &ff10 ));
    fs0.eval( objects, fsc0 );
    printObjects( objects );
  }
  {
    objects.addList( { &obj1, &obj2, &obj3, &obj4 } );
    fires::FilterSet fs0;
    fires::FilterSetConfig fsc0;
    fires::FilterMaxValue< float > ff10( 5.0f );

    fsc0.filters( ).push_back( std::make_pair( "property3", &ff10 ));
    fs0.eval( objects, fsc0 );
    printObjects( objects );
  }

  objects.clearAdds( { &obj1, &obj2, &obj3, &obj4 } );

  fires::FilterSet fs;
  fires::FilterSetConfig fsc;
  fires::FilterScalarRange< float > ff1( 3.0f, 5.0f );
  fires::FilterScalarRange< int > fi1( 0, 9 );

  printObjects( objects );

  fsc.filters( ).push_back( std::make_pair( "property3", &ff1 ));
  fs.eval( objects, fsc );
  printObjects( objects );

  ff1.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  fs.eval( objects, fsc );
  printObjects( objects );

  objects.clearAdds( { &obj1, &obj2, &obj3, &obj4 } );

  fsc.filters( ).push_back( std::make_pair( "property4", &fi1 ));
  fs.eval( objects, fsc );
  printObjects( objects );

  objects.clear( );
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );

  ff1.rangeInclusion( ) = fires::FilterRange::INSIDE_RANGE;
  fsc.filterPropertyLabel( ) = std::string( "fires::filter" );
  fs.eval( objects, fsc );
  printObjects( objects, "fires::filter" );

  ff1.rangeInclusion( ) = fires::FilterRange::OUTSIDE_RANGE;
  fs.eval( objects, fsc );
  printObjects( objects, "fires::filter" );

}
