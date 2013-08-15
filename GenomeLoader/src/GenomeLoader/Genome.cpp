/* 
 * File:   Genome.cpp
 * Author: bam4d
 * 
 * Created on 23 May 2012, 1:28
 */


#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>

#include <cstdio>
#include <string>
#include <vector>

#include "../../../Neuretix/src/inc/Group.h"
#include "../../../Neuretix/src/inc/Xml.h"
#include "../../../CMarkup/Markup.h"

#include "../inc/Genome.h"



Genome::Genome() {

    uuid_generate(GUUID); //generate a UUID for this genome
}

Genome::Genome(const Genome& orig) {
}

int Genome::SaveGenome(std::string directory)
{
    char guuid_s[36];
    uuid_unparse(GUUID,guuid_s);

    std::string guuid_ss = std::string(guuid_s);
    std::string _genomeDir = directory + "/Genome (" + guuid_ss +")";

    //create a directory with the ClusterMap UUID number
    mkdir(_genomeDir.c_str(),S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if(errno == EEXIST)
        return 2; //ClusterMap already saved....
    // save all the ClusterMaps in the genome
    for(int num_ClusterMaps = 0; num_ClusterMaps<clusterMaps.size(); num_ClusterMaps++)
        clusterMaps[num_ClusterMaps].Save(_genomeDir);

    //save all the ClusterMap links
    for(int num_links = 0; num_links<clusterMapLinks.size(); num_links++)
        clusterMapLinks[num_links].Save(_genomeDir);

}

int Genome::LoadGenome(std::string directory, std::string genomeID, bool delAfterLoad)
{
    char buf[255];
    sprintf(buf,"loading genome: %s\n",genomeID.c_str());
    std::cout<<buf;

    std::string _genomePath = directory + "/Genome ("+std::string(genomeID)+")";

    uuid_parse(genomeID.c_str(),GUUID);

    Clear();
    std::vector<std::string> _clusterMaps;
    std::vector<std::string> _clusterMapLinks;
    std::vector<std::string> _sensorDescriptionLists;
    std::string  _agentData;
    DIR *_genomeDir;

    struct dirent *_genomeDirEnt;


     //get Chromosomes
    _genomeDir = opendir (_genomePath.c_str());
    if (_genomeDir != NULL)
    {
       while (_genomeDirEnt = readdir (_genomeDir)) //iterate through the files in the genome
       {
           if(_genomeDirEnt->d_name[0] != '.' && _genomeDirEnt->d_type == DT_DIR) //filter current directiory and previous directory
           {
        	   std::string _headerToFind;
        	   std::string _headerDir = _genomePath+"/"+std::string(_genomeDirEnt->d_name);

               _headerToFind = _headerDir+"/header.chr";
               if(access(_headerToFind.c_str(),F_OK)!=-1)
               _clusterMaps.push_back(std::string(_genomeDirEnt->d_name));

               _headerToFind = _headerDir+"/header.lnk";
               if(access(_headerToFind.c_str(),F_OK)!=-1)
               _clusterMapLinks.push_back(std::string(_genomeDirEnt->d_name));

            }
        }
        closedir (_genomeDir);
    }
    else return 1;


    for(int _clusterMapsCount = 0; _clusterMapsCount<_clusterMaps.size(); _clusterMapsCount++)
    {
        if(LoadClusterMap(_genomePath,_clusterMaps[_clusterMapsCount])==0)
        	std::cout<<"\t\t-ClusterMap loaded!\n\n";
    }

     for(int _clusterMapLinksCount = 0; _clusterMapLinksCount<_clusterMapLinks.size(); _clusterMapLinksCount++)
    {
        if(LoadLink(_genomePath,_clusterMapLinks[_clusterMapLinksCount])==0)
        	std::cout<<"\t\t-Link loaded!\n\n";
    }
    
    if(delAfterLoad) DirectoryDelete(_genomePath.c_str());
     
   return 0;
}

int Genome::DirectoryDelete(const char* dirName)
{
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];

    dir = opendir(dirName);
    if (dir == NULL) {
        perror("Error opendir()");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            snprintf(path, (size_t) PATH_MAX, "%s/%s", dirName, entry->d_name);
            if (entry->d_type == DT_DIR) {
                DirectoryDelete(path);
            }

             remove(path);
             
        }

    }
    closedir(dir);

    //remove the folder
    rmdir(dirName);
    
    return 0;
}

