/* 
 * File:   GAEngine.cpp
 * Author: bam4d
 * 
 * Created on 23 May 2012, 1:28
 */



#include "../CavalCade/CNNGlobals.h"
#include "GenomeLoaderGlobals.h"

neuron GAEngine::ZERO;
neuron GAEngine::ONE;

GAEngine::GAEngine() {
    ZERO.S_peak = 0;
    ONE.S_peak = 5;
}

//creates a random cluster in a mind
group* GAEngine::CreateRandomCluster(int maxNeurons,int id)
{
    group* _randomCluster;
    int _numNeurons = rand()%maxNeurons+1;
    

    RGB _randCol; //set of random colours
    _randCol.r = 1;
    _randCol.g = 0;
    _randCol.b = 0;

    _randomCluster = new group(_numNeurons,0,_randCol);
    _randomCluster->ID = id;
    //set random points of the neurons
    for(int n_c = 0;n_c<_numNeurons;n_c++)
    {
        _randomCluster->Neuron[n_c]->position = PlotPoint((float)(rand()%_numNeurons-_numNeurons/2)/50.0,(float)(rand()%_numNeurons-_numNeurons/2)/50.0,(float)(rand()%_numNeurons-_numNeurons/2)/50.0);
        _randomCluster->Neuron[n_c]->ID = n_c;
        _randomCluster->Neuron[n_c]->ParentGroupID = id;
    }
    return _randomCluster;
}

//creates a set of random axons joining two clusters together
axonList* GAEngine::CreateRandomAxons(int maxAxons, group* firstCluster, group* secondCluster,float minAmp,float maxAmp,int minSyn,int maxSyn)
{
    int _numAxons = maxAxons;
    int _numNeuInFirstCluster = firstCluster->Neuron.size();
    int _numNeuInSecondCluster = secondCluster->Neuron.size();

    axonList* _randomAxons = new axonList();
    //set random axon connections in the group
    for(int n_a = 0;n_a<_numAxons;n_a++)
    {
        neuron* source = neuron::FindNeuronByID(rand()%_numNeuInFirstCluster,&firstCluster->Neuron);
        neuron* dest = neuron::FindNeuronByID(rand()%_numNeuInSecondCluster,&secondCluster->Neuron);

        float amplitude = ((maxAmp+minAmp)/2)+((((float)(rand()%1000)/1000.0f)-0.5)*(maxAmp-minAmp));
        int synapticdelay = ((maxSyn+minSyn)/2)+((((float)(rand()%1000)/1000.0f)-0.5)*(maxSyn-minSyn));
        if(source!=NULL && dest != NULL)
        _randomAxons->Add(new axon(source,dest,amplitude,synapticdelay));
        //printf("adding axon: G%d N%d-> G%dN%d \n",firstCluster->ID,source->ID,secondCluster->ID,dest->ID);
    }

    return _randomAxons;
}

group * GAEngine::DuplicateCluster(group* _toDuplicate)
{
    group * _newGroup = new group(*_toDuplicate);

    _newGroup->Neuron.clear();//remove the pointers to neurons in duplicatee cluster
    //firstly duplicate all the neurons (in memory) in the group
    for(int n_c = 0;n_c<_toDuplicate->Neuron.size();n_c++)
    {
        _newGroup->Neuron.push_back(new neuron(*_toDuplicate->Neuron[n_c]));
        //performs a shallow copy of the neurons... (still with outgoing axon lists... need to get rid of these!!!
        _newGroup->Neuron.back()->outgoingAxons.clear();
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

    axon* _axonToDuplicate = _toDuplicate->Axons.Head;
    do
    {
        //find the source and destination neurons
        group* _newSourceGroup = group::FindGroupByID(_axonToDuplicate->source->ParentGroupID,&_newClusterMap->clusters);
        group* _newDestinationGroup = group::FindGroupByID(_axonToDuplicate->destination->ParentGroupID,&_newClusterMap->clusters);
        
        neuron* _newSource = neuron::FindNeuronByID(_axonToDuplicate->source->ID,&_newSourceGroup->Neuron);
        neuron* _newDestination = neuron::FindNeuronByID(_axonToDuplicate->destination->ID,&_newDestinationGroup->Neuron);
        _newClusterMap->Axons.Add(new axon(_newSource,_newDestination,_axonToDuplicate->fire_magnitude,_axonToDuplicate->synaptic_delay));

        _axonToDuplicate = _axonToDuplicate->next;
    }
    while(_axonToDuplicate != NULL);
}

ClusterMapLink GAEngine::CreateClusterMapLink(ClusterMap* dest, int dest_CID, ClusterMap* src, int src_CID, int maxAxons)
{
    ClusterMapLink _newLink = ClusterMapLink(dest->UUID,src->UUID);
    group* _src_group = group::FindGroupByID(src_CID,&src->clusters);
    group* _dest_group = group::FindGroupByID(dest_CID,&dest->clusters);

    axonList::Join(&_newLink.join_axons,CreateRandomAxons(maxAxons,_src_group,_dest_group,0.1,0.7,5,15));

    return _newLink;
}

int GAEngine::AddClusterMapToMind(CavalcadeMind* _mind, ClusterMap* _ClusterMap)
{
    for(int n_c = 0; n_c<_ClusterMap->clusters.size(); n_c++)
    {
        //make sure the ID numbers of clusters are unique in a mind
        _ClusterMap->clusters[n_c]->ID = _mind->Cluster.size();
        
        //change the parent group ID for the neurons in this cluster
        for(int n_n = 0; n_n<_ClusterMap->clusters[n_c]->Neuron.size(); n_n++)
        {
            _ClusterMap->clusters[n_c]->Neuron[n_n]->ParentMind = _mind;
            _ClusterMap->clusters[n_c]->Neuron[n_n]->ParentGroupID = _ClusterMap->clusters[n_c]->ID;
        }

        _mind->Cluster.push_back(_ClusterMap->clusters[n_c]);
    }

    axonList::Join(&_mind->Axons,&_ClusterMap->Axons);

    return 0;
}

int GAEngine::AddClusterMapLinkToMind(CavalcadeMind* _mind, ClusterMapLink* _link)
{
    axonList::Join(&_mind->Axons,&_link->join_axons);

    return 0;
}

int GAEngine::GenomeToMind(CavalcadeMind* _mind, Genome* _genome)
{
    if(_genome->ClusterMaps.size()==0 && _genome->ClusterMapLinks.size() ==0)
        return 1;
    
    for(int n_ch = 0; n_ch<_genome->ClusterMaps.size(); n_ch++) //add the ClusterMaps to the mind
    {
        AddClusterMapToMind(_mind,&_genome->ClusterMaps[n_ch]);
    }

    for(int n_chl = 0; n_chl<_genome->ClusterMapLinks.size(); n_chl++) //add the ClusterMap links to the mind
    {
        AddClusterMapLinkToMind(_mind,&_genome->ClusterMapLinks[n_chl]);
    }

    return 0;
}

GAEngine::GAEngine(const GAEngine& orig) {
}

GAEngine::~GAEngine() {
}

