#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <stdexcept> //out of range
#include <sstream> //stringstream

#include "SLelement.h" 
#include "Edge.h"

namespace bridges{
/**
 * @brief This class provides methods to represent adjacency list based graphs
 *
 * The class is simply a wrapper around the C++ STL unordered_map class and thus
 * derives all its operations from it.
 *
 * Generic Parameters:
 *      K that is used as an index,
 *      E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 6/29/15
 */
template<typename K, typename E>
class GraphAdjList : public DataStructure {
    private:
        /** Indexed map of this this graph's verticies */
        unordered_map<K, Element<E>> vertices; // useful to maintain their properties
        /** Map of edge lists for this graph's */
        unordered_map<K, SLelement<Edge<K> >*> adj_list; // holds the adjacency list of edges;
    public:
        virtual ~GraphAdjList() override {
//			for(auto& p : adj_list) {  //frees edges
//				if (p.second){p.second->cleanup();}
//			}
		}
        /** @return The string representation of this data structure type */
        virtual const string getDStype() const override {return "GraphAdjacencyList";}
        /**
         * Adds a vertex of key "k" and value "e" to the graph, and initializes its
         * adjacency list.
         * If this key already exists its value and all source associated edges with
         * be overwriten.
         * If value "e" is not provided the default will be used.
         *
         * @param k The vertex key
         * @param e The vertex data
         */
        void addVertex(const K& k,const E& e= E())
        {
            stringstream conv; conv << k;
            vertices[k] = Element<E>(e, conv.str());
            if(adj_list[k])
            {
                adj_list.at(k)->cleanup();
                adj_list.at(k)=nullptr;
            }
        }
        /**
         * Sets the edge from "src" to "dest", weight to "wt" and data to "data".
         * This will overwrite the existing edge weight.
         * If data is not provided the default will be used;
         *
         * @param src The key of the source Vertex
         * @param dest The key of the destination Vertex
         * @param wt The weight of the edge
         * @param data The edge data
         * @throw out_of_range If "src" or "dest" is non-existenet within this graph
         * @throw bad_alloc If allocation of a graph adjacency list item failed
         */
        void addEdge(const K& src, const K& dest, const unsigned int& wt,
							const string& data = string()) {
            try {
                vertices.at(src); vertices.at(dest);
                if(wt==0){				//remove link data
					vertices.at(src).links.erase(&(vertices.at(dest)));
				} 
                SLelement<Edge<K> > *sle = adj_list.at(src);
                while(sle) {
                    Edge<K> ed = sle->getValue();
                    if(ed.getVertex() == dest){ //edge already exists
                        ed.setWeight(wt); //change edge weight
                        ed.setEdgeData(data); //change edge data
                        sle->setValue(ed); //change slelement data
                        return;
                    }
                    sle = sle->getNext();
                }
						// edge doesn't exist creates default link data 
						// if none already present
                vertices.at(src).links[&(vertices.at(dest))];
                stringstream conv; conv << dest;
                adj_list.at(src) = 
					new SLelement<Edge<K> > (adj_list.at(src), 
						Edge<K> (dest, wt, data), conv.str());// create edge
            }
            catch( const out_of_range& oor){
				cerr<<"Cannot addEdge between non-existent verticies" << endl;
				throw;
			}
        }
        /** @return The vertex list of this graph */
        const unordered_map<K, Element<E>>& getVertices() const {return vertices;}
        /** @return The adjacency list  of the graph */
        const unordered_map<K, SLelement<Edge<K> >*>& getAdjacencyList() const {return adj_list;}
        /**
         * Returns adjacency list of a vertex with name k
         *
         * @param k The key of the source vertex
         * @throw out_of_range If key is non-existent within this graph
         *
         * @return The adjacency list of key "k"
         */
        SLelement<Edge<K> >* getAdjacencyList(const K& k) {
            try{return adj_list.at(k);}
            catch(const out_of_range& oor){cerr <<  "Cannot getAdjacencyList() of a non-existent vertex!" <<endl; throw;}
        }
    private:
        /**
         * Gets the JSON representation of this Graph's nodes and links
         *
         * @return A pair holding the nodes and links JSON strings respectively
         */
        virtual const pair<string,string> getDataStructureRepresentation() const override
        {
            unordered_set<const Element<E>*> nodes;
            for(const auto& key_ele : vertices) // each pair<K,Element> in vertices
            {
                nodes.emplace(&(key_ele.second));
            }
            return Element<E>::generateJSON(nodes); // generate the JSON
        }

}; //end of GraphAdjList class
}//end of bridges namespace
#endif

