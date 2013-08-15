/* 
 * File:   CyclicCacheEvent.h
 * Author: bam4d
 *
 * Created on 15 November 2012, 13:47
 */

#ifndef CYCLICCACHEEVENT_H
#define	CYCLICCACHEEVENT_H

class CyclicCacheEvent {
public:
    CyclicCacheEvent();
    
    virtual ~CyclicCacheEvent();
    
    CyclicCacheEvent* next;
private:

};

#endif	/* CYCLICCACHEEVENT_H */

