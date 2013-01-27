/* 
 * File:   axon_event.h
 * Author: bam4d
 *
 * Created on 19 February 2012, 18:09
 */

#ifndef AXON_EVENT_H
#define	AXON_EVENT_H

class axon_event : public CyclicCacheEvent
{
public:
    axon* fireThis;
    
    axon_event();
    ~axon_event();
    
};

#endif	/* AXON_EVENT_H */

