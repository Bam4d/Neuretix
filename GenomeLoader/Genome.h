/* 
 * File:   Genome.h
 * Author: bam4d
 *
 * Created on 23 May 2013, 13:46
 */

#ifndef GENOME_H
#define	GENOME_H

class Genome {
public:
    Genome();
    Genome(const Genome& orig);

    int SaveGenome(string);
    int LoadGenome(string,string,bool);

    void MoveAllClusters(PlotPoint);
    
    uuid_t GUUID;
    int generation;

    vector<ClusterMap> ClusterMaps;
    vector<ClusterMapLink> ClusterMapLinks;

    void Clear();


    virtual ~Genome();
private:
    int LoadClusterMap(string,string);
    int LoadLink(string,string);
    
    int DirectoryDelete(const char*);

};

#endif	/* GENOME_H */

