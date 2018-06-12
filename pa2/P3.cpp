
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
  bool dirx;
public:
  Edge *edges[1000 + 1];
 Graph(bool dirx) {
  this->dirx = dirx;
  for (int i = 1; i < (1000 + 1); i++) {
    this->edges[i] = NULL;
  }
}

Graph() {}

void add_edge(int x, int y, int w, bool dirx) {
  if (x > 0 && x < (1000 + 1) && y > 0 && y < (1000 + 1)) {
    Edge *edge = new Edge(y, w);
    edge->next = this->edges[x];
    this->edges[x] = edge;
    if (!dirx) {
      add_edge(y, x, w, true);
    }
  }
}
};

void setup(bool found[], int distance[], int parent[]) {
  for (int i = 1; i < (1000 + 1); i++) {
    found[i] = false;
    distance[i] = std::numeric_limits<int>::max();
    parent[i] = -1;
  }
}

void dijkstra(Graph *g, int parent[], int distance[], int &vnode, bool (&found)[1000 + 1]) {
  int w;
  int smallest_dist;
  int neighbor;
  Edge *current;
  found[vnode] = true;
  current = g->edges[vnode];
  while (current != NULL) {
    neighbor = current->k;
    w = current->w;

    if ((distance[vnode] + w) < distance[neighbor]) {
      distance[neighbor] = distance[vnode] + w;
      parent[neighbor] = vnode;
    }
    current = current->next;
  }

  smallest_dist = std::numeric_limits<int>::max();
  for (int i = 1; i < (1000 + 1); i++) {
    if (!found[i] && (distance[i] < smallest_dist)) {
      vnode = i;
      smallest_dist = distance[i];
    }
  }
}
//refer to https://www.geeksforgeeks.org/bidirectional-search/
int main() {
  Graph *g = new Graph(false);
  vector<int> ecc;
  int s_parent[1000 + 1], s_dist[1000 + 1];
  int t_parent[1000 + 1], t_dist[1000 + 1];
  int start, end;
  int V, a, b, w;
  int intxNode;//intersected node
  bool s_found[1000 + 1], t_found[1000 + 1];
  int svNode, tvNode;
  string line;
  ofstream myfile;
  ifstream infile("pa2_ip3.txt");
  vector<int> s_path;
  vector<int> t_path;
  int s_index;
  getline(infile, line);
  istringstream iss(line);
  iss >> V;
  for (int i = 0; i < V; i++) {
    getline(infile, line);
    istringstream iss(line);
    iss >> a >> b >> w;
    g->add_edge(a, b, w, false);
  }
  if (1) {
    getline(infile, line);
    istringstream iss(line);
    iss >> start >> end;
  }
  setup(s_found, s_dist, s_parent);
  s_dist[start] = 0;
  svNode = start;
  setup(t_found, t_dist, t_parent);
  t_dist[end] = 0;
  tvNode = end;
  myfile.open("pa2_op3.txt");
  while (s_found[svNode] == false) {
    intxNode = 0;
    dijkstra(g, s_parent, s_dist, svNode, s_found);
    dijkstra(g, t_parent, t_dist, tvNode, t_found);
    for (int i = 1; i < (V + 1); i++) {
      if ((s_found[i] == t_found[i]) && s_found[i] &&
          t_found[i]) {
        intxNode = 1;
        s_index = i;
      }
    }
    if (intxNode) {
      int temp = s_index;
      while (1) {
        s_path.push_back(temp);
        if (temp == start)
          break;
        temp = s_parent[temp];
      }
      temp = s_index;
      while (1) {
        t_path.push_back(temp);
        if (temp == end)
          break;
        temp = t_parent[temp];
      }
      for (int i = s_path.size() - 1; i >= 0; i--) {
        myfile << s_path[i] << " ";
      }
      myfile << endl;
      for (int i = t_path.size() - 1; i >= 0; i--) {
        myfile << t_path[i] << " ";
      }
      myfile << endl;
      for (int i = s_path.size() - 1; i >= 0; i--) {
        myfile << s_path[i] << " ";
      }
      int found = 0;
      for (int i = 0; i < t_path.size(); i++) {
        if (found) {
          myfile << t_path[i] << " ";
        }
        if (t_path[i] == s_index) {
          found = 1;
        }
      }
      myfile << endl;
      break;
    }
  }
  myfile.close();
  delete g;
}
