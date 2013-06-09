/*
 * File:   CyclicCacheTestClass.h
 * Author: bam4d
 *
 * Created on 24-Jan-2013, 22:04:37
 */

#ifndef CYCLICCACHETESTCLASS_H
#define	CYCLICCACHETESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>
#include "../../CavalCade/CNNGlobals.h"

class CyclicCacheTestClass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CyclicCacheTestClass);

    
    //a single even going through time
    CPPUNIT_TEST(testSingleEventThroughTime);
    
    //multiple events going through time points
    CPPUNIT_TEST(testMultipleEventsThroughTime);
    
    //one time point through a full wrapped cycle
    CPPUNIT_TEST(testSingleEventThroughTimeWrapped);

    CPPUNIT_TEST_SUITE_END();

public:
    CyclicCacheTestClass();
    virtual ~CyclicCacheTestClass();
    void setUp();
    void tearDown();

private:
    void testSingleEventThroughTime();
    void testMultipleEventsThroughTime();
    void testSingleEventThroughTimeWrapped();
    
    CyclicCache* cyclicCache;
    
};

#endif	/* CYCLICCACHETESTCLASS_H */

