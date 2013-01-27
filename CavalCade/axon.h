class neuron; //neuron is defined later
class TemporalWindow;

class axon
{
	
public:
	axon();
	axon(neuron*,neuron*,double,int);
	axon(neuron*,void (_cdecl)(axon*));
	~axon(void);
	neuron* source; //pointer to the source neuron
	neuron* destination; //pointer to the destination neuron
	double fire_magnitude; // fire magnitude (alpha)
	int synaptic_delay; // time (in units of network updates) taken for axon's synapse to fire
	int synaptic_delay_counter; // counter used to 
	void  (*externalmethod)(axon*); //points to the external method to be called on neuron fire
	int isFiring;
	void UpdateAxon(); //Updates the axon
        void MoveCtrlPoints();
        virtual void Fire_TW(); //fires the neuron after it's synaptic delay in TW mode
	axon* next;
	int ID; // axon ID
    
        

        CyclicCache *_TW;

	float ctrlpoints[4][3];
        float ctrlpoint_offsets[2][3]; //offsets for control points on curved axons
	virtual void AcceptFire(); //function is run when source neuron fires

        //vector<axon*>* axonProcessor; //point to a vector of axon pointers in the parent CavalcadeMind ... used to only update axons that are currently firing
        bool tofire;
private:
        void __join(neuron* sourceNeuron);
	

	
};
