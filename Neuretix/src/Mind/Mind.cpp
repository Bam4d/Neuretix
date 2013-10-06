/* 
 * File:   CavalcadeMind.cpp
 * Author: bam4d
 * 
 * Created on 28 November 2010, 14:57
 */
#include <cstdio>
#include <unistd.h>
#include "../inc/Axon.h"
#include "../inc/Group.h"
#include "../inc/AxonEvent.h"
#include "../inc/CyclicCacheTimePoint.h"
#include "../inc/CyclicCache.h"
#include "../inc/AxonList.h"
#include "../inc/Mind.h"

//have to do this for pthread in c++
extern "C"
{
    //processes all neurons in Mind through one iteration of time
    void *NetUpdate(void* arg)
    {
        Mind* _mind = static_cast<Mind*>(arg);

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
        Mind* _mind = static_cast<Mind*>(arg);

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

Mind::Mind() {
    RunNetwork = false;
    RenderGraphics = false;
    Timer = 0;

    SyncMutex = PTHREAD_MUTEX_INITIALIZER;
    TWmutex = PTHREAD_MUTEX_INITIALIZER;
    mindProcessor = 0;
    _t_Window = NULL;
    
    //dont wnat to set this as 0!!!
    CurTime = 1000;

}

void Mind::iterate_TW()
{ //TW method for updating system, TW = Temporal Window

    int num_firedaxons = 0;
    AxonEvent* fire = (AxonEvent*)_t_Window->currentTimePoint->eventLLHead;
    while(_t_Window->currentTimePoint->numEvents>num_firedaxons)
    {
        fire->fireThis->Fire_TW();

        fire = (AxonEvent*)fire->next;
        num_firedaxons++;
    }
    
   _t_Window->Cycle();
   
    if(_cycleCallback!=NULL) _cycleCallback(this);
    CurTime++; //iterate the millisecond counter

}

void Mind::iterate()
{
    for(int l_c = 0; l_c<cluster.size(); l_c++) //update all the groups of neurons
            ((Group*)cluster[l_c])->UpdateGroup();

    axon2Update = axons.Head; //make rendering as efficient as possible

    if(axon2Update!=NULL)
    do
    {
        axon2Update->UpdateAxon(); //update the timings of the axons
        axon2Update = axon2Update->next;
    }
    while(axon2Update!=NULL);

}

int Mind::StartMindThread(int netTimer, bool render)
{
    net_timer = netTimer;
    RunNetwork = true;
    if(render) RenderGraphics = true;

    pthread_create(&mindProcessor, NULL, NetUpdate, this);
}

int Mind::StartMindThread_TW(int netTimer, bool render, void (*cycleCallback)(Mind*))
{
    _cycleCallback = cycleCallback;
    StartMindThread_TW(netTimer,render);
}

int Mind::StartMindThread_TW(int netTimer, bool render)
{
    _cycleCallback = NULL;
    net_timer = netTimer;
    RunNetwork = true;
    if(render) RenderGraphics = true;

    _t_Window = new CyclicCache(20,20); //generate a 20ms temporal window
    axons.SetTW(_t_Window); //set the temporal window of this mind's axonlist to the one just created

    pthread_create(&mindProcessor, NULL, NetUpdate_TW, this);
}

int Mind::StopMindThread_TW()
{
    RunNetwork = false;
    RenderGraphics = false;
    if(mindProcessor!=NULL)pthread_join(mindProcessor,NULL);
    if(_t_Window!=NULL) {_t_Window->Release(); delete _t_Window; _t_Window = NULL;} //release the temporal window variables
}


int Mind::StopMindThread()
{
    RunNetwork = false;
    RenderGraphics = false;
    if(mindProcessor!=NULL)pthread_join(mindProcessor,NULL);
}

void Mind::Clear()
{
    //clear linked list but don't deallocate memory as this is done by genome layer
    axons.Clear();
    //clear vector but don't deallocate memory
    cluster.clear();
}

void Mind::MoveClusters(PlotPoint* newPosition)
{
    for(int clus = 0; clus<cluster.size(); clus++) {
    	Group* cluster_p = cluster[clus];
    	cluster_p->Move(cluster_p->groupPos+*newPosition);//  move the Clusters by a set amount newPosition
    }

}


Mind::~Mind()
{
    //Clear();
}

