/**
 * @file    Task.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_TASK_H__
#define __FIRES_TASK_H__

#include <vector>
#include "Objects.h"

namespace fires
{

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
