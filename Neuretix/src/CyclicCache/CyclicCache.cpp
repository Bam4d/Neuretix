/* 
 * File:   CyclicCache.cpp
 * Author: bam4d
 * 
 * Created on 15 November 2012, 14:40
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>

#include "../inc/CyclicCache.h"
#include "../inc/CyclicCacheTimePoint.h"

CyclicCache::CyclicCache() {
    _currentPoint = 0;
    currentTimePoint = NULL;
    maxPoints = 0;
    cache = NULL;
}

CyclicCache::CyclicCache(int maxPoints,int maxEvents) {
    
     cache = new CyclicCacheTimePoint[maxPoints];
     
     //initialise the time points with the max events specified
     for(int timePointCount = 0; timePointCount<maxPoints; timePointCount++)
         cache[timePointCount].InitialiseTimePoint(maxEvents);
     
     _currentPoint = 0;
     this->maxPoints = maxPoints;
     currentTimePoint = &cache[0];
}

//cycles the cache to the next time point, resetting the current timepoint
void CyclicCache::Cycle() {
    
    currentTimePoint->numEvents = 0; //reset the amount of axons in this time point to 0;
    currentTimePoint->nextEvent = currentTimePoint->eventLLHead;
    _currentPoint++;
    if(_currentPoint>maxPoints-1)
       _currentPoint = 0;
    
    currentTimePoint = &cache[_currentPoint];
    
}

CyclicCacheTimePoint* CyclicCache::GetTimePointAtOffset(int offset)
{
    return &cache[(_currentPoint+offset)%maxPoints];
}

void CyclicCache::Release()
{
    delete[] cache;
}

void CyclicCache::LogState() 
{
    std::string outputString;
    for(int points=0; points<maxPoints; points++)
    {
        char buf[10];
        memset(buf, 0, 10);
        sprintf(buf,"%d",cache[points].numEvents);
        outputString.append(std::string(buf)+" ");
    }
    
    outputString.append("\n");
    
    printf(outputString.c_str());
}

CyclicCache::~CyclicCache() {
}

