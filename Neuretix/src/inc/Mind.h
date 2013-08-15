/* 
 * File:   CavalcadeMind.h
 * Author: bam4d
 *
 * Created on 28 November 2010, 14:57
 */

#ifndef CAVALCADEMIND_H
#define	CAVALCADEMIND_H

#include <pthread.h>
#include <vector>

#include "AxonList.h"

class Group;
class Axon;
class CyclicCache;
class PlotPoint;

class Mind {
public:
    AxonList axons; //store the axons as a pointer array
    std::vector<Group*> Cluster; //vector containing neuron clusters

    Mind();
    //int Save(string);
    //int Load(string);


    void iterate();
    void iterate_TW();
    pthread_mutex_t TWmutex; //mutex for stopping TW iterations from corrupting with async input
    pthread_mutex_t SyncMutex; //mutex for stopping Sync iteration from corrupting with async input

    int StartMindThread_TW(int,bool,void (_cdecl)(Mind*));
    int StartMindThread_TW(int,bool);
    int StopMindThread_TW();

    int StartMindThread(int,bool);
    int StopMindThread();

    void Clear();
    void MoveClusters(PlotPoint*);


    virtual ~Mind();

    bool RunNetwork;
    bool RenderGraphics;
    int net_timer;
    int Timer;

    pthread_t mindProcessor;
    CyclicCache* _t_Window;

    long unsigned int CurTime;

private:
    //called on every cycle if not null
    void  (*_cycleCallback)(Mind*);
    char databuf[255]; //buffer to store data in before written to file
    Axon * axon2Update;

};

#endif	/* CAVALCADEMIND_H */

