#include <sys/time.h>

#include <fires/fires.h>

#include <iostream>
#include <math.h>


#define NUM_ATTRIBS 100

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
      this->addFeature( std::string( "feature" ) + std::to_string( i ),
                        new fires::FeaturePtrToFloat( & this->attrs[i] ));
  }


};

#define NUM_OBJS 100000
//3000000

int main ()
{

  fires::System sys;

  srand(1);

  fires::Objects objects;

  for ( int i = 0; i < NUM_OBJS; i++ )
  {

    TestObject * obj =  new TestObject( );
    obj->label( ) = "OB" + std::to_string(i);

    for ( int j = 0 ; j < NUM_ATTRIBS; j++ )
      obj->attrs[j] = float( rand( ) ) / float ( RAND_MAX );


    objects.add( obj );

  }

  fires::FeaturePtrToFloatComparer comparer( 0, 1.0f );

  TestObject* queryObj =  new TestObject( );

  for ( int i = 0 ; i < NUM_ATTRIBS; i++ )
    queryObj->attrs[i] = float( rand( ) ) / float ( RAND_MAX );

  fires::Objects queryObjects;
  queryObjects.add( queryObj );

  fires::QueryFeatures features;
  for ( int i = 0; i < NUM_ATTRIBS; i++ )
    features.add( std::string( "feature" ) + std::to_string( i ),
                  &comparer );



  // fires::System::Results resultSerial, resultParallel;

  {
    struct timeval startTime, endTime;
    long totalTime;
    gettimeofday(&startTime, NULL);
    sys.query( objects, queryObjects, features, "fires::score::serial" );
    gettimeofday(&endTime, NULL);

    totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
    totalTime += (endTime.tv_usec - startTime.tv_usec);

    std::cout << "Serial elapsed: "
              << (totalTime/1000L) / 1000.0f << std::endl;

    //resultSerial = sys.results( );

  }

  {
    struct timeval startTime, endTime;
    long totalTime;
    gettimeofday(&startTime, NULL);
    sys.parallelQuery( objects, queryObjects, features,
                       "fires::score::parallel" );
    gettimeofday(&endTime, NULL);

    totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
    totalTime += (endTime.tv_usec - startTime.tv_usec);

    std::cout << "Parallel elapsed: "
              << ( totalTime/1000L) / 1000.0f  << std::endl;

  }

  std::cout << "Check results: ";
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
    if (( *obj )->getFeature( "fires::score::serial" ) !=
        ( *obj )->getFeature( "fires::score::parallel" ))
    {
      std::cerr << "ERROR" << std::endl;
      return -1;
    }

    std::cout << "OK" << std::endl;
    return 0;


}
