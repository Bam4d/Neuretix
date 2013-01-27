/* 
 * File:   CyclicCache.cpp
 * Author: bam4d
 * 
 * Created on 15 November 2012, 14:40
 */

#include "CNNGlobals.h"

CyclicCache::CyclicCache() {
    
}

CyclicCache::CyclicCache(int maxPoints,int maxEvents) {
    
     Cache = new CyclicCacheTimePoint[maxPoints];
     
     //initialise the time points with the max events specified
     for(int timePointCount = 0; timePointCount<maxPoints; timePointCount++)
         Cache[timePointCount].InitialiseTimePoint(maxEvents);
     
     _currentPoint = 0;
     MaxPoints = maxPoints;
     CurrentTimePoint = &Cache[0];
}

//cycles the cache to the next time point, resetting the current timepoint
void CyclicCache::Cycle() {
    
    CurrentTimePoint->num_events = 0; //reset the amount of axons in this time point to 0;
    CurrentTimePoint->next_event = CurrentTimePoint->eventLLHead;
    _currentPoint++;
    if(_currentPoint>MaxPoints-1)
       _currentPoint = 0;
    
    CurrentTimePoint = &Cache[_currentPoint];
    
}

CyclicCacheTimePoint* CyclicCache::GetTimePointAtOffset(int offset)
{
    return &Cache[(_currentPoint+offset)%MaxPoints];
}

void CyclicCache::Release()
{
    delete[] Cache;
}

void CyclicCache::LogState() 
{
    string  outputString; 
    for(int points=0; points<MaxPoints; points++)
    {
        char buf[10];
        memset(buf,0,10);
        sprintf(buf,"%d",Cache[points].num_events);
        outputString.append(string(buf)+" ");
    }
    
    outputString.append("\n");
    
    printf(outputString.c_str());
}

CyclicCache::~CyclicCache() {
}

