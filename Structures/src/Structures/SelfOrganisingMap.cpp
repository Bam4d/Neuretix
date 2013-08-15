/* 
 * File:   GenerateSOM.cpp
 * Author: bam4d
 * 
 * Created on 28 June 2012, 21:41
 */


#include "../../../Neuretix/src/inc/Axon.h"
#include "../../../NeuroPlasticity/src/inc/STDPGroup.h"
#include "../../../GenomeLoader/src/inc/ClusterMap.h"
#include "../inc/SelfOrganisingMap.h"

/**
 * class used to generate self organising maps
 */
void SelfOrganisingMap::SOM2D(ClusterMap* clusterMap,int dimx,int dimy, float separation, float inhibitoryDistance)
{
    
    STDPGroup* _newGroup = new STDPGroup();
    _newGroup->Init(dimy*dimx,0,RGB(1,0,0));
    
    clusterMap->clusters.push_back(_newGroup);
    
    for(int y = 0; y<dimy; y++)
        for(int x = 0; x<dimx; x++)
        {
            clusterMap->clusters[0]->neurons[dimx*y+x]->position = PlotPoint(x*separation-(dimx*separation)/2.0f,y*separation-(dimy*separation)/2.0f,0);
        }
    
    
    //
    for(int _firstPass = 0; _firstPass<dimy*dimx; _firstPass++)
        for(int _secondPass = 0; _secondPass<dimy*dimx; _secondPass++)
        {
            
            if(inhibitoryDistance>CalculateDistance(clusterMap->clusters[0]->neurons[_firstPass]->position,clusterMap->clusters[0]->neurons[_secondPass]->position) && _firstPass!=_secondPass)
            {
                clusterMap->axons.Add(new Axon(clusterMap->clusters[0]->neurons[_firstPass],clusterMap->clusters[0]->neurons[_secondPass],(float)(rand()%100)/600.0f,rand()%20));
            }
        }
    
}

float SelfOrganisingMap::CalculateDistance(PlotPoint _a, PlotPoint _b)
{
    return sqrt(pow(_b.x-_a.x,2)+pow(_b.y-_a.y,2)+pow(_b.z-_a.z,2));
}


STDPGroup* SelfOrganisingMap::SOM1D(ClusterMap* clusterMap,int numNeurons, float separation, PlotPoint position,float inhibitoryDistance)
{
    STDPGroup* _newGroup = new STDPGroup();
    _newGroup->Init(numNeurons,0,RGB(255,0,0));

    clusterMap->clusters.push_back(_newGroup);
    clusterMap->clusters.back()->Line(separation,position, 0);
    
    
    for(int _firstPass = 0; _firstPass<numNeurons; _firstPass++)
        for(int _secondPass = 0; _secondPass<numNeurons; _secondPass++)
        {
            
            if(inhibitoryDistance>CalculateDistance(_newGroup->neurons[_firstPass]->position,_newGroup->neurons[_secondPass]->position) && _firstPass!=_secondPass)
            {
                clusterMap->axons.Add(new Axon(_newGroup->neurons[_firstPass],_newGroup->neurons[_secondPass],-0.3f,1));
            }
        }
    
    return _newGroup;
}
