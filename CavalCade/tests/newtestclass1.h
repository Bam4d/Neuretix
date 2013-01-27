/*
 * File:   newtestclass1.h
 * Author: bam4d
 *
 * Created on 21-Jan-2013, 22:04:47
 */

#ifndef NEWTESTCLASS1_H
#define	NEWTESTCLASS1_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass1 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass1);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass1();
    virtual ~newtestclass1();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* NEWTESTCLASS1_H */

