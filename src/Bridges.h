#ifndef BRIDGES_H

#define BRIDGES_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <new>

using namespace std;

#include "BSTElement.h"
#include "ADTVisualizer.h"
#include "Connector.h"
#include "GraphAdjList.h"
#include "GraphAdjMatrix.h"
#include "Validation.h"

namespace bridges {
/**
 * @brief This class contains methods to connect and transmit a user's 
 * 	data structure representation to the Bridges server
 * 
 * This class contains the needed initialization functions for BRIDGES
 * and the needed methods to connect to the server
 * 
 * @author Kalpathi Subramanian (C++ port)
 *
 * @date  7/26/15
 *
 * param Generic parameters <K, E>, K is any orderable type (short, unsigned, 
 * int, float, double, char, string), E is any legal type that represents
 * application data.
 * 
 */


template<typename K, typename E> class Bridges {
	private:
		Element<E> *root;			// holds the handle to the data struct
		GraphAdjList<K, E> *graph_adj_list;		// graph handle
		GraphAdjMatrix<K, E> *graph_adj_matrix;	// graph handle
		int assignment,				// assignment number
			assignmentPart;			// holds fractional part (0-100 supported)
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
			assignment = 0;
			assignmentPart = 0;
			graph_adj_list = NULL; 
			graph_adj_matrix = NULL;
			key = userName = "";
			root = NULL;

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

			current = this;
		}

		/**
		 * Bridges constructor
		 * 
		 * @param assignm :  the assignment number
		 * @param app_id :  application id
		 * @param user :  user id
		 *
		 **/
		Bridges(int assignm, string app_id, string user) : Bridges() {
			key = app_id;
			userName = user;
			setAssignment(assignm);
		}

		/**
		 *
		 * Get the current Bridges handle -- needed by other system classes
		 * 
		 * @return  pointer to the Bridges object (Bridges*);
		 * 
		 **/
		static Bridges *getBridgesObject() {
			return current;
		}
		
		/** 
		 *  Get the assignment number 
		 *
		 *	   Can represent a sequence of assignments
		 *     Example: 1.00, 1.01, 1.02  represent 3 visualizations of
		 *     assignment 1
		 *
		 *  @return  : assignment name
		 **/
		string getAssignment() {
			return (assignmentPart < 10) 
				? to_string(assignment) + ".0" + to_string(assignmentPart)
				: to_string(assignment) + "." + to_string(assignmentPart);
		}
		/** 
		 *  Set the assignment number 
		 *
		 *  @param assignment_number : assignment name
		 *
		 */

