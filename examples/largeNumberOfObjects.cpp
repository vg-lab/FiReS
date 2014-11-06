

#include <sys/time.h>

#include <fires/fires.h>

#include <iostream>
#include <math.h>


#define NUM_ATTRIBS 100

class Test
{

public: 
  Test ( )
  {
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

  for ( int i = 0; i < NUM_OBJS; i++ )
  {
    
    TestObject * obj =  new TestObject( );
    obj->label( ) = "OB" + std::to_string(i);

    for ( int j = 0 ; j < NUM_ATTRIBS; j++ )
      obj->attrs[j] = float( rand( ) ) / float ( RAND_MAX );


    sys.addObject( obj );

  }

  fires::FeaturePtrToFloatComparer comparer( 0, 1.0f );



  TestObject * queryObj =  new TestObject( );

  for ( int i = 0 ; i < NUM_ATTRIBS; i++ )
    queryObj->attrs[i] = float( rand( ) ) / float ( RAND_MAX );

  sys.addQueryObject( queryObj );


  for ( int i = 0; i < NUM_ATTRIBS; i++ )
    sys.addFeature( std::string( "feature" ) + std::to_string( i ), 
		    1.0, & comparer );


 
  fires::System::Results resultSerial, resultParallel;   

  {
    struct timeval startTime, endTime;
    long totalTime;
    gettimeofday(&startTime, NULL);
    sys.query();    
    gettimeofday(&endTime, NULL);
    
    totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
    totalTime += (endTime.tv_usec - startTime.tv_usec);

    std::cout << "Serial elapsed: " 
	      << (totalTime/1000L) / 1000.0f << std::endl;

    resultSerial = sys.results( );

  }

  {
    struct timeval startTime, endTime;
    long totalTime;
    gettimeofday(&startTime, NULL);
    sys.parallelQuery();
    gettimeofday(&endTime, NULL);
    
    totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
    totalTime += (endTime.tv_usec - startTime.tv_usec);

    std::cout << "Parallel elapsed: " 
	      << ( totalTime/1000L) / 1000.0f  << std::endl;

    resultParallel  = sys.results( );

  }

  std::cout << "Check results: ";
  if ( resultSerial == resultParallel )
    std::cout << "OK" << std::endl;
  else 
    std::cout << "ERR" << std::endl;


  // Uncomment the following for printing
  
  // for (fires::System::Results::const_iterator it = resultSerial.begin();
  //    it != resultSerial.end(); it++)
  //   std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;

  // std::cout << std::endl;


  // for (fires::System::Results::const_iterator it = resultParallel.begin();
  //    it != resultParallel.end(); it++)
  //   std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;

  // std::cout << std::endl;







}

