#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Edge {
public:
  int k;
  int w;
  Edge *next;
  Edge(int k, int w) {
  this->k = k;
  this->w = w;
  this->next = NULL;
}
};

class Graph {
  bool d;
public:
  Edge *edges[1000 + 1];
Graph(bool d) {
  this->d = d;
  for (int i = 1; i < (1000 + 1); i++) {
    this->edges[i] = NULL;
  }
}

Graph() {}

void add_edge(int x, int y, int w, bool d) {
  if (x > 0 && x < (1000 + 1) && y > 0 && y < (1000 + 1)) {
    Edge *edge = new Edge(y, w);
    edge->next = this->edges[x];
    this->edges[x] = edge;
    if (!d) {
      add_edge(y, x, w, true);
    }
  }
}
};

void setup(bool found[], int dist[], int parent[]) {
  for (int i = 1; i < (1000 + 1); i++) {
    found[i] = false;
    dist[i] = std::numeric_limits<int>::max();
    parent[i] = -1;
  }
}
void dijkstra(Graph *g, int parent[], int dist[], int &vNode, bool (&found)[1000 + 1]) {
  int w;
  int min_d;
  int neighbor;
  Edge *current;
  found[vNode] = true;
  current = g->edges[vNode];
  while (current != NULL) {
    neighbor = current->k;
    w = current->w;
    if ((dist[vNode] + w) < dist[neighbor]) {
      dist[neighbor] = dist[vNode] + w;
      parent[neighbor] = vNode;
    }
    current = current->next;
  }

  min_d = std::numeric_limits<int>::max();
  for (int i = 1; i < (1000 + 1); i++) {
    if (!found[i] && (dist[i] < min_d)) {
      vNode = i;
      min_d = dist[i];
    }
  }
}

int main() {
  Graph *g = new Graph(false);
  int start, mid, end, V, a, b, w;
  string line;
  ofstream myfile;
  int intxNode;
  int sv_node, uv_node,tv_node;
  bool s_found[1000 + 1];
  bool u_found[1000 + 1];
  bool t_found[1000 + 1];
  int s_parent[1000 + 1], s_dist[1000 + 1];
  int t_parent[1000 + 1], t_dist[1000 + 1];
  int u_parent[1000 + 1], u_dist[1000 + 1];
  ifstream infile("pa2_ip4.txt");
  int s_inx;
  int total_edge;
  getline(infile, line);
  istringstream iss(line);
  iss >> total_edge;
  V = 0;
  for (int i = 0; i < total_edge; i++) { // find out # of nodes
    getline(infile, line);
    istringstream iss(line);
    iss >> a >> b >> w;
    if (V < a)
      V = a;
    if (V < b)
      V = b;
    g->add_edge(a, b, w, false);
  }
  if (1) {
    getline(infile, line);
    istringstream iss(line);
    iss >> start >> mid >> end;
  }
  setup(s_found, s_dist, s_parent);
  s_dist[start] = 0;
  sv_node = start;
  setup(u_found, u_dist, u_parent);
  u_dist[mid] = 0;
  uv_node = mid;
  setup(t_found, t_dist, t_parent);
  t_dist[end] = 0;
  tv_node = end;
  while (s_found[sv_node] == false) {
    intxNode = 0;
    dijkstra(g, s_parent, s_dist, sv_node, s_found); //search 3 v
    dijkstra(g, u_parent, u_dist, uv_node, u_found);
    dijkstra(g, t_parent, t_dist, tv_node, t_found);
    for (int i = 1; i < (V + 1); i++) {
      if ((s_found[i] == t_found[i]) &&
          (u_found[i] == t_found[i]) && s_found[i] &&
          u_found[i] && t_found[i]) {
        intxNode = 1;
        s_inx = i;
        myfile.open("pa2_op4.txt");
        myfile << s_inx << endl;
        myfile.close();
        break;
      }
    }
     if (intxNode) {
      break;
    }
  }
  delete g;
  }