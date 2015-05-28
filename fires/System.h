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


#include "Comparer.h"
#include "Object.h"
#include "Objects.h"
#include "QueryFeatures.h"

#include <vector>
#include <map>


namespace fires
{

  /*! \class System
    \brief FiReS system

    Provides the entry point for objects, comparers and results
  */
  class System
  {

  public:

    /**
     * Default destructor
     **/
    virtual ~System( );

    /// Type of distance used when multiple objects on the query set
    typedef enum
    {
      /// Distance is computed agains the average query object
      DISTANCE_TO_AVERAGE_QUERY_OBJECT,
      /// Distance is computed using the minimum distance to all
      /// objects in the query set
      MINIMUM_DISTANCE_TO_QUERY_OBJECTS
    } TDistanceToQuerySet;


    // /**
    //  * Adds a new feature to the container
    //  * @param obj pointer object to be added to the objects container
    //  */
    // void addObject( Object*  obj );

    // /**
    //  * Adds a new feature to the container
    //  * @param obj pointer object to be added to the query objects container
    //  */
    // void addQueryObject( Object*  obj );

    // void addFeature( std::string label,
    //                  float weight,
    //                  Comparer*  comparer );

    // const Results & results();

    // virtual void query( TDistanceToQuerySet queryDistanceType
    //                     = DISTANCE_TO_AVERAGE_QUERY_OBJECT );

    virtual void query( Objects& objects,
                        Objects& queryObjects,
                        QueryFeatures& features,
                        std::string resultsFeatureLabel = "fires::score",
                        TDistanceToQuerySet queryDistanceType
                        = DISTANCE_TO_AVERAGE_QUERY_OBJECT );

    virtual void parallelQuery(
      Objects& objects,
      Objects& queryObjects,
      QueryFeatures& features,
      std::string resultsFeatureLabel = "fires::score",
      TDistanceToQuerySet queryDistanceType
      = DISTANCE_TO_AVERAGE_QUERY_OBJECT );

  protected:

    float _distanceBetweenTwoObjects( Object* obj1, Object* obj2,
                                      QueryFeatures& features );
    virtual void _computeAverageQueryObject( Object& avgObj,
                                             Objects& queryObjects,
                                             QueryFeatures& features );

  };


}

#endif
