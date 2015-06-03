#include <iostream>
#include <fires/fires.h>


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

  // Registering scalar features in an object
  {

    float floatValue = 5.34f;

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
