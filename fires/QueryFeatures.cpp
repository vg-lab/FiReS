#include "QueryFeatures.h"


namespace fires
{
  void QueryFeatures::add(std::string label,
                          float weight,
                          Comparer * comparer)
  {
    this->insert(std::pair<std::string,
                 QueryFeatureData>(label,
                                   QueryFeatureData{weight,
                                       comparer}));
  }

} // namespace fires
