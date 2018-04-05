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
#include "PropertyGIDsManager.h"
#include "Tasks/Sort.h"
#include "Tasks/Filter.h"
#include "Property/PropertyCaster.h"
#include "Property/Aggregator.h"
#include <typeindex>
#include <map>
#include <type_traits>
#include <boost/spirit/home/support/string_traits.hpp>


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
    static void registerProperty(
      fires::Object* obj,
      const std::string& label,
      T value,
      typename std::enable_if< std::is_arithmetic< T >::value >::type* = 0 )
    {
      obj->registerProperty( label, fires::Property( ( T ) value ));
      registerProperty( label, value );
    }

    //! Specialization for scalars
    template < typename T >
    static void registerProperty(
      const std::string& label,
      T /* value */,
      typename std::enable_if< std::is_arithmetic< T >::value >::type* = 0 )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      if ( _properties.find( propertyGID ) == _properties.end( ))
      {
        fires::ScalarPropertySorter< T >* sorter = nullptr;
        fires::ScalarPropertyAggregator< T >* aggregator = nullptr;
        fires::ScalarPropertyCaster< T >* caster = nullptr;

        const auto typeIdx = std::type_index( typeid( T ));

        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt == _sorters.end( ))
        {
          sorter = new fires::ScalarPropertySorter< T >;
          _sorters[ typeIdx ] = sorter;
        }
        else
        {
          sorter =
            dynamic_cast< fires::ScalarPropertySorter< T >* >(
              sorterIt->second );
        }

        // Aggregators
        const auto& aggregatorIt = _aggregators.find( typeIdx );
        if ( aggregatorIt == _aggregators.end( ))
        {
          aggregator = new fires::ScalarPropertyAggregator< T >;
          _aggregators[ typeIdx ] = aggregator;
        }
        else
        {
          aggregator =
            dynamic_cast< fires::ScalarPropertyAggregator< T >* >(
              aggregatorIt->second );
        }

        // Casters
        const auto& casterIt = _casters.find( typeIdx );
        if ( casterIt == _casters.end( ))
        {
          caster = new fires::ScalarPropertyCaster< T >;
          _casters[ typeIdx  ] = caster;
        }
        else
        {
          caster =
            dynamic_cast< fires::ScalarPropertyCaster< T >* >(
              casterIt->second );
        }


        _properties[ propertyGID ] = {
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



    template < typename T >
    static void registerProperty(
        fires::Object* obj,
        const std::string& label,
        T value,
        typename std::enable_if< boost::spirit::traits::is_string< T >::value >::type* = 0)
    {
      obj->registerProperty( label, value );
      registerProperty( label, value );
    }

    //! Specialization for strings
    template < typename T >
    static void registerProperty(
        const std::string& label,
        T /* value */,
        typename std::enable_if< boost::spirit::traits::is_string< T >::value >::type* = 0 )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      if ( _properties.find( propertyGID ) == _properties.end( ))
      {
        fires::StringPropertySorter< T >* sorter = nullptr;
        fires::StringPropertyCaster< T >* caster = nullptr;

        const auto typeIdx = std::type_index( typeid( T ));

        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt == _sorters.end( ))
        {
          sorter = new fires::StringPropertySorter< T >;
          _sorters[ typeIdx ] = sorter;
        }
        else
        {
          sorter = dynamic_cast< fires::StringPropertySorter< T >* >(
            sorterIt->second );
        }

        // Casters
        const auto& casterIt = _casters.find( typeIdx );
        if ( casterIt == _casters.end( ))
        {
          caster  = new fires::StringPropertyCaster< T >;
          _casters[ typeIdx  ] = caster;
        }
        else
        {
          caster = dynamic_cast< fires::StringPropertyCaster< T >* >(
            casterIt->second );
        }

        _properties[ propertyGID ] = {
            sorter,
            nullptr,
            new fires::FilterScalarRange< T >(
                T( ), T( ),
                fires::FilterRange::CLOSED_ENDPOINT,
                fires::FilterRange::CLOSED_ENDPOINT ),
            caster,
        };

      }
    }


    template < typename T >
    static void registerProperty(
      fires::Object* obj,
      const std::string& label,
      T value,
      const std::map< T, std::string >& enumToString =
      std::map< T, std::string >( ),
      typename std::enable_if< std::is_enum< T >::value >::type* = 0 )
    {
      obj->registerProperty( label, fires::Property( ( T ) value ));
      registerProperty( label, value, enumToString );
    }

    //! Specialization for scalars
    template < typename T >
    static void registerProperty(
      const std::string& label,
      T /* value */,
      const std::map< T, std::string >& enumToString =
      std::map< T, std::string >( ),
      typename std::enable_if< std::is_enum< T >::value >::type* = 0 )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      if ( _properties.find( propertyGID ) == _properties.end( ))
      {
        fires::ScalarPropertySorter< T >* sorter = nullptr;
        fires::ScalarPropertyAggregator< T >* aggregator = nullptr;
        fires::EnumPropertyCaster< T >* caster = nullptr;

        const auto typeIdx = std::type_index( typeid( T ));

        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt == _sorters.end( ))
        {
          sorter = new fires::ScalarPropertySorter< T >;
          _sorters[ typeIdx ] = sorter;
        }
        else
        {
          sorter =
            dynamic_cast< fires::ScalarPropertySorter< T >* >(
              sorterIt->second );
        }

        // Aggregators
        const auto& aggregatorIt = _aggregators.find( typeIdx );
        if ( aggregatorIt == _aggregators.end( ))
        {
          aggregator = new fires::ScalarPropertyAggregator< T >;
          _aggregators[ typeIdx ] = aggregator;
        }
        else
        {
          aggregator =
            dynamic_cast< fires::ScalarPropertyAggregator< T >* >(
              aggregatorIt->second );
        }

        // Casters
        const auto casterIt = _casters.find( typeIdx );
        if ( casterIt == _casters.end( ))
        {
          caster = new fires::EnumPropertyCaster< T >( enumToString );
          _casters[ typeIdx ] = caster;
        }
        else
        {
          caster =
            dynamic_cast< fires::EnumPropertyCaster< T >* >( casterIt->second );
        }

        _properties[ propertyGID ] = {
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

    template < typename T >
    static
    void registerProperty(
        fires::Object* obj,
        const std::string& label,
        T value,
        typename std::enable_if< std::is_class< T >::value && ! boost::spirit::traits::is_string< T >::value >::type* = 0 )
    {
      obj->registerProperty( label, value );
    }


    static fires::PropertySorter* getSorter( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
        return nullptr;

      return _properties[ propertyGID ].sorter;
    }

    static fires::PropertySorter* getSorter( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getSorter( propertyGID );
    }

    static fires::Filter* getFilter( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
        return nullptr;

      return _properties[ propertyGID ].filter;
    }

    static fires::Filter* getFilter( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getFilter( propertyGID );
    }

    static fires::PropertyAggregator* getAggregator( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
        return nullptr;

      return _properties[ propertyGID ].aggregator;
    }

    static fires::PropertyAggregator* getAggregator( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getAggregator( propertyGID );
    }

    static fires::PropertyCaster* getPropertyCaster( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
        return nullptr;

      return _properties[ propertyGID ].caster;
    }

    static fires::PropertyCaster* getPropertyCaster( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getPropertyCaster( propertyGID );
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

    FIRES_API static std::map< PropertyGID, TPropertyInfo > _properties;
    FIRES_API static std::map< std::type_index, PropertySorter* > _sorters;
    FIRES_API
    static std::map< std::type_index, PropertyAggregator* > _aggregators;
    FIRES_API static std::map< std::type_index, PropertyCaster* > _casters;


  };

}

#endif
