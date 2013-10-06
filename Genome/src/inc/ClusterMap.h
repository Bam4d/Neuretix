/* 
 * File:   ClusterMap.h
 * Author: bam4d
 *
 *
 * Created on 17 April 2011, 12:48
 */

#ifndef CLUSTERMAP_H
#define	CLUSTERMAP_H

#include <string>
#include <cstring>
#include <vector>

#include "../../../Neuretix/src/inc/AxonList.h"
#include "../inc/Genetic.h"

class Group;

class ClusterMap : public Genetic {
public:
    ClusterMap();
    ClusterMap(int,std::string);

    int Save(std::string); //saves a ClusterMap record in a directory

    AxonList axons;
    std::vector<Group*> clusters;

    static ClusterMap* FindClusterMapByUUID(uuid_t,std::vector<ClusterMap>*);

    void Clear();
    virtual ~ClusterMap();
private:
    int SaveClusterMapData(std::string);

};

#endif	/* CLUSTERMAP_H */

