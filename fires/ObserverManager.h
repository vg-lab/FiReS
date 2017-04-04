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
#ifndef __FIRES__OBSERVERMANAGER_H__
#define __FIRES__OBSERVERMANAGER_H__

#include <fires/api.h>
#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
#include "Object/Object.h"
#include "PropertyGIDsManager.h"


namespace fires
{

#define FIRES_OBSERVER_CALLBACK( CBNAME, NOTIFIER, LABEL )          \
  void CBNAME( fires::Object* NOTIFIER, const std::string& LABEL )

  class ObserverManager
  {
  public:
    typedef std::function< void ( Object*, const std::string& ) >
    ObserverCallback;
    typedef std::vector< std::pair< void*, ObserverCallback >> ObserverCallbacks;
    typedef std::unordered_map< Object*,
                                std::unordered_map< PropertyGID ,
                                                    ObserverCallbacks >>
    ObserverCallbacksMap;

    template < class OBSERVER >
    static void addObserver(
     Object* notifier, const std::string& propLabel, OBSERVER* observer,
      void ( OBSERVER::*memberFunc )( Object*, const std::string& ))
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( propLabel );

      _callbacksMap[ notifier][ propertyGID ].push_back(
        std::make_pair( observer, std::bind( memberFunc, observer,
                                             notifier, propLabel )));
    }

    FIRES_API
    static void trigger( Object* notifier, const std::string& propLabel );
    FIRES_API
    static void removeObserver( void* observer );
    FIRES_API
    static void removeNotifier( Object* notifier );

  protected:
    FIRES_API
    static ObserverCallbacksMap _callbacksMap;

  };

} // namespace fires
#endif
