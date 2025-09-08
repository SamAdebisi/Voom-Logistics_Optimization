#include <gtest/gtest.h>
#include "voom/common/graph.hpp"
#include "voom/route_opt/astar.hpp"

TEST(AStar, Simple){
  voom::common::Graph g; 
  g.add_edge(1,2,1.0); 
  g.add_edge(2,3,1.0);
  auto [p,c]=voom::route_opt::astar(g,1,3);
  ASSERT_EQ(p.size(),3u); ASSERT_DOUBLE_EQ(c,2.0);
}