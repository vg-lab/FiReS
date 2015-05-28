/**
 * @file    QueryFeatures.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__QUERY_FEATURES_H__
#define __FIRES__QUERY_FEATURES_H__

#include "Comparer.h"
#include <map>

namespace fires
{
  typedef struct
  {
    float weight;
    Comparer* comparer;
  } QueryFeatureData;

  /*! \class System::QueryFeatures
      \brief Container of the features for query

      It holds a map for the features. The key of the map is a string
      which represents the name of the feature
  */
  class QueryFeatures
    : public std::map< std::string, QueryFeatureData >
  {

  public:

    /**
     * Adds a new feature to the container
     * @param label is the name of the feature and the key to be
     *        used afterwards
     * @param weight weight of this feature
     * @param comparer pointer to the comparer object to be used
     *        with this feature
     */
    void add( std::string label,
              float weight,
              Comparer* comparer );

  }; // class QueryFeatures

} // namespace fires

#endif
