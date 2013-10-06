/* 
 * File:   PreSynapticTimePoint.h
 * Author: bam4d
 *
 * Created on 15 November 2012, 16:05
 */

#ifndef PRESYNAPTICTIMEPOINT_H
#define	PRESYNAPTICTIMEPOINT_H

#include "../../../Neuretix/src/inc/TimePoint.h"

class Axon;

class PreSynapticTimePoint : public TimePoint  {
public:
    PreSynapticTimePoint();
    virtual ~PreSynapticTimePoint();
    
    void Add(Axon* toAdd);
private:

};

#endif	/* PRESYNAPTICTIMEPOINT_H */

