/* 
 * File:   PreSynapticCycleCache.cpp
 * Author: bam4d
 * 
 * Created on 16 November 2012, 14:34
 */

#include "../inc/PreSynapticCyclicCache.h"
#include "../inc/PreSynapticTimePoint.h"

PreSynapticCyclicCache::PreSynapticCyclicCache() {
}

PreSynapticCyclicCache::PreSynapticCyclicCache(int maxPoints, int maxEvents)
{
    cache = new PreSynapticTimePoint[maxPoints];
     
     //initialise the time points with the max events specified
     for(int timePointCount = 0; timePointCount<maxPoints; timePointCount++)
         cache[timePointCount].InitialiseTimePoint(maxEvents);
     
     _currentPoint = 0;
     this->maxPoints = maxPoints;
     currentTimePoint = &cache[0];
}

//cycles the cache by a certain amount
void PreSynapticCyclicCache::Cycle(int cycles) 
{
    //reset all of the 
    for(int cycleCount = 0; cycleCount<cycles; cycleCount++)
    {
        _currentPoint++;
        if(_currentPoint>maxPoints-1)
            _currentPoint = 0;
        
        currentTimePoint = &cache[_currentPoint];
        currentTimePoint->numEvents = 0; //reset the events in the new timepoint (erases all synaptic history that is not in the range of the TimePoints)
        currentTimePoint->nextEvent = currentTimePoint->eventLLHead;
    }
}

void PreSynapticCyclicCache::Reset()
{
    
    for(int numTimePoints = 0; numTimePoints<this->maxPoints; numTimePoints++)
    {
            cache[numTimePoints].numEvents = 0; //reset the amount of axons in this time point to 0;
            cache[numTimePoints].nextEvent = cache[numTimePoints].eventLLHead;
    }
}

PreSynapticCyclicCache::~PreSynapticCyclicCache() {
}

