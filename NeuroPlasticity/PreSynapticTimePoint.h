/* 
 * File:   PreSynapticTimePoint.h
 * Author: bam4d
 *
 * Created on 15 November 2012, 16:05
 */

#ifndef PRESYNAPTICTIMEPOINT_H
#define	PRESYNAPTICTIMEPOINT_H

class PreSynapticTimePoint : public TimePoint  {
public:
    PreSynapticTimePoint();
    virtual ~PreSynapticTimePoint();
    
    void Add(axon* toAdd);
private:

};

#endif	/* PRESYNAPTICTIMEPOINT_H */

