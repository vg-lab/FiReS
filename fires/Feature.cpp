#include "Feature.h"

#include <string>

namespace fires
{

  Feature::Feature( void )
  {
  };

  Feature::~Feature( )
  {
  };

  Feature* Feature::newFeature( void ) const
  {
    return nullptr;
  };

  void Feature::deleteFeature( void )
  {
    return;
  };

  Feature& Feature::operator +=( const Feature& rhs )
  {
    throw std::runtime_error(
      std::string( "Error: += operator not implemented for Feature." ) +
      std::string( " rhs address = " + std::to_string( long( & rhs ))));

    return *this;
  }

  Feature& Feature::operator /= ( const int& rhs )
  {
    throw std::runtime_error(
      std::string( "Error: /= operator not implemented Feature ") +
      std::string( "( rhs = " ) + std::to_string( rhs ) +
      std::string( ")" ));

    return *this;
  }


} // namespace fires;
