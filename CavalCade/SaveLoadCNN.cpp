#include "CNNGlobals.h"


SaveLoadCNN::SaveLoadCNN(void)
{
}

SaveLoadCNN::~SaveLoadCNN(void)
{
}



void SaveLoadCNN::SaveAxonData(axonList axons, string FileName)
{
	CMarkup AxonToSave = GetAxonXml(axons);
	AxonToSave.Save(FileName);
}

void SaveLoadCNN::SaveClusterData(vector<group*> ClusterList, string FileName)
{
	CMarkup ClusterToSave = GetClusterXml(ClusterList);
	ClusterToSave.Save(FileName);
}

void SaveLoadCNN::SaveControlMap(string _fileName, vector<ControlTimer>* _controlMap)
{
	CMarkup ControlMapToSave = GetControlMapXML(_controlMap);
	ControlMapToSave.Save(_fileName);
}

void SaveLoadCNN::SaveNetwork(CavalcadeMind* mindToSave, string filename)
{
    string _controlFilename = filename;
    string _axonFilename = filename;
    string _clusterFilename = filename;
    _axonFilename += "-al.xml";
    _clusterFilename += "-cl.xml";
    _controlFilename += "-cm.xml";
    SaveClusterData(mindToSave->Cluster,_clusterFilename);
    SaveAxonData(mindToSave->Axons,_axonFilename);
    SaveControlMap(_controlFilename,&mindToSave->SimulationController);

    CMarkup CNNFile;

    CNNFile.AddElem("NetworkFiles");
    CNNFile.IntoElem();

    CNNFile.AddElem("Cluster");
    CNNFile.SetAttrib("Filename",_clusterFilename.substr(_clusterFilename.find_last_of('/')+1,_clusterFilename.size()-1));

    CNNFile.AddElem("Axons");
    CNNFile.SetAttrib("Filename",_axonFilename.substr(_axonFilename.find_last_of('/')+1,_axonFilename.size()-1));

    CNNFile.AddElem("Cluster");
    CNNFile.SetAttrib("Control",_controlFilename.substr(_controlFilename.find_last_of('/')+1,_controlFilename.size()-1));

    CNNFile.Save(filename.append(".cnn"));
}

int SaveLoadCNN::LoadAxonData(string FileName, axonList * Axon, vector<group*>* Cluster)
{
	CMarkup AxonXml;
	AxonXml.Load(FileName);

	return GetAxonVec(AxonXml, Axon, Cluster);
}

int SaveLoadCNN::LoadAxonData(string FileName, axonList * Axon, vector<group*>* destCluster, vector<group*>* srcCluster)
{
	CMarkup AxonXml;
	AxonXml.Load(FileName);

	return GetAxonVec(AxonXml, Axon, destCluster, srcCluster);
}

int SaveLoadCNN::LoadClusterData(string FileName, vector<group*>* Cluster)
{
	CMarkup ClusterXml;
	ClusterXml.Load(FileName);

	return GetClusterVec(ClusterXml, Cluster);
}

int SaveLoadCNN::LoadControlMap(string _fileName, vector<ControlTimer>* _controlMap)
{
	CMarkup ControlMapXml;
	ControlMapXml.Load(_fileName);

	return GetControlVec(ControlMapXml, _controlMap);
}

void SaveLoadCNN::LoadNetwork(string _fileName, axonList *_axon, vector<group*>* _cluster, vector<ControlTimer>* _controlMap)
{
    string netDir = _fileName.substr(0,_fileName.find_last_of('/'));
    CMarkup _networkXml;
    _networkXml.Load(_fileName);

    _networkXml.FindElem("NetworkFiles");
    _networkXml.IntoElem();

    //load cluster
    _networkXml.FindElem("Cluster");
    LoadClusterData(netDir+"/"+_networkXml.GetAttrib("Filename"),_cluster);
    //load axons
    _networkXml.FindElem("Axons");
    LoadAxonData(netDir+"/"+_networkXml.GetAttrib("Filename"),_axon,_cluster);
    //load control map
    _networkXml.FindElem("Control");
    LoadControlMap(netDir+"/"+_networkXml.GetAttrib("Filename"),_controlMap);

}


