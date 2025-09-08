#pragma once
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <cstdint>
#include <algorithm>
#include "voom/common/graph.hpp"

namespace voom::route_opt {
using Path = std::vector<int64_t>;
inline Path rec(
    int64_t s, int64_t t, const std::unordered_map<int64_t,int64_t>& p){ 
        Path path; int64_t cur=t; 
        while(cur!=s && p.count(cur)){ 
            path.push_back(cur); 
            cur=p.at(cur);} path.push_back(s); 
            std::reverse(path.begin(), path.end()); 
            return path; 
            }

std::pair<Path,double> dijkstra(
    const common::Graph& g, int64_t s, int64_t t);
}