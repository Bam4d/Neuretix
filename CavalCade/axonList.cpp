#include "CNNGlobals.h"

axonList::axonList(void)
	: numAxons(0), Head(0)
{
}

int axonList::Count()
{
	return numAxons;
}

void axonList::SetTW(TemporalWindow* _TW)
{
    axon * _current = Head;

    while(_current!=NULL)
    {
        _current->_TW = _TW;
        _current = _current->next;
    }
}

void axonList::Add(axon *_newAxon)
{
	//axon * toAdd = _newAxon; //copies the of the new axon to the linked list location
	_newAxon->next = Head;
	Head = _newAxon;
	_newAxon->ID = numAxons; //ID of the Axon
	numAxons++;
	
}

axon * axonList::operator[](int Position) //get the axon at this index...
{
        axon *Current = Head;

        for(int i = 0; i < Position; i++)
        {
                Current = Current->next;
                if(Current->next == NULL)
                    break;
        }

return Current;
}

void axonList::Empty()
{
    //clears and de-allocates all memory locations at genome level.
    //loop through deletes until next item in list is null
	while(Delete());

        Clear();
}

void axonList::Clear()
{
	Head = 0;
	numAxons = 0;
}

bool axonList::Delete()
{
	if( Head == NULL || numAxons==0)
		return false;
	else
	{
                
		axon* temp_head = Head->next;
		delete Head;
		Head = temp_head;
		numAxons--;
		return true;
	}
}

void axonList::Join(axonList* Host, axonList* toAdd)
{
    //add one axonList to another axonList
    if(toAdd->numAxons>0)
    {
        toAdd->operator[](toAdd->numAxons-1)->next = Host->Head;

        Host->Head = toAdd->Head;

        Host->numAxons += toAdd->numAxons;
    }

    //renumber all the axons

    axon * toAddIterator = Host->Head;
    long _idIterator = 0;
    while(toAddIterator!=NULL)
    {
        toAddIterator->ID = _idIterator++;
        toAddIterator = toAddIterator->next;
    }
}

axon* axonList::FindAxonByID(axonList* _list,int _axonID)
{
    if(_list!=NULL)
    {
        axon* temp_axon = _list->Head;
        while(temp_axon->ID!=_axonID){temp_axon = temp_axon->next;}
        return temp_axon;
    }
    return NULL;
}


axonList::~axonList(void)
{
}
