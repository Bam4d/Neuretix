/*
 * File:   newtestclass.cpp
 * Author: bam4d
 *
 * Created on 21-Jan-2013, 21:41:07
 */

#include "newtestclass.h"
#include "CyclicCache.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testCycle() {
    CyclicCache cyclicCache;
    cyclicCache.Cycle();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testCyclicCache() {
    CyclicCache cyclicCache();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testCyclicCache2() {
    int maxPoints;
    int maxEvents;
    CyclicCache cyclicCache(maxPoints, maxEvents);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testLogState() {
    CyclicCache cyclicCache;
    cyclicCache.LogState();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testRelease() {
    CyclicCache cyclicCache;
    cyclicCache.Release();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

