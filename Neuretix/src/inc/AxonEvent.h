/* 
 * File:   AxonEvent.h
 * Author: bam4d
 *
 * Created on 19 February 2012, 18:09
 */

#ifndef AXON_EVENT_H
#define	AXON_EVENT_H

#include "CyclicCacheEvent.h"

class Axon;

class AxonEvent : public CyclicCacheEvent
{
public:
    Axon* fireThis;
    
    AxonEvent();
    ~AxonEvent();
    
};

#endif	/* AXON_EVENT_H */