CMarkup SaveLoadCNN::GetAxonXml(axonList AxonList)
{
	CMarkup AxonXml;
	char buf[50];//used for conversion operations
	AxonXml.AddElem( "AxonData" );
	AxonXml.IntoElem();
	//AxonList

        axon* axonToSave = AxonList.Head;
        do
	{

            AxonXml.AddElem( "Axon" );

            sprintf(buf,"%d",axonToSave->ID);
            AxonXml.SetAttrib("AID",buf); //axonID

            sprintf(buf,"%d",axonToSave->source->ID);
            AxonXml.SetAttrib("NsID",buf); //source neuronID

            sprintf(buf,"%d",axonToSave->destination->ID);
            AxonXml.SetAttrib("NdID",buf); //desination neuronID

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

CMarkup SaveLoadCNN::GetClusterXml(vector<group*> ClusterList)
{
	
	CMarkup ClusterXml;
	char buf[50];//used for conversion operations
	ClusterXml.AddElem( "ClusterData" );
		ClusterXml.IntoElem();

	for(int l_c = 0; l_c<ClusterList.size(); l_c++)
	{
		ClusterXml.AddElem( "Group" );

                sprintf(buf,"%d",ClusterList[l_c]->ID);
		ClusterXml.SetAttrib("GID",buf);

		sprintf(buf,"%.10f",ClusterList[l_c]->grouppos.x);
		ClusterXml.SetAttrib("x",buf);

		sprintf(buf,"%.10f",ClusterList[l_c]->grouppos.y);
		ClusterXml.SetAttrib("y",buf);

		sprintf(buf,"%.10f",ClusterList[l_c]->grouppos.z);
		ClusterXml.SetAttrib("z",buf);

		sprintf(buf,"%f",ClusterList[l_c]->baseCol.r);
		ClusterXml.SetAttrib("r",buf);

		sprintf(buf,"%f",ClusterList[l_c]->baseCol.g);
		ClusterXml.SetAttrib("g",buf);

		sprintf(buf,"%f",ClusterList[l_c]->baseCol.b);
		ClusterXml.SetAttrib("b",buf);

		ClusterXml.IntoElem();
		for(int n_c = 0; n_c<ClusterList[l_c]->Neuron.size(); n_c++)
		{
			ClusterXml.AddElem( "Neuron" );

                        sprintf(buf,"%d",ClusterList[l_c]->Neuron[n_c]->ID);
			ClusterXml.SetAttrib("NID",buf);

			sprintf(buf,"%.10f",ClusterList[l_c]->Neuron[n_c]->position.x);
			ClusterXml.SetAttrib("x",buf);

			sprintf(buf,"%.10f",ClusterList[l_c]->Neuron[n_c]->position.y);
			ClusterXml.SetAttrib("y",buf);

			sprintf(buf,"%.10f",ClusterList[l_c]->Neuron[n_c]->position.z);
			ClusterXml.SetAttrib("z",buf);

			sprintf(buf,"%.10f",ClusterList[l_c]->Neuron[n_c]->exc_TC);
			ClusterXml.SetAttrib("Epsilon",buf);

			sprintf(buf,"%.10f",ClusterList[l_c]->Neuron[n_c]->fire_threshold);
			ClusterXml.SetAttrib("Threshold",buf);

			sprintf(buf,"%d",ClusterList[l_c]->Neuron[n_c]->refractory_period);
			ClusterXml.SetAttrib("Refractory",buf);

		}
		ClusterXml.OutOfElem();
	}

	return ClusterXml;
}

//save the control mapping to an xml file
CMarkup SaveLoadCNN::GetControlMapXML(vector<ControlTimer>* _simulationController)
{
	CMarkup ControlMapXML;
	char buf[50];//used for conversion operations
	ControlMapXML.AddElem("ControlTimerMap");
	ControlMapXML.IntoElem();

	for(int timeout_count = 0; timeout_count<_simulationController->size(); timeout_count++)
	{
		ControlMapXML.AddElem("Timeout");

                sprintf(buf,"%d",(*_simulationController)[timeout_count].Timeout);
		ControlMapXML.SetAttrib("Time",buf);

		ControlMapXML.SetAttrib("OutputFilename",(*_simulationController)[timeout_count].outputFilename);
		ControlMapXML.IntoElem();
		for(int neuronrecords = 0; neuronrecords<(*_simulationController)[timeout_count].RecordTheseNeurons.size(); neuronrecords++)
		{	
			ControlMapXML.AddElem("RecordNeuron");
                        sprintf(buf,"%d",(*_simulationController)[timeout_count].RecordTheseNeurons[neuronrecords].NeuronID);
			ControlMapXML.SetAttrib("NID",buf);
			sprintf(buf,"%d",(*_simulationController)[timeout_count].RecordTheseNeurons[neuronrecords].ClusterID);
                        ControlMapXML.SetAttrib("GID",buf);
		}

		for(int spikerecords = 0; spikerecords<(*_simulationController)[timeout_count].RecordTheseSpikes.size(); spikerecords++)
		{
			ControlMapXML.AddElem("RecordSpike");
                        sprintf(buf,"%d",(*_simulationController)[timeout_count].RecordTheseSpikes[spikerecords].axonToRecord->ID);
			ControlMapXML.SetAttrib("AID",buf);
		}

		for(int firerecords = 0; firerecords<(*_simulationController)[timeout_count].FireThese.size(); firerecords++)
		{
			ControlMapXML.AddElem("Fires");
                        sprintf(buf,"%d",(*_simulationController)[timeout_count].FireThese[firerecords].NeuronID);
			ControlMapXML.SetAttrib("NID",buf);
			sprintf(buf,"%d",(*_simulationController)[timeout_count].FireThese[firerecords].ClusterID);
                        ControlMapXML.SetAttrib("GID",buf);
		}
		ControlMapXML.OutOfElem();
	}
	return ControlMapXML;
}

int SaveLoadCNN::GetControlVec(CMarkup _controlMapXml, vector<ControlTimer>* _controlMap)
{
	_controlMapXml.FindElem("ControlTimerMap");
	_controlMapXml.IntoElem();

        _controlMap->clear();

	//go into each timer element and find its timeout value, then add the commands at each value
	while(_controlMapXml.FindElem("Timeout"))
	{
		
		//create the initial ControlTimer with filename and time value
		ControlTimer _tempControlTimer = ControlTimer(atoi(_controlMapXml.GetAttrib("Time").c_str()), _controlMapXml.GetAttrib("OutputFilename"));

		//then go into the element to find what we need to do at this timeout
		_controlMapXml.IntoElem();
		while(_controlMapXml.FindElem("RecordNeuron"))
		{
			_tempControlTimer.RecordTheseNeurons.push_back(NeuronRecord(atoi(_controlMapXml.GetAttrib("NID").c_str()),atoi(_controlMapXml.GetAttrib("GID").c_str())));
		}

//		while(_controlMapXml.FindElem("RecordSpike"))
//		{
//			_tempControlTimer.RecordTheseSpikes.push_back(AxonSpikeRecord(atoi(_controlMapXml.GetAttrib("AID").c_str())));
//		}

		while(_controlMapXml.FindElem("Fires"))
		{
			_tempControlTimer.FireThese.push_back(NeuronFires(atoi(_controlMapXml.GetAttrib("NID").c_str()),atoi(_controlMapXml.GetAttrib("GID").c_str())));
		}


		//add the temporary ControlTimer to the _controlMap Vector
		_controlMap->push_back(_tempControlTimer);
		_controlMapXml.OutOfElem();
	}

        return _controlMap->size();
}

int SaveLoadCNN::GetAxonVec(CMarkup AxonXml,axonList * Axon, vector<group*>* Cluster)
{
//	axon_iter = 0;
        bool _sourceFound, _destFound;
        Axon->Clear();
	AxonXml.FindElem("AxonData");
	AxonXml.IntoElem();
	while ( AxonXml.FindElem("Axon") )
	{
		//get a pointer to the source neuron
		neuron* source = neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NsID").c_str()),&group::FindGroupByID(atoi(AxonXml.GetAttrib("GsID").c_str()),Cluster)->Neuron);
		//get a pointer to the destination neuron
		neuron* destination = neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NdID").c_str()),&group::FindGroupByID(atoi(AxonXml.GetAttrib("GdID").c_str()),Cluster)->Neuron);
		
                if(source == NULL)
                {
                    printf("Could not load axon: source neuron not found. NsID=%s, GsID=%s\n", AxonXml.GetAttrib("NsID").c_str(),AxonXml.GetAttrib("GsID").c_str());
                    _sourceFound = false;
                }
                else
                    _sourceFound = true;

                if(destination==NULL)
                {
                    printf("Could not load axon: destination neuron not found NdID=%s, GdID=%s\n", AxonXml.GetAttrib("NdID").c_str(),AxonXml.GetAttrib("GdID").c_str());
                    _destFound = false;
                }
                else
                    _destFound = true;

                if(_destFound &&_sourceFound)
                {
                    //generate axons in specified cluster
                    Axon->Add(new axon(source,destination,atof(AxonXml.GetAttrib("Mag").c_str()),atoi(AxonXml.GetAttrib("SynDelay").c_str())));
                    Axon->ID = atol(AxonXml.GetAttrib("AID").c_str());
                }
	}
        
        return Axon->Count();

}

int SaveLoadCNN::GetAxonVec(CMarkup AxonXml,axonList * Axon, vector<group*>* destCluster, vector<group*>* srcCluster)
{
//	axon_iter = 0;

        Axon->Clear();
	AxonXml.FindElem("AxonData");
	AxonXml.IntoElem();
	while ( AxonXml.FindElem("Axon") )
	{
		//get a pointer to the source neuron
		neuron* source = neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NsID").c_str()),&group::FindGroupByID(atoi(AxonXml.GetAttrib("GsID").c_str()),srcCluster)->Neuron);
		//get a pointer to the destination neuron
		neuron* destination = neuron::FindNeuronByID(atoi(AxonXml.GetAttrib("NdID").c_str()),&group::FindGroupByID(atoi(AxonXml.GetAttrib("GdID").c_str()),destCluster)->Neuron);

                if(source == NULL)
                    printf("Could not load axon: source neuron not found. NsID=%s, GsID=%s\n", AxonXml.GetAttrib("NsID").c_str(),AxonXml.GetAttrib("GsID").c_str());
                if(destination==NULL)
                    printf("Could not load axon: destination neuron not found NdID=%s, GdID=%s\n", AxonXml.GetAttrib("NdID").c_str(),AxonXml.GetAttrib("GdID").c_str());
		//generate axons in specified cluster
                if(source!=NULL&&destination!=NULL)
		Axon->Add(new axon(source,destination,atof(AxonXml.GetAttrib("Mag").c_str()),atoi(AxonXml.GetAttrib("SynDelay").c_str())));
	}

        return Axon->Count();

}

int SaveLoadCNN::GetClusterVec(CMarkup ClusterXml,vector<group*>* Cluster)
{

    PlotPoint gP,nP;
    RGB col;
    vector<neuron*> n_temp;
    int clusterID = 0;

    Cluster->clear(); //clear the vector

    ClusterXml.FindElem("ClusterData");
    ClusterXml.IntoElem();
    while ( ClusterXml.FindElem("Group") )
    {
        clusterID = atoi(ClusterXml.GetAttrib("GID").c_str());
        n_temp.clear();

        //get the colours of the neurons in this group
        col.r = atof(ClusterXml.GetAttrib("r").c_str());
        col.g = atof(ClusterXml.GetAttrib("g").c_str());
        col.b = atof(ClusterXml.GetAttrib("b").c_str());



        ClusterXml.IntoElem();
        while ( ClusterXml.FindElem("Neuron"))
        {

            nP.x = atof(ClusterXml.GetAttrib("x").c_str());
            nP.y = atof(ClusterXml.GetAttrib("y").c_str());
            nP.z = atof(ClusterXml.GetAttrib("z").c_str());

            n_temp.push_back(new neuron(clusterID,
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

        group* _newGroup = new group();
        _newGroup->Init(n_temp,clusterID,gP,col);
        Cluster->push_back(_newGroup);
    }

    return Cluster->size();
}