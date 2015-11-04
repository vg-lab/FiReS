/**
 * @file    PropertyCaster.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__PROPERTYCASTER_H__
#define __FIRES__PROPERTYCASTER_H__

#include "Property.h"
#include <sstream>

namespace fires
{

  class PropertyCaster
  {
  public:

    virtual ~PropertyCaster( void )
    {
    }

    typedef enum
    {
      ROUND = 0,
      CEIL,
      FLOOR
    } TIntCasting;

    virtual int toInt( const Property&, TIntCasting casting = ROUND ) = 0;
    virtual std::string toString( const Property& property ) = 0;

  };

  template < typename T >
  class ScalarPropertyCaster : public PropertyCaster
  {
  public:

    virtual ~ScalarPropertyCaster( void )
    {
    }

    virtual int toInt( const Property& property, TIntCasting casting = ROUND )
    {
      switch ( casting )
      {
      case ROUND:
        return int( round( property.value< T >( )));
        break;
      case CEIL:
        return int( ceil( property.value< T >( )));
        break;
      case FLOOR:
        return int( floor( property.value< T >( )));
        break;
      default:
        throw std::runtime_error( "Invalid casting type" );
      }
    }

    virtual std::string toString( const Property& property )
    {
      std::ostringstream iss;
      iss << property.value< T >( );
      return std::string( iss.str( ));
    }
  };

} // namespace fires

#endif
