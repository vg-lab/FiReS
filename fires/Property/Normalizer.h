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
#ifndef __FIRES_NORMALIZER_H__
#define __FIRES_NORMALIZER_H__

#include "Property.h"

#include <map>


namespace fires
{

  /*! \class Normalizer

   */
  class Normalizer
  {
  public:
    FIRES_API
    virtual ~Normalizer( )
    {
    }

    FIRES_API
    virtual void reset( const std::string& label ) = 0;

    FIRES_API
    virtual void update( const std::string& label,
                         const Property& property_ ) = 0;

    FIRES_API
    virtual Property normalizeProperty( const std::string& /* label */,
                                      const Property& property_ ) const
    {
      return property_;
    }

    FIRES_API
    virtual float normalizeDistance( const float distance )
    {
      return distance;
    }

    FIRES_API
    virtual void freeNormalizedProperty( Property& /* property_ */ ) { };
  };


  template < typename T >
  class ScalarNormalizer : public Normalizer
  {
  public:

    ScalarNormalizer( void )
    {
    }

    virtual void reset( const std::string& label )
    {
      _minValue[ label ] = std::numeric_limits< T >::max( );
      _maxValue[ label ] = std::numeric_limits< T >::min( );
    }

    virtual ~ScalarNormalizer( )
    {
    }

    virtual void update( const std::string &label_,
                         const Property& property_ )
    {
      if ( property_.value< T >( ) < _minValue[ label_ ] )
        _minValue[ label_ ] = property_.value< T >( );
      if (  property_.value< T >( ) > _maxValue[ label_ ] )
        _maxValue[ label_ ] = property_.value< T >( );

      // std::cout << property_.value< T >( ) << std::endl;
      // std::cout << "New accum values " << _minValue[ label_ ] << " " << _maxValue[ label_ ] << std::endl;

    }

    virtual Property normalizeProperty( const std::string& label_,
                                      const Property& property_ ) const
    {
      // std::cout <<  "Normalize " << std::endl << property_.value< T >( ) << " " <<  _minValue.at( label_ ) << " "
      //           <<  _maxValue.at( label_ ) << std::endl
      //           <<  ( property_.value< T >( ) - _minValue.at( label_ )) /
      //                ( _maxValue.at( label_ ) - _minValue.at( label_ ))
      //           << std::endl;
      return Property(( property_.value< T >( ) - _minValue.at( label_ )) /
                     ( _maxValue.at( label_ ) - _minValue.at( label_ )));
    }

  protected:

    std::map< std::string, T > _minValue;
    std::map< std::string, T > _maxValue;

  };


  template < typename T >
  class ScalarNormalizer< T* >
    : public ScalarNormalizer< T >
  {
  public:

    ScalarNormalizer( void )
      : ScalarNormalizer< T >( )
    {
    }

    virtual ~ScalarNormalizer( )
    {
    }

    virtual void update( const std::string& label_,
                         const Property& property_ )
    {
      if ( *property_.value< T* >( ) < this->_minValue[ label_ ] )
        this->_minValue[ label_ ] = *property_.value< T* >( );
      if (  *property_.value< T* >( ) > this->_maxValue[ label_ ] )
        this->_maxValue[ label_ ] = *property_.value< T* >( );

      // std::cout << property_.value< T >( ) << std::endl;
      // std::cout << "New accum values " << _minValue << " " << _maxValue << std::endl;

    }

    virtual Property normalizeProperty( const std::string& label_,
                                      const Property& property_ ) const
    {
      // std::cout <<  *property_.value< T* >( ) << " " <<  this->_minValue << " "
      //           <<  this->_maxValue << " "  << this->_minValue   << std::endl;
      return Property(
        new T(( *property_.value< T* >( ) - this->_minValue.at( label_ )) /
              ( this->_maxValue.at( label_ ) - this->_minValue.at( label_ ))));
    }

    virtual void freeNormalizedProperty( Property& property_ )
    {
      delete property_.value< T* >( );
    }

  };

  #ifdef FIRES_USE_VMMLIB

  template < class V, size_t M, typename T >
  class VectorNormalizer
    : public ScalarNormalizer< vmml::vector< M, T >>
  {
  public:
    VectorNormalizer( )
      : ScalarNormalizer< vmml::vector< M, T >>( )
    {
    }

    virtual void reset( const std::string& label_ )
    {
      this->_minValue[ label_ ] =
        vmml::vector< M, T >( std::numeric_limits< T >::max( ));
      this->_maxValue[ label_ ] =
        vmml::vector< M, T >( std::numeric_limits< T >::min( ));
    }

    virtual void update( const std::string& label_,
                         const Property& property_ )
    {
      // std::cout << "update vector" << std::endl;
      this->_update( label_, property_.value< vector< M, T >>( ));
    }

    virtual float normalizeDistance( const float distance )
    {
      return distance / sqrt( M );
    }


  protected:
    void _update( const std::string& label_,
                  const vector< M, T >& v )
    {
      for ( unsigned int idx = 0; idx < M; idx++ )
      {
        if ( v[ idx ] < this->_minValue[ label_ ][ idx ] )
          this->_minValue[ label_ ][ idx ] = v[ idx ];
        if ( v[ idx ] > this->_maxValue[ label_ ][ idx ] )
          this->_maxValue[ label_ ][ idx ] = v[ idx ];
      }
    //   // std::cout << property_.value< T >( ) << std::endl;
       // std::cout << "New accum values " << this->_minValue[ label_ ] << " " << this->_maxValue[ label_ ] << std::endl;
    }


  };

