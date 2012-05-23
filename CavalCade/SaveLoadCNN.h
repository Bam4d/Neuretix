using namespace std;

class SaveLoadCNN
{
public:
	SaveLoadCNN(void);
	~SaveLoadCNN(void);
	
	
	static void SaveAxonData(axonList, string FileName);
	static void SaveClusterData(vector<group*> , string FileName);
	static void SaveControlMap(string, vector<ControlTimer>*);
        static void SaveNetwork(CavalcadeMind*,string);

	static int LoadAxonData(string, axonList*, vector<group*>*);
        static int LoadAxonData(string, axonList*, vector<group*>*,vector<group*>*); // loading axon data across chromosomes
	static int LoadClusterData(string, vector<group*>*);
	static int LoadControlMap(string,vector<ControlTimer>*);
	static void LoadNetwork(string, axonList*, vector<group*>*, vector<ControlTimer>*);

private:
	static CMarkup GetAxonXml(axonList);
	static CMarkup GetClusterXml(vector<group*> );
	static CMarkup GetControlMapXML(vector<ControlTimer>*);

	static int GetAxonVec(CMarkup,axonList*,vector<group*>*);
        static int GetAxonVec(CMarkup,axonList*,vector<group*>*,vector<group*>*); // loading axon data across chromosomes
	static int GetClusterVec(CMarkup,vector<group*>* );
	static int GetControlVec(CMarkup,vector<ControlTimer>*);
	
};



