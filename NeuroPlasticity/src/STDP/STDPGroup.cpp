/* 
 * File:   STDPGroup.cpp
 * Author: bam4d
 * 
 * Created on 07 July 2012, 18:04
 */

#include "../inc/STDPGroup.h"
#include "../inc/STDPNeuron.h"


STDPGroup::STDPGroup() {
  
}

void STDPGroup::Init(int numNeu, int id, RGB baseCol) {
    this->id = id; //set the ID of this group
    this->baseCol = baseCol;
	//generate the new neurons
	groupPos = PlotPoint(0,0,0);

	for (int neuron_counter = 0; neuron_counter<numNeu; neuron_counter++)
	{
		neurons.push_back(new STDPNeuron(id,this->baseCol));
		neurons[neuron_counter]->id = neuron_counter;
	}
    
}

void STDPGroup::ResetChannels()
{
    for (int neuron_counter = 0; neuron_counter<neurons.size(); neuron_counter++)
	{
            ((STDPNeuron*)neurons[neuron_counter])->ResetChannels();
	}
}

STDPGroup::STDPGroup(const STDPGroup& orig) {
}

STDPGroup::~STDPGroup() {
}

