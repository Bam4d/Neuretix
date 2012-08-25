#include "CNNGlobals.h"
#include "LeakyIntegrator.h"

neuron::neuron()
{
    //LastFireTimestamp = 0;
    S_level = 0;
    S_peak = 0;
    S_TC = DEF_SD_TC;
    ParentMind = NULL;
    
    ActionPotential = LeakyIntegrator(DEF_EXC_TC,10,DEF_FIRETHRESH);
}

neuron::neuron(int PID,RGB col)
{
    //set the default values of all variables
    fire_threshold = DEF_FIRETHRESH;
    impulses_recieved = 0;
    impulses_fired = 0;
    excitation_level = 0;
    exc_TC = DEF_EXC_TC;
    amplitude_peak = 0.0;
    refractory_countdown = 0;
    refractory_period = DEF_REFRAC_TIME;
    excitation_time = 0;
    LastFireTimestamp = 0;
    LastStimTimestamp = 0;
    
    ActionPotential = LeakyIntegrator(DEF_EXC_TC,10,DEF_FIRETHRESH);

    //S initialisation
    S_TC = DEF_SD_TC;
    S_level = 0;
    S_peak = 0;
    S_excitation_time = 0;

    ParentGroupID = PID;

    neuCol = col;
    
    ParentMind = NULL;
}

neuron::neuron(int PID, PlotPoint neuPos, double firethresh, double epsilon, double refrac,RGB col)
{
    ParentGroupID = PID;
    position = neuPos;
    fire_threshold = firethresh;
    exc_TC = epsilon;
    if(refrac!=0)
            refractory_period = refrac;
    else
            refractory_period = DEF_REFRAC_TIME;
    refractory_countdown = 0;

    LastFireTimestamp = 0;
    LastStimTimestamp = 0;
    
    ActionPotential = LeakyIntegrator(DEF_EXC_TC,10,DEF_FIRETHRESH);

    impulses_recieved = 0;
    impulses_fired = 0;
    excitation_level = 0;
    excitation_time = 0;
    amplitude_peak = 0.0;

    S_TC = DEF_SD_TC;
    S_level = 0;
    S_peak = 0;
    S_excitation_time = 0;

    neuCol = col;
    
    ParentMind = NULL;
}

void neuron::Stimulate_TW(double amplitude)
{
    //**DELETE AFTER OXFORD INTERVIEW**//
    if(ParentMind->_t_Window == NULL) Stimulate(amplitude);
    
    if(ActionPotential.Stimulate(amplitude))
    {
        refractory_countdown = 0;
        Fire_TW();
    }
        

    impulses_recieved++;
}

void neuron::Fire_TW()
{
    for(int x=0;x<outgoingAxons.size();x++)
        outgoingAxons[x]->AcceptFire();

    refractory_countdown = refractory_period; //only here to make visualisation cool
    
    S_peak = S_level + DEF_SD_MAG; //add the spike to the current SDPD excitation level
    S_level = S_peak;
    
    ActionPotential.Reset();
    
}

//called to stimulate the current neuron
void neuron::Stimulate(double amplitude)
{


    if(refractory_countdown == 0)
    {

        excitation_level = amplitude_peak*exp(-(excitation_time)/exc_TC); //calculate the excitation level

        if(excitation_level<0.01f) amplitude_peak = 0; //if the potential has dropped below certain value since last stimulus, reset the running sum of consecutive pulses
        
        excitation_time = 0; //reset the time between stimulations
        amplitude_peak = excitation_level + amplitude; //add the stimulated response onto the potential
        excitation_level = amplitude_peak; //set the excitation level of the neuron after the fire

        impulses_recieved++;
    }
}


//called to fire the current neuron
void neuron::Fire()
{
    //cause a spike in SDPD of this neuron to denote 'suppy'
    S_excitation_time  = 0; //reset the time between fires
    S_peak = S_level + DEF_SD_MAG; //add the spike to the current SDPD excitation level
    S_level = S_peak;
    //reset the excitation levels to refractory period and peak to 0
    excitation_level = DEF_REFRAC_LEV;
    amplitude_peak = 0;
    refractory_countdown = refractory_period;

    //raise the event of the neuron firing
    for(int x=0;x<outgoingAxons.size();x++)
        outgoingAxons[x]->AcceptFire();

    impulses_fired++;
}

//updates the potentials
void neuron::UpdatePotentials()
{

    if(refractory_countdown != 0)
    {
        refractory_countdown--;
    }
    else
    {
        //excitation_time++;
        if(amplitude_peak<0)amplitude_peak = 0;
        excitation_time++;
        //excitation_level = amplitude_peak*exp(-(++excitation_time)/exc_TC);

        //update the neuron potential
        if(amplitude_peak>fire_threshold) //if the excitation level is above the threshold value then fire the neuron
        {
            Fire();
        }
    }

    //update the Supply and demand
    S_level = S_peak*exp(-(++S_excitation_time)/S_TC);
    if(S_level<0.01) S_peak = 0; //don't let peaks float if neuron suddenly stops firing
}


neuron* neuron::FindNeuronByID(int ID, vector<neuron*>* neuronList) //returns a pointer to the neuron with ID==ID in a group
{
    if(neuronList!=NULL)
    {
	for(int n_c = 0; n_c<neuronList->size(); n_c++)
		if(neuronList->at(n_c)->ID == ID) return neuronList->at(n_c);
    }
	return NULL;
}

double neuron::calcSLevel_TW()
{
//    if(ParentMind!=NULL) S_level = S_peak*exp(-(double)((int)(ParentMind->CurTime-LastFireTimestamp))/S_TC);
//    else S_level = S_peak;
    return S_level;
}


neuron::~neuron(void)
{
    outgoingAxons.clear();
}
