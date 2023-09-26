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
#include "Log.h"

#include <string>
#include <iostream>

#include <fires/defines.h>


namespace fires
{

  TLogLevel Log::_logLevel =
#ifdef _DEBUG
    LOG_LEVEL_VERBOSE;
#else
    LOG_LEVEL_ERROR;
#endif

  std::ostream* Log::_stream = &std::cerr;


  TLogLevel Log::logLevel( void )
  {
    return _logLevel;
  }

  void Log::setLogLevel( const TLogLevel logLevel_ )
  {
    _logLevel = logLevel_;
  }

  void Log::setStream( std::ostream& stream_ )
  {
    _stream = &stream_;
  }

  const std::ostream& Log::stream( void )
  {
    return *_stream;
  }

#ifdef FIRES_WITH_LOGGING

  void Log::log( const std::string& msg,
                 const TLogLevel level )
  {
    Log::log( msg, *_stream, level );
  }

  TLogLevel stringToLogLevel( std::string logLevelString )
  {
  if ( logLevelString == "WARNING" )
    return LOG_LEVEL_WARNING;

  if ( logLevelString == "ERROR" )
    return LOG_LEVEL_ERROR;

  if ( logLevelString == "VERBOSE" )
    return LOG_LEVEL_VERBOSE;

  std::cerr << "fires: Unknown log level" << std::endl;
  return LOG_LEVEL_UNKNOWN;
}


  void Log::log( const std::string& msg,
                 std::ostream& stream,
                 const TLogLevel level )
  {
    TLogLevel currentLogLevel = _logLevel;

    char* envLogLevelString = getenv ( "FIRES_LOG_LEVEL" );

    if ( envLogLevelString )
    {
      auto envLogLevel = stringToLogLevel( envLogLevelString );

      if ( envLogLevel != LOG_LEVEL_UNKNOWN )
        currentLogLevel = envLogLevel;
    }

    if ( currentLogLevel >= level )
    {
      stream << std::boolalpha
             << msg << std::endl;
    }
  }


#else
  void Log::log( const std::string&,
                 std::ostream&,
                 const TLogLevel )
  {
  }

  void Log::log( const std::string&,
                 const TLogLevel )
  {
  }
#endif



} // namespace fires