int Genome::LoadClusterMap(std::string genomeDir, std::string ClusterMapUUID)
{
    char buf[255];
    std::string _ClusterMapDirStr;
    CMarkup _ClusterMapHeader;
    DIR *_ClusterMapDir;

    _ClusterMapDirStr = genomeDir + "/" + ClusterMapUUID;

    _ClusterMapDir = opendir (_ClusterMapDirStr.c_str());
   if (_ClusterMapDir != NULL)
   {
       //check for normal ClusterMap first
       if(_ClusterMapHeader.Load(_ClusterMapDirStr+"/header.chr") == true)
       {
           sprintf(buf,"\tClusterMap: %s\n",ClusterMapUUID.c_str());
           std::cout<<buf;
           _ClusterMapHeader.FindElem("ClusterMap");
           clusterMaps.push_back(ClusterMap(atoi(_ClusterMapHeader.GetAttrib("Dominance").c_str()),ClusterMapUUID));

           //load the clusters
           int _clustersCount = SaveLoadCNN::LoadClusterData(_ClusterMapDirStr+"/clusters.xml",&clusterMaps.back().clusters);
           sprintf(buf,"\t\t-Loaded: %d clusters\n",_clustersCount);
           std::cout<<buf;

           //load the axons
           int _axonsCount = SaveLoadCNN::LoadAxonData(_ClusterMapDirStr+"/axons.xml",&clusterMaps.back().axons,&clusterMaps.back().clusters);
           sprintf(buf,"\t\t-Loaded: %d axons.\n",_axonsCount);
           std::cout<<buf;
       }
       else return 1; //is not a ClusterMap
   }
   else return 2; //could not open the ClusterMap directory

   closedir (_ClusterMapDir);

    return 0;
}

int Genome::LoadLink(std::string genomeDir, std::string ClusterMapLinkUUID)
{
    // in header.lnk SrcUUID="2821bf5b-24b2-43ec-b7cc-1d31f3612422" DstUUID="c39a659c-b49e-4778-bed8-34fde93aea06"/>
    char buf[255];
    std::string _linkDirStr;
    CMarkup _linkHeader;
    DIR *_linkDir;

    _linkDirStr = genomeDir + "/" + ClusterMapLinkUUID;

    _linkDir = opendir (_linkDirStr.c_str());
   if (_linkDir != NULL)
   {
       //check for normal ClusterMap first
       if(_linkHeader.Load(_linkDirStr+"/header.lnk") == true)
       {
           sprintf(buf,"\tLink: %s\n",ClusterMapLinkUUID.c_str());
           std::cout<<buf;

           uuid_t _srcUUID;
           uuid_t _destUUID;
           _linkHeader.FindElem("LinkData");
           uuid_parse(_linkHeader.GetAttrib("SrcUUID").c_str(),_srcUUID);
           uuid_parse(_linkHeader.GetAttrib("DstUUID").c_str(),_destUUID);

           clusterMapLinks.push_back(ClusterMapLink(_destUUID,_srcUUID,ClusterMapLinkUUID));

           ClusterMap* _srcChrom = ClusterMap::FindClusterMapByUUID(_srcUUID,&clusterMaps);
           if(_srcChrom == NULL)
           {
               char uuid_s[36];
               uuid_unparse(_srcUUID,uuid_s);
               sprintf(buf,"\t\t-ClusterMap with UUID: %s not found in genome. Aborting link load.",uuid_s);
               std::cout<<buf;
               return 3;
           }
           ClusterMap* _destChrom = ClusterMap::FindClusterMapByUUID(_destUUID,&clusterMaps);
           if(_destChrom == NULL)
           {
               char uuid_s[36];
               uuid_unparse(_destUUID,uuid_s);
               sprintf(buf,"\t\t-ClusterMap with UUID: %s not found in genome. Aborting link load.",uuid_s);
               std::cout<<buf;
               return 3;
           }

           //load the axons from the link
           int _axonsCount = SaveLoadCNN::LoadAxonData(_linkDirStr+"/axons.xml",&clusterMapLinks.back().join_axons,&_destChrom->clusters,&_srcChrom->clusters);
           
           sprintf(buf,"\t\t\t-Loaded: %d axons.\n",_axonsCount);
           std::cout<<buf;
       }
       else return 1; //is not a link
   }
   else return 2; //could not open the link directory

   closedir (_linkDir);

    return 0;
}



void Genome::MoveAllClusters(PlotPoint newLocation)
{
    for(int num_ClusterMaps = 0; num_ClusterMaps<clusterMaps.size(); num_ClusterMaps++)
        for(int num_clusters = 0; num_clusters<clusterMaps[num_ClusterMaps].clusters.size(); num_clusters++)
            clusterMaps[num_ClusterMaps].clusters[num_clusters]->Move(clusterMaps[num_ClusterMaps].clusters[num_clusters]->groupPos+newLocation);
}

void Genome::Clear()
{
    if(clusterMaps.size()>0)
    {
        for(int maps = 0; maps<clusterMaps.size(); maps++)
            clusterMaps[maps].Clear();
        
        clusterMaps.clear();
    }
    if(clusterMapLinks.size()>0)
    {
        for(int maps = 0; maps<clusterMapLinks.size(); maps++)
            clusterMapLinks[maps].Clear();
        
        clusterMapLinks.clear();
    }
}

Genome::~Genome() {
    
}

