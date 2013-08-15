/* 
 * File:   axon_event.cpp
 * Author: bam4d
 * 
 * Created on 19 February 2012, 18:09
 */
#include <cstdlib>

#include "../inc/AxonEvent.h"

AxonEvent::AxonEvent() {
    
        next = NULL;
        fireThis = NULL;
    
}


AxonEvent::~AxonEvent() {
}

