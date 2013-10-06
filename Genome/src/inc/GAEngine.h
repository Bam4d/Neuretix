/* 
 * File:   GAEngine.h
 * Author: bam4d
 *
 * Created on 23 May 2012 1:45
 */



#ifndef GAENGINE_H
#define	GAENGINE_H

class Neuron;
class Group;
class AxonList;
class ClusterMap;
class ClusterMapLink;
class Genome;

class GAEngine {
public:
    GAEngine();
    GAEngine(const GAEngine& orig);
    virtual ~GAEngine();

    Group* CreateRandomCluster(int,int);
    AxonList* CreateRandomAxons(int,Group*,Group*,float,float,int,int);

    ClusterMapLink CreateClusterMapLink(ClusterMap*,int,ClusterMap*,int,int);

    static int GenomeToMind(Mind*,Genome*); //converts the Genome description to a CavalcadeMind instance

    ClusterMap DuplicateClusterMap(ClusterMap*); //duplicates a ClusterMap's clusters axons, makes sure axon's source and destination pointers are updated
    ClusterMap DuplicateClusterMap_InGenome(ClusterMap*); //same as DuplicateClusterMap, but assigns a new UUID.. so acts as a seperate ClusterMap in the genome

    //neurons that have a constant S_Level of 0 or 1
    static Neuron ONE;
    static Neuron ZERO;
private:
    Group* DuplicateCluster(Group*); //duplicates a cluster and all the neurons contained
    void DuplicateAxonList(ClusterMap*,ClusterMap*); //duplicates an axonList and pointers of axons

    static int AddClusterMapToMind(Mind*, ClusterMap*);
    static int AddClusterMapLinkToMind(Mind*, ClusterMapLink* );
};

#endif	/* GAENGINE_H */

