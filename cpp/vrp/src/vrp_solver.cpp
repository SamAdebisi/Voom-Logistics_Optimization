#include "voom/vrp/vrp_solver.hpp"
#include <unordered_set>

namespace voom::vrp {
VRPResult solve_greedy(
    const voom::common::Graph& g, 
    const std::vector<int64_t>& depots, 
    const std::vector<int64_t>& orders, int k){
  VRPResult res; 
  res.routes.resize(std::max(1,k));
  std::unordered_set<int64_t> unassigned(orders.begin(), orders.end());
  size_t idx=0; 
  for(auto o : unassigned){
    int64_t d = depots[idx % depots.size()];
    auto [p,c] = voom::route_opt::dijkstra(g, d, o);
    res.routes[idx % res.routes.size()].path = p; 
    res.routes[idx % res.routes.size()].cost += c; 
    idx++;
  }
  res.total_cost=0.0; 
  for(auto& r: res.routes) res.total_cost += r.cost; 
  return res;
}
}