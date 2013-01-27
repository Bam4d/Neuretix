#include "../CavalCade/CNNGlobals.h"
#include "../NeuroPlasticity/NeuroplasticityGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"
#include "testHeader.h"
#include <cstdlib>


/* test that when an axon excites a neuron more than 10 ms before it fires due to other excitations, that it is not updated*/

bool test3neuronfired = false;

STDPNeuron* test3firstPreSynNeuron;
STDPNeuron* test3secondPreSynNeuron;
STDPNeuron* test3outputNeuron;
axon* test3firstPreSynAxon;
axon* test3secondPreSynAxon;
axon* test3outputAxon;

void Test3CycleCallback(CavalcadeMind* mind)
{
    long unsigned int time = mind->CurTime;
    printf("Test 3 - time %d\n", mind->CurTime);
    if(time == 1000) 
    {
        printf("first neuron fired\n");
        test3firstPreSynNeuron->Fire_TW(); //fire the first axon first
    }
    
     if(time == 1010) 
    {
         printf("second neuron fired\n");
        test3secondPreSynNeuron->Fire_TW(); //fire the first axon first
    }
    
    if(time == 1013)
    {
        if(test3neuronfired)
        {
            //the neuron has fired so we need to test that only the axon that causes the neuron to fire and the first axon is not updated
            if(test3secondPreSynAxon->fire_magnitude == 0.8+0.8*PRESYNAPTIC_LRATE && test3firstPreSynAxon->fire_magnitude == 0.3)
                TestCompleted(3,true);
            else
                TestCompleted(3,false);
        }
        else
            TestCompleted(3,false);
    }
    
}

void Test3AxonOutputCallback(axon* axon)
{
  printf("output axon fired\n");  
  test3neuronfired = true;
}

MindAndGenome* StartTest3()
{
    MindAndGenome* mindAndGenome = new MindAndGenome;
    mindAndGenome->genome = new Genome();
    mindAndGenome->mind = new CavalcadeMind();
    
    mindAndGenome->genome->ClusterMaps.push_back(ClusterMap());
    
    
    ClusterMap* cluster = &mindAndGenome->genome->ClusterMaps[0];
    STDPGroup* group = new STDPGroup();
    cluster->clusters.push_back(group);
    group->Init(3,0,RGB(0,0,0));
    
    test3firstPreSynNeuron = (STDPNeuron*)group->Neuron[0];
    test3secondPreSynNeuron = (STDPNeuron*)group->Neuron[1];
    test3outputNeuron = (STDPNeuron*)group->Neuron[2];
    
    //neuron connected to output by a first axon
    test3firstPreSynAxon = new SAxon(test3firstPreSynNeuron,test3outputNeuron,0.3,1);
    cluster->Axons.Add(test3firstPreSynAxon);
    
    // neuron connected by a second axon to the output neuron
    test3secondPreSynAxon = new SAxon(test3secondPreSynNeuron,test3outputNeuron,0.8,1);
    cluster->Axons.Add(test3secondPreSynAxon);
    
    //output callback axon to function
    test3outputAxon = new axon(test3outputNeuron,Test3AxonOutputCallback);
    cluster->Axons.Add(test3outputAxon);
    
    GAEngine::GenomeToMind(mindAndGenome->mind,mindAndGenome->genome);
    mindAndGenome->mind->StartMindThread_TW(1000,false,Test3CycleCallback);
    
    return mindAndGenome;
    
}




