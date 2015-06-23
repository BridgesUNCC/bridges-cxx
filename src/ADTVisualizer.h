#ifndef ADT_VISUALIZER_H

#define ADT_VISUALIZER_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

#include "GraphList.h"
#include "DLelement.h"
#include "TreeElement.h"
#include "BSTElement.h"

/** 
 *	The Bridges class uses this object to keep track of the Visualization 
 *	representation prior to passing the information to the Bridges Server.
 *	<p>
 *	An end user will generally not need to interact directly with this 
 * 	class.
 *
 *	@author Kalpathi Subramanian (C++ port), 6/15/15
 *
 **/

template<typename K, typename E> class ADTVisualizer {
	private:
		string visualizerType;
		string visualizerIdentifier;
		unordered_map<string, string> adt_type;

		bool visualizeJSON = false;

		
	public:
	
		/**
	 	* constructor using the superclass Object
	 	* when using this constructor the default ADT structure is graph 
	 	* @throws Exception 
	 	*/														
		ADTVisualizer(){
			visualizerType = "";
			visualizerIdentifier = "";
//			adt_type.emplace("Graph_AdjacencyMatrix", "graphl");
//			adt_type.emplace("Array_Stack","llist");
//			adt_type.emplace("Array_Queue","llist");
			adt_type.emplace("GraphAdjacencyList", "graphl");
			adt_type.emplace("LinkedListStack","llist");
			adt_type.emplace("LinkedListQueue","llist");
			adt_type.emplace("BinaryTree","tree");
			adt_type.emplace("BinarySearchTree","tree");
			adt_type.emplace("SinglyLinkedList", "llist");
			adt_type.emplace("DoublyLinkedList", "Dllist");
			adt_type.emplace("ArrayList", "ArrayList");
		}

		/**
		 * Outputs the flag  that controls if the JSON is to be output
 		 * @return the visualizeJSON flag
 		 **/

		bool isVisualizeJSON() {
			return visualizeJSON;
		}

		/**
 		 * @param visualizeJSON the visualizeJSON to set
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
		 * 	@return one the of the strings represented in ADTVisualizer.ADT_TYPE 
		 * 	that represents the type of Bridges Visualization (e.g. 
		 * 	"graph", "llist", etc.)
		 **/
		string getVisualizerType() {
			return visualizerType;
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
			
		string getGraphAdjList_Representation(
			unordered_map<string, GraphList<E> > graph_adj_list){
									// first gather the nodes and links by
									// traversing the graph
			list<Element<E>*> nodes, links; 
		
			for (auto& key_val: graph_adj_list){
									//  get the graph nodes
				SLelement<E> *src_vertex = (key_val.second).getSourceVertex();
				nodes.push_front (src_vertex);
									//  get the graph links
				SLelement<Edge> *a_list = (key_val.second).getAdjacencyList();
				while (a_list != NULL) {
					links.push_front(src_vertex);
								// look up the vertex corresponding to this edge
								// since only the nodes are used in the graph
								// for visualization. Edges in adjacency list
								// are for the graph reprentation only
					Edge e = a_list->getValue();
					SLelement<E> *dest_vertex = 
							graph_adj_list[e.getVertex()].getSourceVertex();
					links.push_front(dest_vertex);
					a_list = a_list->getNext();
				}
			}
							// use the singly linked list case to get the JSON!
			return generateJSON_Of_Nodes_And_Links(nodes, links);
		}
			
		/**
		 * This method creates a JSON representation of the graph - 
		 * Adj. Matrix Rep. 
		 * @param first_element - is the starting element(node)
		 * @return - this method returns the JSON string
		 */
		string getSLRepresentation(SLelement<E> *first_element) {

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
		 * @param e
		 * @return
		 **/
		string getDLRepresentation(DLelement<E> *first_element) {
		
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
		
		string getArrayListRepresentation(vector<Element<E>*> b_array) {
								// generate the JSON string
			list<Element<E>*> nodes, links;
			for (auto& el : b_array) {
				nodes.push_front (el);
			}
			string s =  generateJSON_Of_Nodes_And_Links(nodes, links);

			return s;
		}

		/**
		 * This method returns the JSON string representation of the tree 
		 * made by using preorder traversal
		 * @param e
		 * @return
		 **/
		string getTreeRepresentation(TreeElement<E> *root) {
		
			list<Element<E>*> nodes, links;
		
			preOrder(root, nodes, links);
									// generate the JSON string
			return  generateJSON_Of_Nodes_And_Links(nodes, links);
		}

		string getBSTRepresentation(BSTElement<K, E> *root) {
			list<BSTElement<K, E>*> nodes, links;
		
			preOrder(root, nodes, links);
									// generate the JSON string
			return  generateJSON_Of_Nodes_And_Links(nodes, links);

		}
			
		/**
		 * Use a preorder traversal to collect the nodes and links in the tree
		 * @param root
		 * @param element_to_index
		 * @param i
		 * @return
		 **/

		void preOrder(TreeElement<E> *root, list<Element<E>*> nodes, 
								list<Element<E>*> links){
		
			if (root != NULL){
				nodes.push_front(root);
				if (root->getLeft() != NULL){
					links.push_front(root);
					links.push_front(root->getLeft());
				}
				if (root->getRight() != NULL){
					links.push_front(root);
					links.push_front(root->getRight());
				}
				preOrder(root->getLeft(), nodes, links);
				preOrder(root->getRight(), nodes, links);
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
				links_JSON +="{";
				for (auto& entry : lvis->getProperties() ){
					links_JSON += 	
							"\"" + entry.first + "\":\"" + entry.second + "\",";
				}
		
						// write out the source and targets of the link
				int s_id = map[stoi(parent->getIdentifier())];
				int t_id = map[stoi(child->getIdentifier())];
				links_JSON += 
						"\"source\":" + to_string(s_id) + ","
						"\"target\":" + to_string(t_id)  + "},";
			}
		
			return build_JSON(nodes_JSON, links_JSON);	 
		}
		
		/**
			 * Generating the JSON string given a set of nodes 
			 * and links for the singly linked list
			 * @param nodes
			 * @param links
			 * @param data structure type
			 * @return string
		*/
		string generateJSON_SLL (list< SLelement<E>* > nodes, 
						list< SLelement<E>* > links){
							// map the nodes to a sequence of ids, 0...N-1
							// then get the JSON string for nodes
			unordered_map<int,int> map;
			string nodes_JSON = "";
			int i = 0;
			while (!nodes.empty()){
				SLelement<E>  *element = nodes.front(); nodes.pop_front();
				map[stoi(element->getIdentifier())] = i++;
							// cant exceed max number of elements
				Validation::getCurrent()->validate_ADT_size(i);
				nodes_JSON += element->getRepresentation() + ",";
			}
								// get the JSON string for links
			string links_JSON = "";
			while (!links.empty()){
								// get the link
				SLelement<E> *child = links.front(); links.pop_front();
				SLelement<E> *parent = links.front(); links.pop_front();
		
								// get the link properties
				LinkVisualizer *lvis = parent->getLinkVisualizer(child);
				links_JSON +="{";
				for (auto& entry : lvis->getProperties() ){
					links_JSON += 	
							"\"" + entry.first + "\":\"" + entry.second + "\",";
				}
		
						// write out the source and targets of the link
				int s_id = map[stoi(parent->getIdentifier())];
				int t_id = map[stoi(child->getIdentifier())];
				links_JSON += 
						"\"source\":" + to_string(s_id) + ","
						"\"target\":" + to_string(t_id)  + "},";
			}
		
			return build_JSON(nodes_JSON, links_JSON);	 
		}
		
		/**
		 * This method creates the JSON for a doubly linked list
		 * @param nodes - this is the Linked list of DLelements
		 * @param links - this is the list containing the links
		 * @return returns the JSON string for the current ADT
		 */
		string generateJSON_DLL (list<DLelement<E>* > nodes, 
						list<DLelement<E>* > links){
							// map the nodes to a sequence of ids, 0...N-1
							// then get the JSON string for nodes
			unordered_map<int,int> map;
			string nodes_JSON = "";
			int i = 0;
			while (!nodes.empty()){
				DLelement<E>  *element = nodes.front(); nodes.pop_front();
				map[stoi(element->getIdentifier())] = i++;
							// cant exceed max number of elements
				Validation::getCurrent()->validate_ADT_size(i);
				nodes_JSON += element->getRepresentation() + ",";
			}
								// get the JSON string for links
			string links_JSON = "";
			while (!links.empty()){
								// get the link
				DLelement<E> *child = links.front(); links.pop_front();
				DLelement<E> *parent = links.front(); links.pop_front();
		
								// get the link properties
				LinkVisualizer *lvis = parent->getLinkVisualizer(child);
				links_JSON +="{";
				for (auto& entry : lvis->getProperties() ){
					links_JSON += 	
						"\"" + entry.first + "\":\"" + entry.second + "\",";
				}
							// write out the source and targets of the link
				int s_id = map[stoi(parent->getIdentifier())];
				int t_id = map[stoi(child->getIdentifier())];
				links_JSON += 
						"\"source\":" + to_string(s_id) +
						"\"target\":" + to_string(t_id)  + "},";
			}
		
			return build_JSON(nodes_JSON, links_JSON);	 
		}
		
		/**
		 * This method builds the JSON for the Binary Tree
		 * @param nodes - list of the tree nodes
		 * @param links - list of the tree links
		 * @return complete JSON string for the current ADT
		 */
		string getJSON_BinaryTree(list<TreeElement<E>*> nodes, 
								list<TreeElement<E>*> links){
								// map the nodes to a sequence of ids, 0...N-1
								// then get the JSON string for nodes
			unordered_map<int,int> map;
			string nodes_JSON = "";
			int i = 0;
			while (!nodes.empty()){
				TreeElement<E>  *element = nodes.front(); nodes.pop_front();
				map[stoi(element->getIdentifier())] = i++;
							// cant exceed max number of elements
				Validation::getCurrent()->validate_ADT_size(i);
				nodes_JSON += element->getRepresentation() + ",";
			}
								// get the JSON string for links
			string links_JSON = "";
			while (!links.empty()){
								// get the link
				TreeElement<E> *child = links.front(); links.pop_front();
				TreeElement<E> *parent = links.front(); links.pop_front();
		
								// get the link properties
				LinkVisualizer *lvis = parent->getLinkVisualizer(child);
				links_JSON +="{";
				for (auto& entry : lvis->getProperties() ){
					links_JSON += 	
						"\"" + entry.first + "\":\"" + entry.second + "\",";
				}
						// write out the source and targets of the link
				int s_id = map[stoi(parent->getIdentifier())];
				int t_id = map[stoi(child->getIdentifier())];
				links_JSON += 
						"\"source\":" + to_string(s_id) +
						"\"target\":" + to_string(t_id)  + "},";
			}
		
			return build_JSON(nodes_JSON, links_JSON);	 
		}
		
		/**
		 * This method builds the JSON for the Graph ADT
		 * @param nodes - list of the tree nodes
		 * @param links - list of the tree links
		 * @return complete JSON string for the current ADT
		 */
		string generateJSON_Graph ( list<SLelement<E>* > nodes, 
			list<SLelement<E>* > links_src, list<SLelement<E>* > links_dest){
							// map the nodes to a sequence of ids, 0...N-1
							// then get the JSON string for nodes
			unordered_map<int,int> map;
			string nodes_JSON = "";
			int i = 0;
			while (!nodes.empty()){
				SLelement<E>  *element = nodes.front(); nodes.pop_front();
				map[stoi(element->getIdentifier())] = i++;
							// cant exceed max number of elements
				Validation::getCurrent()->validate_ADT_size(i);
				nodes_JSON += element->getRepresentation() + ",";
			}
								// get the JSON string for links
			string links_JSON = "";
			while (!links_src.empty()){
								// get the link
				SLelement<E> *child = links_dest.front();links_dest.pop_front();
				SLelement<E> *parent = links_src.front();links_src.pop_front();
		
								// get the link properties
				LinkVisualizer *lvis = parent->getLinkVisualizer(child);
				links_JSON +="{";
				for (auto& entry : lvis->getProperties() ){
					links_JSON += 	
						"\"" + entry.first + "\":\" " + entry.second + "\",";
				}
							// write out the source and targets of the link
				int s_id = map[stoi(parent->getIdentifier())];
				int t_id = map[stoi(child->getIdentifier())];
				links_JSON += 
						"\"source\":" + to_string(s_id) +
						"\"target\":" + to_string(t_id)  + "},";
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
					string("{") + "\"name\":\"edu.uncc.cs.bridges\"," + 
						"\"version\":\"0.4.0\"," +
						"\"visual\":\"" + visualizerType + "\",";

			if (nodes_JSON.size())
				s_final += string("\"nodes\":[") + nodes_JSON + "]";

			if (links_JSON.size())
				s_final += string(",") + "\"links\":[" + links_JSON + "]" + "}";
		
			if (isVisualizeJSON())
				cout << "JSON String:\t" << s_final << endl;
		
			return s_final;
		}
};
#endif

