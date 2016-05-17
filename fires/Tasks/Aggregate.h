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

    void clearAggregatedObject( void )
    {
      return _aggregatedObject.clearProperties( );
    }

    void clearProperties( void )
    {
      return _properties.clear( );
    }

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
