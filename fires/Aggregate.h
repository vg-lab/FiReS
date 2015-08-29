/**
 * @file    Aggregate.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__AGGREGATE_H__
#define __FIRES__AGGREGATE_H__

#include "Object.h"
#include "Task.h"

namespace fires
{

  class FeatureAggregate
  {
  public:

    typedef enum
    {
      MIN = 0,
      MAX,
      MEAN
    } TAggregate;


    virtual ~FeatureAggregate( void )
    {
    }

    virtual void add( Object&, Object&,
                      std::string featureLabel,
                      TAggregate type = TAggregate::MAX ) = 0;

    virtual void divide( Object&, std::string featureLabel,
                         unsigned int size ) = 0;


  };

  template < typename T >
  class ScalarFeatureAggregate : public FeatureAggregate
  {
  public:

    virtual ~ScalarFeatureAggregate( void )
    {
    }

    virtual void add( Object& aggregatedObject, Object& objectToAggregate,
                      std::string featureLabel,
                      TAggregate type = TAggregate::MAX )
    {

      switch ( type )
      {
      case MAX:
        if ( objectToAggregate.getFeature( featureLabel ).value< T >( ) >
             aggregatedObject.getFeature( featureLabel ).value< T >( ))
          aggregatedObject.getFeature( featureLabel ) =
            objectToAggregate.getFeature( featureLabel );
            break;

      case MIN:
        if ( objectToAggregate.getFeature( featureLabel ).value< T >( ) <
             aggregatedObject.getFeature( featureLabel ).value< T >( ))
          aggregatedObject.getFeature( featureLabel ) =
            objectToAggregate.getFeature( featureLabel );
            break;

      case MEAN:
        aggregatedObject.getFeature( featureLabel ).set(
          T( objectToAggregate.getFeature( featureLabel ).value< T >( )  +
             aggregatedObject.getFeature( featureLabel ).value< T >( )));
            break;

      default:
        break;

      }

    }

    virtual void divide( Object& aggregatedObject, std::string featureLabel,
                         unsigned int size )
    {
      aggregatedObject.getFeature( featureLabel ).set(
          T ( aggregatedObject.getFeature( featureLabel ).value< T >( ) /
              float( size )));
    }

  };



  class AggregateConfig : public TaskConfig
  {

  public:

    typedef struct
    {
      std::string label;
      FeatureAggregate* aggregate;
      FeatureAggregate::TAggregate type;
    } TAggregateFeature;


    AggregateConfig( void )
    {
    }

    virtual ~AggregateConfig( void )
    {
    }

    void addFeature( std::string featureLabel_,
                     FeatureAggregate* aggregateer_,
                     FeatureAggregate::TAggregate type_ =
                     FeatureAggregate::MAX )
    {
      _features.push_back( TAggregateFeature{ featureLabel_,
            aggregateer_, type_ });
    }

    std::vector< TAggregateFeature >& features( void )
    {
      return _features;
    }

    void clear( void )
    {
      _features.clear( );
    }

    Object& aggregatedObject( )
    {
      return _aggregatedObject;
    }

  protected:

    std::vector< TAggregateFeature > _features;

    Object _aggregatedObject;

  };

  class Aggregate : public Task
  {

  public:

    virtual Objects& eval( Objects &objs, TaskConfig& config )
    {

      AggregateConfig* aggregateConfig =
        static_cast< AggregateConfig* >( &config );

      if ( !aggregateConfig )
        return objs;

      Object& aggregatedObj = aggregateConfig->aggregatedObject( );
      aggregatedObj.clearFeatures( );

      auto features = aggregateConfig->features( );

      aggregatedObj.label( ) = "aggregated";

      for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      {
        for ( auto f = features.begin( ); f != features.end( ); ++f )
        {
          std::string label = ( *f ).label;
          if ( !aggregatedObj.hasFeature( label ))
          {
            aggregatedObj.registerFeature( label, 0 );
            aggregatedObj.getFeature( label ) = ( *obj )->getFeature( label );
          }
          else
          {
            ( *f ).aggregate->add( aggregatedObj, **obj, label, ( *f ).type );
          }
        }
      }

      for ( auto f = features.begin( ); f != features.end( ); ++f )
      {
        if (( *f ).type == FeatureAggregate::MEAN )
        {
          ( *f ).aggregate->divide( aggregatedObj, ( *f ).label,
				    ( unsigned int ) objs.size( ));
        }
      }

      objs.clear( );
      objs.push_back( &aggregatedObj );

      return objs;
    }

  };


} // namespace fires

#endif
