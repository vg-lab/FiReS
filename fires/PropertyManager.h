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
          _sorters.insert( sorterIt, std::make_pair(typeIdx,sorter ));
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
          _aggregators.insert( aggregatorIt,
            std::make_pair(typeIdx,aggregator ));
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
          _casters.insert( casterIt, std::make_pair( typeIdx, caster ) );
        }
        else
        {
          caster = dynamic_cast< ScalarPropertyCaster< T >* >(
            casterIt->second );
        }

        // Type Name
        std::string typeName = typeIdx.name( );
        const auto iteratorSerialize = _serializeMap.find( typeName );
        if ( iteratorSerialize == _serializeMap.end( ))
        {
          _serializeMap.insert( iteratorSerialize,
                                std::pair < std::string, std::type_index >(
                                  typeName, typeIdx ));
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
          _sorters.insert( sorterIt,std::make_pair( typeIdx, sorter ));
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
          _casters.insert( casterIt, std::make_pair( typeIdx, caster ));
        }
        else
        {
          caster = dynamic_cast< StringPropertyCaster< T >* >(
            casterIt->second );
        }

        // Type Name
        std::string typeName = typeIdx.name( );
        const auto iteratorSerialize = _serializeMap.find( typeName );
        if ( iteratorSerialize == _serializeMap.end( ))
        {
          _serializeMap.insert( iteratorSerialize,
                                std::pair < std::string, std::type_index >(
                                  typeName, typeIdx ));
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
          _sorters.insert( sorterIt,std::make_pair( typeIdx, sorter ));
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
          _aggregators.insert( aggregatorIt,
            std::make_pair( typeIdx, aggregator ));
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
          _casters.insert( casterIt, std::make_pair( typeIdx, caster ));
        }
        else
        {
          caster =
            dynamic_cast< EnumPropertyCaster< T >* >( casterIt->second );
        }

        // Type Name
        std::string typeName = typeIdx.name( );
        const auto iteratorSerialize = _serializeMap.find( typeName );
        if ( iteratorSerialize == _serializeMap.end( ))
        {
          _serializeMap.insert( iteratorSerialize,
             std::pair < std::string, std::type_index >( typeName, typeIdx ));
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
      typename std::enable_if< std::is_class< T >::value && ! boost::spirit::traits::is_string< T >::value >::type* = 0 )
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

    static void registerProperty( const std::string& label,
      const std::type_index typeIdx,
      PropertyCaster* caster, PropertyAggregator* aggregator,
      PropertySorter* sorter, Filter*  filter
      )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      if ( _properties.find( propertyGID ) == _properties.end( ))
      {
        // Sorters
        const auto& sorterIt = _sorters.find( typeIdx );
        if ( sorterIt == _sorters.end( ))
        {
          _sorters.insert( sorterIt, std::make_pair( typeIdx,sorter ));
        }

        // Aggregators
        const auto& aggregatorIt = _aggregators.find( typeIdx );
        if ( aggregatorIt == _aggregators.end( ))
        {
          _aggregators.insert( aggregatorIt,std::make_pair( typeIdx,aggregator ));
        }

        // Casters
        const auto casterIt = _casters.find( typeIdx );
        if ( casterIt == _casters.end( ))
        {
          _casters.insert( casterIt,std::make_pair( typeIdx,caster ));
        }

        _properties[ propertyGID ] = {
          sorter,
          aggregator,
          filter,
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
        _sorters.insert( sorterIt, std::make_pair( typeIdx,sorter ));
      }
      else
      {
        sorterIt->second = sorter;
      }

      // Aggregators
      const auto& aggregatorIt = _aggregators.find( typeIdx );
      if ( aggregatorIt == _aggregators.end( ))
      {
        _aggregators.insert( aggregatorIt,std::make_pair( typeIdx,aggregator ));
      }
      else
      {
        aggregatorIt->second = aggregator;
      }

      // Casters
      const auto casterIt = _casters.find( typeIdx );
      if ( casterIt == _casters.end( ))
      {
        _casters.insert( casterIt,std::make_pair( typeIdx,caster ));
      }
      else
      {
        casterIt->second = caster;
      }

      // Type Name
      std::string typeName = typeIdx.name( );
      const auto typeNameIt = _serializeMap.find( typeName );
      if ( casterIt == _casters.end( ))
      {
        _serializeMap.insert( typeNameIt,std::make_pair( typeName, typeIdx ));
      }

    }

    static void addBasicTypes( ){

      addType( typeid( int ),new ScalarPropertyCaster< int >( ),
        new ScalarPropertyAggregator< int >( ),
        new ScalarPropertySorter< int >( ));
      addType( typeid( unsigned int),new ScalarPropertyCaster<unsigned  int>( ),
        new ScalarPropertyAggregator<unsigned  int>( ),
        new ScalarPropertySorter<unsigned  int>( ));

      addType( typeid( char ),new ScalarPropertyCaster< char >( ),
        new ScalarPropertyAggregator< char >( ),
        new ScalarPropertySorter< char >( ));
      addType( typeid( signed char ),
        new ScalarPropertyCaster< signed char >( ),
        new ScalarPropertyAggregator< signed char >( ),
        new ScalarPropertySorter< signed char >( ));
      addType( typeid( unsigned char ),new ScalarPropertyCaster< unsigned char >( ),
        new ScalarPropertyAggregator< unsigned char >( ),
        new ScalarPropertySorter< unsigned char >( ));

      addType( typeid( short ),new ScalarPropertyCaster< short >( ),
        new ScalarPropertyAggregator< short >( ),
        new ScalarPropertySorter< short >( ));
      addType( typeid( unsigned short),new ScalarPropertyCaster<unsigned  short>( ),
        new ScalarPropertyAggregator<unsigned  short>( ),
        new ScalarPropertySorter<unsigned  short>( ));

      addType( typeid( long ),new ScalarPropertyCaster< long >( ),
        new ScalarPropertyAggregator< long >( ),
        new ScalarPropertySorter< long >( ));
      addType( typeid( unsigned long),new ScalarPropertyCaster<unsigned  long>( ),
        new ScalarPropertyAggregator<unsigned long>( ),
        new ScalarPropertySorter<unsigned  long>( ));
      addType( typeid( long long ),new ScalarPropertyCaster< long long >( ),
        new ScalarPropertyAggregator< long long >( ),
        new ScalarPropertySorter< long long >( ));
      addType( typeid( unsigned long long),new ScalarPropertyCaster<unsigned long long>( ),
        new ScalarPropertyAggregator<unsigned long long>( ),
        new ScalarPropertySorter<unsigned long long>( ));

      addType( typeid( float ),new ScalarPropertyCaster< float >( ),
        new ScalarPropertyAggregator< float >( ),
        new ScalarPropertySorter< float >( ));

      addType( typeid( double ),new ScalarPropertyCaster< double >( ),
        new ScalarPropertyAggregator< double >( ),
        new ScalarPropertySorter< double >( ));
      addType( typeid( long double ),new ScalarPropertyCaster< long double >( ),
        new ScalarPropertyAggregator< long double >( ),
        new ScalarPropertySorter< long double >( ));

      addType( typeid( bool ),new ScalarPropertyCaster< bool >( ),
        new ScalarPropertyAggregator< bool >( ),
        new ScalarPropertySorter< bool >( ));

      addType( typeid( std::string ),new StringPropertyCaster< std::string >( ),
        nullptr,
        new ScalarPropertySorter< std::string >( ));

    }

    static void DEBUGShowMap(){
      for(auto a : _serializeMap){
        Property p;
        //a.second.caster->fromString(p,"0");
        //std::cout << a.first <<": " << a.second.caster->toString(p) << std::endl;
        std::cout << a.first << std::endl;
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
        return nullptr;

      return _properties[ propertyGID ].caster;
    }

    static PropertyCaster* getPropertyCaster( const std::string& label )
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( label );
      return getPropertyCaster( propertyGID );
    }

    static void setPropertyTypeCaster( std::type_index typeIndex,
      PropertyCaster* caster )
    {
      auto iteratorCaster = _casters.find( typeIndex );
      if ( iteratorCaster == _casters.end( )){
        _casters.insert(iteratorCaster, std::pair
        < std::type_index,PropertyCaster* > ( typeIndex, caster ));
      }
      else{
        iteratorCaster->second = caster;
      }

      // Type Name
      std::string typeName = typeIndex.name( );
      const auto iteratorSerialize = _serializeMap.find( typeName );
      if ( iteratorSerialize == _serializeMap.end( ))
      {
        _serializeMap.insert( iteratorSerialize,
          std::make_pair( typeName, typeIndex ));
      }
    }

    static void setPropertyTypeAgregator( std::type_index typeIndex,
       PropertyAggregator* agregator )
    {
      auto iteratorAgregator = _aggregators.find( typeIndex );
      if ( iteratorAgregator == _aggregators.end( )){
        _aggregators.insert(iteratorAgregator,
          std::make_pair( typeIndex, agregator ));
      }
      else{
        iteratorAgregator->second = agregator;
      }

      // Type Name
      std::string typeName = typeIndex.name( );
      const auto iteratorSerialize = _serializeMap.find( typeName );
      if ( iteratorSerialize == _serializeMap.end( ))
      {
        _serializeMap.insert( iteratorSerialize,
          std::make_pair( typeName, typeIndex ));
      }
    }

    static void setPropertyTypeSorter( std::type_index typeIndex,
      PropertySorter* sorter )
    {
      auto iteratorSorter = _sorters.find( typeIndex );
      if ( iteratorSorter == _sorters.end( )){
        _sorters.insert(iteratorSorter,
         std::make_pair( typeIndex, sorter ));
      }
      else{
        iteratorSorter->second = sorter;
      }

      // Type Name
      std::string typeName = typeIndex.name( );
      const auto iteratorSerialize = _serializeMap.find( typeName );
      if ( iteratorSerialize == _serializeMap.end( ))
      {
        _serializeMap.insert( iteratorSerialize,
          std::pair < std::string, std::type_index >(
          typeName, typeIndex ));
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

    static PropertyAggregator* getTypeAggregator(std::type_index typeIndex)
    {
      auto iterator = _aggregators.find( typeIndex );
      if ( iterator == _aggregators.end( )){
        return nullptr;
      }
      else{
        return iterator->second;
      }
    }

    static PropertySorter* getTypeSorter(std::type_index typeIndex)
    {
      auto iterator = _sorters.find( typeIndex );
      if ( iterator == _sorters.end( )){
        return nullptr;
      }
      else{
        return iterator->second;
      }
    }

    static PropertyCaster* getTypeCaster(std::type_index typeIndex)
    {
      auto iterator = _casters.find( typeIndex );
      if ( iterator == _casters.end( )){
        return nullptr;
      }
      else{
        return iterator->second;
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
      _serializeMap.clear( );
    }

    static std::type_index* getSerializeIndex( std::string typeName ){
      const auto iteratorSerialize = _serializeMap.find( typeName );
      FIRES_CHECK_THROW(iteratorSerialize != _serializeMap.end( ),
       "Type: "+typeName+" not register.")
      return &iteratorSerialize->second;
    }

  protected:

    FIRES_API static std::map< PropertyGID, TPropertyInfo > _properties;
    FIRES_API static std::map< std::type_index, PropertySorter* > _sorters;
    FIRES_API
    static std::map< std::type_index, PropertyAggregator* > _aggregators;
    FIRES_API static std::map< std::type_index, PropertyCaster* > _casters;
    FIRES_API static std::map< std::string, std::type_index > _serializeMap;

  };

}

#endif
