/* 
 * File:   CyclicCacheTimePoint.cpp
 * Author: bam4d
 * 
 * Created on 15 November 2012, 13:51
 */

#include <cstdlib>

#include "../inc/CyclicCacheTimePoint.h"
#include "../inc/AxonEvent.h"


CyclicCacheTimePoint::CyclicCacheTimePoint()
{
	numEvents = 0;
	eventLLHead = NULL;
	_maxEvents = 0;
	nextEvent = NULL;
}

void CyclicCacheTimePoint::InitialiseTimePoint(int maxEvents) {
    
    _maxEvents = maxEvents;
    eventLLHead = new AxonEvent;
    nextEvent = eventLLHead;
    CyclicCacheEvent* creationIterator = eventLLHead;
    for(int max_events = 0; max_events<maxEvents; max_events++)
    {
        creationIterator->next = new AxonEvent;
        creationIterator = creationIterator->next;
    }

    numEvents = 0;
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
        numEvents = 0;
}



