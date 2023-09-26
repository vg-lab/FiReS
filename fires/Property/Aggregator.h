/*
 * Copyright (c) 2014-2016 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/vg-lab/FiReS>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#ifndef __FIRES__AGGREGATOR_H__
#define __FIRES__AGGREGATOR_H__

#include "../Object/Object.h"
#include <type_traits>

namespace fires
{
  class Object;


  class PropertyAggregator
  {
  public:

    typedef enum
    {
      SUM = 0,
      MIN,
      MAX,
      MEAN
    } TAggregation;

    virtual ~PropertyAggregator( void )
    {
    }

    virtual void add( Object&, Object&,
                      const std::string& propertyLabel,
                      const std::string& destPropertyLabel,
                      TAggregation type = TAggregation::MAX ) = 0;

    virtual void divide( Object&, const std::string& propertyLabel,
                         unsigned int size ) = 0;

  };

  template < typename T, class Enable = void >
  class ScalarPropertyAggregator : public PropertyAggregator
  {
  public:

    virtual ~ScalarPropertyAggregator( void )
    {
    }

    virtual void add( Object& aggregatedObject, Object& objectToAggregator,
                      const std::string& propertyLabel,
                      const std::string& destPropertyLabel,
                      TAggregation type = TAggregation::MAX )
    {

      switch ( type )
      {
      case MAX:
        if ( objectToAggregator.getProperty( propertyLabel ).value< T >( ) >
             aggregatedObject.getProperty( destPropertyLabel ).value< T >( ))
          aggregatedObject.getProperty( destPropertyLabel ) =
            objectToAggregator.getProperty( propertyLabel );
            break;

      case MIN:
        if ( objectToAggregator.getProperty( propertyLabel ).value< T >( ) <
             aggregatedObject.getProperty( destPropertyLabel ).value< T >( ))
          aggregatedObject.getProperty( destPropertyLabel ) =
            objectToAggregator.getProperty( propertyLabel );
            break;

      case MEAN:
      case SUM:
        aggregatedObject.getProperty( destPropertyLabel ).set(
          T( objectToAggregator.getProperty( propertyLabel ).value< T >( )  +
             aggregatedObject.getProperty( destPropertyLabel ).value< T >( )));
            break;

      default:
        break;

      }

    }

    virtual void divide( Object& aggregatedObject,
                         const std::string& propertyLabel,
                         unsigned int size )
    {
      aggregatedObject.getProperty( propertyLabel ).set(
          T ( aggregatedObject.getProperty( propertyLabel ).value< T >( ) /
              float( size )));
    }

  };

  template < typename T >
  class ScalarPropertyAggregator
  < T, typename std::enable_if< std::is_enum< T >::value >::type >
    : public PropertyAggregator
  {
  public:

    virtual ~ScalarPropertyAggregator( void )
    {
    }

    virtual void add( Object& /* aggregatedObject */,
                      Object& /* objectToAggregator */,
                      const std::string& /* propertyLabel */,
                      const std::string& /* destPropertyLabel */,
                      TAggregation type = TAggregation::MAX )
    {
      ( void ) type;
    }

    virtual void divide( Object& aggregatedObject,
                         const std::string& propertyLabel,
                         unsigned int /* size */ )
    {
      aggregatedObject.getProperty( propertyLabel ).set( T( 0 ));
    }

  };

} //namespace fires

#endif
