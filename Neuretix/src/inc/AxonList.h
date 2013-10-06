
#ifndef AXONLIST_H
#define	AXONLIST_H

class CyclicCache;
class Axon;

class AxonList //linked list of axons so we can have as many dynamically created axons in groupings as we want :D SHIIIIIT
{
public:
	AxonList(void);
	~AxonList(void);
	void Add(Axon*_newAxon);
	int Count();//gets the size of the linked list
        
        void Empty(); //clears the linked list and deallocates memory
	void Clear(); //clears the linked list
	bool Delete(); //deletes item from end of list
	void SetTW(CyclicCache*); //sets the temporal window pointer in ever axon in this list;

	static void Join(AxonList* Host, AxonList* toAdd); //joins two axonLists

	static Axon* FindAxonByID(AxonList*,int); //find an axon in this list by it's ID

	Axon* Head;
	
	Axon* operator[](int);

	int ID;

private:
	unsigned int numAxons;
};

#endif
