#include "QueryFeatures.h"


namespace fires
{
  void QueryFeatures::add( std::string label,
                           Comparer * comparer,
                           float weight )
  {
    this->insert(
      std::pair< std::string, QueryFeatureData >(
        label,
        QueryFeatureData( comparer, weight )));
  }

} // namespace fires
