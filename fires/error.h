/**
 * @file    error.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __FIRES_ERROR__
#define __FIRES_ERROR__

#include <stdexcept>

#define FIRES_LOG( msg )                                          \
  std::cerr << "fires "                                           \
  << __FILE__ << "("                                             \
  << __LINE__ << "): "                                           \
  << msg << std::endl;

#define FIRES_THROW( msg )                                        \
  {                                                              \
    FIRES_LOG( msg );                                             \
    throw std::runtime_error( msg );                             \
  }

#define FIRES_CHECK_THROW( cond, errorMsg )                       \
    {                                                            \
      if ( ! (cond) ) FIRES_THROW( errorMsg );                    \
    }

#ifndef NDEBUG
  #define FIRES_DEBUG_CHECK( cond, errorMsg )                     \
{                                                                \
  FIRES_CHECK_THROW( cond, errorMsg )                             \
}
#else
  #define FIRES_DEBUG_CHECK( cond, errorMsg )
#endif


#endif // __FIRES_ERROR__
