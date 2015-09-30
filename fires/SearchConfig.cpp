#include "SearchConfig.h"


namespace fires
{
  void SearchConfig::add( const std::string& label,
                          Comparer* comparer_,
                          Averager* averager_,
                          Normalizer* normalizer_,
                          float weight )
  {
    _propertiesConfig.insert(
      std::pair< std::string, QueryPropertyData >(
        label,
        QueryPropertyData( comparer_, averager_, normalizer_, weight )));
  }

} // namespace fires
