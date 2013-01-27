

class axonList //linked list of axons so we can have as many dynamically created axons in groupings as we want :D SHIIIIIT
{
public:
	axonList(void);
	~axonList(void);
	void Add(axon *_newAxon);
	int Count();//gets the size of the linked list
        
        void Empty(); //clears the linked list and deallocates memory
	void Clear(); //clears the linked list
	bool Delete(); //deletes item from end of list
        void SetTW(CyclicCache *); //sets the temporal window pointer in ever axon in this list;

        static void Join(axonList* Host, axonList* toAdd); //joins two axonLists

        static axon* FindAxonByID(axonList*,int); //find an axon in this list by it's ID

	axon * Head;
	
	axon * operator[](int);

	int ID;

private:
	unsigned int numAxons;
};

