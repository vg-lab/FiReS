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
#ifndef __FIRES_TASK_H__
#define __FIRES_TASK_H__

#include <vector>
#include "../Object/Objects.h"

namespace fires
{

  class Objects;

  class TaskConfig
  {

  };

  class Task
  {
  public:

    virtual ~Task( void )
    {
    }

    virtual Objects& eval( Objects &objs, TaskConfig &config ) = 0;

  };

  class TasksConfig
  {

  public:

    TasksConfig( Task* task_, TaskConfig* config_ )
      : _task( task_ ), _config( config_ )
    {
    }

    virtual ~TasksConfig( void )
    {
    }

    Task* task( void )
    {
      return _task;
    }

    TaskConfig* config( void )
    {
      return _config;
    }

  protected:
    Task* _task;
    TaskConfig* _config;
  };

  typedef std::vector< TasksConfig > Tasks;

} // namespace fires

#endif
