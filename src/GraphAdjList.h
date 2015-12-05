#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <stdexcept> //out of range
#include <sstream> //stringstream

#include "SLelement.h" //string, unordered_map, iostream, using std

namespace bridges {
/**
 * @brief This class provides methods to represent adjacency list based
 * graphs
 *
 * The GraphAdjList class can be used to represent adjacency list based
 * graphs in BRIDGES.
 * <p>
 * In order to support any ordered type as index, this class is implemented
 * as a wrapper  around the C++ STL  unordered_map class
 * and, thus, derives all its operations from it. The Key parameter must
 * an orderable type, while E represents any application data that is
 * maintained as part of the application.
 * <p>
 * BRIDGES provides methods to visualize the graph  and its contents.
 *
 * Generic paramter Key used as index into the adjacency lists
 * Generic parameter  E  used to represent application specific data
 *
 * @author Kalpathi Subramanian, 6/29/15
 * @date 6/29/15
 */
template<typename K, typename E>
class GraphAdjList
{
    public:
        /** @brief This helper class is used by GraphAdjList to keep track of edge information */
        class Edge
        {
            private:
                double weight = LinkVisualizer::DEFAULT_WEIGHT;
                K vertex = K(); // refers to a terminating vertex
                string edge_data;// any application data can be held here
            public:
                /**
                 * This constructor sets the terminating vertex to "dest", edge weight to "wt",
                 * and edge data to "data". If an argument is not given, its default is used.
                 *
                 * @param wt The edge weight
                 * @param v The terminating vertex
                 */
                Edge(K v,int wt=LinkVisualizer::DEFAULT_WEIGHT,string data=string()) : weight(wt), vertex(v), edge_data(data) {}
                /** Assignment Operator */
                Edge& operator=(const Edge& that)
                {
                    weight = that.weight;
                    edge_data = that.edge_data;
                    vertex = that.vertex;
                    return *this;
                }
                /** Copy Constructor */
                Edge(const Edge& e) : Edge(e.vertex,e.weight,e.edge_data) {}
                /**
                 * Set edge weight to "wt"
                 *
                 * @param wt The edge weight
                 */
                void setWeight(const int& wt)
                {
                    try
                    {
                        Validation::validateWeight(wt); // validate weight
                        weight = wt;
                    }
                    catch (const string& msg)
                    {
                        cerr << msg << endl;
                        cerr << "Using default weight(" << (weight = LinkVisualizer::DEFAULT_WEIGHT) << ").." << endl;
                    }
                }
                /**
                 * Returns edge weight
                 *
                 * @return The edge weight
                 */
                int getWeight() const {return weight;}
                /**
                 * Sets terminating vetex to "dest"
                 *
                 * @param dest The terminating vertex
                 */
                void setVertex(const K& dest){vertex = dest;}
                /**
                 * Returns terminating vertex
                 *
                 * @return The terminating vertex
                 */
                K getVertex() const {return vertex;}
                /**
                 * Sets edge data to "data"
                 *
                 * @param data Application data
                 */
                void setEdgeData(const string& data){edge_data = data;}
                /**
                 * Get edge data
                 *
                 * @return The edge data
                 */
                string getEdgeData() const {return edge_data;}
        }; //end of Edge class
	private:
	    GraphAdjList(const GraphAdjList&)=delete; //Deny Implicit Copy Constructor
	    GraphAdjList& operator=(const GraphAdjList&)=delete; //Deny Implicit Assignment Operator

        unordered_map<K, Element<E>> vertices; // keep track of the graph nodes; useful to maintain their properties
		unordered_map<K, SLelement<Edge>*> adj_list; // holds the adjacency list of edges; owns all SLelement*
	public:
		/** Constructors */
		GraphAdjList() {}
		/** Destructor */
		~GraphAdjList()
		{
			for(auto& p : adj_list) //each pair<K,SLelement*> in adj_list
            {
				SLelement<Edge>::cleanup(p.second); //frees SLelement* edges
			}
			vertices.clear(); adj_list.clear();
		}
        /**
		 * Adds a vertex of key "k" and value "e" to the graph,
		 * and initializes the adjacency list.
		 * If this key already exists its value and all source associated
		 * edge data will be overwriten.
		 *
		 * @param k Vertex key
		 * @param e Vertex data
		 */
		void addVertex(const K& k,const E& e)
		{
		    stringstream conv; conv<<k;
			vertices[k] = Element<E>(e, conv.str());
			SLelement<Edge>::cleanup(adj_list[k]); //cleans if exists; sets to NULL
		}
		/**
		 * Sets the weight to "wt" of the edge from "src" to "dest".
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
			    SLelement<Edge>* sle = adj_list.at(src); adj_list.at(dest); //throws error if non-existent
			    while(sle)
                {
                    Edge ed = sle->getValue();
                    if(ed.getVertex() == dest)//edge already exists
                    {
                        ed.setWeight(wt); //change edge weight
                        sle->setValue(ed); //change slelement data
                        return;
                    }
                    sle = sle->getNext();
                }
                //edge doesn't already exist
                stringstream conv; conv<<dest;
			    adj_list.at(src) = new SLelement<Edge>(adj_list.at(src),Edge(dest,wt),conv.str());
			}
			catch(const out_of_range& oor) // either vertex not found
			{
			    cerr << "Cannot addEdge between non-existent Verticies." << endl;
			}
			catch(const bad_alloc& ba) // allocation fail
			{
			    cerr << "Allocation of graph adjacency list item failed, exiting.." << endl;
				exit(EXIT_FAILURE);
			}
		}
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
		 * Returns the adjacency lists
		 *
		 * @return The adjacency lists
		 */
		 const unordered_map<K, SLelement<Edge>*>& getAdjacencyList() const {return adj_list;}
		/**
		 * Returns adjacency list of key "k" or NULL if non-existent
		 *
		 * @param k Input Key
		 * @return The adjacency list of key "k"
		 */
		const SLelement<Edge>* getAdjacencyList(const K& k) const
		{
			try
			{
			    return adj_list.at(k);
			}
			catch(const out_of_range& oor) // not found
			{
			    cerr << "Adjacency List for vertex " << k << "not found!" << endl;
				return nullptr;
			}
		}
		/**
		 * Returns a pair of JSON strings of the nodes and links
		 * of the adjacency list based graph
		 *
		 * @return A pair of node and link JSON
		 */
		pair<string,string> getDataStructureRepresentation()
		{
			list<const Element<E>*> nodes;

            ///Graph's control of maps ensures if a key exists in one of these maps, it will exist in all of them
            for(const auto& key_sle: adj_list) //each pair<K,SLelement*> in adj_list
            {
                Element<E>& src = vertices.at(key_sle.first);
                nodes.push_front(&src);
                SLelement<Edge>* a_list = key_sle.second;
                while(a_list)
                {
                    const Edge& e = a_list->getValue();
                    ///Because getAdjList returns reference of SLelement*, there is a possibility Edge may contain an invalid vertex
                    try
                    {
                        Element<E>& dest = vertices.at(e.getVertex());
                        src.getLinkVisualizer(&dest).setWeight(e.getWeight()); //Sets link weight to edge weight
                    }
                    catch(const out_of_range& oor)
                    {
                        cerr << "Exception: Link vertex " << e.getVertex() << "not found, exiting..";
                        exit(EXIT_FAILURE);
                    }
                    a_list = a_list->getNext();
                }
            }
			return Element<E>::generateJSON_Of_Nodes_And_Links(nodes);
		}
}; //end of GraphAdjList class
}//end of bridges namespace
#endif

