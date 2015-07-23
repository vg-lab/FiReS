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

  class FeatureSorter
  {
  public:
    virtual ~FeatureSorter( void )
    {
    }

    virtual bool isLowerThan( Feature&, Feature& ) = 0;

    virtual bool isEqual( Feature&, Feature& ) = 0;

  };

  template < typename T >
  class ScalarFeatureSorter : public FeatureSorter
  {
  public:

    virtual ~ScalarFeatureSorter( void )
    {
    }

    virtual bool isLowerThan( Feature& f1, Feature& f2 )
    {
      return  f1.value< T >( ) < f2.value< T >( );
    }

    virtual bool isEqual( Feature& f1, Feature& f2 )
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

    void addFeature( std::string featureLabel_,
                     FeatureSorter* sorter_,
                     TSortOrder order_ = ASCENDING )
    {
      _features.push_back( TSortFeature{ featureLabel_, sorter_, order_ });
    }

    void clear( void )
    {
      _features.clear( );
    }

    virtual bool operator( ) ( Object* obj1, Object* obj2 ) const
    {
      for ( auto featureIt = _features.cbegin( );
            featureIt != _features.cend( ); ++featureIt )
      {
        const std::string label = ( *featureIt ).label;

        if ( !obj1->hasFeature( label ))
          return false;

        if ( !obj2->hasFeature( label ))
          return true;

        if (( *featureIt ).sorter->isEqual(
              obj1->getFeature( label ),
              obj2->getFeature( label )))
          continue;

        bool lt = ( *featureIt ).sorter->isLowerThan(
          obj1->getFeature( label ),
          obj2->getFeature( label ));

        return (( *featureIt ).order == TSortOrder::ASCENDING ) ?
          lt : !lt;


      }
      return false;
    }

  protected:

    typedef struct
    {
      std::string label;
      FeatureSorter* sorter;
      TSortOrder order;
    } TSortFeature;

    std::vector< TSortFeature > _features;

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
