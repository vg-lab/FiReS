#include "Objects.h"


namespace fires
{

  void Objects::add( Object* object )
  {
    this->push_back(object);
  }

  void Objects::del( Object* object )
  {
    //TODO: check if this is the best way to do it
    auto newEnd = std::remove( this->begin( ), this->end( ), object );
    this->erase( newEnd, this->end( ));
  }


} // namespace fires
