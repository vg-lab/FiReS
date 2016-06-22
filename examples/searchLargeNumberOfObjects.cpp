#if defined( Win32 ) || defined( _WINDOWS ) || defined( MSVC )
#include <iostream>
int main( void )
{
  std::cerr << "Not implemented in Windows yet!" << std::endl;
}
#else
#include <sys/time.h>

#include <fires/fires.h>

#include <iostream>
#include <math.h>

#define NUM_OBJS 100000
#define NUM_ATTRIBS 100

fires::Object* deleteObject( fires::Object* obj )
{
  delete obj;
  return nullptr;
}

class Test
{

public:
  Test ( void )
  {
    for ( unsigned int i = 0; i < NUM_ATTRIBS; ++i )
      attrs[i] = 0;
  }

  float attrs[NUM_ATTRIBS];


};

class TestObject
  : public Test
  , public fires::Object
{

public:

  TestObject ( )
  {

    for ( int i = 0; i < NUM_ATTRIBS; i++ )
      this->registerProperty( std::string( "property" ) + std::to_string( i ),
                             &this->attrs[i]);
  }


};


int main ( void )
{


  srand(1);

  fires::Objects objects;

  std::cout << "Creating objects" << std::endl;
  for ( int i = 0; i < NUM_OBJS; i++ )
  {
    TestObject* obj =  new TestObject( );
    obj->label( ) = "OB" + std::to_string(i);

    for ( int j = 0 ; j < NUM_ATTRIBS; j++ )
      obj->attrs[j] = float( rand( ) ) / float ( RAND_MAX );

    objects.add( obj );

  }

  fires::ScalarComparer< float* > comparer;
  fires::ScalarAverager< float* > averager;


  std::cout << "Creating query object" << std::endl;
  TestObject* queryObj =  new TestObject( );
  for ( int i = 0 ; i < NUM_ATTRIBS; i++ )
    queryObj->attrs[i] = float( rand( ) ) / float ( RAND_MAX );


  fires::SearchConfig sc;
  for ( int i = 0; i < NUM_ATTRIBS; i++ )
    sc.add( std::string( "property" ) + std::to_string( i ),
            &comparer, &averager );

  sc.queryObjects( ).add( queryObj );


  {

    std::cout << "Performing query" << std::endl;
    sc.resultsPropertyLabel( ) = "fires::score::serial";

    fires::Search search;
    struct timeval startTime, endTime;
    long totalTime;
    gettimeofday(&startTime, NULL);
    search.eval( objects, sc );
    gettimeofday(&endTime, NULL);

    totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
    totalTime += (endTime.tv_usec - startTime.tv_usec);

    std::cout << "Serial elapsed: "
              << (totalTime/1000L) / 1000.0f << std::endl;

  }

  // {
  //   struct timeval startTime, endTime;
  //   long totalTime;
  //   gettimeofday(&startTime, NULL);
  //   engine.parallelQuery( objects, queryObjects, properties,
  //                      "fires::score::parallel" );
  //   gettimeofday(&endTime, NULL);

  //   totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
  //   totalTime += (endTime.tv_usec - startTime.tv_usec);

  //   std::cout << "Parallel elapsed: "
  //             << ( totalTime/1000L) / 1000.0f  << std::endl;

  // }

  // std::cout << "Check results: ";
  // for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  //   if (( *obj )->getProperty( "fires::score::serial" ) !=
  //       ( *obj )->getProperty( "fires::score::parallel" ))
  //   {
  //     std::cerr << "ERROR" << std::endl;
  //     return -1;
  //   }

  //   std::cout << "OK" << std::endl;


  std::cout << "Freeing objects" << std::endl;
  auto it = objects.begin( );
  std::transform( objects.begin( ), objects.end( ), it, deleteObject );
  delete queryObj;

  std::cout << "Finished" << std::endl;


  return 0;


}
#endif