  template < class V, size_t M, typename T >
  class VectorNormalizer< V*, M, T >
    : public VectorNormalizer< V, M, T >
  {
  public:
    VectorNormalizer( )
      : VectorNormalizer< V, M, T >( )
    {
    }

    virtual void update( const std::string& label_,
                         const Property& property_ )
    {
      // std::cout << "update vector*" << std::endl;
      this->_update( label_, *property_.value< vector< M, T >* >( ));
      // std::cout << "DONE" << std::endl;
    }

    virtual Property normalizeProperty( const std::string& label_,
                                      const Property& property_ ) const
    {
      return Property( new vector< M, T >(
                        (( *property_.value< vector< M, T >* >( )) -
                         this->_minValue.at( label_ )) /
                        ( this->_maxValue.at( label_ ) -
                          this->_minValue.at( label_ ))));
    }

    virtual void freeNormalizedProperty( Property& property_ )
    {
      delete property_.value< vector< M, T >* >( );
    }


  };


  template < class V, size_t M, typename T >
  class VectorNormalizer< V*, M, T* >
    : public VectorNormalizer< V, M, T >
  {
  public:
    VectorNormalizer( )
      : VectorNormalizer< V, M, T >( )
    {
    }

    virtual void update( const std::string& label_,
                         const Property& property_ )
    {
      // std::cout << "update vector*" << std::endl;
      auto v = property_.value< vector< M, T* >* >( );

      for ( unsigned idx = 0; idx < M; idx++ )
      {
        if ( *( *v )[ idx ] < this->_minValue[ label_ ][ idx ] )
          this->_minValue[ label_ ][ idx ] = *( *v )[ idx ];
        if ( *( *v )[ idx ] > this->_maxValue[ label_ ][ idx ] )
          this->_maxValue[ label_ ][ idx ] = *( *v )[ idx ];
      }
      // std::cout << "DONE" << std::endl;
    }

    virtual Property normalizeProperty( const std::string& label_,
				      const Property& property_  ) const
    {

      auto vp = property_.value< vector< M, T* >* >( );

      auto v = new vector< M, T* >; //(( T* ) 0 );
      // std::cout << *v << std::endl;
      for ( unsigned int idx = 0; idx < M; ++idx )
      {
        ( *v )[ idx ] = //new T;
          new T(
            (*( *vp ).at( idx ) - this->_minValue.at( label_ )[ idx ] ) /
            ( this->_maxValue.at( label_ )[ idx ] -
              this->_minValue.at( label_ )[ idx ] ));
      }
      // std::cout << *v << std::endl;
      return Property( v );
    }

    virtual void freeNormalizedProperty( Property& property_ )
    {
     auto v = property_.value< vector< M, T* >* >( );
      for ( unsigned int idx = 0; idx < M; idx++ )
        delete ( *v )[ idx ];

      delete v;
    }


  };




//   template < class V, size_t M, typename T >
//   class VectorNormalizer< V, M, T* >
//     : public ScalarNormalizer< vmml::vector< M, T >>
//   {
//   public:
//     VectorNormalizer( )
//       : ScalarNormalizer< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
//     {
//     }

//     FIRES_API
//     virtual void accum( const Property& property_ )
//     {
//       vector< M, T > v;
//       vector< M, T * > vp = property_.value< vector< M, T* >>( );
//       for ( unsigned int i = 0; i < M ; i++ )
//         v( i ) = *vp( i );

//       this->_accumValue += v;
//     }

//     FIRES_API
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
//   class VectorNormalizer< V*, M, T* >
//     : public ScalarNormalizer< vmml::vector< M, T >>
//   {
//   public:
//     VectorNormalizer( )
//       : ScalarNormalizer< vmml::vector< M, T >>( vmml::vector< M, T >::ZERO )
//     {
//     }

//     FIRES_API
//     virtual void accum( const Property& property_ )
//     {

//       property_.value< vector< M, T* >* >( );
//       vector< M, T > v;
//       vector< M, T* > vp = *( property_.value< vector< M, T* >* >( ));
//       for ( unsigned int i = 0; i < M ; i++ )
//         v( i ) = *vp( i );

//       this->_accumValue += v;
//     }

//     FIRES_API
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



#endif

}


#endif
