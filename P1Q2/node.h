using namespace std;
#ifndef NODE
#define NODE
class Node
{
	public:
	int value;
	int address; 
	int priority;
	Node(int address=0, int value=0, int priority=0)
	{
		this->value = value;
		this->address = address;
		this->priority = priority;
	}
};
#endif