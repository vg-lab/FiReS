/**
 * @file    Engine.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

// #ifdef FIRES_WITH_OPENMP
// #include <omp.h>
// #endif
// #include <stdio.h>
// #include <stdlib.h>


#include "Engine.h"
// #include <fires/fires.h>

// #include <iostream>
// #include <assert.h>
// #include <math.h>
// #include <exception>    // std::runtime_error
// #include <algorithm>    // std::sort
// #include <limits>       // std::numeric_limits

namespace fires
{


  //
  // Engine methods
  //
  Engine::~Engine( )
  {
  }

//   void Engine::_computeAverageQueryObject( Object& avgObj,
//                                            Objects& queryObjects,
//                                            QueryFeatures& features  )
//   {
//     for ( auto qfd = features.begin( ); qfd != features.end( ); ++qfd )
//     {

//       std::string featLabel = qfd->first;
//       qfd->second.averager( )->reset( );

//       for ( auto obj = queryObjects.begin( );
//             obj != queryObjects.end( ); ++obj )
//       {
//         qfd->second.averager( )->accum(( *obj )->getFeature( featLabel ));
//       }

//       qfd->second.averager( )->divide( queryObjects.size( ));
//       avgObj.registerFeature( featLabel,
//                               qfd->second.averager( )->feature( ));
//     }
//   }


//   float Engine::_distanceBetweenTwoObjects( Object* obj1, Object* obj2,
//                                             QueryFeatures& features )
//   {
//     float dist = 0;

//     for ( auto qfd = features.begin( ); qfd != features.end( ); ++qfd )
//     {
//         std::string featLabel = qfd->first;
//         fires::Comparer* comparer = qfd->second.comparer( );

//         float d = comparer->distance( obj1->getFeature( featLabel ),
//                                       obj2->getFeature( featLabel ));

//       dist += fabs( qfd->second.weight( )) * d * d;

//     }

//     dist = sqrtf( dist ) / sqrt( features.size( ));

//     return dist;

//   }

//   void Engine::query( Objects& objects,
//                       Objects& queryObjects,
//                       QueryFeatures& features,
//                       std::string resultsFeatureLabel,
//                       Engine::TDistanceToQuerySet queryDistanceType )
//   {

//     // If no objects in the query return
//     if ( queryObjects.size() == 0 || features.size( ) == 0 )
//       return;

//     // If the distance to the query set is done using the average
//     Object queryAvgObj;
//     if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
//       _computeAverageQueryObject( queryAvgObj, queryObjects, features );


//     for ( Objects::iterator obj = objects.begin(); obj != objects.end(); ++obj )
//     {
//       float dist = std::numeric_limits< float >::max( );

//       if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
//         dist = _distanceBetweenTwoObjects( &queryAvgObj, *obj, features );
//       else
//         if (queryDistanceType == MINIMUM_DISTANCE_TO_QUERY_OBJECTS )
//         {
//           for ( auto queryObjIt = queryObjects.begin( );
//                 queryObjIt != queryObjects.end( ); ++queryObjIt )
//           {
//             dist =
//               std::min( dist,
//                         _distanceBetweenTwoObjects( *queryObjIt, *obj,
//                                                     features ));
//             if ( dist == 0.0f )
//               break;
//           }
//         }
//         else
//           throw std::runtime_error("Engine::query: no distance type known");


//       ( *obj )->registerFeature( resultsFeatureLabel,
//                                  dist );
//       ( *obj )->setFeature( resultsFeatureLabel, Feature( dist ));

//     } // for each object
//   }
} // namespace fires


//EOF
