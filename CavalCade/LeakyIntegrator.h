/* 
 * File:   LeakyIntegrator.h
 * Author: bam4d
 *
 * Created on 05 August 2012, 21:28
 */

#ifndef LEAKYINTEGRATOR_H
#define	LEAKYINTEGRATOR_H

class CavalcadeMind;

class LeakyIntegrator {
public:
    LeakyIntegrator();
    LeakyIntegrator(float epsilon, int refractoryPeriod,float threshold);
    LeakyIntegrator(const LeakyIntegrator& orig);
    virtual ~LeakyIntegrator();
    
    virtual bool Stimulate(float amplitude);
    virtual void Reset();
    
    
    float excitationLevel;
    float amplitudePeak;
    float threshold;
    
    long unsigned int* currentTime;
    long unsigned int lastResetTimestamp;
    long unsigned int lastStimTimestamp;
private:
    
    float epsilon;
    
    
    
    int refractoryPeriod;
    

};

#endif	/* LEAKYINTEGRATOR_H */

