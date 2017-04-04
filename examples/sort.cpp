#include <fires/fires.h>

// Function to print out results
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
  }

};


int main( void )
{

  fires::Sort sorter;
  fires::SortConfig sortConfig;
  fires::ScalarPropertySorter< float > sfsf;
  fires::ScalarPropertySorter< int > sfsi;
  fires::Objects objs;

  TestObject o1, o2, o3, o4;

  o1.label( ) = "o1";
  o2.label( ) = "o2";
  o3.label( ) = "o3";
  o4.label( ) = "o4";

  objs.add( &o1 );
  objs.add( &o2 );
  objs.add( &o3 );
  objs.add( &o4 );

  o1.registerProperty( "f1", 3.1f );
  o2.registerProperty( "f1", 4.1f );
  o3.registerProperty( "f1", 1.2f );
  o4.registerProperty( "f1", 3.1f );

  std::cout << std::endl << "Original" << std::endl;

  printObjects( objs );


  std::cout << std::endl << "Ascending and descending" << std::endl;

  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf );
  sorter.eval( objs, sortConfig );
  printObjects( objs );

  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );

  o1.registerProperty( "f2", 1 );
  o2.registerProperty( "f2", 2 );
  o3.registerProperty( "f2", 3 );
  o4.registerProperty( "f2", 4 );

  std::cout << std::endl << "Adding second property" << std::endl;

  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf );
  sortConfig.addProperty( "f2", &sfsi );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );

  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf );
  sortConfig.addProperty( "f2", &sfsi, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );


  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf, fires::SortConfig::DESCENDING );
  sortConfig.addProperty( "f2", &sfsi, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );

  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf, fires::SortConfig::DESCENDING );
  sortConfig.addProperty( "f2", &sfsi, fires::SortConfig::ASCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );


  TestObject o5;
  o5.label( ) = "o5";
  objs.add( &o5 );

  std::cout << std::endl
            << "Adding object without propertys being sorted" << std::endl;

  printObjects( objs );


  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf, fires::SortConfig::ASCENDING );
  sortConfig.addProperty( "f2", &sfsi, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );

  printObjects( objs );


  objs.clear( );
  objs.add( &o5 );
  objs.add( &o1 );
  objs.add( &o2 );
  objs.add( &o3 );
  objs.add( &o4 );


  printObjects( objs );


  sortConfig.clear( );
  sortConfig.addProperty( "f1", &sfsf, fires::SortConfig::ASCENDING );
  sortConfig.addProperty( "f2", &sfsi, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );

  printObjects( objs );


}
