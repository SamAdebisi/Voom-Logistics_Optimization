#include "voom/sim/sim_engine.hpp"
#include <thread>

namespace voom::sim {
std::future<void> Engine::run_async(){
  return std::async(std::launch::async, [this]{
    Event e; while(q_.try_pop(e)) { /* process */ }
  });
}
}