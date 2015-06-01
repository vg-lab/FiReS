/**
 * @file    Engine.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


#include <fires/Engine.h>
#include <fires/fires.h>

#include <iostream>
#include <assert.h>
#include <math.h>
#include <exception>    // std::runtime_error
#include <algorithm>    // std::sort
#include <limits>       // std::numeric_limits

namespace fires
{


  //
  // Engine methods
  //
  Engine::~Engine( )
  {
  }

  void Engine::_computeAverageQueryObject( Object& avgObj,
                                           Objects& queryObjects,
                                           QueryFeatures& features  )
  {

    for (QueryFeatures::iterator sysFeatIter = features.begin();
         sysFeatIter != features.end(); ++sysFeatIter)
    {
      Feature * forig = queryObjects[0]->getFeature( sysFeatIter->first );
      Feature * fnew =  forig->newFeature( );

      avgObj.addFeature( sysFeatIter->first , fnew );
    }

    for (QueryFeatures::iterator sysFeatIter = features.begin();
         sysFeatIter != features.end(); ++sysFeatIter)
    {

      std::string label = sysFeatIter->first;

      Feature * avgFeat = avgObj.getFeature( label );

      for ( Objects::iterator queryObjIt = queryObjects.begin( );
            queryObjIt != queryObjects.end( ); ++queryObjIt )
      {


        Feature * queryFeat =
          ( ( * queryObjIt )->getFeature( label ) );

        assert( static_cast< FeaturePtrToScalar< float >* >( queryFeat ));

        (* avgFeat ) += ( * queryFeat );
      }

      (* avgFeat ) /= int( queryObjects.size( ));

    }

  }



  // void Engine::_computeMaxAndMiniObject( Object & minObj  )
  // {

  //   for (QueryFeatures::iterator sysFeatIter = _features.begin();
  //          sysFeatIter != _features.end(); sysFeatIter++)
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
  //          sysFeatIter != _features.end(); sysFeatIter++)
  //   {

  //     std::string label = sysFeatIter->first;

  //     Feature * minFeat = minObj.getFeature( label );
  //     Feature * maxFeat = maxObj.getFeature( label );

  //     for (Objects::iterator obj = _objs.begin();
  //            obj != _objs.end(); obj++)
  //     {
  //         {

  //           Feature * objFeat = ( ( * obj )->getFeature( label ));

  //           minObj.

  //           (* avgFeat ) += ( * queryFeat );

  //         }

  //         (* avgFeat ) /= _queryObjs.size();
  //     }
  // }



  float Engine::_distanceBetweenTwoObjects( Object *obj1, Object * obj2,
                                            QueryFeatures& features )
  {
    float dist = 0;

    for (QueryFeatures::iterator sysFeatIter = features.begin( );
         sysFeatIter != features.end( ); ++sysFeatIter )
    {
      Feature *f1 = obj1->getFeature( sysFeatIter->first );
      Feature *f2 = obj2->getFeature( sysFeatIter->first );

      if ( !f1 || !f2 )
        throw std::runtime_error( "features not defined in the object" );

      const Comparer* comparer = sysFeatIter->second.comparer( );

      if ( ! comparer )
        throw std::runtime_error(
          std::string( "Engine::_distanceBetweenTwoObjects: " ) +
          std::string( "no comparer defined for feature" ) +
                       sysFeatIter->first );

      float d = comparer->distance( f1, f2 );

      dist += fabs( sysFeatIter->second.weight( )) * d * d;

    }
    dist = sqrtf(dist) / sqrt( features.size( ));

    return dist;

  }

  void Engine::query( Objects& objects,
                      Objects& queryObjects,
                      QueryFeatures& features,
                      std::string resultsFeatureLabel,
                      Engine::TDistanceToQuerySet queryDistanceType )
  {

    // If no objects in the query return
    if ( queryObjects.size() == 0 )
      return;

    // If the distance to the query set is done using the average
    Object queryAvgObj;
    if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      _computeAverageQueryObject( queryAvgObj, queryObjects, features );


    for ( Objects::iterator obj = objects.begin(); obj != objects.end(); ++obj )
    {

      float dist = std::numeric_limits< float >::max( );

      if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
        dist = _distanceBetweenTwoObjects( &queryAvgObj, *obj, features );
      else
        if (queryDistanceType == MINIMUM_DISTANCE_TO_QUERY_OBJECTS )
        {
          for ( auto queryObjIt = queryObjects.begin( );
                queryObjIt != queryObjects.end( ); ++queryObjIt )
          {
            dist =
              std::min( dist,
                        _distanceBetweenTwoObjects( *queryObjIt, *obj,
                                                    features ));
            if ( dist == 0.0f )
              break;
          }
        }
        else
          throw std::runtime_error("Engine::query: no distance type known");


      ( *obj )->addFeature(  resultsFeatureLabel,
                             new FeatureScalar< float >( dist ));
      //_results.push_back(ResultsElement{(*obj), dist});

    } // for each object


    // Free memory for average object features
    if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      for (QueryFeatures::iterator sysFeatIter = features.begin();
           sysFeatIter != features.end(); ++sysFeatIter )
      {
        Feature * feat = queryAvgObj.getFeature( sysFeatIter->first );
        feat->deleteFeature( );
        delete feat;
      }


    // Sort results
    // std::sort( _results.begin( ),
    //            _results.end( ),
    //            ResultsElementSortFunction );


  }



  void Engine::parallelQuery( Objects& objects,
                              Objects& queryObjects,
                              QueryFeatures& features,
                              std::string resultsFeatureLabel,
                              Engine::TDistanceToQuerySet queryDistanceType )
  {
#ifdef Win32

    std::runtime_error( "OpenMP not supported in Win32" );
#else
    
    // If no objects in the query return
    if ( queryObjects.size( ) == 0 )
      return;

    // Clear results
//    _results.clear();

    // If the distance to the query set is done using the average
    Object queryAvgObj;
    if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      _computeAverageQueryObject( queryAvgObj, queryObjects, features );

#define NUM_THREADS 6

    // Engine::Results tmpResults[NUM_THREADS];

    int tid = 0;
    ((void )tid);

#pragma omp parallel for  num_threads(NUM_THREADS) schedule(static) private(tid)
    for ( int i = 0; i < int( objects.size( )); ++i )
    {

      auto obj = & objects[i];

      float dist = std::numeric_limits< float >::max( );

      if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
        dist = _distanceBetweenTwoObjects( &queryAvgObj, *obj, features );
      else
        if (queryDistanceType == MINIMUM_DISTANCE_TO_QUERY_OBJECTS )
        {
          for ( auto queryObjIt = queryObjects.begin( );
                queryObjIt != queryObjects.end( ); ++queryObjIt )
          {
            dist =
              std::min( dist,
                        _distanceBetweenTwoObjects( *queryObjIt, *obj, features ));
            if ( dist == 0.0f )
              break;
          }
        }
        else
          throw std::runtime_error("Engine::query: no distance type known");

      // tid = omp_get_thread_num();
      ( *obj )->addFeature( resultsFeatureLabel,
                            new FeatureScalar< float >( dist ));

      //tmpResults[tid].push_back( ResultsElement{ ( * obj ), dist });
//        _results.push_back(ResultsElement{(*obj), dist});

      } // for each object


//    _results.reserve( _objs.size( ) );
    // for ( int i = 0; i < NUM_THREADS; i++ )
    // {
    //   _results.insert( _results.end( ),
    //                    tmpResults[i].begin( ),
    //                    tmpResults[i].end( ));
    // }


    // Free memory for average object features
    if ( queryDistanceType == Engine::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      for (QueryFeatures::iterator sysFeatIter = features.begin();
           sysFeatIter != features.end(); ++sysFeatIter )
      {
        Feature * feat = queryAvgObj.getFeature( sysFeatIter->first );
        feat->deleteFeature( );
        delete feat;
      }


    // Sort results
    // std::sort( _results.begin( ),
    //            _results.end( ),
    //            ResultsElementSortFunction );

#endif
  }



} // namespace fires


// EOF
