/* 
 * File:   preSynapticEvent.h
 * Author: bam4d
 *
 * Created on 15 November 2012, 16:04
 */

#ifndef PRESYNAPTICEVENT_H
#define	PRESYNAPTICEVENT_H

class PreSynapticEvent : public CyclicCacheEvent {
public:
    PreSynapticEvent();
    virtual ~PreSynapticEvent();
    
    axon* adjustThis;
private:

};

#endif	/* PRESYNAPTICEVENT_H */

