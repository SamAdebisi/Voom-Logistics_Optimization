#include <benchmark/benchmark.h>
#include "voom/common/graph.hpp"
#include "voom/route_opt/astar.hpp"

static void BM_AStar(benchmark::State& st){
  voom::common::Graph g; 
  for(int i=1;i<1000;++i) g.add_edge(i,i+1,1.0);
  for(auto _ : st){ auto [p,c]=voom::route_opt::astar(g,1,999); 
  benchmark::DoNotOptimize(c); }
}
BENCHMARK(BM_AStar);
BENCHMARK_MAIN();