/* 
 * File:   PreSynapticCycleCache.cpp
 * Author: bam4d
 * 
 * Created on 16 November 2012, 14:34
 */

#include "NeuroplasticityGlobals.h"

PreSynapticCyclicCache::PreSynapticCyclicCache() {
}

PreSynapticCyclicCache::PreSynapticCyclicCache(int maxPoints, int maxEvents)
{
    Cache = new PreSynapticTimePoint[maxPoints];
     
     //initialise the time points with the max events specified
     for(int timePointCount = 0; timePointCount<maxPoints; timePointCount++)
         Cache[timePointCount].InitialiseTimePoint(maxEvents);
     
     _currentPoint = 0;
     MaxPoints = maxPoints;
     CurrentTimePoint = &Cache[0];
}

//cycles the cache by a certain amount
void PreSynapticCyclicCache::Cycle(int cycles) 
{
    //reset all of the 
    for(int cycleCount = 0; cycleCount<cycles; cycleCount++)
    {
        _currentPoint++;
        if(_currentPoint>MaxPoints-1)
            _currentPoint = 0;
        
        CurrentTimePoint = &Cache[_currentPoint];
        CurrentTimePoint->num_events = 0; //reset the events in the new timepoint (erases all synaptic history that is not in the range of the TimePoints)
        CurrentTimePoint->next_event = CurrentTimePoint->eventLLHead;
    }
}

void PreSynapticCyclicCache::Reset()
{
    
    for(int numTimePoints = 0; numTimePoints<MaxPoints; numTimePoints++)
    {
            Cache[numTimePoints].num_events = 0; //reset the amount of axons in this time point to 0;
            Cache[numTimePoints].next_event = Cache[numTimePoints].eventLLHead;
    }
}

PreSynapticCyclicCache::~PreSynapticCyclicCache() {
}

