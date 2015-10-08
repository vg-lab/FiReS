/**
 * @file    Search.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__SEARCH_H__
#define __FIRES__SEARCH_H__


#include "../Property/Comparer.h"
#include "../Object/Object.h"
#include "../Object/Objects.h"
#include "SearchConfig.h"
#include "Task.h"

#include <vector>
#include <map>


namespace fires
{

  /*! \class Search
    \brief FiReS search

  */
  class Search : public Task
  {

  public:

    /**
     * Default destructor
     **/
    FIRES_API
    virtual ~Search( );

    FIRES_API
    virtual Objects& eval( Objects &objs, TaskConfig& config );


  protected:

    FIRES_API
    float _distanceBetweenTwoObjects( Object* obj1, Object* obj2,
                                      SearchConfig& config );
    FIRES_API
    virtual void _computeAverageQueryObject( Object& avgObj,
                                             Objects& queryObjects,
                                             SearchConfig& config );

  };


}

#endif
