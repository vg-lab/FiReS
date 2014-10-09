/**
 * @file    Comparer.cpp
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "Comparer.h"

#include <iostream>
#include <math.h>

namespace fires
{

  float Comparer::distance(Feature *f1, Feature *f2)
  {
    std::cerr << "No distance function provided "
	      << "in the comparer. Returning 0." 
	      << std::endl;
    return 0.0f;
  }

}


