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
#include "DependenciesManager.h"
#include <stack>

namespace fires
{

  DependenciesManager::DependsOn DependenciesManager::_dependsOn =
    DependenciesManager::DependsOn( );
  DependenciesManager::IsDependecyOf DependenciesManager::_isDependencyOf =
    DependenciesManager::IsDependecyOf( );
  DependenciesManager::DirtyProperties DependenciesManager::_dirtyProps =
    DependenciesManager::DirtyProperties( );

  void DependenciesManager::addDependency(
      Object* dependent, const std::string& dependentPropLabel,
      Object* dependency, const std::string& dependencyPropLabel )
  {
    auto dependencyPropertyGID = PropertyGIDsManager::getPropertyGID(
      dependencyPropLabel );
    auto dependentPropertyGID =
      PropertyGIDsManager::getPropertyGID( dependentPropLabel );

    bool exists = ( _dependsOn[ dependent ].count( dependentPropertyGID ) == 1 );
    auto& pair = _dependsOn[ dependent ][ dependentPropertyGID ];
    if ( !exists )
      pair.first = nullptr;
    pair.second.insert( std::make_pair( dependency, dependencyPropertyGID ));

    _isDependencyOf[ dependency ][ dependencyPropertyGID ].insert(
      std::make_pair( dependent, dependentPropertyGID ));

  }

  void DependenciesManager::setDependentsDirty( Object* obj,
                                                const std::string& propLabel )
  {
    auto propertyGID = PropertyGIDsManager::getPropertyGID( propLabel );
    std::stack< std::pair< Object*, PropertyGID >> toProcess;
    toProcess.push( std::make_pair( obj, propertyGID ));

    while ( !toProcess.empty( ))
    {
      auto currentDep = toProcess.top( );
      auto currentObj = currentDep.first;
      auto currentPropertyGID = currentDep.second;
      toProcess.pop( );
      for ( const auto& dependent :
              _isDependencyOf[ currentObj ][ currentPropertyGID ] )
      {
        if ( _dirtyProps.count( dependent.first ) == 0 ||
             _dirtyProps.at( dependent.first ).size( ) == 0 )
        {
          _dirtyProps[ dependent.first ].insert( dependent.second );
          toProcess.push( std::make_pair( dependent.first, dependent.second ));
        }
      }
    }
  }

  bool DependenciesManager::getDirtiness( Object* obj,
                                          const std::string& propLabel )
  {
    auto propertyGID = PropertyGIDsManager::getPropertyGID( propLabel );
    return ( _dirtyProps.count( obj ) != 0 &&
             _dirtyProps.at( obj ).count( propertyGID ) != 0 );

  }


  void DependenciesManager::updateProperty( Object* obj,
                                            const std::string& propLabel )
  {
    // std::cout << std::endl << ".------------_" << std::endl;
    // std::cout << propLabel << std::endl;
    auto propertyGID = PropertyGIDsManager::getPropertyGID( propLabel );
    const auto& objDirtyPropsIt = _dirtyProps.find( obj );
    if ( objDirtyPropsIt == _dirtyProps.end( ))
      return;
    auto dirtyPropIt = objDirtyPropsIt->second.find( propertyGID );
    if ( dirtyPropIt == objDirtyPropsIt->second.end( ))
      return;

    const auto dependencyIt = _dependsOn[ obj ].find( propertyGID );
    if ( dependencyIt != _dependsOn[ obj ].end( ) &&
         dependencyIt->second.first )
      ( dependencyIt->second.first )( obj, propLabel );

    objDirtyPropsIt->second.erase( dirtyPropIt );
    if ( objDirtyPropsIt->second.size( ) == 0 )
      _dirtyProps.erase( objDirtyPropsIt );

  }

  void DependenciesManager::removeObject( Object* obj )
  {
    _dependsOn.erase( obj );
    for ( auto& objPair : _dependsOn )
      for ( auto& propPair : objPair.second )
      {
        ObjectPropertyPairSet& pairSet = propPair.second.second;
        for ( auto pairIter = pairSet.begin( ); pairIter != pairSet.end( ); )
          if ( pairIter->first == obj )
            pairIter = pairSet.erase( pairIter );
          else
            ++pairIter;
      }

    _isDependencyOf.erase( obj );
    for ( auto& objPair : _isDependencyOf )
      for ( auto& propPair : objPair.second )
      {
        ObjectPropertyPairSet& pairSet = propPair.second;
        for ( auto pairIter = pairSet.begin( ); pairIter != pairSet.end( ); )
          if ( pairIter->first == obj )
            pairIter = pairSet.erase( pairIter );
          else
            ++pairIter;
      }
  }
}
