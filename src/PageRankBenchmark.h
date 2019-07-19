#ifndef PAGERANK_BENCHMARK_H
#define PAGERANK_BENCHMARK_H

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
    
    class PageRankBenchmark :public GraphBenchmark {
    private:
       LineChart& plot;

    public:
       PageRankBenchmark(LineChart& p)
	 :plot (p) {
	 p.setXLabel("Number of Edges");
	 p.setYLabel("Runtime (in s)");

      }
      
       void run(std::string algoName,
		void (*pralgo)(const GraphAdjList<std::string>& gr,
				std::unordered_map<std::string, double>& out)) {
	 std::vector<double> time;
	 std::vector<double> vtxCounts;
	 std::vector<double> edgeCounts;

	 for (int years = 0; years < 120; years=1.2*years+1) {
	   int year = 2019 - years;
	   std::cerr<<"*"<<std::flush;
	  GraphAdjList<std::string> graph;
	  long vertexCount;
	  long edgeCount;
	  std::tie(vertexCount, edgeCount)= generateWikidataMovieActor(year, 2019, graph);
	  
	  std::unordered_map<std::string, double> pr;

	  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	  
	  pralgo(graph, pr);
	  
	  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	  
	  std::chrono::duration<double> elapsed_seconds = end-start;

	  
	  time.push_back ((double)elapsed_seconds.count() );
	  vtxCounts.push_back ( (double)vertexCount );
	  edgeCounts.push_back ( (double)edgeCount );

	  if (elapsed_seconds.count() > time_cap) {
	    break;
	  }
	}
	plot.setXData(algoName, edgeCounts);
	plot.setYData(algoName, time);
	std::cerr<<"\n"<<std::flush;
       }
    };
  }
}

#endif
