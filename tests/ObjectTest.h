/**
 * @file    ObjectTest.h
 * @brief   
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_OBJECT_TEST__
#define __FIRES_OBJECT_TEST__

#include <limits.h>
#include <gtest/gtest.h>

#include <fires/fires.h>

class ObjectTest : public ::testing::Test 
{
 
protected:

  ObjectTest()
  {
  }

  virtual ~ObjectTest() 
  {
  }

};


TEST_F(ObjectTest, object) 
{
  ASSERT_EQ(0,0); 

  fires::Object obj; 

  fires::Feature f1, f2;

  // ASSERT_EQ( features.size( ), 0 );
  obj.addFeature( "feature1", &f1 );
  ASSERT_NE( obj.getFeature( "feature1" ), nullptr );
  ASSERT_EQ( obj.getFeature( "feature1" ), &f1 );
  ASSERT_EQ( obj.getFeature( "feature2" ), nullptr );

  obj.addFeature( std::string("feature2"), &f2 );
  ASSERT_NE( obj.getFeature( "feature1" ), nullptr );
  ASSERT_EQ( obj.getFeature( "feature1" ), &f1 );
  ASSERT_NE( obj.getFeature( "feature2" ), nullptr );
  ASSERT_EQ( obj.getFeature( "feature2" ), &f2 );

  obj.addFeature( std::string("feature1"), &f2 );
  ASSERT_EQ( obj.getFeature( std::string( "feature1" ) ), &f1 );

  obj.delFeature( std::string("feature2"));
  ASSERT_EQ( obj.getFeature( "feature2" ), nullptr );
  ASSERT_EQ( obj.getFeature( "feature1" ), &f1 );

  obj.addFeature( "feature2", &f2 );
  ASSERT_EQ( obj.getFeature( "feature2" ), &f2 );


  obj.setFeature( "feature1", &f2 );
  ASSERT_EQ( obj.getFeature( "feature1" ), &f2 );
  ASSERT_EQ( obj.getFeature( "feature2" ), &f2 );

  obj.setFeature( "feature2", &f1 );
  ASSERT_EQ( obj.getFeature( "feature1" ), &f2 );
  ASSERT_EQ( obj.getFeature( "feature2" ), &f1 );

  obj.clearFeatures( );
  ASSERT_EQ( obj.getFeature( "feature1" ), nullptr );
  ASSERT_EQ( obj.getFeature( "feature2" ), nullptr );

#define TEST_LABEL "testLabel" 

  obj.label() = TEST_LABEL;
  ASSERT_EQ( obj.label(), TEST_LABEL );
  obj.label() = "";
  ASSERT_NE( obj.label(), TEST_LABEL );
}



#endif



