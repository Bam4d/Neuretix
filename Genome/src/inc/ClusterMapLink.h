/* 
 * File:   ClusterMapLink.h
 * Author: bam4d
 *
 * Created on 29 April 2011, 16:37
 */

#ifndef CLUSTERMAPLINK_H
#define	CLUSTERMAPLINK_H

#include <string>

#include "../../../Neuretix/src/inc/AxonList.h"
#include "Genetic.h"

class ClusterMapLink : public Genetic {
public:
    ClusterMapLink();
    ClusterMapLink(uuid_t dest, uuid_t src);
    ClusterMapLink(uuid_t dest, uuid_t src,std::string);
    virtual ~ClusterMapLink();

    int Save(std::string);

    void Clear();

    uuid_t SourceClusterMapUUID;
    uuid_t DestinationClusterMapUUID;

    AxonList join_axons;
private:

    void SaveLinkData(std::string,std::string,std::string);

};

#endif	/* CLUSTERMAPLINK_H */

