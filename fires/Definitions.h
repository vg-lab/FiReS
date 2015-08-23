#ifndef __DIRES__DEFINITIONS__
#define __DIRES__DEFINITIONS__


#ifdef FIRES_USE_VMMLIB
#include <vmmlib/vmmlib.hpp>
#endif

namespace fires
{

#ifdef FIRES_USE_VMMLIB
  // Define standard types
  template < size_t M = 0, typename T = int >
  using vector = vmml::vector< M, T>;

  typedef vmml::vector< 2, float > Vec2f;
  typedef vmml::vector< 3, float > Vec3f;
  typedef vmml::vector< 4, float > Vec4f;

  typedef vmml::vector< 2, int > Vec2i;
  typedef vmml::vector< 3, int > Vec3i;
  typedef vmml::vector< 4, int > Vec4i;

  typedef vmml::vector< 2, float* > Vec2pf;
  typedef vmml::vector< 3, float* > Vec3pf;
  typedef vmml::vector< 4, float* > Vec4pf;

  typedef vmml::vector< 2, int* > Vec2pi;
  typedef vmml::vector< 3, int* > Vec3pi;
  typedef vmml::vector< 4, int* > Vec4pi;
#endif

}


#endif
