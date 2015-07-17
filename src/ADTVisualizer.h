#ifndef ADT_VISUALIZER_H

#define ADT_VISUALIZER_H

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

#include "GraphAdjMatrix.h"
#include "GraphAdjList.h"
#include "DLelement.h"
#include "TreeElement.h"
#include "BSTElement.h"


/** 
 *  The ADTVisualizer class is responsible for taking a data structure
 *  as input and generating a JSON representation prior to sending it
 *  to the server for visualization.  The Bridges class uses this object 
 *	to keep track of the Visualization representation.
 *	<p>
 *	An end user will generally not need to interact directly with this 
 * 	class.
 *
 *	@author Kalpathi Subramanian (C++ port), 6/15/15
 *
 **/

namespace bridges {

template<typename K, typename E> class ADTVisualizer {
	private:
		string visualizerType;
		string visualizerIdentifier;
		unordered_map<string, string> adt_type;

		bool visualizeJSON = false;
		int array_size;

							// some constants used to generate JSON strings
		string 
			QUOTE = "\"",
			COMMA = ",",
			COLON = ":",
			OPEN_CURLY = "{", 
			CLOSE_CURLY = "}", 
			OPEN_PAREN = "[",
			CLOSE_PAREN = "]";
		
	public:
	
		/**
	 	* constructor 
	 	*/														
		ADTVisualizer(){
			visualizerType = "";
			visualizerIdentifier = "";
			adt_type.emplace("Array_Stack","llist");
			adt_type.emplace("Array_Queue","llist");
			adt_type.emplace("GraphAdjacencyMatrix", "graphm");
			adt_type.emplace("GraphAdjacencyList", "graphl");
			adt_type.emplace("LinkedListStack","llist");
			adt_type.emplace("LinkedListQueue","llist");
			adt_type.emplace("BinaryTree","tree");
			adt_type.emplace("BinarySearchTree","tree");
			adt_type.emplace("SinglyLinkedList", "llist");
			adt_type.emplace("DoublyLinkedList", "dllist");
			adt_type.emplace("Array", "Array");
		}

		/**
		 * Outputs the flag  that controls if the JSON is to be output
 		 * @return the visualizeJSON flag
 		 **/

		bool isVisualizeJSON() {
			return visualizeJSON;
		}

		/**
		 * Flag to control outputting the  JSON string
		 *
 		 * @param visualizeJSON the visualizeJSON to set
		 *
 		 **/
		void setVisualizeJSON(bool vis_json_flag) {
    		visualizeJSON = vis_json_flag;
		}

		/**
		 * @return the visualizerIdentifier
		 **/
		string getVisualizerIdentifier() {
			return visualizerIdentifier;
		}

		/**
		 * @param visualizerIdentifier the visualizerIdentifier to set
		 **/
		void setVisualizerIdentifier(string vis_identifier) {
			visualizerIdentifier = vis_identifier;
		}

		/**
		 * 	This method returns the visualizer type as a string
		 *
		 * 	@return visualizer type(string)
		 **/
		string getVisualizerType() {
			return visualizerType;
		}
		
		/**
		 *  This method sets the array's size for use by other  methods
		 * 	@param size 
		 *
		 **/
		void setArraySize(int size) {
			array_size = size;
		}
		/**
		 * 	This method returns the size of the array data structure
		 *
		 * 	@return  size (int)
		 *
		 **/
		int getArraySize() {
			return array_size;
		}
		
		/**
		 * 	This method sets the visualizer type
		 * 	@param visualizerType a string in ADTVisualizer.ADT_TYPE 
		 *	representing the type of Bridges Visualization (e.g. "graph", 
		 *	"llist", etc.)
		 *	@throws Exception
		 **/
		void setVisualizerType(string vis_type) {
			visualizerType = adt_type[vis_type];
		}
		/**
		 *
		 *  This method generates the JSON representation of an adjacency
		 *  matrix based graph
		 *
		 *	@param graph_adj_matrix --input graph of type GraphAdjMatrix<K, E>*
		 *
		 *  @return -- JSON  string representation of the graph
		 *
		 **/
			
		string getDataStructureRepresentation( GraphAdjMatrix<K, E> 
										*graph_adj_matrix){
									// first gather the nodes and links by
									// traversing the graph
			list<Element<E>*> nodes, links; 
		
			unordered_map<K, Element<E> > 
				*vertices = graph_adj_matrix->getVertices();
			unordered_map<K, unordered_map<K, double> > 
				*matrix = graph_adj_matrix->getMatrix(); 
			
			for (auto& nkey_val: *vertices) {
									//  get the graph node
				nodes.push_front (&nkey_val.second);
			}
			for (auto& lkey_val: *matrix){
									//  get the source links
				if (vertices->find(lkey_val.first) == vertices->end()){
					stringstream error_str; 
					error_str << "Exception: Link src vertex " << 
						lkey_val.first  << " not found, exiting..";
					throw error_str.str();
				}

				for (auto& l2key_val : lkey_val.second) {
					if (vertices->find(l2key_val.first) == vertices->end()){
						stringstream error_str; 
						error_str << "Exception: Link dest vertex " << 
							l2key_val.first  << " not found, exiting..";
						throw error_str.str();
					}
					if ((*graph_adj_matrix->getMatrix())
							[lkey_val.first][l2key_val.first] > 0.) {
											// set the weight
						double wt = (*matrix)[lkey_val.first][l2key_val.first];
						(*vertices)[lkey_val.first].getLinkVisualizer(
							&(*vertices)[l2key_val.first])->setWeight(wt);
											// get the links
						links.push_front(&(*vertices)[lkey_val.first]);
						links.push_front(&(*vertices)[l2key_val.first]);
					}
				}
			}
								// generate the JSON
			return generateJSON_Of_Nodes_And_Links(nodes, links);
		}

		/**
		 *
		 *  This method generates the JSON representation of an adjacency
		 *  list based graph
		 *
		 *	@param graph_adj_list--input graph -- of type GraphAdjList<K, E>*
		 *
		 *  @return -- JSON  string representation of the graph
		 *
		 **/
			
		string getDataStructureRepresentation(GraphAdjList<K, E> 
											*graph_adj_list){

			list<Element<E>*> nodes, links; 
			unordered_map<K, Element<E> > 
               		*vertices = graph_adj_list->getVertices();
			unordered_map<K, SLelement<Edge<K> >*> 
					*adj_list = graph_adj_list->getAdjacencyList();
									// gather the nodes and links by
									// traversing the graph
			for (auto& key_val: *vertices) //  get the graph node
				nodes.push_front(&key_val.second);

			for (auto& key_val: *adj_list){
									//  get the source node
				if (vertices->find(key_val.first) == vertices->end()){
					stringstream error_str;
					error_str << "Exception: Vertex " << key_val.first 
							<< " not found, exiting..";
					throw error_str.str();
				}
									//  get the graph links
				SLelement<Edge<K> > *a_list = key_val.second;
				while (a_list != NULL) {
								// get the edge and check if non-zero weight
					Edge<K>  e = a_list->getValue();
								// look up the vertex
					Element<E> *src_vertex = &(*vertices)[key_val.first];
					if (e.getWeight() > 0.0) {
						links.push_front((Element<E>*) src_vertex);
								// look up the destination vertex
						Element<E> *dest_vertex = &(*vertices)[e.getVertex()];
						links.push_front(dest_vertex);
								// add the edge weight to the properties list
						src_vertex->getLinkVisualizer(dest_vertex)->setWeight(
												e.getWeight());
					}
					a_list = a_list->getNext();
				}
			}
							// use the singly linked list case to get the JSON!
			return generateJSON_Of_Nodes_And_Links(nodes, links);
		}
			
		/**
		 * This method creates a JSON representation of a single linked list - 
		 *
		 * @param - head of the linked list (SLelement<E>*)
		 *
		 * @return - this method returns the JSON string
		 *
		 */
		string getDataStructureRepresentation(SLelement<E> *first_element) {

				list<Element<E>*> nodes, links;
										// first get the nodes and links
				SLelement<E> *sle = first_element;
				for (sle = first_element; sle != NULL; sle = sle->getNext()) {
					nodes.push_front(sle);
					if (sle->getNext() != NULL) {	// link exists
						links.push_front(sle);
						links.push_front(sle->getNext());
					}
				}
									// generate the JSON string
		//		return generateJSON_SLL(nodes, links);
				return generateJSON_Of_Nodes_And_Links(nodes, links);
		}
			
		/**
		 * This method returns the JSON string of a doubly linked list 
		 *
		 * @param - head of the linked list (DLelement<E>*)
		 * @return
		 **/
		string getDataStructureRepresentation(DLelement<E> *first_element) {
		
				list<Element<E>*> nodes, links; 
											// first get the nodes and links
				DLelement<E> *dle = first_element;
				for (dle = first_element; dle!= NULL; dle = dle->getNext()) {
					nodes.push_front(dle);
					if (dle->getNext() != NULL) {	// link exists
						links.push_front(dle);
						links.push_front(dle->getNext());
					}
					if (dle->getPrev() != NULL) {	// link exists
						links.push_front(dle);
						links.push_front(dle->getPrev());
					}
				}
									// generate the JSON string
				return generateJSON_Of_Nodes_And_Links(nodes, links);
		}
		/**
		 * This method returns the JSON string of a Bridges array
		 *
		 * @param - array of elements
		 *
		 * @return - the JSON string
		 **/
		
		string getDataStructureRepresentation(Element<E> *b_array) {
								// generate the JSON string
cout << "Array size: " << array_size << endl;
			list<Element<E>*> nodes, links;
			for (int k = 0; k < array_size; k++)
				nodes.push_front(&b_array[k]);
			string s =  generateJSON_Of_Nodes_And_Links(nodes, links);

			return s;
		}

		/**
		 * This method returns the JSON string representation of the tree 
		 * made by using preorder traversal
		 *
		 * @param root - root of binary tree (TreeElement<E> *)
		 *
		 * @return JSON string
		 **/
		string getDataStructureRepresentation(TreeElement<E> *root) {
		
			list<Element<E>*> nodes, links;
		
			preOrderBT(root, &nodes, &links);
									// generate the JSON string
			return  generateJSON_Of_Nodes_And_Links(nodes, links);
		}
		/**
		 * This method returns the JSON string representation of the binary
		 * search tree representation.
		 *
		 * @param root - root of binary tree (BSTElement<E> *)
		 *
		 * @return JSON string
		 **/

		string getDataStructureRepresentation(BSTElement<K, E> *root) {

			list<Element<E>*> nodes, links;
		
			preOrderBST(root, &nodes, &links);
									// generate the JSON string
			return  generateJSON_Of_Nodes_And_Links(nodes, links);
		}
			
	private:
		/**
		 * Use a preorder traversal to collect the nodes and links in the 
		 * binary tree
		 *
		 * @param root
		 * @param nodes - list of returned nodes in the tree
		 * @param  links - list of returned links in the tree
		 *
		 **/
		void preOrderBT(TreeElement<E> *root, list<Element<E>*> *nodes, 
								list<Element<E>*> *links){
		
			if (root != NULL){
				nodes->push_front(root);
				if (root->getLeft() != NULL){
					links->push_front(root);
					links->push_front(root->getLeft());
				}
				if (root->getRight() != NULL){
					links->push_front(root);
					links->push_front(root->getRight());
				}
				preOrderBT(root->getLeft(), nodes, links);
				preOrderBT(root->getRight(), nodes, links);
			}
		}

		/**
		 * Use a preorder traversal to collect the nodes and links in the 
		 * binary tree
		 *
		 * @param root - root of the binary search tree
		 * @param nodes - list of returned nodes in the tree
		 * @param  links - list of returned links in the tree
		 *
		 * @return
		 **/
		void preOrderBST(BSTElement<K, E> *root, list<Element<E>*> *nodes, 
								list<Element<E>*> *links){
			if (root != NULL){
				nodes->push_front(root);
				if (root->getLeft() != NULL){
					links->push_front(root);
					links->push_front(root->getLeft());
				}
				if (root->getRight() != NULL){
					links->push_front(root);
					links->push_front(root->getRight());
				}
				preOrderBST(root->getLeft(), nodes, links);
				preOrderBST(root->getRight(), nodes, links);
			}
		}
		
		string generateJSON_Of_Nodes_And_Links(list<Element<E>*> nodes, 
							list<Element<E>*> links) {
							// map the nodes to a sequence of ids, 0...N-1
							// then get the JSON string for nodes
			unordered_map<int,int> map;
			string nodes_JSON = "";
			int i = 0;
			while (!nodes.empty()){
				Element<E>  *element = nodes.front(); nodes.pop_front();
				map[stoi(element->getIdentifier())] = i++;
							// cant exceed max number of elements
				Validation::getCurrent()->validate_ADT_size(i);
				nodes_JSON += element->getRepresentation() + ",";
			}
								// get the JSON string for links
			string links_JSON = "";
			while (!links.empty()){
								// get the link
				Element<E> *child = links.front(); links.pop_front();
				Element<E> *parent = links.front(); links.pop_front();
		
								// get the link properties
				LinkVisualizer *lvis = parent->getLinkVisualizer(child);
				links_JSON += OPEN_CURLY;
				for (auto& entry : lvis->getProperties() ){
					links_JSON += 	
						QUOTE + entry.first + QUOTE 
							+ COLON + 
						QUOTE + entry.second + QUOTE + COMMA;
				}
		
						// write out the source and targets of the link
				int s_id = map[stoi(parent->getIdentifier())];
				int t_id = map[stoi(child->getIdentifier())];
				links_JSON += 
					QUOTE + "source" + QUOTE + COLON + to_string(s_id) + COMMA +
					QUOTE + "target" + QUOTE + COLON + to_string(t_id) +
					CLOSE_CURLY + COMMA;
			}
		
			return build_JSON(nodes_JSON, links_JSON);	 
		}
		
		/**
		 * This method builds the JSON string
		 *
		 * @param nodes_JSON the string builder object of existing nodes 
		 * @param links_JSON the string builder object of existing links between 
		 * 		the nodes
		 *
		 * @return ADT's JSON
		 **/
		string build_JSON(string nodes_JSON, string links_JSON){

			if (nodes_JSON.size())
				nodes_JSON = nodes_JSON.erase(nodes_JSON.size()-1, 1);
			if (links_JSON.size())
				links_JSON = links_JSON.erase(links_JSON.size()-1, 1);

			string s_final = 
				OPEN_CURLY + 
					QUOTE + "name" + QUOTE  + COLON + 
					QUOTE + "edu.uncc.cs.bridges" + QUOTE +  COMMA +
					QUOTE + "version" + QUOTE  + COLON + 
					QUOTE + "0.4.0" + QUOTE +  COMMA +
					QUOTE + "visual" + QUOTE  + COLON + 
					QUOTE + visualizerType + QUOTE +  COMMA;

			if (nodes_JSON.size())
				s_final += QUOTE + "nodes" + QUOTE + COLON + 
					OPEN_PAREN + nodes_JSON + CLOSE_PAREN;

			if (links_JSON.size())
				s_final += COMMA + QUOTE + "links" + QUOTE + COLON +
					OPEN_PAREN + links_JSON + CLOSE_PAREN;
					 

			s_final += CLOSE_CURLY;

			if (isVisualizeJSON())
				cout << "JSON String:\t" << s_final << endl;

			return s_final;
		}
};

}
#endif

