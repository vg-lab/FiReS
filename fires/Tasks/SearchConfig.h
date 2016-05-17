/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/gmrvvis/FiReS>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#ifndef __FIRES__SEARCH_CONFIG_H__
#define __FIRES__SEARCH_CONFIG_H__

#include "../Property/Comparer.h"
#include "../Property/Averager.h"
#include "../Property/Normalizer.h"
#include "Task.h"
#include <map>
#include <string>

namespace fires
{

  class QueryPropertyData
  {
  public:

    FIRES_API
    QueryPropertyData( Comparer* comparer_ = 0,
                      Averager* averager_ = 0,
                      Normalizer* normalizer_ = 0,
                      const float weight_ = 1.0f )
      : _comparer( comparer_ )
      , _averager( averager_ )
      , _normalizer( normalizer_ )
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
    Normalizer* normalizer( void )
    {
      return _normalizer;
    }

    FIRES_API
    void normalizer( Normalizer* normalizer_ )
    {
      _normalizer = normalizer_;
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
    Normalizer* _normalizer;
    float _weight;


  };

  /*! \class System::SearchConfig
      \brief Container of the properties for query

      It holds a map for the properties. The key of the map is a string
      which represents the name of the property
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
      , _resultsPropertyLabel( "fires::score" )
    {
    }

    virtual ~SearchConfig( )
    {
    }

    /**
     * Adds a new property to the container
     * @param label is the name of the property and the key to be
     *        used afterwards
     * @param weight weight of this property
     * @param comparer pointer to the comparer object to be used
     *        with this property
     */
    FIRES_API
    void add( const std::string& label,
              Comparer* comparer_ = nullptr,
              Averager* averager_ = nullptr,
              Normalizer* normalizer_ = nullptr,
              float weight = 1.0f );
    FIRES_API
    Comparer* comparer( const std::string& label )
    {
      return _propertiesConfig[ label ].comparer( );
    }

    FIRES_API
    Averager* averager( const std::string& label )
    {
      return _propertiesConfig[ label ].averager( );
    }

    FIRES_API
    Normalizer* normalizer( const std::string& label )
    {
      return _propertiesConfig[ label ].normalizer( );
    }


    FIRES_API
    TDistanceToQuerySet& distanceToQueryType( void )
    {
      return _distanceToQueryType;
    }

    FIRES_API
    std::map< std::string, QueryPropertyData >& properties( void )
    {
      return _propertiesConfig;
    }

    FIRES_API
    Objects& queryObjects( void )
    {
      return _queryObjects;
    }

    FIRES_API
    std::string& resultsPropertyLabel( void )
    {
      return _resultsPropertyLabel;
    }

    FIRES_API
    void clearQueryObjects( void )
    {
      return _queryObjects.clear( );
    }

    FIRES_API
    void clearProperties( void )
    {
      return _propertiesConfig.clear( );
    }

    FIRES_API
    void clear( void )
    {
      clearQueryObjects( );
      clearProperties( );
    }

  protected:
    //! Configuration for each property
    std::map< std::string, QueryPropertyData > _propertiesConfig;

    //! Query objects
    Objects _queryObjects;

    // Type of distance to the query set
    TDistanceToQuerySet _distanceToQueryType;

    std::string _resultsPropertyLabel;

  }; // class SearchConfig

} // namespace fires

#endif
