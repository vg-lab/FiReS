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

    virtual int toInt( Feature& ) = 0;


  };

  template < typename T >
  class ScalarFeatureCaster : public FeatureCaster
  {
  public:

    virtual ~ScalarFeatureCaster( void )
    {
    }

    virtual int toInt( Feature& feature )
    {
      return int( feature.value< T >( ));
    }

  };

} // namespace fires

#endif
