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
#ifndef __FIRES__SEARCH_H__
#define __FIRES__SEARCH_H__


#include "../Property/Comparer.h"
#include "../Object/Object.h"
#include "../Object/Objects.h"
#include "SearchConfig.h"
#include "Task.h"

#include <vector>
#include <map>


namespace fires
{

  /*! \class Search
    \brief FiReS search

  */
  class Search : public Task
  {

  public:

    /**
     * Default destructor
     **/
    FIRES_API
    virtual ~Search( );

    FIRES_API
    virtual Objects& eval( Objects &objs, TaskConfig& config );


  protected:

    FIRES_API
    float _distanceBetweenTwoObjects( Object* obj1, Object* obj2,
                                      SearchConfig& config );
    FIRES_API
    virtual void _computeAverageQueryObject( Object& avgObj,
                                             Objects& queryObjects,
                                             SearchConfig& config );

  };


}

#endif
