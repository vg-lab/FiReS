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

#include <map>


namespace fires
{

  class Object
  {

  public:

    class Features : public std::map<std::string, Feature *>
    {
    
    public:

      void add(std::string label, Feature *feature); 

    };

 
    void addFeature( std::string label, Feature *feature );

    Feature * getFeature( std::string label );

    Features & features( void );

    std::string label( void );

    void label(std::string label);


  protected:
  
    Features _features;
    std::string _label;

    
  };
  
  
}

#endif
