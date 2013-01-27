/* 
 * File:   CyclicCacheTimePoint.cpp
 * Author: bam4d
 * 
 * Created on 15 November 2012, 13:51
 */

#include "CNNGlobals.h"


CyclicCacheTimePoint::CyclicCacheTimePoint()
{
    
}

void CyclicCacheTimePoint::InitialiseTimePoint(int maxEvents) {
    
    _maxEvents = maxEvents;
    eventLLHead = new axon_event;
    next_event = eventLLHead;
    CyclicCacheEvent* creationIterator = eventLLHead;
    for(int max_events = 0; max_events<maxEvents; max_events++)
    {
        creationIterator->next = new axon_event;
        creationIterator = creationIterator->next;
    }

    num_events = 0;
}

bool CyclicCacheTimePoint::Delete()
{
    if(eventLLHead == 0 )
    return false;
    else
    {
        CyclicCacheEvent* temp_head = eventLLHead->next;
        delete eventLLHead;
        eventLLHead = temp_head;

        return true;
    }
}

CyclicCacheTimePoint::~CyclicCacheTimePoint() 
{
        while(Delete());
        num_events = 0;
}



