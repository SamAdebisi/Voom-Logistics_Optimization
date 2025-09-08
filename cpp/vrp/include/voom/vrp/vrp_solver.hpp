#pragma once
#include <vector>
#include <cstdint>
#include "voom/common/graph.hpp"
#include "voom/route_opt/dijkstra.hpp"

namespace voom::vrp {
struct Route { 
    std::vector<int64_t> path; 
    double cost{}; 
    };
struct VRPResult { 
    std::vector<Route> routes; 
    double total_cost{}; 
    };

// Greedy nearest-depot baseline. Replace with metaheuristics.
VRPResult solve_greedy(
    const voom::common::Graph& g, 
    const std::vector<int64_t>& depots, 
    const std::vector<int64_t>& orders, int k);
}