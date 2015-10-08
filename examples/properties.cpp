#include <iostream>
#include <fires/fires.h>
#include <math.h>

class ClassProperty
{

public:

  int i;
  float j;

};

std::ostream& operator<<( std::ostream& os,
                          const ClassProperty& dt)
{
  os << "(" << dt.i << "," << dt.j << ")";
    return os;
}

int main( void )
{

  // Testing int property
  {
    int i = 3;
    float f = 5.6f;

    fires::Property f1( i );
    std::cout << "Should be 3 --> " << f1.value< int >( ) << std::endl;

    i = 5;
    std::cout << "Should still be 3 --> " << f1.value< int >( ) << std::endl;

    f1.set< int >( i );
    std::cout << "Should be 5 now --> " << f1.value< int >( ) << std::endl;

    // Muting it to float
    f1.set< float >( f );
    std::cout << "Should be 5.6 now --> " << f1.value< float >( ) << std::endl;
    std::cout << std::endl;

  }

  {
    int i = 3;
    int j = 6;

    fires::Property f1( i );
    fires::Property f2( j );

    std::cout << "Should be 3 now --> " << f1.value< int >( ) << std::endl;
    std::cout << "Should be 6 now --> " << f2.value< int >( ) << std::endl;

    std::cout << std::endl;


    fires::SearchConfig sc;
    fires::Comparer* c = new fires::ScalarComparer< int >( );

    std::cout << c->distance( f1, f2 ) << std::endl;

    sc.add( std::string( "property1" ), c, 0, nullptr, 0.5f );
    std::cout << sc.comparer( "property1" )->distance( f1, f2 )
              << std::endl;


  }

  // Registering scalar properties in an object
  {

    float floatValue = 5.34f;
    float floatValue2 = 7.23f;

    fires::Property ff( floatValue );
    fires::Property ffp( &floatValue );

    fires::Object obj;
    obj.registerProperty( "property1", ff );
    obj.registerProperty( "property2", ffp );

    std::cout << "Should be 5.34 --> "
              << obj.getProperty( "property1" ).value< float >( ) << std::endl;

    std::cout << "Should be 5.34 --> "
              << *obj.getProperty( "property2" ).value< float* >( ) << std::endl;

    floatValue = 7.48f;

    std::cout << "Should remain 5.34 --> "
              << obj.getProperty( "property1" ).value< float >( ) << std::endl;

    std::cout << "Should have changed to " << floatValue
              << *obj.getProperty( "property2" ).value< float* >( ) << std::endl;

    std::cout << std::endl;

    //floatValue = 5.34f;

    fires::Property ff2( floatValue2 );
    fires::Property ffp2( &floatValue2 );

    // std::cout << fires::scalarDistance< float >( ff, ff2 ) << std::endl;
    // std::cout << fires::scalarPtrDistance< float >( ffp, ffp2 ) << std::endl;

    std::cout << std::endl;


  }

  // Registering class-based properties in an object
  {
    ClassProperty cf1;
    cf1.i = 3; cf1.j = 5.6f;

    fires::Property f1( cf1 );

    std::cout << f1.value< ClassProperty >( ) << std::endl;

    fires::Object obj;
    obj.registerProperty( "property1", f1 );
    std::cout << obj.getProperty( "property1" ).value< ClassProperty >( )
              << std::endl;


  }


  {

    class TestObject : public fires::Object
    {

    public:

      TestObject( void )
      {
        this->registerProperty( "property1", fires::Property( &attr1 ));
        this->registerProperty( "property2", fires::Property( &attr2 ));

        this->registerProperty( "property3", fires::Property( 1 ));
        this->registerProperty( "property4", fires::Property( 5.4f ));

      }

      int attr1;
      float attr2;

    };

    class TestObject2 : public fires::Object
    {

    public:

      TestObject2( void )
      {
        this->registerProperty( "property1", fires::Property( &attr1 ));
        this->registerProperty( "property2", fires::Property( &attr2 ));

        this->registerProperty( "property3", fires::Property( 4 ));
        this->registerProperty( "property4", fires::Property( 6.7f ));

      }

      int attr1;
      float attr2;

    };


    TestObject obj1;
    TestObject2 obj2;

    std::cout << obj2.getProperty( "property3" ).value< int >( ) << std::endl;
    std::cout << obj2.getProperty( "property4" ).value< float >( ) << std::endl;

    obj1.attr1 = 3;
    obj1.attr2 = 4.1f;

    obj2.attr1 = 5;
    obj2.attr2 = 2.3f;

    fires::Objects objs;
    objs.add( &obj1 );
    objs.add( &obj2 );

    fires::SearchConfig qf;

    fires::ScalarComparer< int > sci;
    fires::ScalarComparer< float > scf;
    fires::ScalarComparer< int* > scpi;
    fires::ScalarComparer< float* > scpf;
    fires::ScalarAverager< int > sai;
    fires::ScalarAverager< float > saf;
    fires::ScalarAverager< int* > sapi;
    fires::ScalarAverager< float* > sapf;

    qf.add( std::string( "property1" ), &scpi, &sapi);
    qf.add( std::string( "property2" ), &scpf, &sapf);
    qf.add( std::string( "property3" ), &sci, &sai);
    qf.add( std::string( "property4" ), &scf, &saf);


    fires::Object meanObj;

    for ( auto qfd = qf.properties( ).begin( );
          qfd != qf.properties( ).end( ); ++qfd )
    {

      std::string featLabel = qfd->first;
      std::cout << "Averaging property: " << featLabel << std::endl;
      qfd->second.averager( )->reset( );

      for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      {
        qfd->second.averager( )->accum(( *obj )->getProperty( featLabel ));
      }

      qfd->second.averager( )->divide( (unsigned int ) objs.size( ));
      std::cout << qfd->second.averager( )->property( ).type( ) << std::endl;
      meanObj.registerProperty( featLabel,
                               qfd->second.averager( )->property( ));


    }


    std::cout << "Mean obj " << *meanObj.getProperty( "property1" ).value< int* >( )
              << std::endl;
    std::cout << "Mean obj " << *meanObj.getProperty( "property2" ).value< float* >( )
              << std::endl;
    std::cout << "Mean obj " << meanObj.getProperty( "property3" ).value< int >( )
              << std::endl;
    std::cout << "Mean obj " << meanObj.getProperty( "property4" ).value< float >( )
              << std::endl;



    for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      for ( auto qfd = qf.properties( ).begin( );
            qfd != qf.properties( ).end( ); ++qfd )
      {
        std::string featLabel = qfd->first;
        fires::Comparer* comparer = qfd->second.comparer( );

        std::cout << comparer->distance( obj1.getProperty( featLabel ),
                                         ( *obj )->getProperty( featLabel ))
                  << std::endl;

      }

    std::cout << std::endl;

    for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      for ( auto qfd = qf.properties( ).begin( );
            qfd != qf.properties( ).end( ); ++qfd )
      {
        std::string featLabel = qfd->first;
        fires::Comparer* comparer = qfd->second.comparer( );

        std::cout << comparer->distance( meanObj.getProperty( featLabel ),
                                         ( *obj )->getProperty( featLabel ))
                  << std::endl;

      }


  }



}
