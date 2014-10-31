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
#include <exception>    // std::runtime_error
#include <algorithm>    // std::sort
#include <limits>       // std::numeric_limits

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
				  Comparer * comparer,
				  float minPossibleDist,
				  float maxPossibleDist)
  {
    this->insert(std::pair<std::string, 
		 QueryFeatureData>(label,
				   QueryFeatureData{weight,
				       // minPossibleDist,
				       // maxPossibleDist,
				       // 1,
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
			  Comparer * comparer,
			  float minPossibleDist,
			  float maxPossibleDist) 
  {
    _features.add(label, weight, comparer, 
		  minPossibleDist, maxPossibleDist );
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

      avgObj.addFeature( sysFeatIter->first , fnew );
    }

    for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	 sysFeatIter != _features.end(); sysFeatIter++)
    {
      
      std::string label = sysFeatIter->first;

      Feature * avgFeat = avgObj.getFeature( label );
      
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



  // void System::_computeMaxAndMiniObject( Object & minObj  ) 
  // {

  //   for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
  // 	 sysFeatIter != _features.end(); sysFeatIter++)
  //   {
  //     Feature * forig = _queryObjs[0]->getFeature( sysFeatIter->first );
  //     Feature * fmin =  forig->newFeature( );
  //     Feature * fmax =  forig->newFeature( );

  //     minObj.addFeature( sysFeatIter->first , fmin );
  //     minObj.setToMaxValue( );
  //     maxObj.addFeature( sysFeatIter->first , fmax );
  //     maxObj.setToMinValue( );
  //   }

  //   for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
  // 	 sysFeatIter != _features.end(); sysFeatIter++)
  //   {
      
  //     std::string label = sysFeatIter->first;

  //     Feature * minFeat = minObj.getFeature( label );
  //     Feature * maxFeat = maxObj.getFeature( label );
      
  //     for (Objects::iterator obj = _objs.begin(); 
  // 	   obj != _objs.end(); obj++)
  //     {           
  // 	{

  // 	  Feature * objFeat = ( ( * obj )->getFeature( label ));
	  
  // 	  minObj.
	  
  // 	  (* avgFeat ) += ( * queryFeat );

  // 	}
	
  // 	(* avgFeat ) /= _queryObjs.size();	
  //     }
  // }



  float System::_distanceBetweenTwoObjects( Object *obj1, Object * obj2 )
  {
    float dist = 0;
    
    for (QueryFeatures::iterator sysFeatIter = _features.begin( ); 
	 sysFeatIter != _features.end( ); sysFeatIter++ )
    {
      Feature *f1 = obj1->getFeature( sysFeatIter->first );
      Feature *f2 = obj2->getFeature( sysFeatIter->first );
      
      if ( !f1 || !f2 )
	throw std::runtime_error( "features not defined in the object" );
      
      Comparer *comparer = sysFeatIter->second.comparer;
      
      if ( ! comparer ) 
	throw std::runtime_error( 
	  std::string( "System::_distanceBetweenTwoObjects: " ) + 
	  std::string( "no comparer defined for feature" ) + 
		       sysFeatIter->first );

      float d = comparer->distance( f1, f2 );
      
      dist += fabs( sysFeatIter->second.weight ) * d * d;

    }
    dist = sqrtf(dist) / sqrt( _features.size( ));    

    return dist;

  } 

  void System::query( System::TDistanceToQuerySet queryDistanceType ) 
  {
    
    // If no objects in the query return
    if (_queryObjs.size() == 0)
      return;

    // Clear results
    _results.clear();

    // If the distance to the query set is done using the average
    Object queryAvgObj;
    if ( queryDistanceType == System::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      _computeAverageQueryObject( queryAvgObj );          


// #define NUM_THREADS 6

//     Objects::Results tmpRes[NUM_THREADS];

// #pragma omp parallel num_threads(NUM_THREADS)
//     {
// #pragma omp for
//       for (size_t i = 0; i < _objs.size(); i++)
//       {           

      for (Objects::iterator obj = _objs.begin(); obj != _objs.end(); obj++)
      {           

//	auto obj = & _objs[i];

	float dist = std::numeric_limits< float >::max( );

	if ( queryDistanceType == System::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
	  dist = _distanceBetweenTwoObjects( & queryAvgObj, * obj );
	else 
	  if (queryDistanceType == MINIMUM_DISTANCE_TO_QUERY_OBJECTS )
	  {
	    for ( auto queryObjIt = _queryObjs.begin( );
		  queryObjIt != _queryObjs.end( ); queryObjIt++ )
	    {
	      dist = 
		std::min( dist,
			  _distanceBetweenTwoObjects( * queryObjIt, * obj ));
	      if ( dist == 0.0f ) 
		break;
	    }
	  }
	  else
	    throw std::runtime_error("System::query: no distance type known");


	_results.push_back(ResultsElement{(*obj), dist});      

      } // for each object
//    } 
      
    // Free memory for average object features
    if ( queryDistanceType == System::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      for (QueryFeatures::iterator sysFeatIter = _features.begin(); 
	   sysFeatIter != _features.end(); sysFeatIter++)
      {
	Feature * feat = queryAvgObj.getFeature( sysFeatIter->first );
	feat->deleteFeature( );
	delete feat;
      }


    // Sort results
    std::sort( _results.begin( ), 
	       _results.end( ),
	       ResultsElementSortFunction );
    

  }
  
} // namespace fires


// EOF
