/* 
 * File:   CavalcadeMind.cpp
 * Author: bam4d
 * 
 * Created on 28 November 2010, 14:57
 */

#include "CNNGlobals.h"
#include "CavalcadeMind.h"

//have to do this for pthread in c++
extern "C"
{
    //processes all neurons in Mind through one iteration of time
    void *NetUpdate(void* arg)
    {
        CavalcadeMind* _mind = static_cast<CavalcadeMind*>(arg);

        if(_mind!=NULL)
        {
            do
            {
                usleep(_mind->net_timer); //1000 microseconds = 1 milisecond
                pthread_mutex_lock(&_mind->SyncMutex);
                _mind->iterate();
                _mind->Timer++;
                pthread_mutex_unlock(&_mind->SyncMutex);
            }
            while(_mind->RunNetwork);
            usleep(50);
        }
        else
        {
            printf("Could not start mind thread.");
        }
        pthread_exit(NULL);


        return 0;
    }

    //processes all neurons in Mind through one iteration of time
    void *NetUpdate_TW(void* arg)
    {
        CavalcadeMind* _mind = static_cast<CavalcadeMind*>(arg);

        if(_mind!=NULL)
        {
            do
            {
                usleep(_mind->net_timer); //1000 microseconds = 1 milisecond
                pthread_mutex_lock(&_mind->TWmutex); //make sure that no async inputs can interrupt while this iteration completes
                _mind->iterate_TW();
                _mind->Timer++;
                pthread_mutex_unlock(&_mind->TWmutex);

            }
            while(_mind->RunNetwork);
            usleep(50);
        }
        else
        {
            printf("Could not start mind thread.");
        }
        pthread_exit(NULL);


        return 0;
    }
}

CavalcadeMind::CavalcadeMind() {
    RunNetwork = false;
    RenderGraphics = false;
    Timer = 0;

    CPU_SET(0,&affinitySet);
    CPU_SET(1,&affinitySet);
    CPU_SET(2,&affinitySet);
    CPU_SET(3,&affinitySet);
    CPU_SET(4,&affinitySet);
    CPU_SET(5,&affinitySet);

    SyncMutex = PTHREAD_MUTEX_INITIALIZER;
    TWmutex = PTHREAD_MUTEX_INITIALIZER;
    mindProcessor = 0;
    _t_Window = NULL;
    CurTime = 0;

}

void CavalcadeMind::iterate_TW()
{ //TW method for updating system, TW = Temporal Window
    TimePoint* _curTimePoint = &_t_Window->Window[_t_Window->CurrentPoint];

    int num_firedaxons = 0;
    axon_event* fire = _curTimePoint->axon_eventLLHead;
    while(_curTimePoint->num_axonsToFire>num_firedaxons)
    {
        fire->fireThis->Fire_TW();
        //////////////////////// record the spike
//        if(CurTime>4000 && CurTime<5000 && fire->fireThis->ID<200)
//        {
//            sprintf(databuf,"%d\t%d\n",CurTime,fire->fireThis->ID);
//             (*SimulationController[0].DataOut) << databuf;
//        }
        /////////////////////////
        fire = fire->next;
        num_firedaxons++;
    }
    
    _curTimePoint->num_axonsToFire = 0; //reset the amount of axons in this time point to 0;
    _curTimePoint->next_axon_event = _curTimePoint->axon_eventLLHead;
    _t_Window->CurrentPoint++;
    if(_t_Window->CurrentPoint>_t_Window->MaxPoints-1)
        _t_Window->CurrentPoint = 0;

//    for(int l_c = 0; l_c<Cluster.size(); l_c++) //update all the groups of neurons
//            Cluster[l_c]->UpdateGroup();


    CurTime++; //iterate the millisecond counter

}

