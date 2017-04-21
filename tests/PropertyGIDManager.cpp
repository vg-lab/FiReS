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

BOOST_AUTO_TEST_CASE( test_property_gids )
{
  std::string p1Label( "p1" );
  auto p1Gid = fires::PropertyGIDsManager::getPropertyGID( p1Label );
  BOOST_CHECK_EQUAL( p1Gid,
                     fires::PropertyGIDsManager::getPropertyGID( p1Label ));
  BOOST_CHECK_EQUAL( fires::PropertyGIDsManager::getPropertyLabel( p1Gid ),
                     p1Label );

  std::string p2Label( "p2" );
  auto p2Gid = fires::PropertyGIDsManager::getPropertyGID( p2Label );
  BOOST_CHECK_EQUAL( p1Gid,
                     fires::PropertyGIDsManager::getPropertyGID( p1Label ));
  BOOST_CHECK_EQUAL( fires::PropertyGIDsManager::getPropertyLabel( p1Gid ),
                     p1Label );
  BOOST_CHECK_EQUAL( p2Gid,
                     fires::PropertyGIDsManager::getPropertyGID( p2Label ));
  BOOST_CHECK_EQUAL( fires::PropertyGIDsManager::getPropertyLabel( p2Gid ),
                     p2Label );

  BOOST_CHECK( p1Gid != p2Gid );

}
