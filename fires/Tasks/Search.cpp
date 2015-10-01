#include "Search.h"
#include "error.h"

namespace fires
{

  Search::~Search( )
  {
  }

  void Search::_computeAverageQueryObject( Object& avgObj,
                                           Objects& queryObjects,
                                           SearchConfig& config )
  {
    for ( auto qfd = config.properties( ).begin( );
          qfd != config.properties( ).end( ); ++qfd )
    {

      std::string featLabel = qfd->first;
      qfd->second.averager( )->reset( );

      for ( auto obj = queryObjects.begin( );
            obj != queryObjects.end( ); ++obj )
      {
        qfd->second.averager( )->accum(( *obj )->getProperty( featLabel ));
      }

      qfd->second.averager( )->divide(( unsigned int ) queryObjects.size( ));
      avgObj.registerProperty( featLabel,
                              qfd->second.averager( )->property( ));
    }
  }


  float Search::_distanceBetweenTwoObjects( Object* obj1, Object* obj2,
                                            SearchConfig& config )
  {
    float dist = 0;

    for ( auto qfd = config.properties( ).begin( );
          qfd != config.properties( ).end( ); ++qfd )
    {
        std::string featLabel = qfd->first;
        fires::Comparer* comparer = qfd->second.comparer( );

        float d;

        Normalizer* n = qfd->second.normalizer( );
        if ( n )
        {
          Property f1 = n->normalizeProperty( featLabel,
                                            obj1->getProperty( featLabel ));
          Property f2 = n->normalizeProperty( featLabel,
                                            obj2->getProperty( featLabel ));
          d = comparer->distance( f1, f2 );
          d = n->normalizeDistance( d );
          n->freeNormalizedProperty( f1 );
          n->freeNormalizedProperty( f2 );
        }
        else
          d = comparer->distance( obj1->getProperty( featLabel ),
                                  obj2->getProperty( featLabel ));


//      dist += fabs( qfd->second.weight( )) * d * d;
      dist += d;

    }

//    dist = sqrtf( dist ) / sqrt( config.properties( ).size( ));
    dist /= config.properties( ).size( );

    return dist;

  }

  // void Search::query( Objects& objects,
  //                     Objects& queryObjects,
  //                     QueryProperties& properties,
  //                     std::string resultsPropertyLabel,
  //                     Search::TDistanceToQuerySet queryDistanceType )

  // {

  Objects& Search::eval( Objects &objects, TaskConfig &config )
  {

    SearchConfig* searchConfig = static_cast< SearchConfig* >( &config );
    FIRES_DEBUG_CHECK( searchConfig, "error casting to SearchConfig" );

    auto properties = searchConfig->properties( );
    auto queryDistanceType = searchConfig->distanceToQueryType( );
    auto queryObjects = searchConfig->queryObjects( );
    auto resultsPropertyLabel = searchConfig->resultsPropertyLabel( );

    // If no objects in the query return
    if ( queryObjects.size( ) == 0 || properties.size( ) == 0 )
      return objects;


    for ( auto qfd = searchConfig->properties( ).begin( );
          qfd != searchConfig->properties( ).end( ); ++qfd )
    {

      std::string featLabel = qfd->first;
      Normalizer* n = qfd->second.normalizer( );

      if ( n )
      {
        n->reset( featLabel );

        for ( auto obj = objects.begin( );
              obj != objects.end( ); ++obj )
          n->update( featLabel, ( *obj )->getProperty( featLabel ));

        for ( auto obj = queryObjects.begin( );
              obj != queryObjects.end( ); ++obj )
          n->update( featLabel, ( *obj )->getProperty( featLabel ));

      }
    }



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


      ( *obj )->registerProperty( resultsPropertyLabel, 0.0f );
      ( *obj )->setProperty( resultsPropertyLabel, Property( dist ));

    } // for each object

    return objects;

  } // eval

} // namespace fires


// EOF
