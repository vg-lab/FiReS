/**
 * @file    Sort.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__SORT_H__
#define __FIRES__SORT_H__


namespace fires
{

  class PropertySorter
  {
  public:
    virtual ~PropertySorter( void )
    {
    }

    virtual bool isLowerThan( Property&, Property& ) = 0;

    virtual bool isEqual( Property&, Property& ) = 0;

  };

  template < typename T >
  class ScalarPropertySorter : public PropertySorter
  {
  public:

    virtual ~ScalarPropertySorter( void )
    {
    }

    virtual bool isLowerThan( Property& f1, Property& f2 )
    {
      return  f1.value< T >( ) < f2.value< T >( );
    }

    virtual bool isEqual( Property& f1, Property& f2 )
    {
      return  f1.value< T >( ) == f2.value< T >( );
    }

  };



  class SortConfig : public TaskConfig
  {

  public:

    typedef enum
    {
      ASCENDING = 0,
      DESCENDING
    } TSortOrder;


    SortConfig( void )
    {
    }

    virtual ~SortConfig( void )
    {
    }

    void addProperty( std::string propertyLabel_,
                     PropertySorter* sorter_,
                     TSortOrder order_ = ASCENDING )
    {
      _propertys.push_back( TSortProperty{ propertyLabel_, sorter_, order_ });
    }

    void clear( void )
    {
      _propertys.clear( );
    }

    virtual bool operator( ) ( Object* obj1, Object* obj2 ) const
    {
      for ( auto propertyIt = _propertys.cbegin( );
            propertyIt != _propertys.cend( ); ++propertyIt )
      {
        const std::string label = ( *propertyIt ).label;

        if ( !obj1->hasProperty( label ))
          return false;

        if ( !obj2->hasProperty( label ))
          return true;

        if (( *propertyIt ).sorter->isEqual(
              obj1->getProperty( label ),
              obj2->getProperty( label )))
          continue;

        bool lt = ( *propertyIt ).sorter->isLowerThan(
          obj1->getProperty( label ),
          obj2->getProperty( label ));

        return (( *propertyIt ).order == TSortOrder::ASCENDING ) ?
          lt : !lt;


      }
      return false;
    }

  protected:

    typedef struct
    {
      std::string label;
      PropertySorter* sorter;
      TSortOrder order;
    } TSortProperty;

    std::vector< TSortProperty > _propertys;

  };

  class Sort : public Task
  {

  public:

    virtual Objects& eval( Objects &objs, TaskConfig& config )
    {
      SortConfig* sortConfig =
        static_cast< SortConfig* >( &config );

      if ( !sortConfig )
        return objs;

      std::sort( objs.begin( ), objs.end( ), *sortConfig );

      return objs;
    }

  };


} // namespace fires

#endif
