/**
 * @file    Aggregator.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__AGGREGATOR_H__
#define __FIRES__AGGREGATOR_H__

#include "Object.h"
#include "Task.h"

namespace fires
{

  class PropertyAggregator
  {
  public:

    typedef enum
    {
      MIN = 0,
      MAX,
      MEAN
    } TAggregation;


    virtual ~PropertyAggregator( void )
    {
    }

    virtual void add( Object&, Object&,
                      std::string propertyLabel,
                      TAggregation type = TAggregation::MAX ) = 0;

    virtual void divide( Object&, std::string propertyLabel,
                         unsigned int size ) = 0;


  };

  template < typename T >
  class ScalarPropertyAggregator : public PropertyAggregator
  {
  public:

    virtual ~ScalarPropertyAggregator( void )
    {
    }

    virtual void add( Object& aggregatedObject, Object& objectToAggregator,
                      std::string propertyLabel,
                      TAggregation type = TAggregation::MAX )
    {

      switch ( type )
      {
      case MAX:
        if ( objectToAggregator.getProperty( propertyLabel ).value< T >( ) >
             aggregatedObject.getProperty( propertyLabel ).value< T >( ))
          aggregatedObject.getProperty( propertyLabel ) =
            objectToAggregator.getProperty( propertyLabel );
            break;

      case MIN:
        if ( objectToAggregator.getProperty( propertyLabel ).value< T >( ) <
             aggregatedObject.getProperty( propertyLabel ).value< T >( ))
          aggregatedObject.getProperty( propertyLabel ) =
            objectToAggregator.getProperty( propertyLabel );
            break;

      case MEAN:
        aggregatedObject.getProperty( propertyLabel ).set(
          T( objectToAggregator.getProperty( propertyLabel ).value< T >( )  +
             aggregatedObject.getProperty( propertyLabel ).value< T >( )));
            break;

      default:
        break;

      }

    }

    virtual void divide( Object& aggregatedObject, std::string propertyLabel,
                         unsigned int size )
    {
      aggregatedObject.getProperty( propertyLabel ).set(
          T ( aggregatedObject.getProperty( propertyLabel ).value< T >( ) /
              float( size )));
    }

  };



  class AggregatorConfig : public TaskConfig
  {

  public:

    typedef struct
    {
      std::string label;
      PropertyAggregator* aggregate;
      PropertyAggregator::TAggregation type;
    } TAggregatorProperty;


    AggregatorConfig( void )
    {
    }

    virtual ~AggregatorConfig( void )
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

    void clear( void )
    {
      _properties.clear( );
    }

    Object& aggregatedObject( )
    {
      return _aggregatedObject;
    }

  protected:

    std::vector< TAggregatorProperty > _properties;

    Object _aggregatedObject;

  };

  class Aggregator : public Task
  {

  public:

    virtual Objects& eval( Objects &objs, TaskConfig& config )
    {

      AggregatorConfig* aggregateConfig =
        static_cast< AggregatorConfig* >( &config );

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
