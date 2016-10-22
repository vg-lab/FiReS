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
#ifndef __FIRES_FILTER_H__
#define __FIRES_FILTER_H__

#include "Task.h"

namespace fires
{

  class Objects;
  
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
  class FilterValue:
    public Filter
  {
  public:
    FilterValue( const T value_ )
      : _value( value_ )
    {
    }

    virtual bool eval( const Property& property ) const
    {
      return ( property.value< T >( ) == _value );
    }

    protected:
      T _value;
  };

  template < typename T >
  class FilterMinValue:
    public FilterRange
  {
  public:
    FilterMinValue( const T min_,
                    const TRangeEndpoint minEndpoint__ = OPENED_ENDPOINT )
      : _min( min_ ),
        _minEndpoint( minEndpoint__ )
    {
    }

    virtual bool eval( const Property& property ) const
    {
      T fv = property.value< T >( );
      bool v =
        (( _minEndpoint == OPENED_ENDPOINT ) ?
         ( fv > _min ) : ( fv >= _min ));
      return v;
    }

    protected:
      T _min;
      TRangeEndpoint _minEndpoint;
  };

  template < typename T >
  class FilterMaxValue:
    public FilterRange
  {
  public:
    FilterMaxValue( const T max_,
                    const TRangeEndpoint maxEndpoint__ = OPENED_ENDPOINT )
      : _max( max_ ),
        _maxEndpoint( maxEndpoint__ )
    {
    }

    virtual bool eval( const Property& property ) const
    {
      T fv = property.value< T >( );
      bool v =
        (( _maxEndpoint == OPENED_ENDPOINT ) ?
         ( fv < _max ) : ( fv <= _max ));
      return v;
    }

    protected:
      T _max;
      TRangeEndpoint _maxEndpoint;
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

   typedef std::pair< std::string, Filter* > TFilterPair;
   typedef std::vector< TFilterPair > TFilterPairs;

   FilterSetConfig( //bool removeFiltered_ = true,
     const std::string &filterPropertyLabel_ = std::string( "" ));
   // : _removeFiltered( removeFiltered_ )

   void clear( void )
   {
     _filters.clear( );
   }
   class ObjectFulfilsFilter
   {
    protected:
      TFilterPairs _filters;
      const std::string _filterPropertyLabel;

    public:
      ObjectFulfilsFilter( TFilterPairs filters_,
                           const std::string& filterPropertyLabel_ = "" );
      bool operator( )( Object* obj ) const;
    };

   TFilterPairs& filters( void );
   std::string& filterPropertyLabel( void );

  protected:

    bool _removeFiltered;
    std::string _filterPropertyLabel;
    TFilterPairs _filters;


  };

  class FilterSet : public Task
  {
  public:
    virtual Objects& eval( Objects &objs, TaskConfig &config );

  }; // class FilterSet


} // namespace flter


#endif
