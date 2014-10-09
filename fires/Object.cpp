/**
 * @file    Object.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "Object.h"

namespace fires
{

  void Object::Features::add(std::string label, Feature *feature) 
  {
    this->insert(std::pair<std::string, Feature *>(label, feature));
  }

  
  void Object::addFeature( std::string label, Feature * feature ) 
  {
    _features.add(label,feature);
  }
  
  Feature * Object::getFeature( std::string label )
  {
    // TODO: change this to find
    return _features[label];
  }

  Object::Features & Object::features( void )
  {
    return _features;
  }

  std::string  Object::label( void )
  {
    return _label;
  }

  void Object::label( std::string label )
  {
    _label = label;
  }
 
  
} // namespace fires

// EOF
