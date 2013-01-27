/* 
 * File:   STDPGroup.cpp
 * Author: bam4d
 * 
 * Created on 07 July 2012, 18:04
 */

#include "NeuroplasticityGlobals.h"

STDPGroup::STDPGroup() {
  
}

void STDPGroup::Init(int numNeu, int id, RGB basecol) {
      ID = id; //set the ID of this group
	baseCol = basecol;
	//generate the new neurons
        grouppos = PlotPoint(0,0,0);

	for (int neuron_counter = 0; neuron_counter<numNeu; neuron_counter++)
	{
            Neuron.push_back(new STDPNeuron(id,baseCol));
	    Neuron[neuron_counter]->ID = neuron_counter;
	}
    
}

void STDPGroup::ResetChannels()
{
    for (int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++)
	{
            ((STDPNeuron*)Neuron[neuron_counter])->ResetChannels();
	}
}

STDPGroup::STDPGroup(const STDPGroup& orig) {
}

STDPGroup::~STDPGroup() {
}

