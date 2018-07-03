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
#ifndef __FIRES__OBJECT_H__
#define __FIRES__OBJECT_H__

#include <fires/api.h>
#include "../Property/Property.h"
#include "../PropertyGIDsManager.h"
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include <map>

namespace fires
{

  class ObjectProperties
    : public std::map< PropertyGID, Property >
  {

  public:
    FIRES_API
    ObjectProperties( void );
    FIRES_API
    void registerProperty( const std::string& label,
       const Property& property );
    FIRES_API
    bool unregisterProperty( const std::string& label );
    FIRES_API
    Property& get( const std::string& label );
    FIRES_API
    const Property& get( const std::string& label ) const;
    FIRES_API
    bool set( const std::string& label, const Property& property );

  }; // class ObjectProperties


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
    Object( const Object& object );

    /**
     * Destructor
     */
    FIRES_API
    virtual ~Object( );

    // FIRES_API
    // template< typename ValueType >
    // void registerProperty( const std::string& label, ValueType value )
    // {
    //   this->registerProperty( label, Property( value ));
    //   PropertyManager::register< ValueType >( label, value );
    // }

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
     * @return the property if found and throw exception otherwise
     */
    FIRES_API
    Property& getProperty( const std::string& label );

    /**
     * Get a property of this object as const
     * @param label label string to retrieve the property
     * @return the property if found and throw exception otherwise
     */
    FIRES_API
    const Property& getProperty( const std::string& label ) const;

    /**
     * Get a property of this object
     * @param label label string to retrieve the property
     * @return the property if found and throw exception otherwise
     */
    FIRES_API
    Property& operator[]( const std::string& label );

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

    /**
     * Get all properties
     * @return all properties
     */
    FIRES_API
    ObjectProperties& properties( void );

    /**
     * Get all properties as const
     * @return all properties
     */
    FIRES_API
    const ObjectProperties& properties( void ) const;

    /**
     * Get a reference to the label of the object
     * @return reference to label
     */
    FIRES_API
    std::string& label( void );

    /**
     * Get the label of the object as const
     * @return label of the object as const
     */
    FIRES_API
    const std::string& label( void ) const;

    /** @name Operators */
    ///@{
    FIRES_API
    Object& operator= ( const Object& other );
    ///@}

    /**Serialize this object properties
    * @param stream to write the object
    * @param linePrefix prefix at the start of every line
    */
    FIRES_API
    void serialize( std::ostream& stream, bool minimizeStream = true,
      const std::string& linePrefix = "" ) const;

    /**Reads and loads this object properties
    * @stream stream containing JSON from which data will be loaded
    */
    FIRES_API
    void deserialize( std::istream& stream );

    /**Reads and loads this object properties
    * @root boost JSON root object from which data will be loaded
    */
    FIRES_API
    void deserialize( const boost::property_tree::ptree& root );

  protected:

    //! Set of properties of this object
    ObjectProperties _properties;

    //! Label of this object
    std::string _label;

  }; // class Object

} // namespace fires

#endif
