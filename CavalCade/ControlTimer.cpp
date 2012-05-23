#include "CNNGlobals.h"



ControlTimer::ControlTimer(int _timeout, string _outputfilename)
{
	Timeout = _timeout;
	DataOut = new ofstream();
	if(_outputfilename.size()!=0)
	{
		DataOut->open(_outputfilename.c_str());
		outputFilename.assign(_outputfilename);
	}

}


ControlTimer::~ControlTimer(void)
{
}

NeuronRecord::NeuronRecord(int _neuronID, int _clusterID)
{ 
	ClusterID = _clusterID;
	NeuronID = _neuronID;
}

NeuronRecord::~NeuronRecord()
{
}

NeuronFires::NeuronFires(int _neuronID, int _clusterID)
{
	ClusterID = _clusterID;
	NeuronID = _neuronID;
}

NeuronFires::~NeuronFires()
{
}

AxonSpikeRecord::AxonSpikeRecord(CavalcadeMind* _mind,int _axonID)
{
	axonToRecord = axonList::FindAxonByID(&_mind->Axons,_axonID);
}

AxonSpikeRecord::~AxonSpikeRecord()
{
}