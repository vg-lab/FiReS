/**
 * @file    Object.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__OBJECT_H__
#define __FIRES__OBJECT_H__

#include <fires/api.h>
#include "../Property/Property.h"

#include <string>
#include <iostream>
#include <map>

namespace fires
{

  namespace detail
  {
    class Object;
  }

  /*! \class Object
    \brief A class to represent objects that can be used in fires.

    This class provides access to object properties and properties
  */
  class Object
  {

  public:

    /**
     * Default constructor
     */
    FIRES_API
    Object( );

    /**
     * Copy constructor
     */
    FIRES_API
    Object( Object& object );

    /**
     * Destructor
     */
    FIRES_API
    virtual ~Object( );

    /**
     * Register a property to this object
     * @param label label string for the property
     * @param property property to be added
     */
    FIRES_API
    void registerProperty( const std::string& label, const Property& property );

    /**
     * Unregister a property of this object
     * @param label label of the property to be deleted
     * @return true if the property could be deleted
     */
    FIRES_API
    bool unregisterProperty( const std::string& label );

    /**
     * Get a property of this object
     * @param label label string to retrieve the property
     * @return the property if found or nullptr otherwise
     */
    FIRES_API
    Property& getProperty( const std::string& label );

    /**
     * Get a property of this object
     * @param label label string to retrieve the property
     * @param property property to be setted
     * @return true in case property was setted, false otherwise
     */
    FIRES_API
    bool setProperty( const std::string& label, const Property& property);

    /**
     * Queries if a property has been registered in this object
     * @param label label string to retrieve the property
     * @return true if found
     */
    FIRES_API
    bool hasProperty( const std::string& label ) const;

    /**
     * Clears the properties of this object (no memory freeing)
     */
    FIRES_API
    void clearProperties( void );

    FIRES_API
    std::map< std::string, Property >& getProperties( void );

    /**
     * Get a reference to the label of the object
     * @return reference to label
     */
    FIRES_API
    std::string& label( void );

    /**
     * Get the label of the object
     * @return label of the object
     */
    FIRES_API
    std::string label( void ) const;

  protected:

    detail::Object* _impl;

  };


}

#endif
