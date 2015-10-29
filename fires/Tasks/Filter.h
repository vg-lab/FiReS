/**
 * @file    Filter.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_FILTER_H__
#define __FIRES_FILTER_H__

#include "Task.h"

namespace fires
{

  class Filter
  {

  public:
    virtual ~Filter( )
    {
    }

    virtual bool eval( const Property& ) const = 0;

  };

  class FilterRange
    : public Filter
  {
  public:
    typedef enum
    {
      INSIDE_RANGE = 0,
      OUTSIDE_RANGE
    } TRangeInclusion;

    typedef enum
    {
      CLOSED_ENDPOINT = 0,
      OPENED_ENDPOINT
    } TRangeEndpoint;

  };

  template < typename T >
  class FilterScalarRange
    : public FilterRange
  {

  public:

    virtual ~FilterScalarRange( void )
    {
    }

    FilterScalarRange( const T min_,
                       const T max_,
                       const TRangeEndpoint minEndpoint_ = OPENED_ENDPOINT,
                       const TRangeEndpoint maxEndpoint_ = OPENED_ENDPOINT,
                       const TRangeInclusion rangeInclusion_ = INSIDE_RANGE )
      : _min( min_ )
      , _max( max_ )
      , _minEndpoint( minEndpoint_ )
      , _maxEndpoint( maxEndpoint_ )
      , _rangeInclusion( rangeInclusion_ )
    {
    }

    T& min( void )
    {
      return _min;
    }

    T& max( void )
    {
      return _max;
    }

    TRangeEndpoint& minEndpoint( void )
    {
      return _minEndpoint;
    }

    TRangeEndpoint& maxEndpoint( void )
    {
      return _maxEndpoint;
    }

    TRangeInclusion& rangeInclusion( void )
    {
      return _rangeInclusion;
    }

    virtual bool eval( const Property& property ) const
    {
      T fv = property.value< T >( );
      bool v =
        (( _minEndpoint == OPENED_ENDPOINT ) ?
         ( fv > _min ) : ( fv >= _min )) &&
        (( _maxEndpoint == OPENED_ENDPOINT ) ?
         ( fv < _max ) : ( fv <= _max ));

      switch ( _rangeInclusion )
      {
      case INSIDE_RANGE:
        return v;
        break;
      case OUTSIDE_RANGE:
        return !v;
        break;
      default:
        throw std::runtime_error(
          std::string( "fires::FilterScalar::eval: " ) +
          std::string( "range inclusion type invalid" ));
         }
    }

  protected:
    T _min;
    T _max;
    TRangeEndpoint _minEndpoint;
    TRangeEndpoint _maxEndpoint;
    TRangeInclusion _rangeInclusion;

  };


 class FilterSetConfig : public TaskConfig
  {
  public:

    typedef std::vector< std::pair< std::string, Filter* >> TFilterPairs;

    FilterSetConfig( //bool removeFiltered_ = true,
      const std::string &filterPropertyLabel_ = std::string( "" ))
      // : _removeFiltered( removeFiltered_ )
      : _filterPropertyLabel( filterPropertyLabel_ )
    {
    }

    class ObjectFulfilsFilter
    {
    protected:
      TFilterPairs _filters;
      const std::string _filterPropertyLabel;

    public:
      ObjectFulfilsFilter( TFilterPairs filters_,
                           const std::string& filterPropertyLabel_ = "" )
        : _filters( filters_ )
        , _filterPropertyLabel( filterPropertyLabel_ )
      {
      }

      bool operator( )( Object* obj ) const
      {
        bool fulfilsFilters = true;
        for ( auto filter  = _filters.begin( );
              filter != _filters.end( ); ++filter )
        {
          auto propertyLabel = ( *filter ).first;
          auto filterObject = ( *filter ).second;
          bool fulfilsFilter =
            filterObject->eval(( obj->getProperty( propertyLabel )));
          if ( !fulfilsFilter )
          {
            fulfilsFilters = false;
            break;
          }
        }

        if ( _filterPropertyLabel != "" )
          obj->registerProperty( _filterPropertyLabel, fulfilsFilters );

        return !fulfilsFilters;
      }
    };

    TFilterPairs& filters( void )
    {
      return _filters;
    }

    // bool& removeFiltered( void )
    // {
    //   return _removeFiltered;
    // }

    std::string& filterPropertyLabel( void )
    {
      return _filterPropertyLabel;
    }

  protected:

    bool _removeFiltered;
    std::string _filterPropertyLabel;
    TFilterPairs _filters;


  };

  class FilterSet : public Task
  {
  public:

    virtual Objects& eval( Objects &objs, TaskConfig &config )
    {

      FilterSetConfig* filterSetConfig =
        static_cast< FilterSetConfig* >( &config );

      auto filters = filterSetConfig->filters( );
      // const bool& removeFiltered = filterSetConfig->removeFiltered( );
      const std::string& filterPropertyLabel =
        filterSetConfig->filterPropertyLabel( );

      // Avoid going through all objects if no filter needed
      if ( filters.size( ) == 0 )
      {
        return objs;
      }

      if ( filterPropertyLabel == "" )
      {

        objs.erase(
          std::remove_if( objs.begin( ), objs.end( ),
                          FilterSetConfig::ObjectFulfilsFilter( filters )) ,
          objs.end( ));
      }
      else
      {
        std::for_each( objs.begin( ), objs.end( ),
                       FilterSetConfig::ObjectFulfilsFilter(
                         filters, filterPropertyLabel ));
      }

      return objs;

    }

  }; // class FilterSet


} // namespace flter


#endif
