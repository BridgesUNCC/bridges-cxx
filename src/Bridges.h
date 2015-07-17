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
#include "GraphAdjList.h"
#include "GraphAdjMatrix.h"
#include "Validation.h"

/**
 * Connection to the Bridges server.
 * 
 * This class contains the needed initialization functions for BRIDGES
 * and the needed infrastructure to connect to the server
 * 
 * @author Kalpathi Subramanian (C++ port)

 * @param Generic parameters <K, E>, K is any orderable type (short, unsigned, 
 * int, float, double, char, string), E is any legal type that represents
 * application data.
 * 
 **/

namespace bridges {

template<typename K, typename E> class Bridges {
	private:
		Element<E> *root;			// holds the handle to the data struct
		GraphAdjList<K, E> *graph_adj_list;		// graph handle
		GraphAdjMatrix<K, E> *graph_adj_matrix;	// graph handle
		Element<E> *array_list;
		int assignment;				// assignment number
		int assignmentPart = 0;	    // holds fractional part (0-100 supported)
		string key;					// application id
		string userName;			// user id
		ADTVisualizer<K, E> *visualizer ;
		Validation *validation;		// class to validate visual properties
		Connector  *connector;

		static Bridges *current;

						// common messages 
		
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
				cerr << "bad_alloc (ADTVisualizer Object Allocation) caught: " 
							<< ba.what() << endl; 
			}
			try {
				connector  = new Connector;
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (Connector Object Allocation)  caught: " 
							<< ba.what() << endl; 
			}
			try {
				validation  = new Validation;
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (Validation Object Allocation)  caught: " 
								<< ba.what() << endl; 
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
		 * Get the current Bridges handl -- needed by other system classes
		 * 
		 * @return  assignment number -  this is an integer value;
		 * 
		 **/
		static Bridges *getBridgesObject() {
			return current;
		}
		
		/** 
		 *  Get the assignment number 
		 *
		 **/
		string getAssignment() {
			return (assignmentPart < 10) 
				? to_string(assignment) + ".0" + to_string(assignmentPart)
				: to_string(assignment) + "." + to_string(assignmentPart);
		}
		/** 
		 *  Set the assignment number 
		 *
		 *  @param assignment number (int)
		 **/

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
		
		/** 
		 *  Get the user id
		 *
		 *  @return user id (string)
		 **/
		string getUserName() {
			return userName;
		}
	
		/** 
		 *  Set the user id
		 *
		 *  @param user name (string)
		 **/
		void setUserName(string uname) {
			userName = uname;
		}
		/** 
		 *  Get the application id
		 *
		 *  @return application id (string)
		 **/
		
		string getKey() {
			return key;
		}

		/** 
		 *  Set the application id -- needed for server communication
		 *
		 *  @param application id(string)
		 **/
		
		void setKey(string key_val) {
			key = key_val;
		}
	
		
		/**
  		 *
		 * This method returns the current ADT visualizer
		 *
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
		 * the Array data structure
		 *
		 * @param e - is a 
		 * @param size -- array size (int)
		 *
		 * @throws Exception
		 **/
		void setDataStructure(Element<E>* arr, int size){
			try {
				if (size <= 0)
					throw "Warning: Array is of zero or negative size!";
				array_list = arr;
				visualizer->setArraySize(size);
				visualizer->setVisualizerType("Array");
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
		}
		
		/**
		 * This method sets the first element and the type of ADT for the 
		 * singly linked list structure
		 *
		 * @param head - SLelement<E>*  
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
		 * the doubly linked list
		 *
		 * @param head - head of a DLelement<E> list
		 *
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
		 * binary tree
		 *
		 * @param root - is the binary tree root, of type TreeElement<E>*
		 * 
		 * @throws Exception
		 **/
		void setDataStructure(TreeElement<E> *tree_root){
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
		 * binary search tree
		 * @param root - is the tree root, of type BSTElement<E>* 
		 *
		 * @throws Exception
		 **/
		void setDataStructure(BSTElement<K, E> *tree_root){
			try {
				if (tree_root == NULL)
					throw "Warning: Data Structure(Tree) is empty!";
			}
			catch (const char *msg) {
				cerr << msg << endl;
			}
			root = tree_root;
			visualizer->setVisualizerType("BinarySearchTree");
		}
		
		/**
		 * This method is sets the adjacency list for the Graph ADT
		 *
		 * @param graph, which consists of the vertices and adjacency
         *	 lists for each vertex (implmented using STL maps)
		 * @param K, must be an orderable parameter, as it serves as
		 *  the key into the maps
		 *
		 * @throws Exception
		 **/
		void setDataStructure(GraphAdjList<K, E> *adj_list){
			graph_adj_list = adj_list;
			visualizer->setVisualizerType("GraphAdjacencyList");
		}

		/**
		 * This method is sets the adjacency matrix for the Graph ADT
		 *
		 * @param K, must be an orderable parameter, as it serves as
		 *  the key into the maps
		 * @param graph, represented as an adjacency matrix, consisting
		 *   of  the vertices(map) and a 2D map, for the adj. matrix
		 * 
		 * @throws Exception
		 *
		 **/
		void setDataStructure(GraphAdjMatrix<K, E> *adj_matrix){
			graph_adj_matrix = adj_matrix;
			visualizer->setVisualizerType("GraphAdjacencyMatrix");
		}
		
		/**
		 * This method toggles the flag that permits the JSON to be output
		 * 
		 */
		void toggleJSONdisplay(){
			if (getVisualizer()->isVisualizeJSON())
				getVisualizer()->setVisualizeJSON(false);
			else
				getVisualizer()->setVisualizeJSON(true);
		}
		
		/**
		 * This method initiates the creation of the JSON string representation
		 * of the current data structure, which is then sent to the server
		 * via the post() call, which ultimately executes the http request
		 * from the server
		 *
		 */
		void visualize() {
							// form the url for the http post request
			string url_to_server = connector->getServerURL() + 
				"/assignments/" + getAssignment() + "?apikey=" +  getKey();
			string url_to_vis = connector->getServerURL() + 
				"/assignments/" + getAssignment() + "/" +  getUserName();

			string ds = visualizer->getVisualizerType();

			if (ds == "Array")
				visualize_Array(url_to_server, url_to_vis);
			else if (ds == "llist")
				visualize_LinkedList(url_to_server, url_to_vis);
			else if (ds == "dllist")
				visualize_DoublyLinkedList(url_to_server, url_to_vis);
			else if (ds == "tree")
				visualize_BinaryTree(url_to_server, url_to_vis);
			else if (ds == "bst")
				visualize_BinarySearchTree(url_to_server, url_to_vis);
			else if (ds == "graphl")
				visualize_GraphAdjList(url_to_server, url_to_vis);
			else if (ds == "graphm")
				visualize_GraphAdjMatrix(url_to_server, url_to_vis);

		}
		/**
		 * visualize a singly linked list, linked list based stack or queue. 
		 * This may be called many times. 
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 **/
		void visualize_LinkedList(string url_s, string url_u) {
			string ds_json;
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
											(SLelement<E> *) root);
	        	connector->post(url_s, ds_json); 
	        								// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url_u 
						<< endl;
	        	assignmentPart++;
			} 
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Singly Linkeded List):" << ds_json << endl;
			}
		}
		
		/**
		 * Visualize a doubly linked list. This may be called many times.
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 **/
		void visualize_DoublyLinkedList(string url_s, string url_u) {
			string ds_json;
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
										(DLelement<E>*)root);
	        	connector->post(url_s, ds_json); 
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url_u 
							<< endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Doubly Linkeded List):" << ds_json << endl;
			}
		}
		
		/**
		 * Visualize an array. This may be called many times.
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 *
		 **/
		void visualize_Array(string url_s, string url_u) {
			string ds_json;
	        try {
				ds_json = visualizer->getDataStructureRepresentation(array_list);
	        	connector->post(url_s, ds_json);
	        							// return a url to the user
				cout << "success! Check out your visuals at " << "\n\t\t" + url_u 
							<< endl;
	        	assignmentPart++;
			} 
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Array List):" << ds_json << endl;
			}
		}
		/**
		 * Visualize a binary tree. This may be called many times. 
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 **/
		void visualize_BinaryTree(string url_s, string url_u) {
			string ds_json;
	        try {
				ds_json = 
					visualizer->getDataStructureRepresentation(
								(TreeElement<E>*)root);
				connector->post(url_s, ds_json); 
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url_u 
							<< endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Binary Tree):" << ds_json << endl;
			}
		}
		/**
		 *
		 * Visualize a binary search tree. 
		 * This may be called many times.  
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 **/
		void visualize_BinarySearchTree(string url_s, string url_u) {
			string ds_json;
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
									(BSTElement<K, E> *) root);
				connector->post(url_s, ds_json); 
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + url_u 
							<< endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Generated JSON(Binary Tree):" << ds_json << endl;
			}
		}
		/**
		 * Visualize a graph represented with an adjacency matrix. 
		 * This may be called many times.  
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 *
		 */
		void visualize_GraphAdjMatrix(string url_s, string url_u) {
			string ds_json;
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
												graph_adj_matrix);
				connector->post(url_s, ds_json);
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t"+
								url_u << endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Errors in either JSON creation, or " ;
				cerr << "posting assignment to the server failed!" << endl;
				cerr << "JSON(Graph):" << ds_json << endl;
			}
		}
	
		/**
		 * Visualize a graph represented with adjacency lists. 
		 * This may be called many times.  
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 *
		 *
		 */
		void visualize_GraphAdjList(string url_s, string url_u) {
			string ds_json;
	        try {
				ds_json = 
					visualizer->getDataStructureRepresentation(graph_adj_list);
				connector->post(url_s, ds_json);
	        							// Return a URL to the user
				cout << "Success! Check out your visuals at " << "\n\t\t" + 
											url_u << endl;
	        	assignmentPart++;
			}
			catch (...) {
				cerr << "Errors in either JSON creation, or ";
				cerr << "posting assignment to the server failed!" << endl;
				cerr << "JSON(Graph):" << ds_json << endl;
			}
		}
	
		/**
		 * @return the root of the binary tree or binary search tree
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

}

#endif
