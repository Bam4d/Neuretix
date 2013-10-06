/* 
 * File:   PreSynapticTimePoint.cpp
 * Author: bam4d
 * 
 * Created on 15 November 2012, 16:05
 */

#include "../inc/PreSynapticTimePoint.h"
#include "../inc/PreSynapticEvent.h"

PreSynapticTimePoint::PreSynapticTimePoint() {
}

void PreSynapticTimePoint::Add(Axon* toAdd)
{
    ((PreSynapticEvent*)nextEvent)->adjustThis = toAdd;//add the axon to the list of axons to fire at this time point
    //want to check here that if the time points linked list of axons to fire is too short, add a new axon
    if(numEvents>=_maxEvents)
    {
        nextEvent->next = new PreSynapticEvent;
        _maxEvents++;
    }
    nextEvent = nextEvent->next;
    numEvents++;
}

PreSynapticTimePoint::~PreSynapticTimePoint() {
}

