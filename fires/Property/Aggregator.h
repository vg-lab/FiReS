/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/gmrvvis/FiReS>
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
