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
#ifndef __FIRES__DEPENDENCIES_MANAGER_H__
#define __FIRES__DEPENDENCIES_MANAGER_H__

#include <fires/api.h>
#include <boost/functional/hash.hpp>
#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "Object/Object.h"
#include "PropertyGIDsManager.h"


namespace fires
{

  /**
   * Class for adding dependencies between different object properties. It
   * allows to associate updater functions to update properties and handles
   * dirtiness of properties.
   * Example: @include examples/dependencies.cpp
   *
   */
  class DependenciesManager
  {
  public:

    //! Type for the callback functions for updating properties
    typedef std::function< void ( Object*, const std::string& ) >
    UpdatePropertyCallback;

    //! Type for holding the dependency or dependent pair of object and property
    typedef std::unordered_set<
      std::pair< Object*, PropertyGID >,
      boost::hash< std::pair< Object*, PropertyGID > >> ObjectPropertyPairSet;

    //! Type for holding the links from dependent to dependencies and also the
    //! upater callbacks
    typedef std::unordered_map<
      Object*,
      std::unordered_map< PropertyGID,
                          std::pair< UpdatePropertyCallback,
                                     ObjectPropertyPairSet >>> DependsOn;

    //! Type for holding the links from dependencies to dependents
    typedef std::unordered_map<
      Object*,
      std::unordered_map< PropertyGID, ObjectPropertyPairSet >> IsDependecyOf;

    //! Type for storing the dirtiness of properties. If the entery
    //! [object][propertyGID] exist in the container the property in that object
    //! is dirty
    typedef std::unordered_map< Object*,
                                std::unordered_set< PropertyGID >>
    DirtyProperties;

    /**
     * Establishes a member function used as updater for a specific object
     * and property
     *
     * @param obj object to which associate the updater callback
     * @param propLabel property
     * @param updater object with the member function
     * @param memberFunc member function used as updater callback
     */
    template < class UPDATER >
    static void setUpdater(
      Object* obj, const std::string& propLabel, UPDATER* updater,
      void ( UPDATER::*memberFunc )( Object*, const std::string&  ))
    {
      auto propertyGID = PropertyGIDsManager::getPropertyGID( propLabel );

      auto& pair = _dependsOn[ obj ][ propertyGID ];
      pair.first = std::bind( memberFunc, updater, obj, propLabel );
    }

    /**
     * Establish a dependency between a property of an object and another
     * property of the same or another object
     *
     * @param dependent object that will depend on
     *                  ( dependency, dependencyPropLabel )
     * @param dependentPropLabel property that will depend on
     *                           ( dependent, propLabel )
     * @param dependency object which will be a dependency of
     *                   ( dependent, propLabel )
     * @param dependencyPropLabel property that will be a dependency of
     *                            ( dependent, propLabel )
     */
    FIRES_API
    static void addDependency(
      Object* dependent, const std::string& dependentPropLabel,
      Object* dependency, const std::string& dependencyPropLabel );

    /**
     * Removes a dependency between a property of an object and another
     * property of the same or another object
     *
     * @param dependent object that depends on
     *                  ( dependency, dependencyPropLabel )
     * @param dependentPropLabel property that depends on
     *                           ( dependent, propLabel )
     * @param dependency object which is a dependency of
     *                   ( dependent, propLabel )
     * @param dependencyPropLabel property that is a dependency of
     *                            ( dependent, propLabel )
     */
    FIRES_API
    static void removeDependency(
        Object* dependent, const std::string& dependentPropLabel,
        Object* dependency, const std::string& dependencyPropLabel );

    /**
     * Sets a property of an object to be dirty
     *
     * @param obj the object that holds the property to be set dirty
     * @param propLabel the name of the property to be set dirty
     */
    FIRES_API
    static void setDependentsDirty( Object* obj, const std::string& propLabel,
                                    bool includeSelf = false );

    /**
     * Returns of a property of an object is dirty
     *
     * @param obj the object that holds the property to test if dirty
     * @param propLabel the name of the property to test if dirty
     * @return true if the property is dirty
     */
    FIRES_API
    static bool getDirtiness( Object* obj, const std::string& propLabel );

    /**
     * Method to update a specific property. This methos is not supposed to be
     * called manually but is called automatically from Object::getProperty. If
     * the proprety is dirty the updater function will be called (if exists),
     * otherwise no update is needed.
     *
     * @param obj the object that holds the property to be updated
     * @param propLabel the name of the property to be updated
     */
    FIRES_API
    static void updateProperty( Object* obj, const std::string& propLabel );

    /**
     * Removes an object both from dependencies and dependents. This method is
     * automatically called when a fires::Object is deleted
     *
     * @param obj the object that will be removed from dependents and
     *            depencendies
     */
    FIRES_API
    static void removeObject( Object* obj );

  protected:

    //! Holds the links from dependents to depdendencies and also the updaters
    FIRES_API static DependsOn _dependsOn;

    //! Holds the links from depdendenciesgg to dependents
    FIRES_API static IsDependecyOf _isDependencyOf;

    //! Hold the properties that are dirty
    FIRES_API static DirtyProperties _dirtyProps;

  };

} // namespace fires
#endif
