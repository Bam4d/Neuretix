#include "CNNGlobals.h"


axon::axon()
{
    externalmethod = NULL;
    _TW = NULL;
    synaptic_delay = 1;
    next = NULL;
}

axon::axon(neuron * sourceNeuron, neuron * destNeuron, double fire_mag, int syn_delay)
{
    synaptic_delay = syn_delay;
    fire_magnitude = fire_mag; //set the fire magnitude (alpha) to that passed in the argument
    destination = destNeuron; //set the desination and source neuron of this axon
    source = sourceNeuron;//set the source neuron pointer of the axon
    tofire = false;
    isFiring = 0;

    ctrlpoints[0][0] = sourceNeuron->position.x;
    ctrlpoints[0][1] = sourceNeuron->position.y;
    ctrlpoints[0][2] = sourceNeuron->position.z;

    ctrlpoint_offsets[0][0] = (float)((rand()%200)-100)/200;
    ctrlpoint_offsets[0][1] = (float)((rand()%200)-100)/200;
    ctrlpoint_offsets[0][2] = (float)((rand()%200)-100)/200;

    ctrlpoints[1][0] = sourceNeuron->position.x + ctrlpoint_offsets[0][0];
    ctrlpoints[1][1] = sourceNeuron->position.y + ctrlpoint_offsets[0][1];
    ctrlpoints[1][2] = sourceNeuron->position.z + ctrlpoint_offsets[0][2];

    ctrlpoint_offsets[1][0] = (float)((rand()%200)-100)/200;
    ctrlpoint_offsets[1][1] = (float)((rand()%200)-100)/200;
    ctrlpoint_offsets[1][2] = (float)((rand()%200)-100)/200;

    ctrlpoints[2][0] = destNeuron->position.x + ctrlpoint_offsets[1][0];
    ctrlpoints[2][1] = destNeuron->position.y + ctrlpoint_offsets[1][1];
    ctrlpoints[2][2] = destNeuron->position.z + ctrlpoint_offsets[1][2];

    ctrlpoints[3][0] = destNeuron->position.x;
    ctrlpoints[3][1] = destNeuron->position.y;
    ctrlpoints[3][2] = destNeuron->position.z;


    _TW = NULL;
    externalmethod = NULL;
    next = NULL;
    __join(sourceNeuron); //create the event hook
}

void axon::MoveCtrlPoints()
{

        ctrlpoints[0][0] = source->position.x;
	ctrlpoints[0][1] = source->position.y;
	ctrlpoints[0][2] = source->position.z;

	ctrlpoints[1][0] = source->position.x + ctrlpoint_offsets[0][0];
	ctrlpoints[1][1] = source->position.y + ctrlpoint_offsets[0][1];
	ctrlpoints[1][2] = source->position.z + ctrlpoint_offsets[0][2];

        ctrlpoints[2][0] = destination->position.x + ctrlpoint_offsets[1][0];
	ctrlpoints[2][1] = destination->position.y + ctrlpoint_offsets[1][1];
	ctrlpoints[2][2] = destination->position.z + ctrlpoint_offsets[1][2];

	ctrlpoints[3][0] = destination->position.x;
	ctrlpoints[3][1] = destination->position.y;
	ctrlpoints[3][2] = destination->position.z;
}

axon::axon(neuron * sourceNeuron, void (*destfunction)()) //when a neuron fires, it runs the function defined
{
    externalmethod = destfunction; //assign this axon's external method pointer to the function passed as an argument
    destination = NULL; //destination neuron is null as fires external function
    source = sourceNeuron; //set the source neuron pointer of the axon
    tofire = false;
    isFiring = 0;
    synaptic_delay = 1;
    __join(sourceNeuron); //create the event hook
    _TW = NULL;
    next = NULL;
}

void axon::AcceptFire() //neuron has fired so axon needs to process this fire
{
    if(_TW != NULL)
    {
        _TW->operator [](synaptic_delay)->Add(this);
    }
    else
    {   //time delay set here
        synaptic_delay_counter = synaptic_delay;
        tofire = true; //need to count down synaptic delay in AxonUpdate function
    }
}

void axon::Fire_TW()
{
    if(externalmethod!=NULL)
        externalmethod();
    else destination -> Stimulate_TW(fire_magnitude); //simulate the destination neuron
}

//updates the values in the axons
void axon::UpdateAxon()
{
	if(isFiring>0)
		isFiring--;

	if(tofire) //check if need to do anything here
		if(synaptic_delay_counter <= 0)
		{
			synaptic_delay_counter = 0;
                        if(externalmethod!=NULL) externalmethod();
                        else destination -> Stimulate(fire_magnitude); //simulate the destination neuron
			tofire = false; //doesnt need to count down synaptic delay or fire anymore
			isFiring = 2;
		}
		else
			synaptic_delay_counter -= 1;
}


void axon::__join(neuron* sourceNeuron)
{
    sourceNeuron->outgoingAxons.push_back(this);
}



axon::~axon(void)
{
	//__unhook(&neuron::Fire, source, &axon::AcceptFire);
}
