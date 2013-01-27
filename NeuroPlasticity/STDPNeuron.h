/* 
 * File:   STDPNeuron.h
 * Author: bam4d
 *
 * Created on 07 July 2012, 16:26
 */

#ifndef STDPNEURON_H
#define	STDPNEURON_H

class STDPNeuron : public neuron {
public:
    STDPNeuron();
    STDPNeuron(int,RGB);
    STDPNeuron(const STDPNeuron& orig);
    
    void Stimulate_TW(axon*,double);
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

