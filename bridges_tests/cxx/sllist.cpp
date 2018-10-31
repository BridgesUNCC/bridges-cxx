#include <iostream>
#include <string>

using namespace std;

#include "Bridges.h"
#include "SLelement.h"

#define LOCAL  0

using namespace bridges;

int main() {


#if LOCAL
	Bridges<string, int> *bridges = new Bridges<string, int>(1, kalpathi60, 
								"856807706412");
#else
	Bridges::initialize(1, "kalpathi60", "486749122386");
#endif
//	Bridges::setTitle("A Trivial Singly Linked List");
	Bridges::setTitle("This is a title for the singly linked -- titles are restricted to 50 characters, if they exceed that they are truncated to 50 chars");
	Bridges::setDescription("In computer science, a linked list is a linear collection of data elements, called nodes, pointing to the next node by means of a pointer. It is a data structure consisting of a group of nodes which together represent a sequence. Under the simplest");

	SLelement<int> *el0 = new SLelement<int>(0, "0");
	SLelement<int> *el1 = new SLelement<int>(1, "1");
	SLelement<int> *el2 = new SLelement<int>(2, "2");
	SLelement<int> *el3 = new SLelement<int>(3, "3");
        
	el0->setNext(el1);
	el1->setNext(el2);
	el2->setNext(el3);


	el0->getVisualizer()->setColor("cyan");
	el0->getLinkVisualizer(el1)->setColor("red");
	el1->getLinkVisualizer(el2)->setColor("blue");
	el2->getLinkVisualizer(el3)->setColor("cyan");

	Bridges::setVisualizeJSON(true);

	Bridges::setDataStructure(el0);

	Bridges::visualize();

	return 0;
}
