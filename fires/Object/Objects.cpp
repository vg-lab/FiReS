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
#include "Objects.h"

namespace fires
{

  void Objects::add( Object* object )
  {
    this->push_back(object);
  }

  void Objects::del( Object* object )
  {
    auto newEnd = std::remove( this->begin( ), this->end( ), object );
    this->erase( newEnd, this->end( ));
  }
  
  void Objects::addList( std::initializer_list<Object*> objects )
  {
    for ( auto obj: objects )
    {
      this->push_back(obj);
    }
  }
  
  void Objects::clearAdds( std::initializer_list<Object*> objects )
  {
    this->clear( );
    for ( auto obj: objects )
    {
      this->push_back(obj);
    }
  }


} // namespace fires
