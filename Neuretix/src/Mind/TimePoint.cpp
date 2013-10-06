/* 
 * File:   TimePoint.cpp
 * Author: bam4d
 * 
 * Created on 19 February 2012, 18:03
 */

#include "../inc/TimePoint.h"
#include "../inc/Axon.h"
#include "../inc/AxonEvent.h"

TimePoint::TimePoint()
{
}

void TimePoint::Add(Axon* _toAdd)
{
    ((AxonEvent*)nextEvent)->fireThis = _toAdd;//add the axon to the list of axons to fire at this time point
    //want to check here that if the time points linked list of axons to fire is too short, add a new axon
    if(numEvents>=_maxEvents)
    {
        nextEvent->next = new AxonEvent;
        _maxEvents++;
    }
    nextEvent = nextEvent->next;
    numEvents++;

}

TimePoint::~TimePoint() 
{
}
