/* 
 * File:   ClusterMap.h
 * Author: bam4d
 *
 *
 * Created on 17 April 2011, 12:48
 */

#ifndef CLUSTERMAP_H
#define	CLUSTERMAP_H

class ClusterMap : public Genetic {
public:
    ClusterMap();
    ClusterMap(int,string);

    int Save(string); //saves a ClusterMap record in a directory

    axonList Axons;
    vector<group*> clusters;

    static ClusterMap* FindClusterMapByUUID(uuid_t,vector<ClusterMap>*);

    void Clear();
    virtual ~ClusterMap();
private:
    int SaveClusterMapData(string);

};

#endif	/* CLUSTERMAP_H */

