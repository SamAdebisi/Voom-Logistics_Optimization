#pragma once
#include <vector>
#include <cstdint>

namespace voom::demand {
struct Decision { 
    int64_t courier; 
    int64_t order; 
    };
std::vector<Decision> greedy_match(
    const std::vector<int64_t>& couriers, 
    const std::vector<int64_t>& orders);
}