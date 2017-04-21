/*
 * Copyright (c) 2014-2016 GMRV/URJC/UPM.
 *
 * Authors: Pablo Toharia <pablo.toharia@upm.es>
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

class Point : public fires::Object
{
public:
  Point( )
  {
    this->registerProperty( "x", 0.0f );
    this->registerProperty( "y", 0.0f );
  }
};

class Edge : public fires::Object
{
public:
  Edge( )
  {
    this->registerProperty( "length", 0.0f );
    fires::DependenciesManager::addDependency( this, "length",
                                               &points[0], "x" );
    fires::DependenciesManager::addDependency( this, "length",
                                               &points[0], "y" );
    fires::DependenciesManager::addDependency( this, "length",
                                               &points[1], "x" );
    fires::DependenciesManager::addDependency( this, "length",
                                               &points[1], "y" );
    fires::DependenciesManager::setUpdater( this, "length",
                                            this, &Edge::computeLength );
  }

  void computeLength( fires::Object*, const std::string& )
  {
    this->setProperty(
      "length", sqrtf(
        powf( points[1].getProperty( "x" ).value< float >( ) -
              points[0].getProperty( "x" ).value< float >( ), 2 ) +
        powf( points[1].getProperty( "y" ).value< float >( ) -
              points[0].getProperty( "y" ).value< float >( ), 2 )));
    std::cout << "[ Edge: updated length ]" << std::endl;
  }

  Point points[2];
};

class Rectangle :  public fires::Object
{
public:
  Rectangle( )
  {
    this->registerProperty( "area", 0.0f );
    fires::DependenciesManager::addDependency( this, "area",
                                               &edges[0], "length" );
    fires::DependenciesManager::addDependency( this, "area",
                                               &edges[1], "length" );
    fires::DependenciesManager::setUpdater( this, "area",
                                            this, &Rectangle::computeArea );
  }

  void computeArea( fires::Object*, const std::string& )
  {
    this->setProperty( "area",
                       edges[0].getProperty( "length" ).value< float >( ) *
                       edges[1].getProperty( "length" ).value< float >( ));
    std::cout << "[ Rectangle: updated area ]" << std::endl;
  }

  Edge edges[2];
};

int main( void )
{

  Rectangle rect;

  rect.edges[0].points[0].setProperty( "x", 1.0f );
  rect.edges[0].points[0].setProperty( "y", 1.0f );
  rect.edges[0].points[1].setProperty( "x", 1.0f );
  rect.edges[0].points[1].setProperty( "y", 2.0f );
  rect.edges[1].points[0].setProperty( "x", 1.0f );
  rect.edges[1].points[0].setProperty( "y", 1.0f );
  rect.edges[1].points[1].setProperty( "x", 3.0f );
  rect.edges[1].points[1].setProperty( "y", 1.0f );

  std::cout << "Requesting area for the first time" << std::endl;
  std::cout << rect.getProperty( "area" ).value< float >( ) << std::endl;
  // output:
  // [ Rectangle: updating area ]
  // [ Edge: updating length ]
  // [ Edge: updating length ]
  // 2

  std::cout << std::endl << "Setting one dependency" << std::endl;
  rect.edges[0].points[1].setProperty( "y", 4.0f );

  std::cout << std::endl << "Requesting for area needs updating dirty deps"
            << std::endl;
  std::cout << rect.getProperty( "area" ).value< float >( ) << std::endl;
  // [ Rectangle: updating area ]
  // [ Edge: updating length ]
  // 6

  std::cout << std::endl << "Requesting for area with no update needed"
            << std::endl;
  std::cout << rect.getProperty( "area" ).value< float >( ) << std::endl;
  // output:
  // 6

  return 0;
}
