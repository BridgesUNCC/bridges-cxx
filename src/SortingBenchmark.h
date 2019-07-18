#ifndef SORTINGBENCHMARK_H
#define SORTINGBENCHMARK_H

#include <LineChart.h>
#include <limits>
#include <vector>
#include <chrono>
#include <stdlib.h>

namespace bridges {
  namespace benchmark {
    using namespace bridges::datastructure;
    
    class SortingBenchmark {
    private:
       LineChart& plot;

       //       Random r;

       int maxSize;
       int baseSize;
       int increment;
       double geoBase;
       double time_cap;


       void generate(int* arr, int n) {
	for (int i = 0; i < n; i++) {
	  arr[i] = ((double)rand())/RAND_MAX * (2 * n);
	}
      }
      
    public:
       SortingBenchmark(LineChart& p)
	 :plot (p) {
	p.setXLabel("Size of Array");
	p.setYLabel("Runtime (in s)");

	//r = new Random();

	maxSize = 1;
	baseSize = 1;
	increment = 1;
	geoBase = 1.;
	time_cap = std::numeric_limits<double>::max();
      }

      void setMaxSize(int size) {
	maxSize = size;
      }

       void setBaseSize(int size) {
	baseSize = size;
      }

       void setIncrement(int inc) {
	increment = inc;
      }

       void setGeometric(double base) {
	geoBase = base;
      }
       
      /**
       * @brief The benchmark will sample a range with a fixed number of
       * points.
       *
       * The benchmark will sample about nbPoint equally distributed in
       * the range [baseSize; maxSize]
       *
       * @param baseSize lower bound of the range sampled
       * @param maxSize upper bound of the range sampled
       * @param nbPoint number of sample
       */
       void linearRange(int baseSize, int maxSize, int nbPoint) {
	setBaseSize (baseSize);
	setMaxSize (maxSize);
	setIncrement ((maxSize - baseSize) / nbPoint);
	setGeometric (1.0);
      }

      /**
       * @brief The benchmark will sample a range using in geometrically
       * increasing sequence
       *
       * The benchmark will sample the range [baseSize; maxSize] using a
       * geometric distribution in base base. That is to say, it will
       * sample baseSize, base*baseSize, base*base*baseSize, ...
       *
       * @param baseSize lower bound of the range sampled
       * @param maxSize upper bound of the range sampled
       * @param base base of the geometric increase
       */
       void geometricRange(int baseSize, int maxSize, double base) {
	setBaseSize (baseSize);
	setMaxSize (maxSize);
	setIncrement (0);
	setGeometric (base);
	if (base <= 1.0) {
	  std::cerr<<"base should be > 1.0\n";
	}
      }

      /**
       * @brief sets an upper bound to the time of a run.
       *
       * The benchmark will end after a run if it takes more than the
       * given amount of time. So it is possible a particular run takes
       * more than the alloted time, but that will be the last run.x
       *
       * @param cap_in_s time limit in seconds
       **/
       void setTimeCap(double cap_in_s) {
	time_cap = cap_in_s;
      }

       void run(std::string algoName, void (*runnable)(int*, int)) {
	 std::vector<double> time;
	 std::vector<double> xData;

	 //	System.out.println(geoBase);
	 //	System.out.println(increment);

	for (int n = baseSize; n <= maxSize;
	     n = std::max((int)(geoBase * n) + increment, n + 1)) {

	  //System.out.println(n);
	  std::vector<int> arr(n);

	  generate(&arr[0], n);

	  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	  
	  runnable(&arr[0], n);
	  
	  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	  
	  std::chrono::duration<double> elapsed_seconds = end-start;
	  
	  
	  time.push_back ((double)elapsed_seconds.count() );
	  xData.push_back ( (double)n );

	  if (elapsed_seconds.count() > time_cap) {
	    break;
	  }
	}
	plot.setXData(algoName, xData);
	plot.setYData(algoName, time);
      }

    };
  }
}

#endif
