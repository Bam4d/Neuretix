/* 
 * File:   STDPNeuron.cpp
 * Author: bam4d
 * 
 * Created on 07 July 2012, 16:27
 */

#define PRESYNAPTIC_LRATE 0.001
#define POSTSYNAPTIC_LRATE 0.001
#define SYNAPTIC_FATIGUE_RATE 0.006

#include "../inc/SAxon.h"
#include "../inc/STDPNeuron.h"
#include "../inc/PreSynapticTimePoint.h"
#include "../inc/PreSynapticEvent.h"
#include "../../../Neuretix/src/inc/Mind.h"


STDPNeuron::STDPNeuron() {
    fatigue = LeakyIntegrator(5000,0,0);
    feedbackCache = PreSynapticCyclicCache(10,20); //10 ms backpropagate cache
}

STDPNeuron::STDPNeuron(int id, RGB neuCol) :
    Neuron(id,neuCol) {
    
    fatigue = LeakyIntegrator(5000,0,0);
    feedbackCache = PreSynapticCyclicCache(10,20); //10 ms backpropagate cache
}

STDPNeuron::STDPNeuron(const STDPNeuron& orig) {
}

void STDPNeuron::ResetChannels()
{
    fatigue.Reset();
}

void STDPNeuron::Fire_TW()
{

    //for every axon pointer stored in the list currently
    for(int numTimePoints = 0; numTimePoints<feedbackCache.maxPoints; numTimePoints++)
    {
        int numUpdatedAxons = 0;
        while(feedbackCache.cache[numTimePoints].numEvents>numUpdatedAxons)
        {
            PreSynapticEvent* preSynapticSpikes = (PreSynapticEvent*)feedbackCache.cache[numTimePoints].eventLLHead;
         
            //adjust the strength of the axon depending on how long ago it fired
            preSynapticSpikes->adjustThis->fire_magnitude += preSynapticSpikes->adjustThis->fire_magnitude*PRESYNAPTIC_LRATE; //make it stronger if it contributed

            preSynapticSpikes = (PreSynapticEvent*)preSynapticSpikes->next;
            numUpdatedAxons++;
        }
        
        //reset the cache for this timepoint
        feedbackCache.cache[numTimePoints].numEvents = 0;
    }
   
   Neuron::Fire_TW();
}

void STDPNeuron::Stimulate_TW(Axon* parent, double amplitude) 
{
    
    //10ms refactory period
    if(this->ParentMind->CurTime - ActionPotential.lastResetTimestamp <=10)
        parent->fire_magnitude -= parent->fire_magnitude*POSTSYNAPTIC_LRATE; //make it weaker as it is after the last fire 
    //get the cycles since the last stimulation
    int doCycles = this->ParentMind->CurTime - ActionPotential.lastStimTimestamp;
    
    
    //cycle the cache to get rid of not needed synaptic history
    if(doCycles>feedbackCache.maxPoints)
        feedbackCache.Reset();
    else
        feedbackCache.Cycle(doCycles);
    
    //add this axon to the cache so we can feedback to it
    ((PreSynapticTimePoint*)feedbackCache.currentTimePoint)->Add(parent);
    
    Stimulate_TW(amplitude);
}

void STDPNeuron::Stimulate_TW(double amplitude)
{
    /*very useful for forcing a layer using syn algorithm to be stimulated by a TW algorithm layer*/
    if(ParentMind->_t_Window == NULL) Stimulate(amplitude);

     if(ActionPotential.Stimulate(amplitude-fatigue.amplitudePeak))
     {
        refractory_countdown = 0;
        Fire_TW();

        //calculate the fatigue of the neuron and how it affects the stimulation amplitude
        fatigue.currentTime = &this->ParentMind->CurTime;
        
        fatigue.Stimulate(SYNAPTIC_FATIGUE_RATE);
     }

    impulses_recieved++;
}

void STDPNeuron::OutputSTDPCache()
{
    feedbackCache.LogState();
}

STDPNeuron::~STDPNeuron(){
}

