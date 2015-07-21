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
#include "fires/Feature.h"

#include <string>
#include <iostream>

namespace fires
{

  namespace detail
  {
    class Object;
  }

  /*! \class Object
    \brief A class to represent objects that can be used in fires.

    This class provides access to object properties and features
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
     * Register a feature to this object
     * @param label label string for the feature
     * @param feature feature to be added
     */
    FIRES_API
    void registerFeature( const std::string& label, const Feature& feature );

    /**
     * Unregister a feature of this object
     * @param label label of the feature to be deleted
     * @return true if the feature could be deleted
     */
    FIRES_API
    bool unregisterFeature( const std::string& label );

    /**
     * Get a feature of this object
     * @param label label string to retrieve the feature
     * @return the feature if found or nullptr otherwise
     */
    FIRES_API
    Feature& getFeature( const std::string& label );

    /**
     * Get a feature of this object
     * @param label label string to retrieve the feature
     * @param feature feature to be setted
     * @return true in case feature was setted, false otherwise
     */
    FIRES_API
    bool setFeature( const std::string& label, const Feature& feature);

    /**
     * Queries if a feature has been registered in this object
     * @param label label string to retrieve the feature
     * @return true if found
     */
    FIRES_API
    bool hasFeature( const std::string& label ) const;

    /**
     * Clears the features of this object (no memory freeing)
     */
    FIRES_API
    void clearFeatures( void );


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
