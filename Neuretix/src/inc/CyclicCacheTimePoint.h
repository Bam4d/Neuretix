/* 
 * File:   CyclicCacheTimePoint.h
 * Author: bam4d
 *
 * Created on 15 November 2012, 13:51
 */

#ifndef CYCLICCACHETIMEPOINT_H
#define	CYCLICCACHETIMEPOINT_H

#include "CyclicCacheEvent.h"

class CyclicCacheTimePoint {
public:
    CyclicCacheTimePoint();
    
    virtual ~CyclicCacheTimePoint();
    
    CyclicCacheEvent* eventLLHead;
    
    CyclicCacheEvent* nextEvent;
    
    void InitialiseTimePoint(int maxEvents);
    virtual bool Delete();
    
    int numEvents;
    
    
protected:
    int _maxEvents;

};

#endif	/* CYCLICCACHETIMEPOINT_H */

