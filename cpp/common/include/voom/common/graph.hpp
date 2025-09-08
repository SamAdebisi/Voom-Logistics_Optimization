#pragma once
#include <cstdint>
#include <vector>
#include <limits>
#include <utility>
#include <unordered_map>

namespace voom::common {
struct Edge { int64_t to; double w; };
class Graph {
 public:
  void add_edge(int64_t u, int64_t v, double w) { adj_[u].push_back({v,w}); }
  const std::vector<Edge>& neighbors(int64_t u) const {
    static const std::vector<Edge> empty;
    auto it = adj_.find(u); return it==adj_.end()? empty : it->second;
  }
 private:
  std::unordered_map<int64_t, std::vector<Edge>> adj_;
};
} // namespace voom::common