package metrics
import "github.com/prometheus/client_golang/prometheus/promhttp"
func Handler() *promhttp.Handler { h := promhttp.Handler(); return &h }