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

#include "Filter.h"

namespace fires
{

  FilterSetConfig::FilterSetConfig( //bool removeFiltered_ = true,
    const std::string &filterPropertyLabel_ )
    : _filterPropertyLabel( filterPropertyLabel_ )
  {
  }

  FilterSetConfig::ObjectFulfilsFilter::ObjectFulfilsFilter(
    TFilterPairs filters_,
    const std::string& filterPropertyLabel_ )
    : _filters( filters_ )
    , _filterPropertyLabel( filterPropertyLabel_ )
  {
  }

  bool FilterSetConfig::ObjectFulfilsFilter::operator( )( Object* obj ) const
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

    if ( !_filterPropertyLabel.empty( ))
      obj->registerProperty( _filterPropertyLabel, fulfilsFilters );

    return !fulfilsFilters;
  }

  FilterSetConfig::TFilterPairs& FilterSetConfig::filters( void )
  {
    return _filters;
  }

  const FilterSetConfig::TFilterPairs& FilterSetConfig::filters( void ) const
  {
    return _filters;
  }

  std::string& FilterSetConfig::filterPropertyLabel( void )
  {
    return _filterPropertyLabel;
  }


  Objects& FilterSet::eval( Objects &objs, TaskConfig &config )
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


} // namespace filter
