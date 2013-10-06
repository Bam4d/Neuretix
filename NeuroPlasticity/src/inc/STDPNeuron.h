/* 
 * File:   STDPNeuron.h
 * Author: bam4d
 *
 * Created on 07 July 2012, 16:26
 */

#ifndef STDPNEURON_H
#define	STDPNEURON_H

#include "../../../Neuretix/src/inc/Neuron.h"
#include "../../../Neuretix/src/inc/LeakyIntegrator.h"
#include "PreSynapticCyclicCache.h"

class STDPNeuron : public Neuron {
public:
    STDPNeuron();
    STDPNeuron(int,RGB);
    STDPNeuron(const STDPNeuron& orig);
    
    void Stimulate_TW(Axon*,double);
    void Stimulate_TW(double);
   
    void Fire_TW();

    void ResetChannels();
    
    void OutputSTDPCache();

    virtual ~STDPNeuron();

    private:
        PreSynapticCyclicCache feedbackCache;
        LeakyIntegrator fatigue;


};

#endif	/* STDPNEURON_H */

