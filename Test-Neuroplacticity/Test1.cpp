#include "../CavalCade/CNNGlobals.h"
#include "../NeuroPlasticity/NeuroplasticityGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"
#include "testHeader.h"
#include <cstdlib>

bool test1neuronfired;

void Test1CycleCallback(CavalcadeMind* mind)
{
    long unsigned int time = mind->CurTime;
    printf("Test 1 - time %d\n", mind->CurTime);
    
    if(time == 1000) //at the first time instance fire the input neuron this should cause the testAxonOutputCallback function to be called at 1003 ms
        mind->Cluster[0]->Neuron[0]->Fire_TW();
    
    if(time == 1003)
    {
        if(test1neuronfired)
        {
            //the neuron has fired so we need to test that the axon's value has been updated correctly
            if(mind->Axons[1]->fire_magnitude == 0.8+0.8*PRESYNAPTIC_LRATE)
                TestCompleted(1,true);
            else
                TestCompleted(1,false);
        }
        else
            TestCompleted(1,false);
    }
    
}

void Test1AxonOutputCallback(axon* axon)
{
  printf("output axon fired\n");  
  test1neuronfired = true;
}

MindAndGenome* StartTest1()
{
    MindAndGenome* mindAndGenome = new MindAndGenome;
    mindAndGenome->genome = new Genome();
    mindAndGenome->mind = new CavalcadeMind();
    
    mindAndGenome->genome->ClusterMaps.push_back(ClusterMap());
    
    
    ClusterMap* cluster = &mindAndGenome->genome->ClusterMaps[0];
    STDPGroup* group = new STDPGroup();
    cluster->clusters.push_back(group);
    group->Init(2,0,RGB(0,0,0));
    
    cluster->Axons.Add(new SAxon(group->Neuron[0],group->Neuron[1],0.8,1));
    cluster->Axons.Add(new axon(group->Neuron[1],Test1AxonOutputCallback));
    
    GAEngine::GenomeToMind(mindAndGenome->mind,mindAndGenome->genome);
    mindAndGenome->mind->StartMindThread_TW(1000,false,Test1CycleCallback);
    
    return mindAndGenome;
    
}

