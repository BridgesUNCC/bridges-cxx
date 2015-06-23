#ifndef BRIDGES_H

#define BRIDGES_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <new>

using namespace std;

#include "BSTElement.h"
#include "Connector.h"
#include "Validation.h"

/**
 * Connection to the Bridges server.
 * 
 * This class contains the needed initialization functions for BRIDGES
 * and the needed infrastructure to connect to the server
 * 
 * @author Kalpathi Subramanian (C++ port)
 * @param <E>
 * 
 **/


template<typename K, typename E> class Bridges {
	private:
		Element<E> *root;			// holds the handle to the data struct
		unordered_map<string, GraphList<E>>  // graph handle
				graph_adj_list;
		vector<Element<E>*> array_list;
		int assignment;				// assignment number
		int assignmentPart = 0;	    // holds fractional part (0-100 supported)
		string key;					// application id
		string userName;			// user id
		ADTVisualizer<K, E> *visualizer ;
		Validation *validation;		// class to validate visual properties
		Connector  *connector;

		static Bridges *current;
		
		void server_error_msg1 () {
			cout << "There was a problem sending the visualization" <<
				" representation to the server. Are you connected to the" <<
				" Internet? Check your network settings. Otherwise, maybe" <<
				" the central DataFormatters server is down. Try"  << 
				" again later.\n";
		}
		void server_error_msg2 () {
			cout << "There was a problem sending the visualization" 
				 << " representation to the server. However, it responded with"
				 << " an impossible 'RateLimitException'. Please contact"
				 << " DataFormatters developers and file a bug report; this"
				 << " error should not be possible.\n";
		}

	public:
		/**
		 * Constructors
		 **/
		Bridges() {
			try {
				visualizer = new ADTVisualizer<K, E>;
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (ADTVisualizer Object Allocation) caught: " << ba.what() <<
						endl; 
			}
			try {
				connector  = new Connector;
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (Connector Object Allocation)  caught: " << ba.what() << endl; 
			}
			try {
				validation  = new Validation;
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (Validation Object Allocation)  caught: " << ba.what() << endl; 
			}
			assignmentPart = 0;

			current = this;
		}

		/**
		 * 
		 * @param assignment number -  this is an integer value;
		 * @param app_id  - application id
		 * @param username
		 * @throws Exception
		 **/
		Bridges(int assignment, string app_id, string user) : Bridges() {
			key = app_id;
			userName = user;
			setAssignment(assignment);
		}

		/**
		 *
		 * Get the current Bridges object -- needed by various classes
		 * 
		 * @return  assignment number -  this is an integer value;
		 * 
		 **/
		static Bridges *getBridgesObject() {
			return current;
		}
		
		/* Accessors and Mutators */
		string getAssignment() {
			return (assignmentPart < 10) 
				? to_string(assignment) + ".0" + to_string(assignmentPart)
//				? to_string(assignment) + ".0" 
				: to_string(assignment) + "." + to_string(assignmentPart);
		}


		void setAssignment(int assignment_number) {
			try {
				if (assignment_number < 0)
					throw assignment_number;
			}
			catch (int val) {
				cout << "Assignment id is negative! Received " 
					<< assignment_number << endl;
			}
		
			assignmentPart=0;
			assignment = assignment_number;
		}
		
		string getUserName() {
			return userName;
		}
	
		void setUserName(string uname) {
			userName = uname;
		}
		
		string getKey() {
			return key;
		}
		
		void setKey(string key_val) {
			key = key_val;
		}
	
		
		/**
  		 *
		 * This method returns the current visualizer
		 * @return visualizer
  		 *
		 */
		ADTVisualizer<K, E> *getVisualizer() {
			return visualizer;
		}
		
		/**
  		 *
		 * This method sets the new visualizer object
		 * @param visualizer
  		 *
		 */
		void setVisualizer(ADTVisualizer<K, E> *vis) {
			visualizer = vis;
		}

		/**
		 * This method sets the first element and the type of ADT for 
		 * the ADTVisualizer object
		 * @param e - is a SLelement<E>
		 * @param visualizerType
		 * this parameter can be set to: "graph", "graphl","stack","queue",
		 * "tree", "llist", "AList" or "Dllist" 
		 * @throws Exception
		 **/
		void setDataStructure(vector<Element<E>*> arr){
			try {
				if (arr.size() == 0)
					throw "Warning: Data Structure(Array) is empty!";
				array_list = arr;
				visualizer->setVisualizerType("ArrayList");
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
		}
		
		/**
		 * This method sets the first element and the type of ADT for the 
		 * ADTVisualizer object
		 * @param e - is a SLelement<E>
		 * @param visualizerType
		 * this parameter can be set to: "graph", "graphl","stack","queue",
		 * 	"tree", "llist" or "Dllist" 
		 **/
		void setDataStructure(SLelement<E> *head){
			try {
				if (head == NULL)
					throw "Warning: Data Structure(Linked List) is empty!";
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
			root = (SLelement<E>*) head;
			visualizer->setVisualizerType("SinglyLinkedList");
		}
		
		/**
		 * This method sets the first element and the type of ADT for 
		 * the ADTVisualizer object
		 * @param e - is a DLelement<E>
		 * @param visualizerType
		 * this parameter can be set to: "graph", "graphl","stack","queue",
		 * "tree", "llist" or "Dllist"
		 **/
		void setDataStructure(DLelement<E> *head){
			try {
				if (head == NULL)
					throw "Warning: Data Structure(Doubly Linked List) is empty!";
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
			root = (DLelement<E> *)head;
			visualizer->setVisualizerType("DoublyLinkedList");
		}
		
		/**
		 * This method sets the first element and the type of ADT for the 
		 * ADTVisualizer object
		 * @param e - is a TreeElement<E>
		 * @param visualizerType
		 * this parameter can be set to: "graph", "graphl","stack","queue",
		 * "tree", "llist", AList or "Dllist"
		 * @throws Exception
		 **/
		void setDataStructure(TreeElement<E> *tree_root, string visualizerType){
			try {
				if (tree_root == NULL)
					throw "Warning: Data Structure(Tree) is empty!";
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
			root = (TreeElement<E> *) tree_root;
			visualizer->setVisualizerType("Binary_Tree");
		}

		/**
		 * This method sets the first element and the type of ADT for the 
		 * ADTVisualizer object
		 * @param e - is a BSTElement<E> for a binary search tree element
		 * @param visualizerType
		 * this parameter can be set to: "graph", "graphl","stack","queue",
		 * "tree", "llist", AList or "Dllist"
		 * @throws Exception
		 **/
		void setDataStructure(BSTElement<K, E> *tree_root, string 
									visualizerType){
			try {
				if (tree_root == NULL)
					throw "Warning: Data Structure(Tree) is empty!";
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
			root = (TreeElement<E> *) tree_root;
			visualizer->setVisualizerType("BinarySearchTree");
		}
		
		/**
		 * This method is sets the adjacency list for the Graph ADT
		 * @param adjacencyList
		 * @param visualizerType
		 * this parameter can be set to: "graph", "graphl","stack",
		 * "queue","tree", "llist" or "Dllist"
		 * @throws Exception
		 **/
		void setDataStructure(unordered_map<string, GraphList<E>> adj_list){
			try {
				if (adj_list.size() == 0)
					throw "Data Structure(Graph) is empty!";
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
			visualizer->setAdjacencyList(adj_list);
			graph_adj_list = adj_list;
			visualizer->setVisualizerType("GraphAdjacencyList");
		}
		
		/**
		 * This method returns the current JSON
		 * @return JSON string
		 */
		void toggleJSONdisplay(){
			if (getVisualizer()->isVisualizeJSON())
				getVisualizer()->setVisualizeJSON(false);
			else
				getVisualizer()->setVisualizeJSON(true);
		}
		
		/**
		 * This method initiates the creation of the JSON string representation
		 * of the current data structure, then send the JSON to the server
		 * via the post() call, which ultimately executes the http request
		 * from the server
		 * @throws InvocationTargetException 
		 * @throws IllegalAccessException 
		 * @throws NoSuchMethodException 
		 */
		void visualize() {
							// form the url for the http post request
			string url = connector->getServerURL() + 
				"/assignments/" + getAssignment() + 
				"/" + userName + "?apikey=" +  getKey();

			string ds = visualizer->getVisualizerType();

			if (ds == "ArrayList")
				visualize_ArrayList(url);
			else if (ds == "llist")
				visualize_LinkedList(url);
			else if (ds == "dllist")
				visualize_DoublyLinkedList(url);
			else if (ds == "tree")
				visualize_BinaryTree(url);
			else if (ds == "graphl")
				visualize_GraphAdjList(url);
		}
		/**
		 * visualize a singly linked list, linked list * based stack or queue. 
		 * This may be called many times.  This is usually an expensive 
		 * operation and involves connecting to the server.
		 *
		 **/
		void visualize_LinkedList(string url) {
			string ds_json;
	        try {
				ds_json = 
					visualizer->getSLRepresentation((SLelement<E> *) root);
	        	connector->post(url, ds_json); 
	        								// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url 
						<< endl;
	        	assignmentPart++;
			} 
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Singly Linkeded List):" << ds_json << endl;
			}
		}
		
		/**
		 * visualize a doubly linked list. This may be called many times.
		 * This is usually an expensive operation and involves connecting 
		 * to the server.  
		 **/
		void visualize_DoublyLinkedList(string url) {
			string ds_json;
	        try {
				ds_json = visualizer->getDLRepresentation((DLelement<E>*)root);
	        	connector->post(url, ds_json); 
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url 
							<< endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Doubly Linkeded List):" << ds_json << endl;
			}
		}
		
		/**
		 * visualize an array. This may be called many times.
		 * This is usually an expensive operation and involves connecting 
		 * to the server.  
		 **/
		void visualize_ArrayList(string url) {
			string ds_json;
	        try {
				ds_json = visualizer->getArrayListRepresentation(array_list);
	        	connector->post(url, ds_json);
	        							// return a url to the user
				cout << "success! Check out your visuals at " << "\n\t\t" + url 
							<< endl;
	        	assignmentPart++;
			} 
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Array List):" << ds_json << endl;
			}
		}
		/**
		 * visualize a binary tree or binary search tree. This may be 
		 * called many times.  This is usually an expensive operation and 
		 * involves connecting to the network.
		 **/
		void visualize_BinaryTree(string url) {
			string ds_json;
	        try {
				ds_json = 
					visualizer->getTreeRepresentation((TreeElement<E>*)root);
				connector->post(url, ds_json); 
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url 
							<< endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Binary Tree):" << ds_json << endl;
			}
		}
	
		/**
		 * Visualize a graph represented with adjacency lists. This may be 
		 * called many times.  This is usually an expensive operation and 
		 * involves connecting to the server.
		 */
		void visualize_GraphAdjList(string url) {
			string ds_json;
	        try {
				ds_json = 
					visualizer->getGraphAdjList_Representation(graph_adj_list);
				connector->post(url, ds_json);
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url 
							<< endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "JSON(Graph):" << ds_json << endl;
			}
		}
	
		/**
		 * @return the root
		 */
		Element<E> *getRoot() {
			return root;
		}
	
		/**
		 * @param root the root to set
		 */
		void setRoot(Element<E> *r) {
			root = r;
		}
};
								// declare static variables

template <typename K, typename E> Bridges<K, E>* Bridges<K, E>::current = NULL;

#endif
