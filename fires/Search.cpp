#include "Search.h"

namespace fires
{

  Search::~Search( )
  {
  }

  void Search::_computeAverageQueryObject( Object& avgObj,
                                           Objects& queryObjects,
                                           SearchConfig& config )
  {
    for ( auto qfd = config.features( ).begin( );
          qfd != config.features( ).end( ); ++qfd )
    {

      std::string featLabel = qfd->first;
      qfd->second.averager( )->reset( );

      for ( auto obj = queryObjects.begin( );
            obj != queryObjects.end( ); ++obj )
      {
        qfd->second.averager( )->accum(( *obj )->getFeature( featLabel ));
      }

      qfd->second.averager( )->divide( queryObjects.size( ));
      avgObj.registerFeature( featLabel,
                              qfd->second.averager( )->feature( ));
    }
  }


  float Search::_distanceBetweenTwoObjects( Object* obj1, Object* obj2,
                                            SearchConfig& config )
  {
    float dist = 0;

    for ( auto qfd = config.features( ).begin( );
          qfd != config.features( ).end( ); ++qfd )
    {
        std::string featLabel = qfd->first;
        fires::Comparer* comparer = qfd->second.comparer( );

        float d = comparer->distance( obj1->getFeature( featLabel ),
                                      obj2->getFeature( featLabel ));

      dist += fabs( qfd->second.weight( )) * d * d;

    }

    dist = sqrtf( dist ) / sqrt( config.features( ).size( ));

    return dist;

  }

  // void Search::query( Objects& objects,
  //                     Objects& queryObjects,
  //                     QueryFeatures& features,
  //                     std::string resultsFeatureLabel,
  //                     Search::TDistanceToQuerySet queryDistanceType )

  // {

  Objects& Search::eval( Objects &objects, TaskConfig &config )
  {

    SearchConfig* searchConfig = static_cast< SearchConfig* >( &config );
    assert( searchConfig );

    auto features = searchConfig->features( );
    auto queryDistanceType = searchConfig->distanceToQueryType( );
    auto queryObjects = searchConfig->queryObjects( );
    auto resultsFeatureLabel = searchConfig->resultsFeatureLabel( );

    // If no objects in the query return
    if ( queryObjects.size( ) == 0 || features.size( ) == 0 )
      return objects;

    // If the distance to the query set is done using the average
    Object queryAvgObj;
    if ( queryDistanceType == SearchConfig::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
      _computeAverageQueryObject( queryAvgObj, queryObjects, *searchConfig );


    for ( Objects::iterator obj = objects.begin(); obj != objects.end(); ++obj )
    {
      float dist = std::numeric_limits< float >::max( );

      if ( queryDistanceType == SearchConfig::DISTANCE_TO_AVERAGE_QUERY_OBJECT )
        dist = _distanceBetweenTwoObjects( &queryAvgObj, *obj, *searchConfig );
      else
        if (queryDistanceType ==
            SearchConfig::MINIMUM_DISTANCE_TO_QUERY_OBJECTS )
        {
          for ( auto queryObjIt = queryObjects.begin( );
                queryObjIt != queryObjects.end( ); ++queryObjIt )
          {
            dist =
              std::min( dist,
                        _distanceBetweenTwoObjects( *queryObjIt, *obj,
                                                    *searchConfig ));
            if ( dist == 0.0f )
              break;
          }
        }
        else
          throw std::runtime_error(
            "fires::Search::query: no distance type known" );


      ( *obj )->registerFeature( resultsFeatureLabel, 0.0f );
      ( *obj )->setFeature( resultsFeatureLabel, Feature( dist ));

    } // for each object

    return objects;

  } // eval

} // namespace fires


// EOF
