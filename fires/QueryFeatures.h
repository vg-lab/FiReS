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
#include <string>

namespace fires
{
  class QueryFeatureData
  {
  public:

    FIRES_API
    QueryFeatureData( Comparer* comparer_, const float weight_ = 1.0f )
      : _comparer( comparer_ )
      , _weight( weight_ )
    {
    }

    FIRES_API
    const Comparer* comparer( void )
    {
      return _comparer;
    }

    FIRES_API
    void comparer( Comparer* comparer_ )
    {
      _comparer = comparer_;
    }

    FIRES_API
    const float& weight( void )
    {
      return _weight;
    }

    FIRES_API
    void weight( const float weight_ )
    {
      _weight = weight_;
    }

  protected:

    Comparer* _comparer;
    float _weight;


  };

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
    FIRES_API
    void add( std::string label,
              Comparer* comparer,
              float weight = 1.0f );

  }; // class QueryFeatures

} // namespace fires

#endif
