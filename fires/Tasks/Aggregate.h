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

#include "../Object/Object.h"
#include "Task.h"


namespace fires
{

  class AggregateConfig : public TaskConfig
  {

  public:

    typedef struct
    {
      std::string label;
      PropertyAggregator* aggregate;
      PropertyAggregator::TAggregation type;
    } TAggregatorProperty;


    AggregateConfig( void )
    {
    }

    virtual ~AggregateConfig( void )
    {
    }

    void addProperty( std::string propertyLabel_,
                     PropertyAggregator* aggregateer_,
                     PropertyAggregator::TAggregation type_ =
                     PropertyAggregator::MAX )
    {
      _properties.push_back( TAggregatorProperty{ propertyLabel_,
            aggregateer_, type_ });
    }

    std::vector< TAggregatorProperty >& properties( void )
    {
      return _properties;
    }

    Object& aggregatedObject( )
    {
      return _aggregatedObject;
    }

    FIRES_API
    void clearAggregatedObject( void )
    {
      return _aggregatedObject.clearProperties( );
    }

    FIRES_API
    void clearProperties( void )
    {
      return _properties.clear( );
    }

    FIRES_API
    void clear( void )
    {
      clearAggregatedObject( );
      clearProperties( );
    }


  protected:

    std::vector< TAggregatorProperty > _properties;

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
      aggregatedObj.clearProperties( );

      auto properties = aggregateConfig->properties( );

      aggregatedObj.label( ) = "aggregated";

      for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      {
        for ( auto f = properties.begin( ); f != properties.end( ); ++f )
        {
          std::string label = ( *f ).label;
          if ( !aggregatedObj.hasProperty( label ))
          {
            aggregatedObj.registerProperty( label, 0 );
            aggregatedObj.getProperty( label ) = ( *obj )->getProperty( label );
          }
          else
          {
            ( *f ).aggregate->add( aggregatedObj, **obj, label, ( *f ).type );
          }
        }
      }

      for ( auto f = properties.begin( ); f != properties.end( ); ++f )
      {
        if (( *f ).type == PropertyAggregator::MEAN )
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
