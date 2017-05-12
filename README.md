[![build status](https://gitlab.gmrv.es/retrieval/FiReS/badges/master/build.svg)](https://gitlab.gmrv.es/retrieval/FiReS/commits/master)
[![coverage report](https://gitlab.gmrv.es/retrieval/FiReS/badges/master/coverage.svg)](https://gitlab.gmrv.es/retrieval/FiReS/commits/master)

# FiReS - property management for Filtering, Retrieval and Search
(c) 2015. GMRV / URJC

www.gmrv.es
gmrv@gmrv.es

## Introduction

FiReS is a library that allow registering type-independent properties in
objects. FiReS also provides tasks that can use the registered properties for
filtering, search, sorting operations over a set of objects.

## Dependencies

Boost.Any is the only required dependency. OpenMP and Boost's Unit
Test Framework are optional.

## Building

FiReS has been succesfully built and used on Ubuntu 16.04, Mac OSX
Yosemite and Windows 7/8/10 (Visual Studio 2013 Win64). The following steps
should be enough to build it:

```bash
git clone https://github.com/gmrvvis/FiReS.git
mkdir FiReS/build && cd FiReS/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## How to use it

### Registering properties
```c++
class MyClass : public fires::Object
{
};
...
MyClass myObject;
myObject.registerProperty( "property1", 3.0f );
myObject.registerProperty( "property2", int( 2 ));
```

### Retrieving properties
```c++
float v1 = myObject.getProperty( "property1" ).value( );
int v2 = myObject.getProperty( "property2" ).value( );
```

### Creating notifier/observer
```c++
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
...
MyClass o1, o2;
o1.label( ) = "o1";
o2.label( ) = "o2";
o1.registerProperty( "p1", 1 );
fires::ObserverManager::addObserver( &o1, "p1", &o2, &MyClass::observerCallback );
o1.setProperty( "p1", 2 );
// output:
// o2: Hey! object o1 updated p1
```

### Sorting
```c++
class MyClass : public fires::Object
{
};

int main ( )
{

  MyClass o1, o2, o3, o4;

  fires::Sort sorter;
  fires::SortConfig sortConfig;
  fires::ScalarPropertySorter< float > sfsf;
  fires::Objects objs;

  // Register property
  o1.registerProperty( "p1", 3.1f );
  o2.registerProperty( "p1", 4.1f );
  o3.registerProperty( "p1", 1.2f );
  o4.registerProperty( "p1", 3.1f );

  // Create the objects container
  objs.addList( { &o1, &o2, &o3, &o4 } );

  // Configure sort config
  sortConfig.addProperty( "p1", &sfsf );

  // Eval the task
  sorter.eval( objs, sortConfig );
}
```
