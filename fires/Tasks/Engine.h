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
#ifndef __FIRES__ENGINE_H__
#define __FIRES__ENGINE_H__

#include <fires/api.h>
#include "../Object/Objects.h"
#include "Task.h"

namespace fires
{

  /*! \class Engine
    \brief FiReS engine

    Provides the entry point for objects, comparers and results
  */
  class Engine
  {

  public:

    /**
     * Default destructor
     **/
    FIRES_API
    virtual ~Engine( );


    FIRES_API
    virtual void run( Objects& objects, Tasks& tasks );

  };


}

#endif
