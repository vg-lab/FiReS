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
#ifndef __FIRES__SORT_H__
#define __FIRES__SORT_H__

#include "../Property/Property.h"
#include "Task.h"
#include "../Object/Objects.h"

namespace fires
{

  class Object;
  class Objects;

  class PropertySorter
  {
  public:
    virtual ~PropertySorter( void )
    {
    }

    virtual bool isLowerThan( Property&, Property& ) = 0;

    virtual bool isEqual( Property&, Property& ) = 0;

  };

  template < typename T >
  class ScalarPropertySorter : public PropertySorter
  {
  public:

    virtual ~ScalarPropertySorter( void )
    {
    }

    virtual bool isLowerThan( Property& f1, Property& f2 )
    {
      return  f1.value< T >( ) < f2.value< T >( );
    }

    virtual bool isEqual( Property& f1, Property& f2 )
    {
      return  f1.value< T >( ) == f2.value< T >( );
    }

  };

  template < typename T >
  class StringPropertySorter : public PropertySorter
  {
    public:

    virtual ~StringPropertySorter( void )
    {
    }

    virtual bool isLowerThan( Property& f1, Property& f2 )
    {
      return ( ( const std::string & ) f1.value< T >( )).compare(
        ( const std::string & ) f2.value<T>( )) < 0;
    }

    virtual bool isEqual( Property& f1, Property& f2 )
    {
      return ( ( std::string ) f1.value< T >( ) ) ==
        ( std::string ) f2.value< T >( );
    }

  };


  class SortConfig : public TaskConfig
  {

  public:

    typedef enum
    {
      ASCENDING = 0,
      DESCENDING
    } TSortOrder;

    typedef struct
    {
      std::string label;
      PropertySorter* sorter;
      TSortOrder order;
    } TSortProperty;
    typedef std::vector< TSortProperty > TSortProperties;
    FIRES_API SortConfig( void );
    FIRES_API virtual ~SortConfig( void );
    FIRES_API void addProperty( const std::string& propertyLabel_,
                                PropertySorter* sorter_,
                                TSortOrder order_ = ASCENDING );
    TSortProperties& properties( void ) { return _properties; }
    FIRES_API void clear( void );
    FIRES_API virtual bool operator( ) ( Object* obj1, Object* obj2 ) const;

  protected:

     TSortProperties _properties;

  };

  class Sort : public Task
  {

  public:

    FIRES_API virtual Objects& eval( Objects &objs, TaskConfig& config );

  };


} // namespace fires

#endif
