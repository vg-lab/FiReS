/**
 * @file    System.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "System.h" 
#include "fires.h" 

#include <iostream>
#include <assert.h>
#include <math.h>
#include <algorithm>    // std::sort

namespace fires
{

  bool ResultsElementSortFunction( System::ResultsElement res1, 
				   System::ResultsElement res2 )
  {
    return ( res1.score < res2.score );
  }


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

  void System::addFeature(std::string label, float weight, 
			  Comparer *comparer) 
  {
    _features.add(label,weight,comparer);
  }


  const System::Results & System::results( void )
  {
    return _results;
  }

  void System::_computeAverageQueryObject( Object & avgObj  ) 
  {

    for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	 sysFeatIter != _features.end(); sysFeatIter++)
    {
      Feature * forig = _queryObjs[0]->getFeature( sysFeatIter->first );
      Feature * fnew =  forig->newFeature( );

      //std::cout << "New " << fnew << std::endl;
      avgObj.addFeature( sysFeatIter->first , fnew );
    }

    for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	 sysFeatIter != _features.end(); sysFeatIter++)
    {
      
      std::string label = sysFeatIter->first;

      Feature * avgFeat = avgObj.getFeature( label );
      
      assert( static_cast< FeaturePtrToFloat * >( avgFeat ));

      for ( QueryObjects::iterator queryObjIt = _queryObjs.begin( );
	    queryObjIt != _queryObjs.end( ); queryObjIt++ )
      {


	Feature * queryFeat = 
	  ( ( * queryObjIt )->getFeature( label ) );

	assert( static_cast< FeaturePtrToFloat * >( queryFeat ));

	(* avgFeat ) += ( * queryFeat );
      }

      (* avgFeat ) /= _queryObjs.size();
      
    }

  }

  void System::query( void ) 
  {
    
    if (_queryObjs.size() == 0)
    {
      std::cerr << "There are no objects in the query set." << std::endl;
      return;
    }

    _results.clear();


    // If the distance to the query set is done using the average
    Object avgObj;
    _computeAverageQueryObject( avgObj );
    

    Object *queryObj = & avgObj; // _queryObjs[0];

    for (Objects::iterator obj = _objs.begin(); obj != _objs.end(); obj++)
    {      

      float dist = 0;

      for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	   sysFeatIter != _features.end(); sysFeatIter++)
      {
	Feature *f1 = queryObj->getFeature(sysFeatIter->first);
	Feature *f2 = (*obj)->getFeature(sysFeatIter->first);

	if ( !f1 || !f2 )
	  throw std::runtime_error( "features not definen in the object" );

	Comparer *comparer = sysFeatIter->second.comparer;

	float d = comparer->distance(f1,f2);
	
	dist += fabs(sysFeatIter->second.weight) * d * d;

      }
      dist = sqrtf(dist);    

      // TODO: change push_backs to more generic method
      _results.push_back(ResultsElement{(*obj), dist});

    }


    // Free memory for average object features
    for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	 sysFeatIter != _features.end(); sysFeatIter++)
    {
      Feature * feat = avgObj.getFeature( sysFeatIter->first );
      feat->deleteFeature( );
      delete feat;
      //  std::cout << "Delete " << feat << std::endl;
    }





    // TODO: sort results
    std::sort( _results.begin( ), 
	       _results.end( ),
	       ResultsElementSortFunction );

  }

  
} // namespace fires


// EOF
