/**
 * @file    System.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "System.h" 

#include <iostream>
#include <math.h>

namespace fires
{

  void System::Objects::add(Object *object) 
  {
    this->push_back(object);
  }    
  
  void System::QueryObjects::add(Object *object) 
  {
    this->push_back(object);
  }    


  void System::QueryFeatures::add(std::string label, 
				  float weight, 
				  Comparer * comparer)
  {
    this->insert(std::pair<std::string, 
		 QueryFeatureData>(label,
				   QueryFeatureData{weight,
				       comparer}));
  }
 
  void System::addObject(Object *obj)
  {
    _objs.add(obj);
  }

  void System::addQueryObject(Object *obj)
  {
    _queryObjs.add(obj);
  }

  void System::addFeature(std::string label, float weight, Comparer *comparer) {
    _features.add(label,weight,comparer);
  }


  const System::Results & System::results( void )
  {
    return _results;
  }

  void System::query( void ) 
  {
    
    if (_queryObjs.size() == 0)
    {
      std::cerr << "There are no objects in the query set." << std::endl;
      return;
    }

    _results.clear();

    // TODO: compute the average object

    Object avgObj;
    for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	 sysFeatIter != _features.end(); sysFeatIter++)
    {
      
    }


    Object *queryObj = _queryObjs[0];

    for (Objects::iterator obj = _objs.begin(); obj != _objs.end(); obj++)
    {      

      float dist = 0;

      for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	   sysFeatIter != _features.end(); sysFeatIter++)
      {
	Feature *f1 = queryObj->getFeature(sysFeatIter->first);
	// TODO check f1 is not NULL
	Feature *f2 = (*obj)->getFeature(sysFeatIter->first);
	// TODO check f2 is not NULL

	Comparer *comparer = sysFeatIter->second.comparer;

	float d = comparer->distance(f1,f2);
	
	dist += fabs(sysFeatIter->second.weight) * d * d;

      }
      dist = sqrtf(dist);
      //      std::cout << (*obj)->label() << ": " << dist << std::endl; 
      //std::cout << dist << std::endl;

      // TODO: change push_backs to more generic method
      _results.push_back(ResultsElement{(*obj), dist});

    }

    // TODO: sort results

  }

  
} // namespace fires


// EOF
