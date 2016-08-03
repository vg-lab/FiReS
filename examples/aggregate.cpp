#include <fires/fires.h>

// Function to print out query results
void printObjects( fires::Objects& objects )
{

  std::cout << "[ ";
  for ( auto obj : objects )
  {
    std::cout << obj->label( ) << " = ( ";

    for ( auto f = obj->properties( ).begin( );
          f != obj ->properties( ).end( ); ++f )
    {
      std::cout << "" << ( *f ).first << ": "
                << obj->getProperty(( *f ).first ).value< float >( ) << " ";
    }

    std::cout << ") ";
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

  fires::Aggregate aggregate;
  fires::AggregateConfig aggregateConfig;
  fires::ScalarPropertyAggregator< float > sfaf;
  fires::ScalarPropertyAggregator< int > sfai;
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

  fires::Objects origObjects = objs;

  o1.registerProperty( "f1", 3.1f );
  o2.registerProperty( "f1", 4.1f );
  o3.registerProperty( "f1", 1.2f );
  o4.registerProperty( "f1", 3.1f );


  // std::cout << std::endl << "Ascending and descending" << std::endl;

  std::cout << "Aggregation MAX" << std::endl;
  printObjects( objs );
  aggregateConfig.clear( );
  aggregateConfig.addProperty( "f1", &sfaf );
  aggregate.eval( objs, aggregateConfig );
  printObjects( objs );

  std::cout << std::endl;

  std::cout << "Aggregation MIN" << std::endl;
  objs = origObjects;
  printObjects( objs );
  aggregateConfig.clear( );
  aggregateConfig.addProperty( "f1", &sfaf, fires::PropertyAggregator::MIN );
  aggregate.eval( objs, aggregateConfig );
  printObjects( objs );

  std::cout << std::endl;

  std::cout << "Aggregation MEAN" << std::endl;
  objs = origObjects;
  printObjects( objs );
  aggregateConfig.clear( );
  aggregateConfig.addProperty( "f1", &sfaf, fires::PropertyAggregator::MEAN );
  aggregate.eval( objs, aggregateConfig );
  printObjects( objs );


  // aggregateConfig.clear( );
  // aggregateConfig.addProperty( "f1", &sfsf, fires::AggregatorConfig::DESCENDING );
  // aggregateer.eval( objs, aggregateConfig  );
  // printObjects( objs );

  o1.registerProperty( "f2", 1.3f );
  o2.registerProperty( "f2", 2.5f );
  o3.registerProperty( "f2", 7.6f );
  o4.registerProperty( "f2", 4.1f );

  std::cout << std::endl << "Adding second property" << std::endl;

  std::cout << "Aggregation MIN f1, MAX f2" << std::endl;
  objs = origObjects;
  printObjects( objs );
  aggregateConfig.clear( );
  aggregateConfig.addProperty( "f1", &sfaf, fires::PropertyAggregator::MIN );
  aggregateConfig.addProperty( "f2", &sfaf, fires::PropertyAggregator::MAX );
  aggregate.eval( objs, aggregateConfig );
  printObjects( objs );


  // aggregateConfig.clear( );
  // aggregateConfig.addProperty( "f1", &sfsf );
  // aggregateConfig.addProperty( "f2", &sfsi );
  // aggregateer.eval( objs, aggregateConfig  );
  // printObjects( objs );

  // aggregateConfig.clear( );
  // aggregateConfig.addProperty( "f1", &sfsf );
  // aggregateConfig.addProperty( "f2", &sfsi, fires::AggregatorConfig::DESCENDING );
  // aggregateer.eval( objs, aggregateConfig  );
  // printObjects( objs );


  // aggregateConfig.clear( );
  // aggregateConfig.addProperty( "f1", &sfsf, fires::AggregatorConfig::DESCENDING );
  // aggregateConfig.addProperty( "f2", &sfsi, fires::AggregatorConfig::DESCENDING );
  // aggregateer.eval( objs, aggregateConfig  );
  // printObjects( objs );

  // aggregateConfig.clear( );
  // aggregateConfig.addProperty( "f1", &sfsf, fires::AggregatorConfig::DESCENDING );
  // aggregateConfig.addProperty( "f2", &sfsi, fires::AggregatorConfig::ASCENDING );
  // aggregateer.eval( objs, aggregateConfig  );
  // printObjects( objs );


  // TestObject o5;
  // o5.label( ) = "o5";
  // objs.add( &o5 );

  // std::cout << std::endl
  //           << "Adding object without properties being aggregateed" << std::endl;

  // printObjects( objs );


  // aggregateConfig.clear( );
  // aggregateConfig.addProperty( "f1", &sfsf, fires::AggregatorConfig::ASCENDING );
  // aggregateConfig.addProperty( "f2", &sfsi, fires::AggregatorConfig::DESCENDING );
  // aggregateer.eval( objs, aggregateConfig  );

  // printObjects( objs );


  // objs.clear( );
  // objs.add( &o5 );
  // objs.add( &o1 );
  // objs.add( &o2 );
  // objs.add( &o3 );
  // objs.add( &o4 );


  // printObjects( objs );


  // aggregateConfig.clear( );
  // aggregateConfig.addProperty( "f1", &sfsf, fires::AggregatorConfig::ASCENDING );
  // aggregateConfig.addProperty( "f2", &sfsi, fires::AggregatorConfig::DESCENDING );
  // aggregateer.eval( objs, aggregateConfig  );

  // printObjects( objs );


}
