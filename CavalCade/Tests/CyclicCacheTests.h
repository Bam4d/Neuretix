/*
 * File:   CyclicCacheTests.h
 * Author: bam4d
 *
 * Created on 21-Jan-2013, 22:05:28
 */

#ifndef CYCLICCACHETESTS_H
#define	CYCLICCACHETESTS_H

#include <cppunit/extensions/HelperMacros.h>

class CyclicCacheTests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CyclicCacheTests);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    CyclicCacheTests();
    virtual ~CyclicCacheTests();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* CYCLICCACHETESTS_H */

