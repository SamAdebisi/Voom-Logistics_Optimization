#pragma once
#include <atomic>
#include <vector>

namespace voom::common {
// Single-producer single-consumer ring buffer. Backpressure via try_*.
template <typename T>
class SpscRing {
 public:
  explicit SpscRing(size_t cap) : buf_(cap+1), head_(0), tail_(0) {}
  bool try_push(const T& v) { 
    auto h=head_.load(std::memory_order_relaxed); 
    auto n=next(h); if(n==tail_.load(std::memory_order_acquire)) 
    return false; 
    buf_[h]=v; head_.store(n,std::memory_order_release); 
  return true; }
  bool try_pop(T& out) { auto t=tail_.load(std::memory_order_relaxed); 
  if(t==head_.load(std::memory_order_acquire)) return false; 
  out=buf_[t]; 
  tail_.store(next(t),std::memory_order_release); return true; 
  }
 private:
  size_t next(size_t i) const { return (i+1)%buf_.size(); }
  std::vector<T> buf_;
  std::atomic<size_t> head_, tail_;
};
} // namespace voom::common