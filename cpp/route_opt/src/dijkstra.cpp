#include "voom/route_opt/dijkstra.hpp"

namespace voom::route_opt {
std::pair<Path,double> dijkstra(
    const common::Graph& g, int64_t s, int64_t t){
  struct Q{ 
    int64_t v; double d; 
  bool operator<(const Q& o) const { return d>o.d; } 
  };
  std::priority_queue<Q> pq; 
  std::unordered_map<int64_t,double> dist; 
  std::unordered_map<int64_t,int64_t> par;
  dist[s]=0.0; 
  pq.push({s,0.0});
  while(!pq.empty()){
    auto [u,du]=pq.top(); 
    pq.pop(); 
    if(u==t) break;
    for(const auto& e: g.neighbors(u)){
      double nd=du+e.w; 
      if(!dist.count(e.to) || nd<dist[e.to]){ 
        dist[e.to]=nd; 
        par[e.to]=u; 
        pq.push({e.to,nd}); 
        }
    }
  }
  if(!dist.count(t)) return {{}, 
  std::numeric_limits<double>::infinity()};
  return {rec(s,t,par), dist[t]};
}
}