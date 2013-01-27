/* 
 * File:   PreSynapticTimePoint.cpp
 * Author: bam4d
 * 
 * Created on 15 November 2012, 16:05
 */

#include "NeuroplasticityGlobals.h"

PreSynapticTimePoint::PreSynapticTimePoint() {
}

void PreSynapticTimePoint::Add(axon* toAdd)
{
    ((PreSynapticEvent*)next_event)->adjustThis = toAdd;//add the axon to the list of axons to fire at this time point
    //want to check here that if the time points linked list of axons to fire is too short, add a new axon
    if(num_events>=_maxEvents)
    {
        next_event->next = new PreSynapticEvent;
        _maxEvents++;
    }
    next_event = next_event->next;
    num_events++;
}

PreSynapticTimePoint::~PreSynapticTimePoint() {
}

