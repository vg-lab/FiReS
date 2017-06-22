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
#ifndef __FIRES__SLICE_H__
#define __FIRES__SLICE_H__

#include "../Property/Property.h"
#include "Task.h"
#include "../Object/Objects.h"

namespace fires
{


  class SliceConfig : public TaskConfig
  {

  public:

    typedef struct
    {
      std::string label;
      // If categorical slicing this vector holds the categories idxs
      std::vector< int > categoriesIdxs;
      // If numerical-based slicing this vector holds the cutting points
      std::vector< float > cuts;
    } TSliceConfig;

    TSliceConfig& config( void ) { return _config; };
    const TSliceConfig& config( void ) const { return _config; };
  protected:

    TSliceConfig _config;

  };

  class Slice : public Task
  {

  public:

    FIRES_API virtual Objects& eval( Objects &objs, TaskConfig& config );
    FIRES_API virtual void eval( GroupsOfObjects &groups, TaskConfig &config );

  };


} // namespace fires

#endif
