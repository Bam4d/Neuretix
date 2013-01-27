/* 
 * File:   GenerateSOM.cpp
 * Author: bam4d
 * 
 * Created on 28 June 2012, 21:41
 */

#include "Structures.h"

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
            clusterMap->clusters[0]->Neuron[dimx*y+x]->position = PlotPoint(x*separation-(dimx*separation)/2.0f,y*separation-(dimy*separation)/2.0f,0);
            //clusterMap->clusters.back()->Line(separation,PlotPoint(0,0,x*separation-dimx*separation/2), 1);
        }
    
    
    //
    for(int _firstPass = 0; _firstPass<dimy*dimx; _firstPass++)
        for(int _secondPass = 0; _secondPass<dimy*dimx; _secondPass++)
        {
            
            if(inhibitoryDistance>CalculateDistance(clusterMap->clusters[0]->Neuron[_firstPass]->position,clusterMap->clusters[0]->Neuron[_secondPass]->position) && _firstPass!=_secondPass)
            {
                clusterMap->Axons.Add(new axon(clusterMap->clusters[0]->Neuron[_firstPass],clusterMap->clusters[0]->Neuron[_secondPass],(float)(rand()%100)/600.0f,rand()%20));
            }
        }
    
}

float SelfOrganisingMap::CalculateDistance(PlotPoint _a, PlotPoint _b)
{
    return sqrt(pow(_b.x-_a.x,2)+pow(_b.y-_a.y,2)+pow(_b.z-_a.z,2));
}


void SelfOrganisingMap::SOM1D(ClusterMap* clusterMap,int dimx,float separation,float inhibitoryDistance)
{
    STDPGroup* _newGroup = new STDPGroup();
    _newGroup->Init(dimx,0,RGB(1,0,0));

    clusterMap->clusters.push_back(_newGroup);
    clusterMap->clusters.back()->Line(separation,PlotPoint(0,0,dimx*separation/2), 1);
    
    
    for(int _firstPass = 0; _firstPass<dimx; _firstPass++)
        for(int _secondPass = 0; _secondPass<dimx; _secondPass++)
        {
            
            if(inhibitoryDistance>CalculateDistance(clusterMap->clusters[0]->Neuron[_firstPass]->position,clusterMap->clusters[0]->Neuron[_secondPass]->position) && _firstPass!=_secondPass)
            {
                clusterMap->Axons.Add(new axon(clusterMap->clusters[0]->Neuron[_firstPass],clusterMap->clusters[0]->Neuron[_secondPass],-0.3f,1));
            }
        }
}
