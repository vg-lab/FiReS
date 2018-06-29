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
#include "../Property/Aggregator.h"
#include "Task.h"


namespace fires
{

  class AggregateConfig : public TaskConfig
  {

  public:

    typedef struct
    {
      std::string label;
      std::string destLabel;
      PropertyAggregator* aggregate;
      PropertyAggregator::TAggregation type;
    } TAggregatorProperty;


    AggregateConfig( void )
    {
    }

    virtual ~AggregateConfig( void )
    {
    }

    void addProperty( const std::string& propertyLabel_,
                      PropertyAggregator* aggregator_,
                      PropertyAggregator::TAggregation type_ =
                      PropertyAggregator::MAX,
                      const std::string& destPropertyLabel_ = "" )
    {
      _properties.push_back(
        TAggregatorProperty
        {
          propertyLabel_, destPropertyLabel_,
          aggregator_, type_
        });
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

      const auto& properties = aggregateConfig->properties( );

      aggregatedObj.label( ) = "aggregated";

      for ( auto obj = objs.begin( ); obj != objs.end( ); ++obj )
      {
        for ( auto f = properties.begin( ); f != properties.end( ); ++f )
        {
          const std::string& label = ( *f ).label;
          const std::string& destLabel =
            (( *f ).destLabel.empty( ) ? label : ( *f ).destLabel);

          if ( !( *obj )->hasProperty( label ))
            continue;

          if ( !aggregatedObj.hasProperty( destLabel ))
          {
            aggregatedObj.registerProperty( destLabel, ( *obj )->getProperty( label ));
          }
          else
          {
            ( *f ).aggregate->add( aggregatedObj, **obj, label, destLabel, ( *f ).type );
          }
        }
      }

      for ( auto f = properties.begin( ); f != properties.end( ); ++f )
      {
        if (( *f ).type == PropertyAggregator::MEAN )
        {
          const std::string& label = ( *f ).label;
          const std::string& destLabel =
            (( *f ).destLabel.empty( ) ? label : ( *f ).destLabel);
          ( *f ).aggregate->divide( aggregatedObj, destLabel,
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
