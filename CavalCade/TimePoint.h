/* 
 * File:   TimePoint.h
 * Author: bam4d
 *
 * Created on 19 February 2012, 18:03
 */

#ifndef TIMEPOINT_H
#define	TIMEPOINT_H

class TimePoint
{
public:

    axon_event* axon_eventLLHead;
    
    axon_event* next_axon_event;
    
    int num_axonsToFire;

    TimePoint();
    

    void Add(axon* _toAdd);

    bool Delete();

    ~TimePoint();
    
private:
    int _maxEvents;

};


#endif	/* TIMEPOINT_H */

