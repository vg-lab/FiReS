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


#include "Feature.h"

#include <string>

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
    Object( );

    /**
     * Destructor 
     */
    ~Object( );
 
    /**
     * Add a feature to this object
     * @param label label string for the feature
     * @param feature feature to be added
     */   
    void addFeature( std::string label, Feature *feature );

    /**
     * Get a feature of this object
     * @param label label string to retrieve the feature
     * @return the feature if found or nullptr otherwise
     */   
    Feature * getFeature( std::string label ) const;

    /**
     * Get a feature of this object
     * @param label label string to retrieve the feature
     * @param feature feature to be setted
     * @return true in case feature was setted, false otherwise
     */   
    bool setFeature( std::string label, Feature * feature);

    /**
     * Get a feature of this object
     * @param label label of the feature to be deleted
     * @return true if the feature could be deleted
     */   
    bool delFeature( std::string label );

    /**
     * Clears the features of this object (no memory freeing)
     */   
    void clearFeatures( void );


    /**
     * Get a reference to the label of the object
     * @return reference to label
     */   
    std::string & label( void );

    /**
     * Get the label of the object
     * @return label of the object
     */   
    std::string label( void ) const;

  protected:
    
    detail::Object * _impl;
    
  };
  
  
}

#endif
