#include "voom/demand/balancer.hpp"

namespace voom::demand {
std::vector<Decision> greedy_match(
    const std::vector<int64_t>& cs, 
    const std::vector<int64_t>& os){
  std::vector<Decision> r; 
  size_t n=std::min(cs.size(), os.size()); 
  r.reserve(n);
  // for(size_t i=0;i<n;++i) r.push_back({
  //   static_cast<int64_t>(i), static_cast<int64_t>(i)
  //   });

  // map actual ids, not indices
  for(size_t i=0;i<n;++i) r.push_back({cs[i], os[i]});
  return r;
}
}