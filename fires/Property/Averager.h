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
#ifndef __FIRES_AVERAGER_H__
#define __FIRES_AVERAGER_H__

#include "Property.h"


namespace fires
{

  /*! \class Averager

    This class serves as a tool for averaging properties
   */

  class Averager
  {
  public:
    FIRES_API
    virtual ~Averager( )
    {
    }

    FIRES_API
    virtual void accum( const Property& /* f1 */ ) = 0;

    FIRES_API
    virtual void divide( const unsigned int /* f1 */ ) = 0;

    FIRES_API
    virtual void reset( void ) = 0;

    // Altough this method should be const then property constructed as
    // const and breaks
    FIRES_API
    virtual Property property( void ) = 0;
  };


  /*! \class ScalarAverager

    This class serves as a tool for averaging scalar properties
   */
  template < typename T >
  class ScalarAverager : public Averager
  {
  public:

    ScalarAverager( T resetValue_ = ( T ) 0 )
      : _resetValue( resetValue_ )
    {
    }

    virtual ~ScalarAverager( )
    {
    }

    virtual void accum( const Property& property_ )
    {
      _accumValue += property_.value< T >( );
    }

    virtual void divide( const unsigned int value )
    {
      _accumValue /= value;
    }

    virtual void reset( void )
    {
      _accumValue = _resetValue;
    }

    virtual Property property( void )
    {
      return Property( _accumValue );
    }

  protected:

    T _resetValue;
    T _accumValue;

  };


  /*! \class ScalarAverager

    Template specialization for averaging properties holding pointer to scalars.
   */
  template < typename T >
  class ScalarAverager< T* >
    : public ScalarAverager< T >
  {
  public:

    ScalarAverager( T resetValue_ = ( T ) 0 )
      : ScalarAverager< T >( resetValue_ )
    {
    }

    virtual ~ScalarAverager( )
    {
    }

    virtual void accum( const Property& property_ )
    {
      this->_accumValue += *property_.value< T* >( );
    }

    virtual Property property( void )
    {
      return Property( &this->_accumValue );
    }

  };

// #ifdef FIRES_USE_VMMLIB

//   template < class V, size_t M, typename T >
//   class VectorAverager
//     : public ScalarAverager< vmml::vector< M, T >>
//   {
//   public:
//     VectorAverager( )
//       : ScalarAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
//     {
//     }

//   };

//   template < class V, size_t M, typename T >
//   class VectorAverager< V*, M, T >
//     : public ScalarAverager< vmml::vector< M, T >* >
//   {
//   public:
//     VectorAverager( )
//       : ScalarAverager< vmml::vector< M, T >* >( vmml::vector< M, T >::ZERO )
//     {
//     }

//   };



//   template < class V, size_t M, typename T >
//   class VectorAverager< V, M, T* >
//     : public ScalarAverager< vmml::vector< M, T >>
//   {
//   public:
//     VectorAverager( )
//       : ScalarAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
//     {
//     }


//     virtual void accum( const Property& property_ )
//     {
//       vector< M, T > v;
//       vector< M, T * > vp = property_.value< vector< M, T* >>( );
//       for ( unsigned int i = 0; i < M ; i++ )
//         v( i ) = *vp( i );

//       this->_accumValue += v;
//     }


//     virtual Property property( void )
//     {

//       vector<M, T* > _vector;

//       for ( unsigned int i = 0; i < M ; i++ )
//       {
//         _vectorValues[ i ] = this->_accumValue( i );
//         _vector( i ) = &_vectorValues[ i ];
//       }

//       return Property( _vector );
//     }

//   protected:

//     T _vectorValues[ M ];


//   };

//   template < class V, size_t M, typename T >
//   class VectorAverager< V*, M, T* >
//     : public ScalarAverager< vmml::vector< M, T >>
//   {
//   public:
//     VectorAverager( )
//       : ScalarAverager< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
//     {
//     }


//     virtual void accum( const Property& property_ )
//     {

//       property_.value< vector< M, T* >* >( );
//       vector< M, T > v;
//       vector< M, T* > vp = *( property_.value< vector< M, T* >* >( ));
//       for ( unsigned int i = 0; i < M ; i++ )
//         v( i ) = *vp( i );

//       this->_accumValue += v;
//     }


//     virtual Property property( void )
//     {
//       for ( unsigned int i = 0; i < M ; i++ )
//       {
//         _vectorValues[ i ] = this->_accumValue( i );
//         _vector( i ) = &_vectorValues[ i ];
//       }

//       return Property( &_vector );
//     }

//   protected:

//     T _vectorValues[ M ];
//     vector<M, T* > _vector;

//   };



// #endif

} // namespace fires


#endif
