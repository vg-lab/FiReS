/*
 * Copyright (c) 2014-2016 VG-Lab/URJC/UPM.
 *
 * Authors: Pablo Toharia <pablo.toharia@upm.es>
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
#include <fires/fires.h>

int main ( void )
{
  class MyClass : public fires::Object
  {
  public:
    FIRES_OBSERVER_CALLBACK( observerCallback, notifier, propertyLabel )
    {
      std::cout << label( ) << ": Hey!" << " object " << notifier->label( )
                << " updated " << propertyLabel << " to "
                << notifier->getProperty( "p1" ).value< int >( ) << std::endl;
    }
  };

  class AnotherClass
  {
  public:
    FIRES_OBSERVER_CALLBACK( observerCallback, notifier, propertyLabel )
    {
      std::cout << "I am not a FiReS object! Hey!" << " object "
                << notifier->label( ) << " updated " << propertyLabel << " to "
                << notifier->getProperty( "p1" ).value< int >( ) << std::endl;
    }
  };


  MyClass* o1 = new MyClass;
  MyClass* o2 = new MyClass;
  o1->label( ) = "o1";
  o2->label( ) = "o2";
  o1->registerProperty( "p1", 1 );
  o1->registerProperty( "p2", 6 );
  AnotherClass ac;

  fires::ObserverManager::addObserver( o1, "p1", o2,
                                       &MyClass::observerCallback );
  fires::ObserverManager::addObserver( o1, "p1", &ac,
                                       &AnotherClass::observerCallback );
  fires::ObserverManager::addObserver( o1, FIRES_ANY, &ac,
                                       &AnotherClass::observerCallback );

  // Modifying property triggers callbacks
  o1->setProperty( "p1", 2 );

  // output:
  // o2: Hey! object o1 updated p1 to 2
  // I am not a FiReS object! Hey! object o1 updated p1 to 2
  // I am not a FiReS object! Hey! object o1 updated fires::any to 2

  fires::ObserverManager::removeObserver( &ac );
  o1->setProperty( "p1", 3 );

  // output:
  // o2: Hey! object o1 updated p1 to 3

  delete o2;
  o1->setProperty( "p1", 4 );

  // output:
  // none

}
