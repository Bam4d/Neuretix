/* 
 * File:   SAxon.cpp
 * Author: bam4d
 * 
 * Created on 28 October 2012, 18:21
 */

#include <cstdlib>
#include "../inc/SAxon.h"
#include "../inc/STDPNeuron.h"

SAxon::SAxon() {
    
}

SAxon::SAxon(Neuron * sourceNeuron, Neuron * destNeuron, double fire_mag, int syn_delay) :
    Axon(sourceNeuron,destNeuron,fire_mag,syn_delay)
{

}

SAxon::SAxon(const SAxon& orig) {
}

void SAxon::Fire_TW()
{
    if(externalmethod!=NULL)
        externalmethod(this);
    //want to give a reference to this axon also so we can backpropagate
    else ((STDPNeuron*)destination) -> Stimulate_TW(this,fire_magnitude); //simulate the destination neuron
    //else destination -> Stimulate_TW(fire_magnitude);
}

SAxon::~SAxon() {
}

