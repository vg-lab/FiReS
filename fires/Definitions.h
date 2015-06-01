#include "Feature.h"
#include "FeatureScalar.h"


namespace fires
{


  FeatureScalar< float >* asFloat( Feature* f )
  {
    return dynamic_cast< fires::FeatureScalar< float >* >( f );
  }

  FeatureScalar< int >* asInteger( Feature* f )
  {
    return dynamic_cast< fires::FeatureScalar< int >* >( f );
  }


}
