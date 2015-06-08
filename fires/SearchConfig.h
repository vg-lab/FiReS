/**
 * @file    SearchConfig.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__SEARCH_CONFIG_H__
#define __FIRES__SEARCH_CONFIG_H__

#include "Comparer.h"
#include "Averager.h"
#include "Task.h"
#include <map>
#include <string>

namespace fires
{

  class QueryFeatureData
  {
  public:

    FIRES_API
    QueryFeatureData( Comparer* comparer_ = 0,
                      Averager* averager_ = 0,
                      const float weight_ = 1.0f )
      : _comparer( comparer_ )
      , _averager( averager_ )
      , _weight( weight_ )
    {
    }

    FIRES_API
    Comparer* comparer( void )
    {
      return _comparer;
    }

    FIRES_API
    void comparer( Comparer* comparer_ )
    {
      _comparer = comparer_;
    }

    FIRES_API
    Averager* averager( void )
    {
      return _averager;
    }

    FIRES_API
    void averager( Averager* averager_ )
    {
      _averager = averager_;
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
    Averager* _averager;
    float _weight;


  };

  /*! \class System::SearchConfig
      \brief Container of the features for query

      It holds a map for the features. The key of the map is a string
      which represents the name of the feature
  */
  class SearchConfig
    : public TaskConfig
  {

  public:

    /// Type of distance used when multiple objects on the query set
    typedef enum
    {
      /// Distance is computed agains the average query object
      DISTANCE_TO_AVERAGE_QUERY_OBJECT,
      /// Distance is computed using the minimum distance to all
      /// objects in the query set
      MINIMUM_DISTANCE_TO_QUERY_OBJECTS
    } TDistanceToQuerySet;

    FIRES_API
    SearchConfig( TDistanceToQuerySet distanceToQueryType_ =
                  DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      : _distanceToQueryType( distanceToQueryType_ )
      , _resultsFeatureLabel( "fires::score" )
    {
    }

    virtual ~SearchConfig( )
    {
    }

    /**
     * Adds a new feature to the container
     * @param label is the name of the feature and the key to be
     *        used afterwards
     * @param weight weight of this feature
     * @param comparer pointer to the comparer object to be used
     *        with this feature
     */
    FIRES_API
    void add( const std::string label,
              Comparer* comparer_,
              Averager* averager_,
              float weight = 1.0f );
    FIRES_API
    Comparer* comparer( const std::string& label )
    {
      return _featuresConfig[ label ].comparer( );
    }

    FIRES_API
    Averager* averager( const std::string& label )
    {
      return _featuresConfig[ label ].averager( );
    }

    FIRES_API
    TDistanceToQuerySet& distanceToQueryType( void )
    {
      return _distanceToQueryType;
    }

    FIRES_API
    std::map< std::string, QueryFeatureData >& features( void )
    {
      return _featuresConfig;
    }

    FIRES_API
    Objects& queryObjects( void )
    {
      return _queryObjects;
    }

    FIRES_API
    std::string& resultsFeatureLabel( void )
    {
      return _resultsFeatureLabel;
    }

  protected:
    //! Configuration for each feature
    std::map< std::string, QueryFeatureData > _featuresConfig;

    //! Query objects
    Objects _queryObjects;

    // Type of distance to the query set
    TDistanceToQuerySet _distanceToQueryType;

    std::string _resultsFeatureLabel;

  }; // class SearchConfig

} // namespace fires

#endif
