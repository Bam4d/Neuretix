/* 
 * File:   preSynapticEvent.cpp
 * Author: bam4d
 * 
 * Created on 15 November 2012, 16:04
 */

#include <cstdlib>

#include "../inc/PreSynapticEvent.h"

PreSynapticEvent::PreSynapticEvent() {
    
    next = NULL;
    this->adjustThis = NULL;
    
}

PreSynapticEvent::~PreSynapticEvent() {
}

