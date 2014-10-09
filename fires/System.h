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


namespace fires
{

 
class System
{

 public:

  class Objects : public std::vector<Object *> 
  {

  public:
    void add(Object *object);

  };

 class QueryObjects :  public std::vector<Object *> 
  {

  public:
    void add(Object *object);
  };


  typedef struct {
    float weight;
    Comparer *comparer;
  } QueryFeatureData;

  class QueryFeatures 
    : public std::map<std::string, QueryFeatureData>
  {

  public:
    void add(std::string label, float weight, Comparer *comparer);

  };


  typedef struct 
  { 
    Object *obj; 
    float score; 
  } ResultsElement;

  class Results : public std::vector<ResultsElement>
  {
  };

  
  void addObject(Object *obj);

  void addQueryObject(Object *obj);

  void addFeature(std::string label, float weight, Comparer *comparer);

  const Results & results();

  virtual void query();

 
 protected:

  Objects _objs;
  QueryObjects _queryObjs; 
  QueryFeatures _features;
  Results _results;


};


}

#endif
