/* 
 * File:   TimePoint.cpp
 * Author: bam4d
 * 
 * Created on 19 February 2012, 18:03
 */

#include "CNNGlobals.h"

TimePoint::TimePoint()
{
}

void TimePoint::Add(axon* _toAdd)
{
    ((axon_event*)next_event)->fireThis = _toAdd;//add the axon to the list of axons to fire at this time point
    //want to check here that if the time points linked list of axons to fire is too short, add a new axon
    if(num_events>=_maxEvents)
    {
        next_event->next = new axon_event;
        _maxEvents++;
    }
    next_event = next_event->next;
    num_events++;

}

TimePoint::~TimePoint() 
{
}