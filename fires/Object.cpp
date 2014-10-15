/**
 * @file    Object.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "Object.h"

#include <map> 

namespace fires
{
  namespace detail
  {
      
    class ObjectFeatures 
      : public std::map< std::string, Feature * >
    {
      
    public:
      
      ObjectFeatures( void )
      {
      }
      
      void add( const std::string label, 
		Feature * feature )
      {
	this->insert( std::pair< std::string, Feature * >
		      ( label, feature ));
      }
      
      bool del( const std::string label )
      {
	ObjectFeatures::const_iterator it = this->find( label );
	
	if ( it == this->end( ) )
	  return false;
	
	this->erase( it );
	return true;
      }
      
      Feature * get( const std::string label ) const
      {
	ObjectFeatures::const_iterator it = this->find( label );
	
	  if ( it == this->end( ) )
	    return nullptr;
	  
	  return ( *it ).second;
      }

      bool set( const std::string label, Feature * feature ) 
      {
	ObjectFeatures::const_iterator it = this->find( label );
	
	if ( it == this->end( ) )
	  return false;
	
	( * this )[label] = feature;
	return true;
      }
      
    }; // class ObjectFeatures
    
    
    class Object
    {
      
    public:

      void addFeature( std::string label, Feature * feature ) 
      {
	_features.add(label,feature);
      }
  
      Feature * getFeature( const std::string label )
      {
	return _features.get( label );
      }

      bool setFeature( std::string label, Feature * feature)
      {
	return _features.set( label, feature );
      }

      bool delFeature( std::string label )
      {
	return _features.del( label );
      }

      void clearFeatures( void )
      {
	_features.clear( );
      }

      ObjectFeatures & features( void )
      {
	return _features;
      }

      std::string & label( void )
      {
	return _label;
      }

      std::string label( void ) const
      {
	return _label;
      }

    protected:

      //! Set of features of this object
      ObjectFeatures _features;

      //! Label of this object
      std::string _label;
    
    }; // class Object

  } // namespace detail


  Object::Object( ) 
    : _impl ( new detail::Object )
  {

  }

  Object::~Object( ) 
  {
    delete _impl;
  }


  void Object::addFeature( std::string label, Feature * feature ) 
  {
    _impl->addFeature( label, feature );
  }
  
  Feature * Object::getFeature( const std::string label ) const
  {
    return _impl->getFeature( label );
  }

  bool Object::setFeature( std::string label, Feature * feature)
  {
    return _impl->setFeature( label, feature );
  }

  bool Object::delFeature( std::string label )
  {
    return _impl->delFeature( label );
  }

  void Object::clearFeatures( void )
  {
    return _impl->clearFeatures( );
  }

  std::string & Object::label( void )
  {
    return _impl->label( );
  }

  std::string Object::label( void ) const
  {
    return _impl->label( );
  }
  
} // namespace fires

// EOF
