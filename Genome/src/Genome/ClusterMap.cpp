/* 
 * File:   ClusterMap.cpp
 * Author: bam4d
 * 
 * Created on 23 May 2012, 1:28
 */
#include <errno.h>
#include <sys/stat.h>
#include <cstdio>

#include "../inc/ClusterMap.h"
#include "../../../Neuretix/src/inc/Xml.h"



ClusterMap::ClusterMap() {

    uuid_generate(UUID);
    Dominance = 0;
}

ClusterMap::ClusterMap(int dominance, std::string uuid_str)
{
    Dominance = dominance;
    uuid_parse(uuid_str.c_str(),UUID);
}

int ClusterMap::Save(std::string directory)
{
    
    char uuid_s[36];
    uuid_unparse(UUID,uuid_s);

    std::string uuid_ss = std::string(uuid_s);
    std::string _ClusterMapDir = directory + "/" + uuid_ss;

    //create a directory with the ClusterMap UUID number
    mkdir(_ClusterMapDir.c_str(),S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if(errno == EEXIST)
        return 2; //ClusterMap already saved....

    SaveLoadCNN::SaveClusterData(clusters,_ClusterMapDir+"/clusters.xml");
    SaveLoadCNN::SaveAxonData(&axons,_ClusterMapDir+"/axons.xml");

    SaveClusterMapData(_ClusterMapDir+"/header.chr");

    return 0;
}

int ClusterMap::SaveClusterMapData(std::string filename)
{
    char buf[50];//used for conversion operations

    CMarkup ClusterMapXml;

    ClusterMapXml.AddElem( "ClusterMapData" );
    sprintf(buf,"%d",Dominance);
    ClusterMapXml.SetAttrib("Dominance",buf);

    ClusterMapXml.Save(filename);

    return 0;
}

ClusterMap* ClusterMap::FindClusterMapByUUID(uuid_t uUID, std::vector<ClusterMap>* ClusterMapList) //retunrs a pointer to the group with ID==ID in a cluster
{
    if(ClusterMapList!=NULL)
    {
	for(int ch_c = 0; ch_c<ClusterMapList->size(); ch_c++)
		if(uuid_compare(ClusterMapList->at(ch_c).UUID,uUID)==0) return &ClusterMapList->at(ch_c);
    }
	return NULL;
}

void ClusterMap::Clear()
{
        for(int num_groups = 0; num_groups<clusters.size(); num_groups++)
        {
            delete clusters[num_groups];
        }
    
    clusters.clear();

    
    axons.Empty(); //clear linked list and delete all axons
}


ClusterMap::~ClusterMap() {

    
}

