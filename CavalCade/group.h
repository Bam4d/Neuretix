

#define TWOPI (M_PI*2)
using namespace std;
class group
{
public:
	group(int,int,RGB);
	group(vector<neuron*>,int,PlotPoint,RGB);
        
        void SetColour(RGB);
        void Move(PlotPoint);//moves the group from it's current location to a new one
	void Line(double,PlotPoint,int);//arranges neurons in a line
	void Circle(double distbetween,PlotPoint center_pos, int xyz);//arranges neurons in a circle
	vector<neuron*> Neuron; //pointer to neurons
	~group(void);
	void UpdateGroup(); //updates the action potentials of neurons in the group
	int ID; //ID number for group identification

	RGB baseCol; //defines the base colour of neurons in this group
	PlotPoint grouppos;
        
	static group* FindGroupByID(int ID, vector<group*>* groupList);
	
};
