#ifndef SHORTESTPATH_BENCHMARK_H
#define SHORTESTPATH_BENCHMARK_H

#include <LineChart.h>
#include <limits>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <GraphBenchmark.h>

namespace bridges {
	namespace benchmark {
		using namespace bridges::datastructure;

		class ShortestPathBenchmark : public GraphBenchmark {
			private:
				LineChart& plot;
				DataSource ds;

			public:
				ShortestPathBenchmark(LineChart& p)
					: plot (p) {
					p.setXLabel("Number of Edges");
					p.setYLabel("Runtime (in s)");

				}

				int getCenter(const OSMData& osm_data, const GraphAdjList<int, OSMVertex, double>& graph,
					double latc, double lonc) {
					//
					auto distfunction = [ = ](const OSMVertex & v) -> double {
						return (v.getLatitude() - latc) * (v.getLatitude() - latc) + (v.getLongitude() - lonc) * (v.getLongitude() - lonc);
					};

					int minindex = 0;
					double dist = distfunction(graph.getVertex(minindex)->getValue());

					for (int i = 1; i < graph.getVertices()->size(); ++i) {
						double locdist = distfunction(graph.getVertex(i)->getValue());
						if (locdist < dist) {
							minindex = i;
							dist = locdist;
						}
					}

					return minindex;
				}

				void run(std::string algoName,
					void (*spalgo)(const GraphAdjList<int, OSMVertex, double>& gr,
						int source,
						std::unordered_map<int, double>& distance,
						std::unordered_map<int, int>& parent)) {
					std::vector<double> time;
					std::vector<double> vtxCounts;
					std::vector<double> edgeCounts;

					// double reflat = 39.9713; //Columbus, OH
					// double reflong = -82.99;

					double reflat = 40.74; //New York City, NC
					double reflong = -73.98;


					for (double radius = 0.02; radius < 0.15; radius += 0.02) {
						std::cerr << "*" << std::flush;
						//std::tie(vertexCount, edgeCount)= generateWikidataMovieActor(year, 2019, graph);

						OSMData osm_data = ds.getOSMData(reflat - radius, reflong - radius,
								reflat + radius, reflong + radius);
						GraphAdjList<int, OSMVertex, double> graph;
						osm_data.getGraph (&graph);

						long vertexCount = countVertices(graph);
						long edgeCount = countEdges(graph);


						int root = getCenter(osm_data, graph, reflat, reflong);

						std::unordered_map<int, double> level;
						std::unordered_map<int, int> parent;

						std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

						spalgo(graph, root, level, parent);

						std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

						std::chrono::duration<double> elapsed_seconds = end - start;


						time.push_back ((double)elapsed_seconds.count() );
						vtxCounts.push_back ( (double)vertexCount );
						edgeCounts.push_back ( (double)edgeCount );

						if (elapsed_seconds.count() > time_cap) {
							break;
						}
					}
					plot.setXData(algoName, edgeCounts);
					plot.setYData(algoName, time);
					std::cerr << "\n" << std::flush;
				}
		};
	}
}

#endif
