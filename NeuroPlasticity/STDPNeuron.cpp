/* 
 * File:   STDPNeuron.cpp
 * Author: bam4d
 * 
 * Created on 07 July 2012, 16:27
 */

#include "NeuroplasticityGlobals.h"

STDPNeuron::STDPNeuron() {
    tiredness = 0;
}

STDPNeuron::STDPNeuron(int id, RGB neuCol) :
    neuron(id,neuCol) {
    
    tiredness = 0;
}

STDPNeuron::STDPNeuron(const STDPNeuron& orig) {
}

void STDPNeuron::Stimulate_TW(double amplitude)
{
    /*very useful for forcing a layer using syn algorithm to be stimulated by a TW algorithm layer*/
    if(ParentMind->_t_Window == NULL) Stimulate(amplitude);

     if(ActionPotential.Stimulate(amplitude))
     {
        refractory_countdown = 0;
        Fire_TW();
     }

    impulses_recieved++;
}

STDPNeuron::~STDPNeuron() {
}

