//#pragma once
#include <grpcpp/grpcpp.h>
#include "optimizer.pb.h"
#include "optimizer.grpc.pb.h"
#include "voom/common/graph.hpp"

class OptimizerImpl final : public voom::Optimizer::Service {
  voom::common::Graph to_graph(const voom::Graph& gpb);
  grpc::Status ShortestPath(grpc::ServerContext*, const voom::RouteRequest* req, voom::RouteReply* rep) override;
  grpc::Status SolveVRP(grpc::ServerContext*, const voom::VRPRequest* req, voom::VRPReply* rep) override;
  grpc::Status ComputeETA(grpc::ServerContext*, const voom::ETAWindowRequest* req, voom::ETAWindowReply* rep) override;
};
