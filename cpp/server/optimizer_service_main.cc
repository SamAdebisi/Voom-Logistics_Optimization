#include <grpcpp/grpcpp.h>
#include <iostream>
#include "optimizer.grpc.pb.h"
#include "optimizer_service.cc"

int main(int argc, char** argv){
  std::string addr = argc>1? argv[1] : "0.0.0.0:50051";
  OptimizerImpl svc; 
  grpc::ServerBuilder b; 
  b.AddListeningPort(addr, grpc::InsecureServerCredentials()); 
  b.RegisterService(&svc); 
  std::unique_ptr<grpc::Server> server(b.BuildAndStart());
  std::cout << "optimizer listening on " << addr << "\n";
  server->Wait();
}