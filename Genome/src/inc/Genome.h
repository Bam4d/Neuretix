/* 
 * File:   Genome.h
 * Author: bam4d
 *
 * Created on 23 May 2013, 13:46
 */

#ifndef GENOME_H
#define	GENOME_H

#include <string>
#include <vector>

#include "../../../OpenGLRendering/src/inc/Rendering.h"

#include "../inc/ClusterMapLink.h"
#include "../inc/ClusterMap.h"

class Genome {
public:
    Genome();
    Genome(const Genome& orig);

    int SaveGenome(std::string);
    int LoadGenome(std::string,std::string,bool);

    void MoveAllClusters(PlotPoint);
    
    uuid_t GUUID;
    int generation;

    std::vector<ClusterMap> clusterMaps;
    std::vector<ClusterMapLink> clusterMapLinks;

    void Clear();


    virtual ~Genome();
private:
    int LoadClusterMap(std::string,std::string);
    int LoadLink(std::string,std::string);
    
    int DirectoryDelete(const char*);

};

#endif	/* GENOME_H */

