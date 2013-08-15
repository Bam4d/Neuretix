/* 
 * File:   GAEngine.cpp
 * Author: bam4d
 * 
 * Created on 23 May 2012, 1:28
 */

#include "../../../Neuretix/src/inc/Axon.h"
#include "../../../Neuretix/src/inc/AxonList.h"
#include "../../../Neuretix/src/inc/Neuron.h"
#include "../../../Neuretix/src/inc/Group.h"
#include "../../../Neuretix/src/inc/Mind.h"

#include "../inc/ClusterMap.h"
#include "../inc/ClusterMapLink.h"
#include "../inc/Genome.h"
#include "../inc/GAEngine.h"



Neuron GAEngine::ZERO;
Neuron GAEngine::ONE;

GAEngine::GAEngine() {
    ZERO.S_peak = 0;
    ONE.S_peak = 5;
}

//creates a random cluster in a mind
Group* GAEngine::CreateRandomCluster(int maxNeurons,int id)
{
    Group* _newGroup = new Group();
    int _numNeurons = rand()%maxNeurons+1;
    

    RGB _randCol; //set of random colours
    _randCol.r = 1;
    _randCol.g = 0;
    _randCol.b = 0;

    
    _newGroup->Init(_numNeurons,0,_randCol);
    _newGroup->id = id;
    //set random points of the neurons
    for(int n_c = 0;n_c<_numNeurons;n_c++)
    {
        _newGroup->neurons[n_c]->position = PlotPoint((float)(rand()%_numNeurons-_numNeurons/2)/50.0,(float)(rand()%_numNeurons-_numNeurons/2)/50.0,(float)(rand()%_numNeurons-_numNeurons/2)/50.0);
        _newGroup->neurons[n_c]->id = n_c;
        _newGroup->neurons[n_c]->ParentGroupID = id;
    }
    return _newGroup;
}

//creates a set of random axons joining two clusters together
AxonList* GAEngine::CreateRandomAxons(int maxAxons, Group* firstCluster, Group* secondCluster,float minAmp,float maxAmp,int minSyn,int maxSyn)
{
    int _numAxons = maxAxons;
    int _numNeuInFirstCluster = firstCluster->neurons.size();
    int _numNeuInSecondCluster = secondCluster->neurons.size();

    AxonList* _randomAxons = new AxonList();
    //set random axon connections in the group
    for(int n_a = 0;n_a<_numAxons;n_a++)
    {
        Neuron* source = Neuron::FindNeuronByID(rand()%_numNeuInFirstCluster,&firstCluster->neurons);
        Neuron* dest = Neuron::FindNeuronByID(rand()%_numNeuInSecondCluster,&secondCluster->neurons);

        float amplitude = ((maxAmp+minAmp)/2)+((((float)(rand()%1000)/1000.0f)-0.5)*(maxAmp-minAmp));
        int synapticdelay = ((maxSyn+minSyn)/2)+((((float)(rand()%1000)/1000.0f)-0.5)*(maxSyn-minSyn));
        if(source!=NULL && dest != NULL)
        _randomAxons->Add(new Axon(source,dest,amplitude,synapticdelay));
        //printf("adding axon: G%d N%d-> G%dN%d \n",firstCluster->ID,source->ID,secondCluster->ID,dest->ID);
    }

    return _randomAxons;
}

Group * GAEngine::DuplicateCluster(Group* _toDuplicate)
{
	Group * _newGroup = new Group(*_toDuplicate);

    _newGroup->neurons.clear();//remove the pointers to neurons in duplicatee cluster
    //firstly duplicate all the neurons (in memory) in the group
    for(int n_c = 0;n_c<_toDuplicate->neurons.size();n_c++)
    {
        _newGroup->neurons.push_back(new Neuron(*_toDuplicate->neurons[n_c]));
        //performs a shallow copy of the neurons... (still with outgoing axon lists... need to get rid of these!!!
        _newGroup->neurons.back()->outgoingAxons.clear();
    }
    

    return _newGroup;
}

ClusterMap GAEngine::DuplicateClusterMap(ClusterMap * _toDuplicate)
{
    ClusterMap _newClusterMap = ClusterMap();

    for(int n_c = 0; n_c<_toDuplicate->clusters.size(); n_c++)
    {
        _newClusterMap.clusters.push_back(DuplicateCluster(_toDuplicate->clusters[n_c]));
    }

    DuplicateAxonList(_toDuplicate,&_newClusterMap);

    uuid_copy(_newClusterMap.UUID,_toDuplicate->UUID);

    return _newClusterMap;
}