void CavalcadeMind::iterate()
{
    for(int l_c = 0; l_c<Cluster.size(); l_c++) //update all the groups of neurons
            Cluster[l_c]->UpdateGroup();

    axon2Update = Axons.Head; //make rendering as efficient as possible

    if(axon2Update!=NULL)
    do
    {
        axon2Update->UpdateAxon(); //update the timings of the axons
        axon2Update = axon2Update->next;
    }
    while(axon2Update!=NULL);

    for(int timeout_count = 0; timeout_count<SimulationController.size(); timeout_count++)
    {
        if(Timer%SimulationController[timeout_count].Timeout == 0)
        {
            for(int neuronrecords = 0; neuronrecords<SimulationController[timeout_count].RecordTheseNeurons.size(); neuronrecords++)
            {
                sprintf(databuf,"%.4f ", Cluster[SimulationController[timeout_count].RecordTheseNeurons[neuronrecords].ClusterID]->Neuron[SimulationController[timeout_count].RecordTheseNeurons[neuronrecords].NeuronID]->excitation_level);
                (*SimulationController[timeout_count].DataOut) << databuf;
            }

            for(int spikerecords = 0; spikerecords<SimulationController[timeout_count].RecordTheseSpikes.size(); spikerecords++)
            {
                if(Timer>=4000&&Timer<=8000)
                if(SimulationController[timeout_count].RecordTheseSpikes[spikerecords].axonToRecord->isFiring>0)
                {
                    sprintf(databuf,"%d\t%d\n",Timer,SimulationController[timeout_count].RecordTheseSpikes[spikerecords].axonToRecord->ID);
                    (*SimulationController[timeout_count].DataOut) << databuf;
                }
            }
            //write a new line in the log file as all data has been logged
//            if((*SimulationController[timeout_count].DataOut) != NULL)
//            {
//                sprintf(databuf,"\n");
//                (*SimulationController[timeout_count].DataOut) << databuf;
//            }

            for(int firerecords = 0; firerecords<SimulationController[timeout_count].FireThese.size(); firerecords++)
            {
               Cluster[SimulationController[timeout_count].FireThese[firerecords].ClusterID]->Neuron[SimulationController[timeout_count].FireThese[firerecords].NeuronID]->Fire();
            }
        }

    }
    
}

int CavalcadeMind::StartMindThread(int netTimer, bool render)
{
    net_timer = netTimer;
    RunNetwork = true;
    if(render) RenderGraphics = true;
    
    //only let the mind threads run on the first 6 processors
    pthread_create(&mindProcessor, NULL, NetUpdate, this);
    pthread_setaffinity_np(mindProcessor,CPU_COUNT(&affinitySet),&affinitySet);
}

int CavalcadeMind::StartMindThread_TW(int netTimer, bool render)
{
    net_timer = netTimer;
    RunNetwork = true;
    if(render) RenderGraphics = true;

    _t_Window = new TemporalWindow(20); //generate a 20ms temporal window
    Axons.SetTW(_t_Window); //set the temporal window of this mind's axonlist to the one just created

    //only let the mind threads run on the first 6 processors
    pthread_create(&mindProcessor, NULL, NetUpdate_TW, this);
    pthread_setaffinity_np(mindProcessor,CPU_COUNT(&affinitySet),&affinitySet);
}

int CavalcadeMind::StopMindThread_TW()
{
    RunNetwork = false;
    RenderGraphics = false;
    if(mindProcessor!=NULL)pthread_join(mindProcessor,NULL);
    if(_t_Window!=NULL) {_t_Window->Release(); delete _t_Window; _t_Window = NULL;} //release the temporal window variables
}


int CavalcadeMind::StopMindThread()
{
    RunNetwork = false;
    RenderGraphics = false;
    if(mindProcessor!=NULL)pthread_join(mindProcessor,NULL);
}

void CavalcadeMind::Clear()
{
    //clear linked list but don't deallocate memory as this is done by genome layer
    Axons.Clear();
    //clear vector but don't deallocate memory
    Cluster.clear();
}

void CavalcadeMind::MoveClusters(PlotPoint newPosition)
{
    for(int clus = 0; clus<Cluster.size(); clus++)
        Cluster[clus]->Move(Cluster[clus]->grouppos+newPosition);//  move the Clusters by a set amount newPosition
}


CavalcadeMind::~CavalcadeMind()
{
    //Clear();
}

