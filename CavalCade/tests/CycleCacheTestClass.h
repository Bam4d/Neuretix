/*
 * File:   CycleCacheTestClass.h
 * Author: bam4d
 *
 * Created on 24-Jan-2013, 21:55:14
 */

#ifndef CYCLECACHETESTCLASS_H
#define	CYCLECACHETESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class CycleCacheTestClass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CycleCacheTestClass);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    CycleCacheTestClass();
    virtual ~CycleCacheTestClass();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* CYCLECACHETESTCLASS_H */

