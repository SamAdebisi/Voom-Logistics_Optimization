#pragma once
#include <future>
#include <vector>
#include <cstdint>
#include "voom/common/lockfree_ring.hpp"

namespace voom::sim {
struct Event { 
    int type; 
    int64_t a; 
    int64_t b; 
    double t; };
class Engine {
 public:
  explicit Engine(size_t q) : q_(q) {}
  std::future<void> run_async();
  bool push(Event e){ return q_.try_push(e);} // drops when full
 private:
  voom::common::SpscRing<Event> q_;
};
}