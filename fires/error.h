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
#ifndef __FIRES__ERROR__
#define __FIRES__ERROR__

#include <stdexcept>

namespace fires
{
  typedef std::runtime_error exception;
}

#define FIRES_THROW( msg )                                        \
  {                                                               \
    Log::log( msg, LOG_LEVEL_ERROR );                             \
    throw std::runtime_error( msg );                              \
  }

#define FIRES_CHECK_THROW( cond, errorMsg )                       \
    {                                                             \
      if ( ! (cond) ) FIRES_THROW( errorMsg );                    \
    }

#ifndef NDEBUG
  #define FIRES_DEBUG_CHECK( cond, errorMsg )                     \
{                                                                 \
  FIRES_CHECK_THROW( cond, errorMsg )                             \
}
#else
  #define FIRES_DEBUG_CHECK( cond, errorMsg )
#endif


#endif // __FIRES_ERROR__
