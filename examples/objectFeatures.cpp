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

  template < typename T >
  float scalarDistance( Feature& f1, Feature &f2 )
  {
    return ( float ) fabs( double( f1.value<T>( ) - f2.value<T>( )));
  }

  template < typename T >
  float scalarPtrDistance( Feature& f1, Feature &f2 )
  {
    return ( float ) fabs( double (*f1.value<T*>( ) - *f2.value<T*>( )));
  }


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
    f1 += f2;
    std::cout << "Should be 9 now --> " << f1.value< int >( ) << std::endl;
    std::cout << "Should be 6 now --> " << f2.value< int >( ) << std::endl;

    std::cout << std::endl;


    std::cout << fires::scalarDistance< int >( f1, f2 ) << std::endl;

    fires::QueryFeatures qf;
    fires::Comparer c;
    c = &fires::scalarDistance< int >;
    qf.add( "feature1", c, 0.5f );
    // qf.add( "feature1", &fires::scalarDistance< int >, 0.5f );

    std::cout << c( f1, f2 ) << std::endl;

    // fires::QueryFeatureData qfd = qf[ "feature1" ];

    // c = qf.comparer( "feature1" );

    // std::cout <<  qf[ "feature1" ].comparer( )( f1, f2 ) << std::endl;

    // fires::Comparer c2 = qf[ "feature1" ].comparer( );


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

    std::cout << "Should have changed to 7.48 --> "
              << *obj.getFeature( "feature2" ).value< float* >( ) << std::endl;

    std::cout << std::endl;

    floatValue = 5.34f;

    fires::Feature ff2( floatValue2 );
    fires::Feature ffp2( &floatValue2 );

    std::cout << fires::scalarDistance< float >( ff, ff2 ) << std::endl;
    std::cout << fires::scalarPtrDistance< float >( ffp, ffp2 ) << std::endl;

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





}