ClusterMap GAEngine::DuplicateClusterMap_InGenome(ClusterMap * _toDuplicate)
{
    ClusterMap _newClusterMap = ClusterMap();

    for(int n_c = 0; n_c<_toDuplicate->clusters.size(); n_c++)
    {
        _newClusterMap.clusters.push_back(DuplicateCluster(_toDuplicate->clusters[n_c]));
    }

    DuplicateAxonList(_toDuplicate,&_newClusterMap);

    return _newClusterMap;
}

void GAEngine::DuplicateAxonList(ClusterMap* _toDuplicate, ClusterMap* _newClusterMap)
{

    Axon* _axonToDuplicate = _toDuplicate->axons.Head;
    do
    {
        //find the source and destination neurons
        Group* _newSourceGroup = Group::FindGroupByID(_axonToDuplicate->source->ParentGroupID,&_newClusterMap->clusters);
        Group* _newDestinationGroup = Group::FindGroupByID(_axonToDuplicate->destination->ParentGroupID,&_newClusterMap->clusters);
        
        Neuron* _newSource = Neuron::FindNeuronByID(_axonToDuplicate->source->id,&_newSourceGroup->neurons);
        Neuron* _newDestination = Neuron::FindNeuronByID(_axonToDuplicate->destination->id,&_newDestinationGroup->neurons);
        _newClusterMap->axons.Add(new Axon(_newSource,_newDestination,_axonToDuplicate->fire_magnitude,_axonToDuplicate->synaptic_delay));

        _axonToDuplicate = _axonToDuplicate->next;
    }
    while(_axonToDuplicate != NULL);
}

ClusterMapLink GAEngine::CreateClusterMapLink(ClusterMap* dest, int dest_CID, ClusterMap* src, int src_CID, int maxAxons)
{
    ClusterMapLink _newLink = ClusterMapLink(dest->UUID,src->UUID);
    Group* _src_group = Group::FindGroupByID(src_CID,&src->clusters);
    Group* _dest_group = Group::FindGroupByID(dest_CID,&dest->clusters);

    AxonList::Join(&_newLink.join_axons,CreateRandomAxons(maxAxons,_src_group,_dest_group,0.1,0.7,5,15));

    return _newLink;
}

int GAEngine::AddClusterMapToMind(Mind* _mind, ClusterMap* _ClusterMap)
{
    for(int n_c = 0; n_c<_ClusterMap->clusters.size(); n_c++)
    {
        //make sure the ID numbers of clusters are unique in a mind
        _ClusterMap->clusters[n_c]->id = _mind->Cluster.size();
        
        //change the parent group ID for the neurons in this cluster
        for(int n_n = 0; n_n<_ClusterMap->clusters[n_c]->neurons.size(); n_n++)
        {
            _ClusterMap->clusters[n_c]->neurons[n_n]->ParentMind = _mind;
            _ClusterMap->clusters[n_c]->neurons[n_n]->ActionPotential.currentTime = &_mind->CurTime;
            _ClusterMap->clusters[n_c]->neurons[n_n]->ParentGroupID = _ClusterMap->clusters[n_c]->id;
        }

        _mind->Cluster.push_back(_ClusterMap->clusters[n_c]);
    }

    AxonList::Join(&_mind->axons,&_ClusterMap->axons);

    return 0;
}

int GAEngine::AddClusterMapLinkToMind(Mind* _mind, ClusterMapLink* _link)
{
    AxonList::Join(&_mind->axons,&_link->join_axons);

    return 0;
}

int GAEngine::GenomeToMind(Mind* _mind, Genome* _genome)
{
    if(_genome->clusterMaps.size()==0 && _genome->clusterMapLinks.size() ==0)
        return 1;
    
    for(int n_ch = 0; n_ch<_genome->clusterMaps.size(); n_ch++) //add the ClusterMaps to the mind
    {
        AddClusterMapToMind(_mind,&_genome->clusterMaps[n_ch]);
    }

    for(int n_chl = 0; n_chl<_genome->clusterMapLinks.size(); n_chl++) //add the ClusterMap links to the mind
    {
        AddClusterMapLinkToMind(_mind,&_genome->clusterMapLinks[n_chl]);
    }

    return 0;
}

GAEngine::GAEngine(const GAEngine& orig) {
}

GAEngine::~GAEngine() {
}

