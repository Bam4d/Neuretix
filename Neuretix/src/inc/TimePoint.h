/* 
 * File:   TimePoint.h
 * Author: bam4d
 *
 * Created on 19 February 2012, 18:03
 */
#ifndef TIMEPOINT_H
#define	TIMEPOINT_H

#include "CyclicCacheTimePoint.h"

class Axon;

class TimePoint : public CyclicCacheTimePoint
{
public:

    TimePoint();

    void Add(Axon* _toAdd);

    ~TimePoint();
    
private:


};


#endif	/* TIMEPOINT_H */

