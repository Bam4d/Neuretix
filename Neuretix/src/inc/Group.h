
#ifndef GROUP_H
#define	GROUP_H



#include <vector>
#include <math.h>

#include "Rendering.h"
#include "Neuron.h"

#define TWOPI (M_PI*2)

class Group
{
public:
    Group();
	void Init(int,int,RGB);
	void Init(std::vector<Neuron*> neurons, int id, PlotPoint plotPoint, RGB rgb);
        
	void SetColour(RGB);
	void Move(PlotPoint);//moves the group from it's current location to a new one
	void Line(double,PlotPoint,int);//arranges neurons in a line
	void Circle(double distbetween,PlotPoint center_pos, int xyz);//arranges neurons in a circle
	std::vector<Neuron*> neurons; //pointer to neurons
	virtual ~Group(void);
	void UpdateGroup(); //updates the action potentials of neurons in the group
	int id; //ID number for group identification

	RGB baseCol; //defines the base colour of neurons in this group
	PlotPoint groupPos;
        
	static Group* FindGroupByID(int id, std::vector<Group*>* groupList);
	
};

#endif
