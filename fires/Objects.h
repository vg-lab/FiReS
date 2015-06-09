/**
 * @file    Objects.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__OBJECTS_H__
#define __FIRES__OBJECTS_H__

#include "Object.h"
#include <vector>

namespace fires
{
  /*! \class System::Objects
    \brief Container of objects

    Simple class to hold a set of objects
  */
  class Objects : public std::vector<Object* >
  {

  public:
    /**
     * Add an object to the container
     * @param object pointer to the object to be added
     */
    FIRES_API
    void add( Object* object );

    FIRES_API
    void del( Object* object );

  }; // class Objects

} // namespace fires

#endif
