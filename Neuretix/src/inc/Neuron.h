
#ifndef NEURON_H
#define	NEURON_H

#include <cstdlib>
#include <vector>
#include "../../../OpenGLRendering/src/inc/Rendering.h"
#include "LeakyIntegrator.h"

class Mind;
class Axon;

class Neuron
{
public:
	Neuron();
	Neuron(int,RGB);
	Neuron(int,PlotPoint,double,double,double,RGB);

    void Fire();
    void Fire_TW();

    void Stimulate(double);
    virtual void Stimulate_TW(double);
    
    int impulses_recieved;
    int impulses_fired;
    
    void UpdatePotentials();
    void IntroduceDemand(double);
    void PropagatedDemand(double magnitude);
    
    double calcSLevel_TW();

    virtual ~Neuron(void);


    //neuron firing potential variables
    double amplitude_peak; //max amplitude at last stimulation
    double fire_threshold; //threshold for firing the neuron
    double exc_TC; //excitability epsilon
    int refractory_period; //resting period time
    int refractory_countdown; //counts down the refractory time for animations
    double excitation_level; //current excitation level of neuron
    LeakyIntegrator ActionPotential;

    int id;
    //graphical output variables
    PlotPoint position;
    RGB neuCol;
    int ParentGroupID; //the group this neuron belongs to

    //list of axon fire functions this neuron is connected to
    std::vector<Axon*> outgoingAxons;

    //used in TW network update methods
    Mind* ParentMind;
    long unsigned int LastFireTimestamp; //time since this neuron last fired
    long unsigned int LastStimTimestamp; //time since this neuron was last stimulated

    
    double S_peak; //max amplitude at last supply spike
    static Neuron* FindNeuronByID(int id, std::vector<Neuron*>* neuronList);

protected:
    double excitation_time; //time since last excitation
    double S_excitation_time; //excitation time for Supply level
    double S_TC; //Time constant for decay of Supply potential
    double S_level; //current level of supply
    
};

#endif
