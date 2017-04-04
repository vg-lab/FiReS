/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/gmrvvis/FiReS>
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
#include "firesTests.h"

using namespace fires;

class TestClass : public Object
{
public:

  TestClass( fires::Object* parent_ = 0, const std::string& prop_ = "" )
    : parentObject( parent_ )
    , parentProp( prop_ )
  {}

  void updateProperty( Object* obj, const std::string& prop )
  {
    BOOST_CHECK_EQUAL( this, obj );
    ++calls;
    this->setProperty( prop,
                       parentObject->getProperty( parentProp ).value< float >( )
                       * 2.0f );
  }
  fires::Object* parentObject;
  std::string parentProp;
  static unsigned int calls;
};

unsigned int TestClass::calls = 0;

BOOST_AUTO_TEST_CASE( test_dependencies )
{
  TestClass* o3 = new TestClass;
  TestClass* o2 = new TestClass( o3, "p3" );
  TestClass* o1 = new TestClass( o2, "p2" );

  o1->registerProperty( "p1", .0f );
  o2->registerProperty( "p2", .0f );
  o3->registerProperty( "p3", .0f );

  DependenciesManager::addDependency( o1, "p1", o2, "p2" );
  DependenciesManager::addDependency( o2, "p2", o3, "p3" );
  DependenciesManager::setUpdater( o1, "p1",
                                   o1, &TestClass::updateProperty );
  DependenciesManager::setUpdater( o2, "p2",
                                   o2, &TestClass::updateProperty );

  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o1, "p1" ), false );
  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o2, "p2" ), false );
  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o3, "p3" ), false );

  o3->setProperty( "p3", 2.0f );

  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o1, "p1" ), true );
  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o2, "p2" ), true );
  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o3, "p3" ), false );

  o1->getProperty( "p1" );

  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o1, "p1" ), false );
  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o2, "p2" ), false );
  BOOST_CHECK_EQUAL( DependenciesManager::getDirtiness( o3, "p3" ), false );

  BOOST_CHECK_EQUAL( o1->getProperty( "p1" ).value< float >( ), 8.0f );
  BOOST_CHECK_EQUAL( o2->getProperty( "p2" ).value< float >( ), 4.0f );
  BOOST_CHECK_EQUAL( o3->getProperty( "p3" ).value< float >( ), 2.0f );
  BOOST_CHECK_EQUAL( TestClass::calls, 2 );

  delete o2;
  o3->setProperty( "p3", 2.0f );
  o1->getProperty( "p1" );
  BOOST_CHECK_EQUAL( TestClass::calls, 2 );

}
