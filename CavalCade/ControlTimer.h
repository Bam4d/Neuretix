using namespace std;

class NeuronFires
{
public:
	NeuronFires(int, int);
	~NeuronFires();

	int ClusterID; //ID of cluster containing neuron we want to record
	int NeuronID; //ID of neuron we want to record

};


//defines which attribute of which neuron to record either on screen or in a log file
class NeuronRecord
{
public:
	NeuronRecord(int, int);
	~NeuronRecord();

	int ClusterID; //ID of cluster containing neuron we want to record
	int NeuronID; //ID of neuron we want to record
};

//defines which attribute of which axon to record either on screen or in a log file
class AxonSpikeRecord
{
public:
	AxonSpikeRecord(CavalcadeMind*,int);
	~AxonSpikeRecord();

        axon* axonToRecord;
};

class ControlTimer
{
public:
	ControlTimer(int, string);
	ControlTimer();
	~ControlTimer(void);

	//timeout value
	int Timeout;

	

	//lists of things to do at the timeout
	vector<NeuronFires> FireThese;
	vector<NeuronRecord> RecordTheseNeurons;
	vector<AxonSpikeRecord> RecordTheseSpikes;

	ofstream* DataOut;
	//string containing filename of data output
	string outputFilename;
};




