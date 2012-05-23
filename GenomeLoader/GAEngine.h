/* 
 * File:   GAEngine.h
 * Author: bam4d
 *
 * Created on 23 May 2012 1:45
 */

#ifndef GAENGINE_H
#define	GAENGINE_H


class GAEngine {
public:
    GAEngine();
    GAEngine(const GAEngine& orig);
    virtual ~GAEngine();

    group* CreateRandomCluster(int,int);
    axonList* CreateRandomAxons(int,group*,group*,float,float,int,int);

    ClusterMapLink CreateClusterMapLink(ClusterMap*,int,ClusterMap*,int,int);

    static int GenomeToMind(CavalcadeMind*,Genome*); //converts the Genome description to a CavalcadeMind instance

    ClusterMap DuplicateClusterMap(ClusterMap*); //duplicates a ClusterMap's clusters axons, makes sure axon's source and destination pointers are updated
    ClusterMap DuplicateClusterMap_InGenome(ClusterMap*); //same as DuplicateClusterMap, but assigns a new UUID.. so acts as a seperate ClusterMap in the genome

    //neurons that have a constant S_Level of 0 or 1
    static neuron ONE;
    static neuron ZERO;
private:
    group* DuplicateCluster(group*); //duplicates a cluster and all the neurons contained
    void DuplicateAxonList(ClusterMap*,ClusterMap*); //duplicates an axonList and pointers of axons

    static int AddClusterMapToMind(CavalcadeMind*, ClusterMap*);
    static int AddClusterMapLinkToMind(CavalcadeMind*, ClusterMapLink* );
};

#endif	/* GAENGINE_H */

