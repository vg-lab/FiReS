/**
 * @file    FeatureCaster.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__FEATURECASTER_H__
#define __FIRES__FEATURECASTER_H__

#include "Feature.h"

namespace fires
{

  class FeatureCaster
  {
  public:

    virtual ~FeatureCaster( void )
    {
    }

    typedef enum
    {
      ROUND = 0,
      CEIL,
      FLOOR
    } TIntCasting;

    virtual int toInt( Feature&, TIntCasting casting = ROUND ) = 0;


  };

  template < typename T >
  class ScalarFeatureCaster : public FeatureCaster
  {
  public:

    virtual ~ScalarFeatureCaster( void )
    {
    }

    virtual int toInt( Feature& feature, TIntCasting casting = ROUND )
    {
      switch ( casting )
      {
      case ROUND:
        return int( round( feature.value< T >( )));
        break;
      case CEIL:
        return int( ceil( feature.value< T >( )));
        break;
      case FLOOR:
        return int( floor( feature.value< T >( )));
        break;
      default:
        throw std::runtime_error( "Invalid casting type" );
      }
    }

  };

} // namespace fires

#endif
