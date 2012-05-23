/* 
 * File:   TimePoint.cpp
 * Author: bam4d
 * 
 * Created on 19 February 2012, 18:03
 */

#include "CNNGlobals.h"

TimePoint::TimePoint() 
{

        _maxEvents = 20; //initially allocate space for 20 simultaneous fires in each time point. (this grows automatically if more fires are required)
        axon_eventLLHead = new axon_event;
        next_axon_event = axon_eventLLHead;
        axon_event* creationIterator = axon_eventLLHead;
        for(int max_events = 0; max_events<_maxEvents; max_events++)
        {
            creationIterator->next = new axon_event;
            creationIterator = creationIterator->next;
        }

        num_axonsToFire = 0;
    
}

void TimePoint::Add(axon* _toAdd)
{
    next_axon_event->fireThis = _toAdd;//add the axon to the list of axons to fire at this time point
    //want to check here that if the time point's linked list of axons to fire is too short, add a new axon
    if(num_axonsToFire>=_maxEvents)
    {
        next_axon_event->next = new axon_event;
        _maxEvents++;
    }
    next_axon_event = next_axon_event->next;
    num_axonsToFire++;

}

bool TimePoint::Delete()
{
    if( axon_eventLLHead == 0 )
    return false;
    else
    {
        axon_event* temp_head = axon_eventLLHead->next;
        delete axon_eventLLHead;
        axon_eventLLHead = temp_head;

        return true;
    }
}

TimePoint::~TimePoint() 
{
        while(Delete());
        num_axonsToFire = 0;
}

