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
#include "SearchConfig.h"


namespace fires
{
  void SearchConfig::add( const std::string& label,
                          Comparer* comparer_,
                          Averager* averager_,
                          Normalizer* normalizer_,
                          float weight )
  {
    _propertiesConfig.insert(
      std::pair< std::string, QueryPropertyData >(
        label,
        QueryPropertyData( comparer_, averager_, normalizer_, weight )));
  }

} // namespace fires
