/**
 * @file    System.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__SYSTEM_H__
#define __FIRES__SYSTEM_H__


#include "Object.h"
#include "Comparer.h"

#include <vector>
#include <map>


namespace fires
{

 
class System
{

 public:

  //
  // System::Objects
  //
  class Objects : public std::vector<Object *> 
  {

  public:
    void add(Object *object);

  };

  //
  // System::QueryObjects
  //
 class QueryObjects :  public std::vector<Object *> 
  {

  public:
    void add(Object *object);
  };


  typedef struct 
  {
    float weight;
    // float minPossibleDist;
    // float maxPossibleDist;
    // float squaredInvMaxMinDiff;
    Comparer *comparer;
  } QueryFeatureData;

  //
  // System::QueryFeatures
  //
  class QueryFeatures 
    : public std::map<std::string, QueryFeatureData>
  {

  public:
    void add(std::string label, 
	     float weight, 
	     Comparer *comparer,
	     float minPossibleDist = 0.0f,
	     float maxPossibleDist = 1.0f);

  };


  typedef struct 
  { 
    Object *obj; 
    float score; 
  } ResultsElement;

  //
  // System::Results
  //
  class Results : public std::vector<ResultsElement>
  {
  };



  typedef enum 
  { 
    DISTANCE_TO_AVERAGE_QUERY_OBJECT,
    MINIMUM_DISTANCE_TO_QUERY_OBJECTS 
  } TDistanceToQuerySet;

  
  void addObject(Object * obj);

  void addQueryObject(Object * obj);

  void addFeature(std::string label, 
		  float weight, 
		  Comparer * comparer,
		  float minPossibleDist = 0.0f,
		  float maxPossibleDist = 1.0f);

  const Results & results();

  virtual void query( TDistanceToQuerySet queryDistanceType 
		      = DISTANCE_TO_AVERAGE_QUERY_OBJECT );

 
 protected:

  float _distanceBetweenTwoObjects( Object *obj1, Object * obj2 );
  virtual void _computeAverageQueryObject( Object & avgObj  );

  Objects _objs;
  QueryObjects _queryObjs; 
  QueryFeatures _features;
  Results _results;


};


}

#endif
