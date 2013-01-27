#include "../CavalCade/CNNGlobals.h"
#include "../NeuroPlasticity/NeuroplasticityGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"
#include "testHeader.h"
#include <cstdlib>


bool test2neuronfired = false;

neuron* test2weakPreSynNeuron;
neuron* test2strongPreSynNeuron;
neuron* test2outputNeuron;
axon* test2weakPreSynAxon;
axon* test2strongPreSynAxon;
axon* test2outputAxon;

void Test2CycleCallback(CavalcadeMind* mind)
{
    long unsigned int time = mind->CurTime;
    printf("Test 2 - time %d\n", mind->CurTime);
    if(time == 1000) //at the first time instance fire the input neuron this should cause the testAxonOutputCallback function to be called at 1003 ms
    {
        printf("weak neuron fired\n");
        test2weakPreSynNeuron->Fire_TW(); //fire the weak axon first
    }
    
     if(time == 1001) //at the first time instance fire the input neuron this should cause the testAxonOutputCallback function to be called at 1003 ms
    {
         printf("strong neuron fired\n");
        test2strongPreSynNeuron->Fire_TW(); //fire the weak axon first
    }
    
    if(time == 1004)
    {
        if(test2neuronfired)
        {
            //the neuron has fired so we need to test that the strong and weak axons have been updated (they have both contributed within the last 10 ms
            if(test2strongPreSynAxon->fire_magnitude == 0.8+0.8*PRESYNAPTIC_LRATE && test2weakPreSynAxon->fire_magnitude == 0.3+0.3*PRESYNAPTIC_LRATE)
                TestCompleted(2,true);
            else
                TestCompleted(2,false);
        }
        else
            TestCompleted(2,false);
    }
    
}

void Test2AxonOutputCallback(axon* axon)
{
  printf("output axon fired\n");  
  test2neuronfired = true;
}

MindAndGenome* StartTest2()
{
    MindAndGenome* mindAndGenome = new MindAndGenome;
    mindAndGenome->genome = new Genome();
    mindAndGenome->mind = new CavalcadeMind();
    
    mindAndGenome->genome->ClusterMaps.push_back(ClusterMap());
    
    
    ClusterMap* cluster = &mindAndGenome->genome->ClusterMaps[0];
    STDPGroup* group = new STDPGroup();
    cluster->clusters.push_back(group);
    group->Init(3,0,RGB(0,0,0));
    
    test2weakPreSynNeuron = group->Neuron[0];
    test2strongPreSynNeuron = group->Neuron[1];
    test2outputNeuron = group->Neuron[2];
    
    //neuron connected to output by a weak axon
    test2weakPreSynAxon = new SAxon(test2weakPreSynNeuron,test2outputNeuron,0.3,1);
    cluster->Axons.Add(test2weakPreSynAxon);
    
    // neuron connected by a strong axon to the output neuron
    test2strongPreSynAxon = new SAxon(test2strongPreSynNeuron,test2outputNeuron,0.8,1);
    cluster->Axons.Add(test2strongPreSynAxon);
    
    //output callback axon to function
    test2outputAxon = new axon(test2outputNeuron,Test2AxonOutputCallback);
    cluster->Axons.Add(test2outputAxon);
    
    GAEngine::GenomeToMind(mindAndGenome->mind,mindAndGenome->genome);
    mindAndGenome->mind->StartMindThread_TW(1000,false,Test2CycleCallback);
    
    return mindAndGenome;
    
}



