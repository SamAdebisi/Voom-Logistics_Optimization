package handlers
import (
  "encoding/json"; "net/http"; "context"; "time"; pb "github.com/voom/voom/proto"; "google.golang.org/grpc"
)

type routeReq struct { Graph struct{Edges []struct{From int64 `json:"from"`; 
	To int64 `json:"to"`; W float64 `json:"w"`} `json:"edges"`} `json:"graph"`; 
	Src int64 `json:"src"`; 
	Dst int64 `json:"dst"` 
}

type routeResp struct { Path []int64 `json:"path"`; Cost float64 `json:"cost"` }

func Optimize(w http.ResponseWriter, r *http.Request){
  var req routeReq; json.NewDecoder(r.Body).Decode(&req)
  conn, _ := grpc.Dial("optimizer:50051", grpc.WithInsecure())
  defer conn.Close()
  c := pb.NewOptimizerClient(conn)
  g := &pb.Graph{}
  for _, e := range req.Graph.Edges { g.Edges = append(g.Edges, &pb.Edge{From:e.From, To:e.To, W:e.W}) }
  ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second); defer cancel()
  rep, err := c.ShortestPath(ctx, &pb.RouteRequest{Graph: g, Src: req.Src, Dst: req.Dst})
  if err != nil { http.Error(w, err.Error(), http.StatusBadGateway); return }
  json.NewEncoder(w).Encode(routeResp{Path: rep.Path, Cost: rep.Cost})
}