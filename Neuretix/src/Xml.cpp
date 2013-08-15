#include <cstdio>

#include "inc/Axon.h"
#include "inc/Group.h"
#include "inc/AxonList.h"
#include "inc/Xml.h"


SaveLoadCNN::SaveLoadCNN(void)
{
}

SaveLoadCNN::~SaveLoadCNN(void)
{
}



void SaveLoadCNN::SaveAxonData(AxonList* axons, std::string FileName)
{
	CMarkup AxonToSave = GetAxonXml(axons);
	AxonToSave.Save(FileName);
}

void SaveLoadCNN::SaveClusterData(std::vector<Group*> ClusterList, std::string FileName)
{
	CMarkup ClusterToSave = GetClusterXml(ClusterList);
	ClusterToSave.Save(FileName);
}

int SaveLoadCNN::LoadAxonData(std::string FileName, AxonList* axon, std::vector<Group*>* cluster)
{
	CMarkup axonXml;
	axonXml.Load(FileName);

	return GetAxonVec(axonXml, axon, cluster);
}

int SaveLoadCNN::LoadAxonData(std::string fileName, AxonList * axon, std::vector<Group*>* destCluster, std::vector<Group*>* srcCluster)
{
	CMarkup axonXml;
	axonXml.Load(fileName);

	return GetAxonVec(axonXml, axon, destCluster, srcCluster);
}

int SaveLoadCNN::LoadClusterData(std::string fileName, std::vector<Group*>* cluster)
{
	CMarkup clusterXml;
	clusterXml.Load(fileName);

	return GetClusterVec(clusterXml, cluster);
}


CMarkup SaveLoadCNN::GetAxonXml(AxonList* axonList)
{
	CMarkup AxonXml;
	char buf[50];//used for conversion operations
	AxonXml.AddElem( "AxonData" );
	AxonXml.IntoElem();

	Axon* axonToSave = axonList->Head;
	do
	{

            AxonXml.AddElem( "Axon" );

            sprintf(buf,"%d",axonToSave->ID);
            AxonXml.SetAttrib("AID",buf); //axonID

            sprintf(buf,"%d",axonToSave->source->id);
            AxonXml.SetAttrib("NsID",buf); //source NeuronID

            sprintf(buf,"%d",axonToSave->destination->id);
            AxonXml.SetAttrib("NdID",buf); //desination NeuronID

            sprintf(buf,"%d",axonToSave->source->ParentGroupID);
            AxonXml.SetAttrib("GsID",buf);//source groupID

            sprintf(buf,"%d",axonToSave->destination->ParentGroupID);
            AxonXml.SetAttrib("GdID",buf);//desination groupID
            
            sprintf(buf,"%d",axonToSave->synaptic_delay);
            AxonXml.SetAttrib("SynDelay",buf); // synaptic delay of axon
            
            sprintf(buf,"%.10f",axonToSave->fire_magnitude); //fire magnitude
            AxonXml.SetAttrib("Mag",buf);

            axonToSave = axonToSave->next;
	}
        while(axonToSave != NULL);

	return AxonXml;

}

CMarkup SaveLoadCNN::GetClusterXml(std::vector<Group*> clusterList)
{
	CMarkup ClusterXml;
	char buf[50];//used for conversion operations
	ClusterXml.AddElem( "ClusterData" );
		ClusterXml.IntoElem();

	for(int l_c = 0; l_c<clusterList.size(); l_c++)
	{

		ClusterXml.AddElem( "Group" );
		Group* g = clusterList[l_c];
		sprintf(buf, "%d", g->id);
		ClusterXml.SetAttrib("GID",buf);

		sprintf(buf,"%.10f",g->groupPos.x);
		ClusterXml.SetAttrib("x",buf);

		sprintf(buf,"%.10f",g->groupPos.y);
		ClusterXml.SetAttrib("y",buf);

		sprintf(buf,"%.10f",g->groupPos.z);
		ClusterXml.SetAttrib("z",buf);

		sprintf(buf,"%f",g->baseCol.r);
		ClusterXml.SetAttrib("r",buf);

		sprintf(buf,"%f",g->baseCol.g);
		ClusterXml.SetAttrib("g",buf);

		sprintf(buf,"%f",g->baseCol.b);
		ClusterXml.SetAttrib("b",buf);

		ClusterXml.IntoElem();
		for(int n_c = 0; n_c<g->neurons.size(); n_c++)
		{
			Neuron* n = g->neurons[n_c];
			ClusterXml.AddElem( "Neuron" );

            sprintf(buf,"%d",n->id);
			ClusterXml.SetAttrib("NID",buf);

			sprintf(buf,"%.10f",n->position.x);
			ClusterXml.SetAttrib("x",buf);

			sprintf(buf,"%.10f",n->position.y);
			ClusterXml.SetAttrib("y",buf);

			sprintf(buf,"%.10f",n->position.z);
			ClusterXml.SetAttrib("z",buf);

			sprintf(buf,"%.10f",n->exc_TC);
			ClusterXml.SetAttrib("Epsilon",buf);

			sprintf(buf,"%.10f",n->fire_threshold);
			ClusterXml.SetAttrib("Threshold",buf);

			sprintf(buf,"%d",n->refractory_period);
			ClusterXml.SetAttrib("Refractory",buf);

		}
		ClusterXml.OutOfElem();
	}

	return ClusterXml;
}

