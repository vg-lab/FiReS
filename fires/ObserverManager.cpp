/*
 * Copyright (c) 2014-2016 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/vg-lab/FiReS>
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
#include "ObserverManager.h"

#include <algorithm>

namespace fires
{
  ObserverManager::ObserverCallbacksMap ObserverManager::_callbacksMap =
    ObserverManager::ObserverCallbacksMap( );

  void ObserverManager::trigger( Object* notifier,
                                 const std::string& propLabel )
  {
    auto propertyGID = PropertyGIDsManager::getPropertyGID( propLabel );

    // If notifier not registered or registerd but not with propLabel, return
    auto it =  _callbacksMap.find( notifier );
    if ( it == _callbacksMap.end( ) ||
         it->second.find( propertyGID ) == it->second.end( ))
      return;

    for ( const auto& cb : _callbacksMap.at( notifier ).at( propertyGID ))
      cb.second( notifier, propLabel );
  }

  class IsObserver
  {
    void* _observer;

  public:
    IsObserver( void* observer_ )
      : _observer( observer_ )
    {}
    bool operator( )( const std::pair< void*,
                      ObserverManager::ObserverCallback >& obs ) const
    {
      return obs.first == _observer;
    }
  };

  void ObserverManager::removeObserver( void* observer )
  {
    for ( auto& notifier : _callbacksMap )
      for ( auto& observation : notifier.second )
      observation.second.erase(
        std::remove_if( observation.second.begin( ),
                        observation.second.end( ),
                        IsObserver( observer )),
        observation.second.end( ));
  }

  void ObserverManager::removeNotifier( Object* notifier )
  {
    for( auto iter = _callbacksMap.begin( ) ; iter != _callbacksMap.end( ); )
    {
      if ( iter->first == notifier )
        _callbacksMap.erase( iter++ );
      else
        ++iter;
    }
  }

}
