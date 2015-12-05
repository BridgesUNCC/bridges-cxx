#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H

#include <stdexcept> //out of range
#include <sstream> //stringstream

#include "Element.h" //unordered_map, string, iostream, using std

namespace bridges{
/**
 * @brief This class provides methods to represent adjacency list based
 *		graphs
 *
 * The GraphAdjMatrix class can be used to represent adjacency matrix based
 * graphs in BRIDGES, with Key representing a data specific generic parameter.
 * The class is simply a wrapper  around the C++ STL  unordered_map class
 * and, thus, derives all its operations from it.  Given the use  of
 * operator overloading, the adjacency matrix implementation is almost
 * identical to a normal array representation, except that any ordered type
 * can be used to index into the matrix.
 * <p>
 * BRIDGES provides methods to visualize the graph  and its contents.
 *
 * param Key is any orderable type, used as index into the adjacency matrix
 * param  E  used to represent application specific data and is any legal
 *			 C++ type
 *
 * @author Kalpathi Subramanian (C++ port)
 * @date 6/29/15
 */
template <typename K, typename E>
class GraphAdjMatrix
{
	private:
        GraphAdjMatrix(const GraphAdjMatrix&)=delete; //Deny Implicit Copy Constructor
	    GraphAdjMatrix& operator=(const GraphAdjMatrix&)=delete; //Deny Implicit Assignment Operator
		//addVertex is the only function that adds pairs to maps; guarenteed if K exists in one, it exists in all
		unordered_map<K, Element<E>> vertices; //keep track of the graph nodes; useful to maintain their properties;
		unordered_map<K, unordered_map<K, int>> matrix; //holds the adjacency matrix of edges

	public:
	    /** Constructor */
	    GraphAdjMatrix(){}
        /** Destructor */
		~GraphAdjMatrix(){vertices.clear();matrix.clear();}
        /**
		 * Adds a vertex of key "k" and value "e" to the graph.
         * Sets its edges to all vericies to be weght 0.
         * If this key already exists its value and all associated
		 * edge values will be overwriten.
		 *
		 * @param k Vertex key
		 * @param e Vertex data
		 */
		void addVertex(const K& k,const E& e)
		{
			stringstream conv; conv<<k; //Converts key into string
			vertices[k] = Element<E>(e, conv.str());
			for(const auto& p : vertices) //each pair<K,Element> in vertices
            {
				matrix[k][p.first] = matrix[p.first][k] = 0;
			}
		}
        /**
		 * Sets weight of edge from "src" to "dest" to "wt".
		 * This will overwrite the existing edge weight.
		 * This weight will also take precidence over LinkVisualizer's weight.
		 *
		 * @param src The key of the source Vertex
		 * @param dest The key of the destination Vertex
		 * @param wt Input weight
		 */
		void addEdge(const K& src,const K& dest,const int& wt)
		{
            try
            {
                Validation::validateWeight(wt);
                matrix.at(src).at(dest) = wt;
            }
            catch(const string& msg) //invalid weight
            {
                cerr << msg << endl << "Weight unchanged..." << endl;
            }
			catch(const out_of_range& oor) // either key not found
			{
			    cerr << "Cannot addEdge between non-existent Verticies." << endl;
			}
		}
		/**
		 * Returns the adjacency matrix
		 *
		 * @return The adjacency matrix
		 */
		const unordered_map<K, unordered_map<K, int>>& getMatrix() const {return matrix;}
		/**
		 * Returns the graph nodes
		 *
		 * @return The vertices
		 */
		const unordered_map<K, Element<E>>& getVertices() const {return vertices;}
		/**
		 * Returns vertex of key "k" or NULL if non-existent
		 *
		 * @param k Input Key
		 * @return The vetex of key "k"
		 */
		Element<E>* getVertex(const K& k)
		{
			try
			{
			    return &(vertices.at(k));
			}
			catch(const out_of_range& oor) // not found
			{
			    cerr << "Vertex " << k << "not found!" << endl;
				return nullptr;
			}
		}
		/**
		 * Returns a pair of JSON strings of the nodes and links
		 * of the adjacency matrix based graph
		 *
		 * @return A pair of node and link JSON
		 */
		pair<string,string> getDataStructureRepresentation()
		{
			list<const Element<E>*> nodes;

            ///Graph's control of maps ensures if a key exists in one of these maps, it will exist in all of them
            for (const auto& key_map: matrix) // each pair<K,map> in matrix
            {
                Element<E>& src = vertices.at(key_map.first);
                nodes.push_front(&src);
                for (const auto& key_int : key_map.second) //each pair<K,int> in matrix.map
                {
                    Element<E>& dest = vertices.at(key_int.first);
                    src.getLinkVisualizer(&dest).setWeight(matrix.at(key_map.first).at(key_int.first)); //Sets link weight to edge weight
                }
            }
			return Element<E>::generateJSON_Of_Nodes_And_Links(nodes); // generate the JSON
		}
}; //end of GraphAdjMatrix class
}//end of bridges namespace
#endif

