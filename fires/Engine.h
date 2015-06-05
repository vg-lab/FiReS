/**
 * @file    Engine.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__ENGINE_H__
#define __FIRES__ENGINE_H__


#include "Comparer.h"
#include "Object.h"
#include "Objects.h"
#include "QueryFeatures.h"

#include <vector>
#include <map>


namespace fires
{

  /*! \class Engine
    \brief FiReS engine

    Provides the entry point for objects, comparers and results
  */
  class Engine
  {

  public:

    /**
     * Default destructor
     **/
    FIRES_API
    virtual ~Engine( );

    /// Type of distance used when multiple objects on the query set
    typedef enum
    {
      /// Distance is computed agains the average query object
      DISTANCE_TO_AVERAGE_QUERY_OBJECT,
      /// Distance is computed using the minimum distance to all
      /// objects in the query set
      MINIMUM_DISTANCE_TO_QUERY_OBJECTS
    } TDistanceToQuerySet;



    FIRES_API
    virtual void query( Objects& objects,
                        Objects& queryObjects,
                        QueryFeatures& features,
                        std::string resultsFeatureLabel = "fires::score",
                        TDistanceToQuerySet queryDistanceType
                        = DISTANCE_TO_AVERAGE_QUERY_OBJECT );

    // FIRES_API
    // virtual void parallelQuery(
    //   Objects& objects,
    //   Objects& queryObjects,
    //   QueryFeatures& features,
    //   std::string resultsFeatureLabel = "fires::score",
    //   TDistanceToQuerySet queryDistanceType
    //   = DISTANCE_TO_AVERAGE_QUERY_OBJECT );

  protected:

    FIRES_API
    float _distanceBetweenTwoObjects( Object* obj1, Object* obj2,
                                      QueryFeatures& features );
    FIRES_API
    virtual void _computeAverageQueryObject( Object& avgObj,
                                             Objects& queryObjects,
                                             QueryFeatures& features );

  };


}

#endif
