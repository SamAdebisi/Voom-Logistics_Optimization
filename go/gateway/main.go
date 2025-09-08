package main
import (
  "log"; "net/http"; "time"; "github.com/gorilla/mux"; "github.com/voom/voom/gateway/handlers"; "github.com/voom/voom/gateway/metrics"
)
func main(){
  r := mux.NewRouter()
  r.HandleFunc("/health", func(w http.ResponseWriter, _ *http.Request){ w.Write([]byte("ok")) })
  r.HandleFunc("/optimize", handlers.Optimize).Methods("POST")
  r.Handle("/metrics", metrics.Handler())
  srv := &http.Server{Addr: ":8080", Handler: r, ReadTimeout: 5*time.Second, WriteTimeout: 10*time.Second}
  log.Println("gateway on :8080"); log.Fatal(srv.ListenAndServe())
}