/* 
 * File:   preSynapticEvent.h
 * Author: bam4d
 *
 * Created on 15 November 2012, 16:04
 */

#ifndef PRESYNAPTICEVENT_H
#define	PRESYNAPTICEVENT_H

#include "../../../Neuretix/src/inc/CyclicCacheEvent.h"

class Axon;

class PreSynapticEvent : public CyclicCacheEvent {
public:
    PreSynapticEvent();
    virtual ~PreSynapticEvent();
    
    Axon* adjustThis;
private:

};

#endif	/* PRESYNAPTICEVENT_H */

