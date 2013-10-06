#include "../inc/Group.h"

Group::Group() {
    this->id = 0;
}

void Group::Init(int numNeu, int id,RGB basecol)
{
	this->id = id; //set the ID of this group
	baseCol = basecol;
	//generate the new neurons
        groupPos = PlotPoint(0,0,0);

	for (int neuron_counter = 0; neuron_counter<numNeu; neuron_counter++)
	{
		Neuron* neuron = new Neuron(id,baseCol);
        neurons.push_back(neuron);
        neuron->id = neuron_counter;
	}
}

void Group::Init(std::vector<Neuron*> neurons, int id, PlotPoint groupPos,RGB baseCol)
{
	this->id = id;
	this->baseCol = baseCol;
	this->neurons = neurons;
	this->groupPos = groupPos;


	for (int neuronCounter = 0; neuronCounter<neurons.size(); neuronCounter++)
	{
		Neuron* neuron = neurons[neuronCounter];
		neuron->id = neuronCounter;
	}
}

void Group::Move(PlotPoint _newPos)
{
    for(int neuron_counter = 0; neuron_counter<neurons.size(); neuron_counter++)
    {
    	Neuron* n = neurons[neuron_counter];
        n->position.x += _newPos.x - groupPos.x;
        n->position.y += _newPos.y - groupPos.y;
        n->position.z += _newPos.z - groupPos.z;
    }

    groupPos = _newPos;

}

void Group::SetColour(RGB col)
{
    baseCol = col;
    for(int neuron_counter = 0; neuron_counter<neurons.size(); neuron_counter++)
    {
    	Neuron* n = neurons[neuron_counter];
        n->neuCol = col;
    }
}

void Group::Line(double distbetween,PlotPoint center_pos, int xyz)//arranges neurons in a line
{
	double offset = -distbetween*((double)(neurons.size()-1))/2.0;
	PlotPoint npos;
	groupPos = center_pos;
	for(int neuron_counter = 0; neuron_counter<neurons.size(); neuron_counter++)
	{
		Neuron* n = neurons[neuron_counter];
		npos = center_pos;
		//calculate neuron position
		
		switch(xyz)
		{
			case 0:npos.x += offset+neuron_counter*distbetween;break;
			case 1:npos.y += offset+neuron_counter*distbetween;break;
			case 2:npos.z += offset+neuron_counter*distbetween;break;
		}

		n->position = npos;
	}
}

void Group::Circle(double distbetween,PlotPoint center_pos, int xyz)//arranges neurons in a circle
{
	double radius = (double)neurons.size()*distbetween/TWOPI;
	double angle;
	PlotPoint npos;
	groupPos = center_pos;//assign the group's position in 3D space
	for(int neuron_counter = 0; neuron_counter<neurons.size(); neuron_counter++)
	{
		Neuron* n = neurons[neuron_counter];
		npos = center_pos;
		//calculate neuron position
		angle = (TWOPI*(double)neuron_counter)/neurons.size();
		switch(xyz)
		{
			case 0:npos.z += radius*sin(angle);npos.y+=radius*cos(angle);break;
			case 1:npos.z += radius*sin(angle);npos.x+=radius*cos(angle);break;
			case 2:npos.x += radius*sin(angle);npos.y+=radius*cos(angle);break;
		}

		n->position = npos;
	}
}

void Group::UpdateGroup()
{
	for(int neuron_counter = 0; neuron_counter<neurons.size(); neuron_counter++) {
		Neuron* n = neurons[neuron_counter];
		n->UpdatePotentials();
	}
}

Group* Group::FindGroupByID(int id, std::vector<Group*>* groupList) //retunrs a pointer to the group with ID==ID in a cluster
{
    if(groupList!=NULL)
    {
		for(int g_c = 0; g_c<groupList->size(); g_c++) {
			Group* g = groupList->at(g_c);
			if(g->id == id) return g;
		}

    }
	return NULL;
}

Group::~Group(void)
{
    for(int neuron_counter = 0; neuron_counter<neurons.size(); neuron_counter++)
        delete neurons[neuron_counter];
    
    neurons.clear();
}
