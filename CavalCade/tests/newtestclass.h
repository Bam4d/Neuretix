/*
 * File:   newtestclass.h
 * Author: bam4d
 *
 * Created on 21-Jan-2013, 21:41:06
 */

#ifndef NEWTESTCLASS_H
#define	NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testCycle);
    CPPUNIT_TEST(testCyclicCache);
    CPPUNIT_TEST(testCyclicCache2);
    CPPUNIT_TEST(testLogState);
    CPPUNIT_TEST(testRelease);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testCycle();
    void testCyclicCache();
    void testCyclicCache2();
    void testLogState();
    void testRelease();

};

#endif	/* NEWTESTCLASS_H */

