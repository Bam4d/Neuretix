/*
 * File:   CyclicCacheTestClass.cpp
 * Author: bam4d
 *
 * Created on 24-Jan-2013, 22:04:37
 */

#include "CyclicCacheTestClass.h"
#include "../../CavalCade/CyclicCache.h"


CPPUNIT_TEST_SUITE_REGISTRATION(CyclicCacheTestClass);

CyclicCacheTestClass::CyclicCacheTestClass() {
}

CyclicCacheTestClass::~CyclicCacheTestClass() {
}

void CyclicCacheTestClass::setUp() {
    //cycle cache with 20 time points and 5 events max at each time point as a default 
    cyclicCache = new CyclicCache(20,5);
}

void CyclicCacheTestClass::tearDown() {
}


void CyclicCacheTestClass::testSingleEventThroughTime() {
    
    //log the initial state of the cyclic cache
    cyclicCache->LogState();
    
    //at point 5 in the future, add an "event"
    ((CyclicCacheTimePoint*)cyclicCache->GetTimePointAtOffset(5))->num_events++; //five ahead of currenttime
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 0
    cyclicCache->Cycle(); //process at 1
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle();//process at 2
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 3
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 4
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 5
    cyclicCache->LogState();
    
    //assert that point 5 has been reset as the cache pointer has cycled to this point
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 0);
}

void CyclicCacheTestClass::testMultipleEventsThroughTime() {
    //log the initial state of the cyclic cache
    cyclicCache->LogState();
    
    //at point 5 in the future, add an "event"
    ((CyclicCacheTimePoint*)cyclicCache->GetTimePointAtOffset(5))->num_events++; //five ahead of currenttime
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 0
    cyclicCache->Cycle(); //process at 1
    cyclicCache->LogState();
    
    //after two cycles, add another event '3' steps in the future (at the same point the last event was placed
    ((CyclicCacheTimePoint*)cyclicCache->GetTimePointAtOffset(3))->num_events++; //five ahead of currenttime
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 2);
    cyclicCache->Cycle();//process at 2
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 2);
    cyclicCache->Cycle(); //process at 3
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 2);
    cyclicCache->Cycle(); //process at 4
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 2);
    cyclicCache->Cycle(); //process at 5
    cyclicCache->LogState();
    
    //assert that point 5 has been reset as the cache pointer has cycled to this point
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 0);
}

void CyclicCacheTestClass::testSingleEventThroughTimeWrapped() {
    
    for(int cycles=0;cycles<19;cycles++)
        cyclicCache->Cycle(); //start the cyclic cache near the end of the cycle... so we can tests that it loops ok
    
    ((CyclicCacheTimePoint*)cyclicCache->GetTimePointAtOffset(6))->num_events++; //6 ahead of currenttime (which is at point 5 wrapped)
    cyclicCache->Cycle(); //process at 19
    cyclicCache->LogState();
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle();//process at 0
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 1
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 2
    cyclicCache->LogState();
    
    
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
    cyclicCache->Cycle(); //process at 3
    cyclicCache->LogState();
    
     CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
     cyclicCache->Cycle(); //process at 4
     cyclicCache->LogState();
    
     CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 1);
     cyclicCache->Cycle(); //process at 5
     cyclicCache->LogState();
    
    //assert that point 5 has been reset as the cache pointer has cycled to this point
    CPPUNIT_ASSERT(cyclicCache->Cache[5].num_events == 0);
}

