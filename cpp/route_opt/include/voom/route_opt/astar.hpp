#pragma once
#include <queue>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdint>
#include <algorithm>
#include "voom/common/graph.hpp"

namespace voom::route_opt {
using Path = std::vector<int64_t>;

inline Path reconstruct(int64_t s, int64_t t, 
const std::unordered_map<int64_t,int64_t>& p){
  Path path; int64_t cur=t; while(cur!=s && p.count(cur)) { 
    path.push_back(cur); 
    cur=p.at(cur);
    } 
    path.push_back(s); 
    std::reverse(path.begin(), path.end()); 
    return path; 
    }

inline double zero_h(int64_t, int64_t){ return 0.0; }

inline std::pair<Path,double> astar(
    const common::Graph& g, int64_t s, int64_t t) {
  struct State{ int64_t v; double f; 
  bool operator<(const State& o) const { return f>o.f; } 
  }; // min-heap
  std::priority_queue<State> pq; 
  std::unordered_map<int64_t,double> gscore; 
  std::unordered_map<int64_t,int64_t> par;
  gscore[s]=0.0; pq.push({s,0.0});
  while(!pq.empty()){
    auto [u,fu]=pq.top(); 
    pq.pop(); 
    if(u==t) break;
    for(const auto& e : g.neighbors(u)){
      double cand = gscore[u] + e.w; 
      if(!gscore.count(e.to) || cand < gscore[e.to]){ gscore[e.to]=cand; 
      par[e.to]=u; double f=cand+zero_h(e.to,t); pq.push({e.to,f}); 
      }
    }
  }
  if(!gscore.count(t)) return {{}, std::numeric_limits<double>::infinity()};
  return {reconstruct(s,t,par), gscore[t]};
}
} // namespace voom::route_opt