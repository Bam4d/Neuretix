#include "CNNGlobals.h"

group::group(int numNeu, int id,RGB basecol)
{
	ID = id; //set the ID of this group
	baseCol = basecol;
	//generate the new neurons
        grouppos = PlotPoint(0,0,0);

	for (int neuron_counter = 0; neuron_counter<numNeu; neuron_counter++)
	{
            Neuron.push_back(new neuron(id,baseCol));
	    Neuron[neuron_counter]->ID = neuron_counter;
	}
}

group::group(vector<neuron*> neurons, int id, PlotPoint pos,RGB basecol)
{
	ID = id; //set the ID of this group
	baseCol = basecol;
	//set the new neurons
	Neuron = neurons;
	grouppos = pos;
	for (int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++)
	{
            Neuron[neuron_counter]->ID = neuron_counter;
            //Neuron[neuron_counter]->position.x += grouppos.x;
            //Neuron[neuron_counter]->position.y += grouppos.y;
            //Neuron[neuron_counter]->position.z += grouppos.z;
	}
}

void group::Move(PlotPoint _newPos)
{
    for(int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++)
    {
        Neuron[neuron_counter]->position.x += _newPos.x - grouppos.x;
        Neuron[neuron_counter]->position.y += _newPos.y - grouppos.y;
        Neuron[neuron_counter]->position.z += _newPos.z - grouppos.z;
    }

    grouppos = _newPos;

}

void group::SetColour(RGB col)
{
    baseCol = col;
    for(int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++)
    {
        Neuron[neuron_counter]->neuCol = col;
    }
}

void group::Line(double distbetween,PlotPoint center_pos, int xyz)//arranges neurons in a line
{
	double offset = -distbetween*((double)(Neuron.size()-1))/2.0;
	PlotPoint npos;
	grouppos = center_pos;
	for(int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++)
	{
		npos = center_pos;
		//calculate neuron position
		
		switch(xyz)
		{
			case 0:npos.x += offset+neuron_counter*distbetween;break;
			case 1:npos.y += offset+neuron_counter*distbetween;break;
			case 2:npos.z += offset+neuron_counter*distbetween;break;
		}

		Neuron[neuron_counter]->position = npos;
	}
}

void group::Circle(double distbetween,PlotPoint center_pos, int xyz)//arranges neurons in a circle
{
	double radius = (double)Neuron.size()*distbetween/TWOPI;
	double angle;
	PlotPoint npos;
	grouppos = center_pos;//assign the group's position in 3D space
	for(int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++)
	{
		npos = center_pos;
		//calculate neuron position
		angle = (TWOPI*(double)neuron_counter)/Neuron.size();
		switch(xyz)
		{
			case 0:npos.z += radius*sin(angle);npos.y+=radius*cos(angle);break;
			case 1:npos.z += radius*sin(angle);npos.x+=radius*cos(angle);break;
			case 2:npos.x += radius*sin(angle);npos.y+=radius*cos(angle);break;
		}

		Neuron[neuron_counter]->position = npos;
	}
}


void group::UpdateGroup()
{
	//update the neuron potentials
	for(int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++) //for all the neurons in this group
		Neuron[neuron_counter]->UpdatePotentials(); //update all the action potentials in the group

}

group* group::FindGroupByID(int ID, vector<group*>* groupList) //retunrs a pointer to the group with ID==ID in a cluster
{
    if(groupList!=NULL)
    {
	for(int g_c = 0; g_c<groupList->size(); g_c++)
		if(groupList->at(g_c)->ID == ID) return groupList->at(g_c);
    }
	return NULL;
}

group::~group(void)
{
    for(int neuron_counter = 0; neuron_counter<Neuron.size(); neuron_counter++)
        delete Neuron[neuron_counter];
    
    Neuron.clear();
}
