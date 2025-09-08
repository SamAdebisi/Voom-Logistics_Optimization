#include <grpcpp/grpcpp.h>
#include "optimizer.pb.h"
#include "optimizer.grpc.pb.h"
#include "voom/route_opt/astar.hpp"
#include "voom/vrp/vrp_solver.hpp"
#include "voom/eta/eta_core.hpp"
#include "voom/common/graph.hpp"

using grpc::ServerContext; 
using grpc::Status; 
using grpc::StatusCode;

class OptimizerImpl final : public voom::Optimizer::Service {
  voom::common::Graph to_graph(const voom::Graph& gpb){
    voom::common::Graph g; for(const auto& e : gpb.edges()) g.add_edge(e.from(), e.to(), e.w()); return g;
  }
  Status ShortestPath(ServerContext*, const voom::RouteRequest* req, voom::RouteReply* rep) override {
    auto g = to_graph(req->graph());
    auto [p,c] = voom::route_opt::astar(g, req->src(), req->dst());
    for(auto v: p) rep->add_path(v); rep->set_cost(c); return Status::OK;
  }
  Status SolveVRP(ServerContext*, const voom::VRPRequest* req, voom::VRPReply* rep) override {
    auto g = to_graph(req->graph());
    std::vector<int64_t> dep(req->depots().begin(), req->depots().end());
    std::vector<int64_t> ord(req->orders().begin(), req->orders().end());
    auto r = voom::vrp::solve_greedy(g, dep, ord, req->k());
    for(const auto& rt : r.routes){ auto* rr = rep->add_routes(); for(auto v: rt.path) rr->add_path(v); 
    rr->set_cost(rt.cost);} rep->set_total_cost(r.total_cost); return Status::OK;
  }
  Status ComputeETA(ServerContext*, const voom::ETAWindowRequest* req, voom::ETAWindowReply* rep) override {
    std::vector<int64_t> path(req->path().begin(), req->path().end());
    auto [mn,mx] = voom::eta::window_for_path(path); rep->set_min_eta(mn); 
    rep->set_max_eta(mx); return Status::OK;
  }
};