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

#include "../Object/Object.h"

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

} //namespace fires

#endif
