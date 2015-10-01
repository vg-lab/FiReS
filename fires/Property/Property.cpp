/**
 * @file    Property.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include "Property.h"

namespace fires
{


  Property::Property( void )
    : _value( )
  {
  }

  Property::~Property( void )
  {
  }

  std::string Property::type( void ) const
  {
    return _value.type( ).name( );
  }

  bool Property::empty( void ) const
  {
    return _value.empty( );
  }



} // namespace fires
