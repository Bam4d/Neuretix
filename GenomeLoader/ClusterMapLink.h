/* 
 * File:   ClusterMapLink.h
 * Author: bam4d
 *
 * Created on 29 April 2011, 16:37
 */

#ifndef CLUSTERMAPLINK_H
#define	CLUSTERMAPLINK_H

class ClusterMapLink : public Genetic {
public:
    ClusterMapLink();
    ClusterMapLink(uuid_t dest, uuid_t src);
    ClusterMapLink(uuid_t dest, uuid_t src,string);
    virtual ~ClusterMapLink();

    int Save(string);
    
    void Mutate();
    void Cross(void*);

    void Clear();

    uuid_t SourceClusterMapUUID;
    uuid_t DestinationClusterMapUUID;

    axonList join_axons;
private:

    void SaveLinkData(string,string,string);

};

#endif	/* CLUSTERMAPLINK_H */

