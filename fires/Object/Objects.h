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
#ifndef __FIRES__OBJECTS_H__
#define __FIRES__OBJECTS_H__

#include "Object.h"
#include <vector>

namespace fires
{
  class Object;
  /**
   * Simple class used as a container of objects based on std::vector
   *
   */
  class Objects : public std::vector< Object* >
  {

  public:
    /**
     * Add an object to the container
     * @param object pointer to the object to be added
     */
    FIRES_API
    void add( Object* object );

    FIRES_API
    void del( Object* object );

    FIRES_API
    void addList( std::initializer_list<Object*> objects );

    FIRES_API
    void clearAdds( std::initializer_list<Object*> objects );

  }; // class Objects

} // namespace fires

#endif
