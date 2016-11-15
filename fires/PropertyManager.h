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
#ifndef __FIRES_PROPERTY_MANAGER__
#define __FIRES_PROPERTY_MANAGER__

#include <fires/api.h>
#include "Tasks/Sort.h"
#include "Tasks/Filter.h"
#include "Property/PropertyCaster.h"
#include "Property/Aggregator.h"
#include <typeindex>
#include <map>
#include <type_traits>

namespace fires
{
  class PropertyManager
  {

  public:

    typedef struct
    {
      fires::PropertySorter* sorter;
      fires::PropertyAggregator* aggregator;
      fires::Filter* filter;
      fires::PropertyCaster* caster;
    } TPropertyInfo;

    template < typename T >
    static
    void registerProperty(
      fires::Object* obj,
      const std::string& label,
      T value,
      typename std::enable_if< std::is_class< T >::value >::type* = 0 )
    {
      obj->registerProperty( label, value );
    }

    template < typename T >
    static void registerProperty(
      fires::Object* obj,
      const std::string& label,
      T value,
      typename std::enable_if< std::is_scalar< T >::value >::type* = 0 )
    {
      obj->registerProperty( label, fires::Property( ( T ) value ));
      registerProperty( label, value );
    }

    //! Specialization for scalars
    template < typename T >
    static void registerProperty(
      const std::string& label,
      T /* value */,
      typename std::enable_if< std::is_scalar< T >::value >::type* = 0 )
    {
      if ( _properties.find( label ) == _properties.end( ))
      {
        fires::ScalarPropertySorter< T >* sorter = nullptr;
        fires::ScalarPropertyAggregator< T >* aggregator = nullptr;
        fires::ScalarPropertyCaster< T >* caster = nullptr;

        // Sorters
        if ( _sorters.find( std::type_index( typeid( T ))) == _sorters.end( ))
        {
          sorter = new fires::ScalarPropertySorter< T >;
          _sorters[ std::type_index( typeid( T )) ] = sorter;
        }
        else
        {
          sorter =
            dynamic_cast< fires::ScalarPropertySorter< T >* >(
              _sorters.find( std::type_index( typeid( T )))->second );
        }

        // Aggregatorrs
        if ( _aggregators.find( std::type_index( typeid( T ))) ==
             _aggregators.end( ))
        {
          aggregator = new fires::ScalarPropertyAggregator< T >;
          _aggregators[ std::type_index( typeid( T )) ] = aggregator;
        }
        else
        {
          aggregator =
            dynamic_cast< fires::ScalarPropertyAggregator< T >* >(
              _aggregators.find( std::type_index( typeid( T )))->second );
        }

        // Casters
        if ( _casters.find( std::type_index( typeid( T ))) ==
             _casters.end( ))
        {
          caster = new fires::ScalarPropertyCaster< T >;
          _casters[ std::type_index( typeid( T )) ] = caster;
        }
        else
        {
          caster =
            dynamic_cast< fires::ScalarPropertyCaster< T >* >(
              _casters.find( std::type_index( typeid( T )))->second );
        }


        _properties[ label ] = {
          sorter,
          aggregator,
          new fires::FilterScalarRange< T >(
            T( ), T( ),
            fires::FilterRange::CLOSED_ENDPOINT,
            fires::FilterRange::CLOSED_ENDPOINT ),
          caster,
        };

      }
    }

    static fires::PropertySorter* getSorter( const std::string& label )
    {
      if ( _properties.find( label ) == _properties.end( ))
        return nullptr;

      return _properties[ label ].sorter;
    }

    static fires::Filter* getFilter( const std::string& label )
    {
      if ( _properties.find( label ) == _properties.end( ))
        return nullptr;

      return _properties[ label ].filter;
    }

    static fires::PropertyAggregator* getAggregator( const std::string& label )
    {
      if ( _properties.find( label ) == _properties.end( ))
        return nullptr;

      return _properties[ label ].aggregator;
    }

    static fires::PropertyCaster* getPropertyCaster( const std::string& label )
    {
      if ( _properties.find( label ) == _properties.end( ))
        return nullptr;

      return _properties[ label ].caster;
    }

    static void setFilterRange( fires::Filter* filter,
                                int minValue, int maxValue )
    {
      if ( dynamic_cast< fires::FilterScalarRange< float >* >( filter ))
      {
        auto fsrf =
          dynamic_cast< fires::FilterScalarRange< float >* >( filter );
        fsrf->min( ) = ( float ) minValue;
        fsrf->max( ) = ( float ) maxValue;
      }
      else if ( dynamic_cast< fires::FilterScalarRange< int >* >( filter ))
      {
        auto fsri =
          dynamic_cast< fires::FilterScalarRange< int >* >( filter );
        fsri->min( ) = ( int ) minValue;
        fsri->max( ) = ( int ) maxValue;
      }
      else if ( dynamic_cast< fires::FilterScalarRange< unsigned int >* >(
                  filter ))
      {
        auto fsrui =
          dynamic_cast< fires::FilterScalarRange< unsigned int >* >( filter );
        fsrui->min( ) = ( unsigned int ) minValue;
        fsrui->max( ) = ( unsigned int ) maxValue;
      }
    }

    static void clear( void )
    {
      for ( auto f :  _properties )
      {
        if ( f.second.filter )
          delete f.second.filter;
      }

      for ( auto f :  _sorters )
      {
        if ( f.second )
          delete f.second;
      }

      for ( auto f :  _aggregators )
      {
        if ( f.second )
          delete f.second;
      }

      for ( auto f :  _casters )
      {
        if ( f.second )
          delete f.second;
      }

      _properties.clear( );
      _sorters.clear( );
      _aggregators.clear( );
      _casters.clear( );
    }

  protected:

    FIRES_API static std::map< std::string, TPropertyInfo > _properties;
    FIRES_API static std::map< std::type_index, PropertySorter* > _sorters;
    FIRES_API
    static std::map< std::type_index, PropertyAggregator* > _aggregators;
    FIRES_API static std::map< std::type_index, PropertyCaster* > _casters;


  };

}

#endif
