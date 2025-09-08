#pragma once
#include <vector>
#include <utility>

namespace voom::eta {
inline std::pair<double,double> window_for_path(
    const std::vector<int64_t>& /*path*/){ 
        return {10.0, 15.0}; 
        }
}