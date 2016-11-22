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
#include "PropertyManager.h"

namespace fires
{

  std::map< std::string, PropertyManager::TPropertyInfo >
  PropertyManager::_properties =
    std::map< std::string, PropertyManager::TPropertyInfo >( );

  std::map< std::type_index, PropertySorter* >
  PropertyManager::_sorters =
    std::map< std::type_index, PropertySorter* >( );

  std::map< std::type_index, PropertyAggregator* >
  PropertyManager::_aggregators =
    std::map< std::type_index, PropertyAggregator* >( );

  std::map< std::type_index, PropertyCaster* >
  PropertyManager::_casters =
    std::map< std::type_index, PropertyCaster* >( );


}
