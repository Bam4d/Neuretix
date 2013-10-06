#include "../../../CMarkup/Markup.h"

#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>

class AxonList;
class Mind;
class Group;

class SaveLoadCNN
{
public:
	SaveLoadCNN(void);
	~SaveLoadCNN(void);
	
	static void SaveAxonData(AxonList*, std::string FileName);
	static void SaveClusterData(std::vector<Group*> , std::string FileName);
    static void SaveNetwork(Mind*, std::string);

	static int LoadAxonData(std::string, AxonList*, std::vector<Group*>*);
    static int LoadAxonData(std::string, AxonList*, std::vector<Group*>*,std::vector<Group*>*); // loading axon data across chromosomes
	static int LoadClusterData(std::string, std::vector<Group*>*);

private:
	static CMarkup GetAxonXml(AxonList*);
	static CMarkup GetClusterXml(std::vector<Group*> );

	static int GetAxonVec(CMarkup,AxonList*,std::vector<Group*>*);
    static int GetAxonVec(CMarkup,AxonList*,std::vector<Group*>*,std::vector<Group*>*); // loading axon data across chromosomes
	static int GetClusterVec(CMarkup,std::vector<Group*>* );
	
};



