/* 
 * File:   main.cpp
 * Author: bam4d
 *
 * Created on 30 December 2012, 12:23
 */

#include "../CavalCade/CNNGlobals.h"
#include "../NeuroPlasticity/NeuroplasticityGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"
#include "../Structures/Structures.h"
#include <cstdlib>
#include <fstream>

using namespace std;

void JoinInputToOutput(group* source, group* destination, axonList* outputAxonList);
void OutputFired(axon*);
void BurstInput(group*,int,int);
void cycleCallback(CavalcadeMind*);
/*
 * 
 */
int main(int argc, char** argv) {

    ofstream dataOut;

    dataOut.open("test.txt");
    /*create a simple cavalcade networks with a self-organising map output layer, one hidden layer and a simple output layer
     * map the outputs of the output layer to spike graphs to see correlation between learning in this network 
     * */
    
    //first create a genome to contain the mind we are building

    Genome STDPGenome;
    STDPGenome.ClusterMaps.push_back(ClusterMap());
    STDPGenome.ClusterMaps.push_back(ClusterMap());
    STDPGenome.ClusterMaps.push_back(ClusterMap());
    STDPGenome.ClusterMapLinks.push_back(ClusterMapLink());
    
    //create the input group of 5 neurons
    ClusterMap* inputClusterMap = &STDPGenome.ClusterMaps[0]; //everything has to be encoded with cluster map structures for simplicity of conversion into minds.
    group inputGroup;
    inputGroup.Init(5,0,RGB(255,255,255));
    
    ClusterMap* hiddenClusterMap = &STDPGenome.ClusterMaps[1]; //everything has to be encoded with cluster map structures for simplicity of conversion into minds.
    STDPGroup hiddenGroup;
    hiddenGroup.Init(5,1,RGB(255,255,255));
    
    
    //create the output SOM group
    ClusterMap* outputClusterMap = &STDPGenome.ClusterMaps[2];
    //organise the output cluster as a 1D Self-Organising Map
    SelfOrganisingMap::SOM1D(outputClusterMap,5,0.1,1.0);
    
    //set the axons in the output later to call the OutputFunction when they fire
    for(int outputNeurons=0;outputNeurons<5; outputNeurons++)
    {
        outputClusterMap->Axons.Add(new axon(outputClusterMap->clusters[0]->Neuron[outputNeurons],OutputFired));
    }
    
    ClusterMapLink* inputOutputLink = &STDPGenome.ClusterMapLinks[0];
    
    //join the input neurons to the output neurons through the hidden layer axons that have STDP weights
    JoinInputToOutput(&inputGroup,&hiddenGroup,&inputOutputLink->join_axons);
    JoinInputToOutput(&hiddenGroup,outputClusterMap->clusters[0],&inputOutputLink->join_axons);
    
    //add the groups to the input and output clusters
   inputClusterMap->clusters.push_back(&inputGroup);
   
   hiddenClusterMap->clusters.push_back(&hiddenGroup);
   
   CavalcadeMind mind;

   GAEngine::GenomeToMind(&mind,&STDPGenome);
   
    mind.StartMindThread_TW(1000,false);
    
    int inputPatterns[25][2] = { {0,0},{1,0},{2,0},{3,0},{4,0},
                                                {0,1},{1,1},{2,1},{3,1},{4,1},
                                                {0,2},{1,2},{2,2},{3,2},{4,2},
                                                {0,3},{1,3},{2,3},{3,3},{4,3},
                                                {0,4},{1,4},{2,4},{3,4},{4,4}};
                                                
            
    
    for(int epochs = 0; epochs = 100; epochs++)
    {
        for(int inputs = 0; inputs<25; inputs++)
        {
            int input1= inputPatterns[inputs][0];
            int input2 = inputPatterns[inputs][1];
            
            //burst input
            BurstInput(&inputGroup,input1,input2);
            
            usleep(50*1000);
            printf("\ntesting combination %d-%d\n", input1, input2);
        }
    }
}

void OutputFired(axon* fired)
{
    printf("output fire combination %d\n", fired->ID);
}




/* fires a burst of activity
 */
void BurstInput(group* inputGroup, int input1,int input2)
{
    inputGroup->Neuron[input1]->Fire_TW();
    inputGroup->Neuron[input2]->Fire_TW();
    usleep(20*1000);
    inputGroup->Neuron[input1]->Fire_TW();
    inputGroup->Neuron[input2]->Fire_TW();
    usleep(20*1000);
    inputGroup->Neuron[input1]->Fire_TW();
    inputGroup->Neuron[input2]->Fire_TW();
    usleep(20*1000);
    inputGroup->Neuron[input1]->Fire_TW();
    inputGroup->Neuron[input2]->Fire_TW();
    usleep(20*1000);
    inputGroup->Neuron[input1]->Fire_TW();
    inputGroup->Neuron[input2]->Fire_TW();
    usleep(20*1000);
   
}

//join two groups with SAxons
void JoinInputToOutput(group* source, group* destination, axonList* outputAxonList)
{
    for(int numInput = 0; numInput<source->Neuron.size(); numInput++) {
        for(int numOutput = 0; numOutput<destination->Neuron.size(); numOutput++)
        {
            double randomDouble =(double)(rand()%1000)/2000.0;
            outputAxonList->Add(new SAxon(source->Neuron[numInput],destination->Neuron[numOutput],randomDouble,rand()%4));
        }
    }
}

