/*
 * File:   newtestclass1.cpp
 * Author: bam4d
 *
 * Created on 21-Jan-2013, 22:04:47
 */

#include "newtestclass1.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass1);

newtestclass1::newtestclass1() {
}

newtestclass1::~newtestclass1() {
}

void newtestclass1::setUp() {
}

void newtestclass1::tearDown() {
}

void newtestclass1::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass1::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