		void setAssignment(int assignment_number) {
			if (assignment_number < 0) {
				cout << "Assignment id is negative! Received " << 
					assignment_number << "..., exiting.." << endl;
				exit(EXIT_FAILURE);
			}
								// reinitialize the assignment part
			assignmentPart = 0;
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
		 *  @param uname : return the user name (string)
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
		 *  @param key_val  : set the application id -- from Bridges account
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
		 *
		 * @param vis  - set the current visualizer object
  		 *
		 */
		void setVisualizer(ADTVisualizer<K, E> *vis) {
			visualizer = vis;
		}

		/**
		 * This method sets the handle for the the Array data structure
		 *
		 * @param arr - array pointer
		 * @param size -- array size (int)
		 *
		 **/
		void setDataStructure(Element<E>* arr, int size){
			if (size <= 0 || arr == NULL) {
				visualizer->setVisualizerType("None");
				cerr <<  "Warning: Array is zero or of negative size or " <<
					" array data structure is NULL!" << endl;
			}
			else {
				root = arr;
				visualizer->setArraySize(size);
				visualizer->setVisualizerType("Array");
			}
		}
		
		/**
		 * This method sets the first element for the singly linked list 
		 * structure
		 *
		 * @param head - first node of the list
		 *
		 **/
		void setDataStructure(SLelement<E> *head){
			if (head == NULL){
				visualizer->setVisualizerType("None");
				cerr <<	"Warning: Data Structure(Linked List) is empty!";
			}
			else{
				root = head;
				visualizer->setVisualizerType("SinglyLinkedList");
			}
		}
		
		/**
		 * This method sets the first element of the doubly linked list
		 *
		 * @param head - first node of the doubly linked list
		 *
		 **/
		void setDataStructure(DLelement<E> *head){
			if (head == NULL){
				visualizer->setVisualizerType("None");
				cerr  << "Warning: Data Structure(Doubly Linked List) is empty!"
											<< endl;
			}
			else {
				root = head;
				visualizer->setVisualizerType("DoublyLinkedList");
			}
		}
		
		/**
		 * This method sets the first element and the type of ADT for the 
		 * binary tree
		 *
		 * @param tree_root - is the binary tree root, of type TreeElement<E>*
		 * 
		 **/
		void setDataStructure(TreeElement<E> *tree_root){
			if (tree_root == NULL) {
				visualizer->setVisualizerType("None");
				cerr <<	"Warning: Data Structure(Tree) is empty!" << endl;
			}
			else {
				root = tree_root;
				visualizer->setVisualizerType("Binary_Tree");
			}
		}

		/**
		 * This method sets the root of the binary search tree
		 *
		 * @param tree_root : is the tree root
		 *
		 **/
		void setDataStructure(BSTElement<K, E> *tree_root){
			if (tree_root == NULL) {
				visualizer->setVisualizerType("None");
				cerr << "Warning:Data Structure(Binary Search Tree) is empty!"
										<< endl;
			}
			else {
				root = tree_root;
				visualizer->setVisualizerType("BinarySearchTree");
			}
		}
		
		/**
		 * This method sets the adjacency list for the Graph ADT
		 * K is generic parameter and  must be orderable, as it serves as
		 * the key into the maps
		 *
		 * @param adj_list :  which consists of the vertices and adjacency
         *	 lists for each vertex (implmented using STL maps)
		 *
		 **/
		void setDataStructure(GraphAdjList<K, E> *adj_list){
			if (adj_list == NULL) {
				visualizer->setVisualizerType("None");
				cerr << "Warning: Data Structure(Graph (Adj. List)) is empty!";
			}
			else {
				graph_adj_list = adj_list;
				visualizer->setVisualizerType("GraphAdjacencyList");
			}
		}

		/**
		 * This method sets the adjacency matrix for the Graph ADT
		 * K is generic parameter and  must be orderable, as it serves as
		 * the key into the maps
		 *
		 * @param adj_matrix : represented as an adjacency matrix, consisting
		 *   of  the vertices(map) and a 2D map, for the adj. matrix
		 * 
		 **/
		void setDataStructure(GraphAdjMatrix<K, E> *adj_matrix){
			if (adj_matrix == NULL) {
				visualizer->setVisualizerType("None");
				cerr << "Warning: Data Structure(Graph (Adj. List)) is empty!"
										<< endl;
			}
			else {
				graph_adj_matrix = adj_matrix;
				visualizer->setVisualizerType("GraphAdjacencyMatrix");
			}
		}
		
		/**
		 * This method initiates the creation of the JSON string representation
		 * of the current data structure, which is then sent to the server
		 * via the post() call, which ultimately executes the http request
		 * from the server and generates a visualization of the data structure
		 *
		 */
		void visualize() {
							// form the url for the http post request
			string url_to_server = connector->getServerURL() + 
				"/assignments/" + getAssignment() + "?apikey=" +  getKey();
			string url_to_vis = connector->getServerURL() + 
				"/assignments/" + getAssignment() + "/" +  getUserName();

			string ds = visualizer->getVisualizerType();

			if (ds == "None")
				cout << "Error! JSON not generated. Likely empty(NULL) " <<
						" data structure" << endl;
			else if (ds == "Array")
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
	private:
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
								static_cast<SLelement<E> *>(root));
	        	connector->post(url_s, ds_json); 
	        								// Return a URL to the user
				cout << endl << "Success: Assignment posted to the server. "
						<< " Check out your visualization at " 
						<< "\n\n\t" + url_u << endl << endl;
	        	assignmentPart++;
			} 
			catch (string error_str) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Curl Error: "<<  error_str << endl;
				cerr << "Generated JSON(Singly Linkeded List):" << ds_json << 
											endl;
			}
		}
		
		/**
		 * Visualize a doubly linked list. This may be called many times.
		 *
		 * @param url_s - URL to be sent to the server
		 * @param url_u - URL to be sent to the user to visualize results
		 **/
		void visualize_DoublyLinkedList(string url_s, string url_u) {
			string ds_json = "";
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
									static_cast<DLelement<E>*>(root));
	        	connector->post(url_s, ds_json); 
	        							// Return a URL to the user
				cout << endl << "Success: Assignment posted to the server. "
						<< " Check out your visualization at " 
						<< "\n\n\t" + url_u << endl << endl;
	        	assignmentPart++;
			}
			catch (string error_str) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Curl Error: "<<  error_str << endl;
				cerr << "Generated JSON(Doubly Linkeded List):" << ds_json<<endl;
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
			string ds_json = "";
	        try {
				ds_json = visualizer->getDataStructureRepresentation(root);
	        	connector->post(url_s, ds_json);
	        							// return a url to the user
				cout << endl << "Success: Assignment posted to the server. "
						<< " Check out your visualization at " 
						<< "\n\n\t" + url_u << endl << endl;
	        	assignmentPart++;
			} 
			catch (string error_str) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Curl Error: "<<  error_str << endl;
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
			string ds_json = "";
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
								static_cast<TreeElement<E>*>(root));
				connector->post(url_s, ds_json); 
	        							// Return a URL to the user
				cout << endl << "Success: Assignment posted to the server. "
						<< " Check out your visualization at " 
						<< "\n\n\t" + url_u << endl << endl;
	        	assignmentPart++;
			}
			catch (string error_str) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Curl Error: "<<  error_str << endl;
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
			string ds_json = "";
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
									static_cast<BSTElement<K, E> *>(root));
				connector->post(url_s, ds_json); 
	        							// Return a URL to the user
				cout << endl << "Success: Assignment posted to the server. "
						<< " Check out your visualization at " 
						<< "\n\n\t" + url_u << endl << endl;
	        	assignmentPart++;
			}
			catch (string error_str){
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Curl Error: "<<  error_str << endl;
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
			string ds_json = "";
	        try {
				ds_json = visualizer->getDataStructureRepresentation(
												graph_adj_matrix);
				connector->post(url_s, ds_json);
	        							// Return a URL to the user
				cout << endl << "Success: Assignment posted to the server. "
						<< " Check out your visualization at " 
						<< "\n\n\t" + url_u << endl << endl;
	        	assignmentPart++;
			}
			catch (string error_str) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Curl Error: "<<  error_str << endl;
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
			string ds_json = "";
	        try {
				ds_json = 
					visualizer->getDataStructureRepresentation(graph_adj_list);
				connector->post(url_s, ds_json);
	        							// Return a URL to the user
				cout << endl << "Success: Assignment posted to the server. "
						<< " Check out your visualization at " 
						<< "\n\n\t" + url_u << endl << endl;
	        	assignmentPart++;
			}
			catch (string error_str) {
				cerr << "Posting assignment to the server failed!" << endl;
				cerr << "Curl Error: "<<  error_str << endl;
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
		 * @param r :  setting the handle to the data structure
		 */
		void setRoot(Element<E> *r) {
			root = r;
		}

	public:
		/**
		 *
		 * Cleanup - this method cleans up and deallocates the data  
		 *  structures, prior to exiting the application
		 *
		 * The user needs to call this method at the end of his application
		 * or if a new data structure is to be created and initialized.
		 *
		 **/
		void cleanup() {
			if (root == NULL)
				return;

			string ds = visualizer->getVisualizerType();

			if (ds == "Array")	// nothing to do - user's responsibility
				;
			else if (ds == "llist") {
				SLelement<E> *sle = static_cast<SLelement<E> *>(root);
				SLelement<E>::cleanup(sle);
			}
			else if (ds == "dllist") {
				DLelement<E> *dle = static_cast<DLelement<E> *>(root);
				DLelement<E>::cleanup(dle);
			}
//			else if (ds == "tree") {
//				TreeElement<E> *tree = static_cast<TreeElement<E> *>(root);
//				TreeElement<E>::cleanup(tree);
//			}
			else if (ds == "tree") {
				BSTElement<K,E> *bst = static_cast<BSTElement<K,E> *>(root);
				BSTElement<K,E>::cleanup(bst);
			}
			else if (ds == "graphl")
				delete graph_adj_list;
			else if (ds == "graphm")
				delete graph_adj_matrix;

			root = NULL;
		}
}; // Bridges template definition ends
								// declare static variables

template <typename K, typename E> Bridges<K, E>* Bridges<K, E>::current = NULL;

} // namespace definition ends

#endif
