#include <iostream>
#include <fires/fires.h>
#include <math.h>

class ClassFeature
{

public:

  int i;
  float j;

};

std::ostream& operator<<( std::ostream& os,
                          const ClassFeature& dt)
{
  os << "(" << dt.i << "," << dt.j << ")";
    return os;
}

namespace fires
{
  // class AveragerFeatures : public map< std::string, 

  // class ObjectAverager
  // {

  //   virtual fires::Object& average( Objects objs,
  //                                   AveragerFeatures features )
  //   {
  //     for ( obj : objs )
  //     {
  //     }
  //   }

  // }



}

int main( void )
{

  // Testing int feature
  {
    int i = 3;
    float f = 5.6f;

    fires::Feature f1( i );
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

    fires::Feature f1( i );
    fires::Feature f2( j );

    std::cout << "Should be 3 now --> " << f1.value< int >( ) << std::endl;
    std::cout << "Should be 6 now --> " << f2.value< int >( ) << std::endl;

    std::cout << std::endl;


    fires::SearchConfig sc;
    fires::Comparer* c = new fires::ScalarComparer< int >( );

    std::cout << c->distance( f1, f2 ) << std::endl;

    sc.add( std::string( "feature1" ), c, 0, 0.5f );
    std::cout << sc.comparer( "feature1" )->distance( f1, f2 )
              << std::endl;


  }

  // Registering scalar features in an object
  {

    float floatValue = 5.34f;
    float floatValue2 = 7.23f;

    fires::Feature ff( floatValue );
    fires::Feature ffp( &floatValue );

    fires::Object obj;
    obj.registerFeature( "feature1", ff );
    obj.registerFeature( "feature2", ffp );

    std::cout << "Should be 5.34 --> "
              << obj.getFeature( "feature1" ).value< float >( ) << std::endl;

    std::cout << "Should be 5.34 --> "
              << *obj.getFeature( "feature2" ).value< float* >( ) << std::endl;

    floatValue = 7.48f;

    std::cout << "Should remain 5.34 --> "
              << obj.getFeature( "feature1" ).value< float >( ) << std::endl;

    std::cout << "Should have changed to " << floatValue
              << *obj.getFeature( "feature2" ).value< float* >( ) << std::endl;

    std::cout << std::endl;

    //floatValue = 5.34f;

    fires::Feature ff2( floatValue2 );
    fires::Feature ffp2( &floatValue2 );

    // std::cout << fires::scalarDistance< float >( ff, ff2 ) << std::endl;
    // std::cout << fires::scalarPtrDistance< float >( ffp, ffp2 ) << std::endl;

    std::cout << std::endl;


  }

  // Registering class-based features in an object
  {
    ClassFeature cf1;
    cf1.i = 3; cf1.j = 5.6f;

    fires::Feature f1( cf1 );

    std::cout << f1.value< ClassFeature >( ) << std::endl;

    fires::Object obj;
    obj.registerFeature( "feature1", f1 );
    std::cout << obj.getFeature( "feature1" ).value< ClassFeature >( )
              << std::endl;


  }


  {

    class TestObject : public fires::Object
    {

    public:

      TestObject( void )
      {
        this->registerFeature( "feature1", fires::Feature( &attr1 ));
        this->registerFeature( "feature2", fires::Feature( &attr2 ));

        this->registerFeature( "feature3", fires::Feature( 1 ));
        this->registerFeature( "feature4", fires::Feature( 5.4f ));

      }

      int attr1;
      float attr2;

    };

    class TestObject2 : public fires::Object
    {

    public:

      TestObject2( void )
      {
        this->registerFeature( "feature1", fires::Feature( &attr1 ));
        this->registerFeature( "feature2", fires::Feature( &attr2 ));

        this->registerFeature( "feature3", fires::Feature( 4 ));
        this->registerFeature( "feature4", fires::Feature( 6.7f ));

      }

      int attr1;
      float attr2;

    };


    TestObject obj1;
    TestObject2 obj2;

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
    fires::ScalarPtrComparer< int > scpi;
    fires::ScalarPtrComparer< float > scpf;
    fires::ScalarAverager< int > sai;
    fires::ScalarAverager< float > saf;
    fires::ScalarPtrAverager< int > sapi;
    fires::ScalarPtrAverager< float > sapf;

    qf.add( std::string( "feature1" ), &scpi, &sapi);
    qf.add( std::string( "feature2" ), &scpf, &sapf);
    qf.add( std::string( "feature3" ), &sci, &sai);
    qf.add( std::string( "feature4" ), &scf, &saf);


    fires::Object meanObj;

    for ( auto qfd = qf.features( ).begin( );
          qfd != qf.features( ).end( ); ++qfd )
    {

      std::string featLabel = qfd->first;
      std::cout << "Averaging feature: " << featLabel << std::endl;
      qfd->second.averager( )->reset( );

      for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      {
        qfd->second.averager( )->accum(( *obj )->getFeature( featLabel ));
      }

      qfd->second.averager( )->divide( objs.size( ));
      std::cout << qfd->second.averager( )->feature( ).type( ) << std::endl;
      meanObj.registerFeature( featLabel,
                               qfd->second.averager( )->feature( ));


    }


    std::cout << "Mean obj " << *meanObj.getFeature( "feature1" ).value< int* >( )
              << std::endl;
    std::cout << "Mean obj " << *meanObj.getFeature( "feature2" ).value< float* >( )
              << std::endl;
    std::cout << "Mean obj " << meanObj.getFeature( "feature3" ).value< int >( )
              << std::endl;
    std::cout << "Mean obj " << meanObj.getFeature( "feature4" ).value< float >( )
              << std::endl;



    for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      for ( auto qfd = qf.features( ).begin( );
            qfd != qf.features( ).end( ); ++qfd )
      {
        std::string featLabel = qfd->first;
        fires::Comparer* comparer = qfd->second.comparer( );

        std::cout << comparer->distance( obj1.getFeature( featLabel ),
                                         ( *obj )->getFeature( featLabel ))
                  << std::endl;

      }

    std::cout << std::endl;

    for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      for ( auto qfd = qf.features( ).begin( );
            qfd != qf.features( ).end( ); ++qfd )
      {
        std::string featLabel = qfd->first;
        fires::Comparer* comparer = qfd->second.comparer( );

        std::cout << comparer->distance( meanObj.getFeature( featLabel ),
                                         ( *obj )->getFeature( featLabel ))
                  << std::endl;

      }


  }



}
