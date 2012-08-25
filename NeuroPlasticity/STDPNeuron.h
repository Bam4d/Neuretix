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
    
    
   void Stimulate_TW(double);
    
    virtual ~STDPNeuron();
private:
    
    float tiredness; //"tiredness" of the neuron so it will not react as quickly if it is constantly excited

};

#endif	/* STDPNEURON_H */

