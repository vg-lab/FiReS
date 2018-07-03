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
      PropertySorter* sorter;
      PropertyAggregator* aggregator;
      Filter* filter;
      PropertyCaster* caster;
    } TPropertyInfo;

    template < typename T >
    static void registerProperty(
      fires::Object* obj,
      const std::string& label,
      T value,
      typename std::enable_if< std::is_arithmetic< T >::value >::type* = 0 )
    {
      obj->registerProperty( label, Property( ( T ) value ));
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
        ScalarPropertySorter< T >* sorter = nullptr;
        ScalarPropertyAggregator< T >* aggregator = nullptr;
        ScalarPropertyCaster< T >* caster = nullptr;

        const auto typeIdx = std::type_index( typeid( T ));

        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt == _sorters.end( ))
        {
          sorter = new ScalarPropertySorter< T >;
          _sorters.insert( std::make_pair( typeIdx, sorter ));
        }
        else
        {
          sorter =
            dynamic_cast< ScalarPropertySorter< T >* >(
              sorterIt->second );
        }

        // Aggregators
        const auto& aggregatorIt = _aggregators.find( typeIdx );
        if ( aggregatorIt == _aggregators.end( ))
        {
          aggregator = new ScalarPropertyAggregator< T >;
          _aggregators.insert( std::make_pair( typeIdx, aggregator ));
        }
        else
        {
          aggregator =
            dynamic_cast< ScalarPropertyAggregator< T >* >(
              aggregatorIt->second );
        }

        // Casters
        const auto& casterIt = _casters.find( typeIdx );
        if ( casterIt == _casters.end( ))
        {
          caster = new ScalarPropertyCaster< T >;
          _casters.insert( std::make_pair( typeIdx, caster ));
        }
        else
        {
          caster = dynamic_cast< ScalarPropertyCaster< T >* >(
            casterIt->second );
        }

        _properties[ propertyGID ] = {
          sorter,
          aggregator,
          new FilterScalarRange< T >(
            T( ), T( ),
            FilterRange::CLOSED_ENDPOINT,
            FilterRange::CLOSED_ENDPOINT ),
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
        StringPropertySorter< T >* sorter = nullptr;
        StringPropertyCaster< T >* caster = nullptr;

        const auto typeIdx = std::type_index( typeid( T ));

        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt == _sorters.end( ))
        {
          sorter = new StringPropertySorter< T >;
          _sorters.insert( std::make_pair( typeIdx, sorter ));
        }
        else
        {
          sorter = dynamic_cast< StringPropertySorter< T >* >(
            sorterIt->second );
        }

        // Casters
        const auto& casterIt = _casters.find( typeIdx );
        if ( casterIt == _casters.end( ))
        {
          caster = new StringPropertyCaster< T >;
          _casters.insert( std::make_pair( typeIdx, caster ));
        }
        else
        {
          caster = dynamic_cast< StringPropertyCaster< T >* >(
            casterIt->second );
        }

        _properties[ propertyGID ] = {
            sorter,
            nullptr,
            nullptr,
            caster,
        };

      }
    }

    template < typename T >
    static void registerProperty(
      Object* obj,
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
        ScalarPropertySorter< T >* sorter = nullptr;
        ScalarPropertyAggregator< T >* aggregator = nullptr;
        EnumPropertyCaster< T >* caster = nullptr;

        const auto typeIdx = std::type_index( typeid( T ));

        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt == _sorters.end( ))
        {
          sorter = new ScalarPropertySorter< T >;
          _sorters.insert( std::make_pair( typeIdx, sorter ));
        }
        else
        {
          sorter =
            dynamic_cast< ScalarPropertySorter< T >* >(
              sorterIt->second );
        }

        // Aggregators
        const auto& aggregatorIt = _aggregators.find( typeIdx );
        if ( aggregatorIt == _aggregators.end( ))
        {
          aggregator = new ScalarPropertyAggregator< T >;
          _aggregators.insert( std::make_pair( typeIdx, aggregator ));
        }
        else
        {
          aggregator =
            dynamic_cast< ScalarPropertyAggregator< T >* >(
              aggregatorIt->second );
        }

        // Casters
        const auto casterIt = _casters.find( typeIdx );
        if ( casterIt == _casters.end( ))
        {
          caster = new EnumPropertyCaster< T >( enumToString );
          _casters.insert( std::make_pair( typeIdx, caster ));
        }
        else
        {
          caster =
            dynamic_cast< EnumPropertyCaster< T >* >( casterIt->second );
        }

        _properties[ propertyGID ] = {
          sorter,
          aggregator,
          new FilterScalarRange< T >(
            T( ), T( ),
            FilterRange::CLOSED_ENDPOINT,
            FilterRange::CLOSED_ENDPOINT ),
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
      registerProperty( label, value );
    }

    template < typename T >
    static void registerProperty(
      const std::string& label,
      T /* value */,
      typename std::enable_if< std::is_class< T >::value &&
        ! boost::spirit::traits::is_string< T >::value >::type* = 0 )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      if ( _properties.find( propertyGID ) == _properties.end( ))
      {
        PropertySorter* sorter = nullptr;
        PropertyAggregator* aggregator = nullptr;
        PropertyCaster* caster = nullptr;

        const auto typeIdx = std::type_index( typeid( T ));

        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt != _sorters.end( ))
        {
          sorter = sorterIt->second ;
        }

        // Aggregators
        const auto& aggregatorIt = _aggregators.find( typeIdx );
        if ( aggregatorIt != _aggregators.end( ))
        {
          aggregator = aggregatorIt->second;
        }

        // Casters
        const auto casterIt = _casters.find( typeIdx );
        if ( casterIt != _casters.end( ))
        {
          caster = casterIt->second;
        }

        _properties[ propertyGID ] = {
          sorter,
          aggregator,
          nullptr,
          caster,
        };

      }
    }

    static void addType(const std::type_index typeIdx,
       PropertyCaster* caster, PropertyAggregator* aggregator,
       PropertySorter* sorter )
    {
      // Sorters
      const auto& sorterIt = _sorters.find( typeIdx );
      if ( sorterIt == _sorters.end( ))
      {
        _sorters.insert( std::make_pair( typeIdx,sorter ));
      }
      else
      {
        sorterIt->second = sorter;
      }

      // Aggregators
      const auto& aggregatorIt = _aggregators.find( typeIdx );
      if ( aggregatorIt == _aggregators.end( ))
      {
        _aggregators.insert( std::make_pair( typeIdx,aggregator ));
      }
      else
      {
        aggregatorIt->second = aggregator;
      }

      // Casters
      const auto casterIt = _casters.find( typeIdx );
      if ( casterIt == _casters.end( ))
      {
        _casters.insert( std::make_pair( typeIdx,caster ));
      }
      else
      {
        casterIt->second = caster;
      }

    }

    static PropertySorter* getSorter( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
        return nullptr;

      return _properties[ propertyGID ].sorter;
    }

    static PropertySorter* getSorter( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getSorter( propertyGID );
    }

    static Filter* getFilter( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
        return nullptr;

      return _properties[ propertyGID ].filter;
    }

    static Filter* getFilter( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getFilter( propertyGID );
    }

    static PropertyAggregator* getAggregator( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
        return nullptr;

      return _properties[ propertyGID ].aggregator;
    }

    static PropertyAggregator* getAggregator( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getAggregator( propertyGID );
    }

    static PropertyCaster* getPropertyCaster( PropertyGID propertyGID )
    {
      if ( _properties.find( propertyGID ) == _properties.end( ))
      {
        return nullptr;
      }

      return _properties[ propertyGID ].caster;
    }

    static PropertyCaster* getPropertyCaster( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getPropertyCaster( propertyGID );
    }

    static void setTypePropertyCaster( std::type_index typeIndex,
      PropertyCaster* caster )
    {
      auto iteratorCaster = _casters.find( typeIndex );
      if ( iteratorCaster == _casters.end( )){
        _casters.insert( std::make_pair( typeIndex, caster ));
      }
      else{
        iteratorCaster->second = caster;
      }
    }

    static void setTypeAgregator( std::type_index typeIndex,
       PropertyAggregator* agregator )
    {
      auto iteratorAgregator = _aggregators.find( typeIndex );
      if ( iteratorAgregator == _aggregators.end( ))
      {
        _aggregators.insert( std::make_pair( typeIndex, agregator ));
      }
      else
      {
        iteratorAgregator->second = agregator;
      }
    }

    static void setTypeSorter( std::type_index typeIndex,
      PropertySorter* sorter )
    {
      auto iteratorSorter = _sorters.find( typeIndex );
      if ( iteratorSorter == _sorters.end( ))
      {
        _sorters.insert( std::make_pair( typeIndex, sorter ));
      }
      else
      {
        iteratorSorter->second = sorter;
      }
    }


    static void setFilterRange( Filter* filter,
      int minValue, int maxValue )
    {
      if ( dynamic_cast< FilterScalarRange< float >* >( filter ))
      {
        auto fsrf =
          dynamic_cast< FilterScalarRange< float >* >( filter );
        fsrf->min( ) = ( float ) minValue;
        fsrf->max( ) = ( float ) maxValue;
      }
      else if ( dynamic_cast< FilterScalarRange< int >* >( filter ))
      {
        auto fsri =
          dynamic_cast< FilterScalarRange< int >* >( filter );
        fsri->min( ) = ( int ) minValue;
        fsri->max( ) = ( int ) maxValue;
      }
      else if ( dynamic_cast< FilterScalarRange< unsigned int >* >(
                  filter ))
      {
        auto fsrui =
          dynamic_cast< FilterScalarRange< unsigned int >* >( filter );
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