int SaveLoadCNN::GetAxonVec(CMarkup AxonXml,AxonList * axonList, std::vector<Group*>* Cluster)
{
//	axon_iter = 0;
	bool _sourceFound, _destFound;
	axonList->Clear();
	AxonXml.FindElem("AxonData");
	AxonXml.IntoElem();
	while ( AxonXml.FindElem("Axon") )
	{
		//get a pointer to the source Neuron
		Neuron* source = Neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NsID").c_str()),&Group::FindGroupByID(atoi(AxonXml.GetAttrib("GsID").c_str()),Cluster)->neurons);
		//get a pointer to the destination Neuron
		Neuron* destination = Neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NdID").c_str()),&Group::FindGroupByID(atoi(AxonXml.GetAttrib("GdID").c_str()),Cluster)->neurons);
		
		if(source == NULL)
		{
			printf("Could not load axon: source Neuron not found. NsID=%s, GsID=%s\n", AxonXml.GetAttrib("NsID").c_str(),AxonXml.GetAttrib("GsID").c_str());
			_sourceFound = false;
		}
		else
			_sourceFound = true;

		if(destination==NULL)
		{
			printf("Could not load axon: destination Neuron not found NdID=%s, GdID=%s\n", AxonXml.GetAttrib("NdID").c_str(),AxonXml.GetAttrib("GdID").c_str());
			_destFound = false;
		}
		else
			_destFound = true;

		if(_destFound &&_sourceFound)
		{
			//generate axons in specified cluster
			axonList->Add(new Axon(source,destination,atof(AxonXml.GetAttrib("Mag").c_str()),atoi(AxonXml.GetAttrib("SynDelay").c_str())));
			axonList->ID = atol(AxonXml.GetAttrib("AID").c_str());
		}
	}
        
        return axonList->Count();

}

int SaveLoadCNN::GetAxonVec(CMarkup AxonXml,AxonList * axon, std::vector<Group*>* destCluster, std::vector<Group*>* srcCluster)
{
//	axon_iter = 0;

        axon->Clear();
	AxonXml.FindElem("AxonData");
	AxonXml.IntoElem();
	while ( AxonXml.FindElem("Axon") )
	{
		//get a pointer to the source Neuron
		Neuron* source = Neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NsID").c_str()),&Group::FindGroupByID(atoi(AxonXml.GetAttrib("GsID").c_str()),srcCluster)->neurons);
		//get a pointer to the destination Neuron
		Neuron* destination = Neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NdID").c_str()),&Group::FindGroupByID(atoi(AxonXml.GetAttrib("GdID").c_str()),destCluster)->neurons);

                if(source == NULL)
                    printf("Could not load axon: source Neuron not found. NsID=%s, GsID=%s\n", AxonXml.GetAttrib("NsID").c_str(),AxonXml.GetAttrib("GsID").c_str());
                if(destination==NULL)
                    printf("Could not load axon: destination Neuron not found NdID=%s, GdID=%s\n", AxonXml.GetAttrib("NdID").c_str(),AxonXml.GetAttrib("GdID").c_str());
		//generate axons in specified cluster
                if(source!=NULL&&destination!=NULL)
		axon->Add(new Axon(source,destination,atof(AxonXml.GetAttrib("Mag").c_str()),atoi(AxonXml.GetAttrib("SynDelay").c_str())));
	}

        return axon->Count();

}

int SaveLoadCNN::GetClusterVec(CMarkup ClusterXml, std::vector<Group*>* Cluster)
{

    PlotPoint gP,nP;
    RGB col;
    std::vector<Neuron*> n_temp;
    int clusterID = 0;

    Cluster->clear(); //clear the vector

    ClusterXml.FindElem("ClusterData");
    ClusterXml.IntoElem();
    while ( ClusterXml.FindElem("Group") )
    {
        clusterID = atoi(ClusterXml.GetAttrib("GID").c_str());
        n_temp.clear();

        //get the colours of the Neurons in this group
        col.r = atof(ClusterXml.GetAttrib("r").c_str());
        col.g = atof(ClusterXml.GetAttrib("g").c_str());
        col.b = atof(ClusterXml.GetAttrib("b").c_str());



        ClusterXml.IntoElem();
        while ( ClusterXml.FindElem("Neuron"))
        {

            nP.x = atof(ClusterXml.GetAttrib("x").c_str());
            nP.y = atof(ClusterXml.GetAttrib("y").c_str());
            nP.z = atof(ClusterXml.GetAttrib("z").c_str());

            n_temp.push_back(new Neuron(clusterID,
                                    nP,
                                    atof(ClusterXml.GetAttrib("Threshold").c_str()),
                                    atof(ClusterXml.GetAttrib("Epsilon").c_str()),
                                    atoi(ClusterXml.GetAttrib("Refractory").c_str()),
                                    col
                                    ));
        }
        ClusterXml.OutOfElem();

        gP.x = atof(ClusterXml.GetAttrib("x").c_str());
        gP.y = atof(ClusterXml.GetAttrib("y").c_str());
        gP.z = atof(ClusterXml.GetAttrib("z").c_str());

        Group* _newGroup = new Group();
        _newGroup->Init(n_temp,clusterID,gP,col);
        Cluster->push_back(_newGroup);
    }

    return Cluster->size();
}
