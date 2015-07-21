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
  }

};


int main( void )
{

  fires::Sort sorter;
  fires::SortConfig sortConfig;
  fires::ScalarFeatureSorter< float > sfsf;
  fires::ScalarFeatureSorter< int > sfsi;
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

  o1.registerFeature( "f1", 3.1f );
  o2.registerFeature( "f1", 4.1f );
  o3.registerFeature( "f1", 1.2f );
  o4.registerFeature( "f1", 3.1f );

  std::cout << std::endl << "Original" << std::endl;

  printObjects( objs );


  std::cout << std::endl << "Ascending and descending" << std::endl;

  sortConfig.clear( );
  sortConfig.addFeature( "f1", &sfsf );
  sorter.eval( objs, sortConfig );
  printObjects( objs );

  sortConfig.clear( );
  sortConfig.addFeature( "f1", &sfsf, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );

  o1.registerFeature( "f2", 1 );
  o2.registerFeature( "f2", 2 );
  o3.registerFeature( "f2", 3 );
  o4.registerFeature( "f2", 4 );

  std::cout << std::endl << "Adding second feature" << std::endl;

  sortConfig.clear( );
  sortConfig.addFeature( "f1", &sfsf );
  sortConfig.addFeature( "f2", &sfsi );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );

  sortConfig.clear( );
  sortConfig.addFeature( "f1", &sfsf );
  sortConfig.addFeature( "f2", &sfsi, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );


  sortConfig.clear( );
  sortConfig.addFeature( "f1", &sfsf, fires::SortConfig::DESCENDING );
  sortConfig.addFeature( "f2", &sfsi, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );

  sortConfig.clear( );
  sortConfig.addFeature( "f1", &sfsf, fires::SortConfig::DESCENDING );
  sortConfig.addFeature( "f2", &sfsi, fires::SortConfig::ASCENDING );
  sorter.eval( objs, sortConfig  );
  printObjects( objs );


  TestObject o5;
  o5.label( ) = "o5";
  objs.add( &o5 );

  std::cout << std::endl
            << "Adding object without features being sorted" << std::endl;

  printObjects( objs );


  sortConfig.clear( );
  sortConfig.addFeature( "f1", &sfsf, fires::SortConfig::ASCENDING );
  sortConfig.addFeature( "f2", &sfsi, fires::SortConfig::DESCENDING );
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
  sortConfig.addFeature( "f1", &sfsf, fires::SortConfig::ASCENDING );
  sortConfig.addFeature( "f2", &sfsi, fires::SortConfig::DESCENDING );
  sorter.eval( objs, sortConfig  );

  printObjects( objs );


}
