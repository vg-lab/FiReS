#include "SearchConfig.h"


namespace fires
{
  void SearchConfig::add( std::string label,
                           Comparer* comparer_,
                           Averager* averager_,
                           float weight )
  {
    _featuresConfig.insert(
      std::pair< std::string, QueryFeatureData >(
        label,
        QueryFeatureData( comparer_, averager_, weight )));
  }

} // namespace fires
