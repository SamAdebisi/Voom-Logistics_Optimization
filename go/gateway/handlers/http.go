package handlers
import (
  "encoding/json"; "net/http"; "context"; "time"; pb "github.com/voom/voom/proto"; "google.golang.org/grpc"
  "container/heap", "errors", "os" 
)

type edge struct{ to int64; w float64 }
type graph map[int64][]edge

type routeReq struct {
    Graph struct{ Edges []struct{ 
      From int64 `json:"from"`; To int64 `json:"to"`; W float64 `json:"w"` } `json:"edges"` } `json:"graph"`
    Src int64 `json:"src"`
    Dst int64 `json:"dst"`
}

type routeResp struct{ Path []int64 `json:"path"`; Cost float64 `json:"cost"` }

// Dijkstra priority queue
type item struct{ v int64; d float64; idx int }
type pq []*item
func (p pq) Len() int { return len(p) }
func (p pq) Less(i, j int) bool { return p[i].d < p[j].d }
func (p pq) Swap(i, j int) { p[i], p[j] = p[j], p[i]; p[i].idx, p[j].idx = i, j }
func (p *pq) Push(x any) { *p = append(*p, x.(*item)) }
func (p *pq) Pop() any { old := *p; n := len(old); it := old[n-1]; *p = old[:n-1]; return it }

func shortestPath(g graph, s, t int64) ([]int64, float64, error) {
    dist := map[int64]float64{s: 0}
    par := map[int64]int64{}
    q := pq{&item{v: s, d: 0}}
    heap.Init(&q)
    for q.Len() > 0 {
        it := heap.Pop(&q).(*item)
        if it.v == t { break }
        for _, e := range g[it.v] {
            nd := it.d + e.w
            if d, ok := dist[e.to]; !ok || nd < d {
                dist[e.to] = nd
                par[e.to] = it.v
                heap.Push(&q, &item{v: e.to, d: nd})
            }
        }
    }
    if _, ok := dist[t]; !ok { return nil, 0, errors.New("unreachable") }
    // reconstruct
    path := []int64{t}
    for cur := t; cur != s; {
        p, ok := par[cur]; if !ok { break }
        path = append([]int64{p}, path...)
        cur = p
    }
    return path, dist[t], nil
}

func Optimize(w http.ResponseWriter, r *http.Request){
    defer r.Body.Close()
    var req routeReq
    if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
        http.Error(w, "bad request", http.StatusBadRequest); return
    }
    // build graph
    g := graph{}
    for _, e := range req.Graph.Edges { g[e.From] = append(g[e.From], edge{to: e.To, w: e.W}) }
    path, cost, err := shortestPath(g, req.Src, req.Dst)
    if err != nil { http.Error(w, err.Error(), http.StatusBadGateway); return }
    _ = os.Getenv("OPTIMIZER_ADDR") // kept for future gRPC integration
    w.Header().Set("Content-Type", "application/json")
    _ = json.NewEncoder(w).Encode(routeResp{Path: path, Cost: cost})
}
