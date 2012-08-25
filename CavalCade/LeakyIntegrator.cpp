/* 
 * File:   LeakyIntegrator.cpp
 * Author: bam4d
 * 
 * Created on 05 August 2012, 21:28
 */

#include "CNNGlobals.h"

/*
 * creates a leaky integrator channel with the required epsilon, refractory period and a reference to the current time in the host mind
 */
LeakyIntegrator::LeakyIntegrator() 
{
    
}

LeakyIntegrator::LeakyIntegrator(float epsilon, int refractoryPeriod, float threshold) {
    this->epsilon = epsilon;
    this->refractoryPeriod = refractoryPeriod;
    this->threshold = threshold;
    excitationLevel = 0;
    amplitudePeak = 0;
    lastStimTimestamp = 0;
    lastResetTimestamp = 0;
    
    
}

LeakyIntegrator::LeakyIntegrator(const LeakyIntegrator& orig) {
}


/*
 * stimulates this leaky integrator channel with the defined amplitude
 */
bool LeakyIntegrator::Stimulate(float amplitude) {
    if(((*currentTime)-lastResetTimestamp)>refractoryPeriod)
    {
        excitationLevel = amplitudePeak*exp(-(double)((int)((*currentTime)-lastStimTimestamp))/epsilon); //calculate the excitation level
        amplitudePeak = excitationLevel + amplitude; //add the stimulated response onto the potential
        excitationLevel = amplitudePeak; //set the excitation level of the neuron after the fire
    }
    
    lastStimTimestamp = (*currentTime);
    
    if(amplitudePeak>threshold)
        return true;
    else return false;
}

/*
 * resets the LeakyIntegrator channel to its refactory state
 */
void LeakyIntegrator::Reset() {
    amplitudePeak = 0;
    lastResetTimestamp = (*currentTime);
}

LeakyIntegrator::~LeakyIntegrator() {
    currentTime = 0;
}

