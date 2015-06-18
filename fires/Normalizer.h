/**
 * @file    Normalizer.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_NORMALIZER_H__
#define __FIRES_NORMALIZER_H__

#include "Feature.h"
#include "Definitions.h"

#include <map>

#ifdef FIRES_WITH_VMMLIB
#include <vmmlib/vmmlib.hpp>
#endif

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
                         const Feature& feature_ ) = 0;

    FIRES_API
    virtual Feature normalize( const std::string& label,
                               const Feature& feature_ ) const = 0;

    FIRES_API
    virtual float normalize( const float distance )
    {
      return distance;
    }

    FIRES_API
    virtual void freeNormalizedFeature( Feature& /* feature_ */ ) { };
  };


  template < typename T >
  class ScalarNormalizer : public Normalizer
  {
  public:

    FIRES_API
    ScalarNormalizer( void )
    {
    }

    FIRES_API
    virtual void reset( const std::string& label )
    {
      _minValue[ label ] = std::numeric_limits< T >::max( );
      _maxValue[ label ] = std::numeric_limits< T >::min( );
    }

    FIRES_API
    virtual ~ScalarNormalizer( )
    {
    }

    FIRES_API
    virtual void update( const std::string &label_,
                         const Feature& feature_ )
    {
      if ( feature_.value< T >( ) < _minValue[ label_ ] )
        _minValue[ label_ ] = feature_.value< T >( );
      if (  feature_.value< T >( ) > _maxValue[ label_ ] )
        _maxValue[ label_ ] = feature_.value< T >( );

      // std::cout << feature_.value< T >( ) << std::endl;
      // std::cout << "New accum values " << _minValue[ label_ ] << " " << _maxValue[ label_ ] << std::endl;

    }

    FIRES_API
    virtual Feature normalize( const std::string &label_,
                               const Feature& feature_ ) const
    {
      // std::cout <<  "Normalize " << std::endl << feature_.value< T >( ) << " " <<  _minValue.at( label_ ) << " "
      //           <<  _maxValue.at( label_ ) << std::endl
      //           <<  ( feature_.value< T >( ) - _minValue.at( label_ )) /
      //                ( _maxValue.at( label_ ) - _minValue.at( label_ ))
      //           << std::endl;
      return Feature(( feature_.value< T >( ) - _minValue.at( label_ )) /
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

    FIRES_API
    ScalarNormalizer( void )
      : ScalarNormalizer< T >( )
    {
    }

    FIRES_API
    virtual ~ScalarNormalizer( )
    {
    }

    FIRES_API
    virtual void update( const std::string& label_,
                         const Feature& feature_ )
    {
      if ( *feature_.value< T* >( ) < this->_minValue[ label_ ] )
        this->_minValue[ label_ ] = *feature_.value< T* >( );
      if (  *feature_.value< T* >( ) > this->_maxValue[ label_ ] )
        this->_maxValue[ label_ ] = *feature_.value< T* >( );

      // std::cout << feature_.value< T >( ) << std::endl;
      // std::cout << "New accum values " << _minValue << " " << _maxValue << std::endl;

    }

    FIRES_API
    virtual Feature normalize( const std::string& label_,
                               const Feature& feature_ ) const
    {
      // std::cout <<  *feature_.value< T* >( ) << " " <<  this->_minValue << " "
      //           <<  this->_maxValue << " "  << this->_minValue   << std::endl;
      return Feature(
        new T(( *feature_.value< T* >( ) - this->_minValue.at( label_ )) /
              ( this->_maxValue.at( label_ ) - this->_minValue.at( label_ ))));
    }


    FIRES_API
    virtual void freeNormalizedFeature( Feature& feature_ )
    {
      delete feature_.value< T* >( );
    }

  };

  #ifdef FIRES_WITH_VMMLIB

  template < class V, size_t M, typename T >
  class VectorNormalizer
    : public ScalarNormalizer< vmml::vector< M, T >>
  {
  public:
    FIRES_API
    VectorNormalizer( )
      : ScalarNormalizer< vmml::vector< M, T >>( )
    {
    }

    FIRES_API
    virtual void reset( const std::string& label_ )
    {
      this->_minValue[ label_ ] =
        vmml::vector< M, T >( std::numeric_limits< T >::max( ));
      this->_maxValue[ label_ ] =
        vmml::vector< M, T >( std::numeric_limits< T >::min( ));
    }

    FIRES_API
    virtual void update( const std::string& label_,
                         const Feature& feature_ )
    {
      // std::cout << "update vector" << std::endl;
      this->_update( label_, feature_.value< vector< M, T >>( ));
    }

    FIRES_API
    virtual float normalize( const float distance )
    {
      return distance / sqrt( M );
    }


  protected:
    FIRES_API
    void _update( const std::string& label_,
                  const vector< M, T >& v )
    {
      for ( auto idx = 0; idx < M; idx++ )
      {
        if ( v[ idx ] < this->_minValue[ label_ ][ idx ] )
          this->_minValue[ label_ ][ idx ] = v[ idx ];
        if ( v[ idx ] > this->_maxValue[ label_ ][ idx ] )
          this->_maxValue[ label_ ][ idx ] = v[ idx ];
      }
    //   // std::cout << feature_.value< T >( ) << std::endl;
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

    FIRES_API
    virtual void update( const std::string& label_,
                         const Feature& feature_ )
    {
      // std::cout << "update vector*" << std::endl;
      this->_update( label_, *feature_.value< vector< M, T >* >( ));
      // std::cout << "DONE" << std::endl;
    }

    FIRES_API
    virtual Feature normalize( const std::string &label_,
                               const Feature& feature_ ) const
    {
      return Feature( new vector< M, T >(
                        (( *feature_.value< vector< M, T >* >( )) -
                         this->_minValue.at( label_ )) /
                        ( this->_maxValue.at( label_ ) -
                          this->_minValue.at( label_ ))));
    }

    FIRES_API
    virtual void freeNormalizedFeature( Feature& feature_ )
    {
      delete feature_.value< vector< M, T >* >( );
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

    FIRES_API
    virtual void update( const std::string& label_,
                         const Feature& feature_ )
    {
      // std::cout << "update vector*" << std::endl;
      auto v = feature_.value< vector< M, T* >* >( );

      for ( auto idx = 0; idx < M; idx++ )
      {
        if ( *( *v )[ idx ] < this->_minValue[ label_ ][ idx ] )
          this->_minValue[ label_ ][ idx ] = *( *v )[ idx ];
        if ( *( *v )[ idx ] > this->_maxValue[ label_ ][ idx ] )
          this->_maxValue[ label_ ][ idx ] = *( *v )[ idx ];
      }
      // std::cout << "DONE" << std::endl;
    }

    FIRES_API
    virtual Feature normalize( const std::string& label_,
                               const Feature& feature_  ) const
    {

      auto vp = feature_.value< vector< M, T* >* >( );

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
      return Feature( v );
    }

    FIRES_API
    virtual void freeNormalizedFeature( Feature& feature_ )
    {
     auto v = feature_.value< vector< M, T* >* >( );
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
//     virtual void accum( const Feature& feature_ )
//     {
//       vector< M, T > v;
//       vector< M, T * > vp = feature_.value< vector< M, T* >>( );
//       for ( unsigned int i = 0; i < M ; i++ )
//         v( i ) = *vp( i );

//       this->_accumValue += v;
//     }

//     FIRES_API
//     virtual Feature feature( void )
//     {

//       vector<M, T* > _vector;

//       for ( unsigned int i = 0; i < M ; i++ )
//       {
//         _vectorValues[ i ] = this->_accumValue( i );
//         _vector( i ) = &_vectorValues[ i ];
//       }

//       return Feature( _vector );
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
//     virtual void accum( const Feature& feature_ )
//     {

//       feature_.value< vector< M, T* >* >( );
//       vector< M, T > v;
//       vector< M, T* > vp = *( feature_.value< vector< M, T* >* >( ));
//       for ( unsigned int i = 0; i < M ; i++ )
//         v( i ) = *vp( i );

//       this->_accumValue += v;
//     }

//     FIRES_API
//     virtual Feature feature( void )
//     {
//       for ( unsigned int i = 0; i < M ; i++ )
//       {
//         _vectorValues[ i ] = this->_accumValue( i );
//         _vector( i ) = &_vectorValues[ i ];
//       }

//       return Feature( &_vector );
//     }

//   protected:

//     T _vectorValues[ M ];
//     vector<M, T* > _vector;

//   };



#endif

}


#endif
