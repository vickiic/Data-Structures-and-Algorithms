#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Edge{
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

void dijkstras(Graph *g, int parent[], int dist[], int s) {
  bool found[1000 + 1];
  Edge *curr;
  int current;
  int neighbor;
  int w;
  int min_d;
  setup(found, dist, parent);
  dist[s] = 0;
  current = s;
  while (found[current] == false) {
    found[current] = true;
    curr = g->edges[current];
    while (curr != NULL) {
      neighbor = curr->k;
      w = curr->w;
      if ((dist[current] + w) < dist[neighbor]) {
        dist[neighbor] = dist[current] + w;
        parent[neighbor] = current;
      }
      curr = curr->next;
    }

    min_d = std::numeric_limits<int>::max();    // set next vertex to the vertex with the smallest dist
    for (int i = 1; i < (1000 + 1); i++) {
      if (!found[i] && (dist[i] < min_d)) {
        current = i;
        min_d = dist[i];
      }
    }
  }
}

int main() {
  Graph *g = new Graph(false);
  vector<int> eccentricity;
  int parent[1000 + 1];
  int dist[1000 + 1];
  int d, d1, radius, s, x, a, b, w;
  string line;
  ofstream myfile;
  ifstream infile("pa2_ip1.txt");
  getline(infile, line);
  istringstream iss(line);
  iss >> x;
  for (int i = 0; i < x; i++) {
    getline(infile, line);
    istringstream iss(line);
    iss >> a >> b >> w;
    g->add_edge(a, b, w, false);
  }
  for (int s = 1; s < (x + 1); s++) {
    dijkstras(g, parent, dist, s);
    d1 = 0;
    for (int j = 1; j < (x + 1); j++) {
      if (s != j) {
        if (d1 < dist[j])
          d1 = dist[j];
      }
    }
    eccentricity.push_back(d1);
  }
  for (int i = 0; i < x; i++)
  d = 0;
  for (int i = 0; i < x; i++) {
    if (d < eccentricity[i])
      d = eccentricity[i];
  }
  myfile.open("pa2_op1.txt");
  myfile << d << endl;
  radius = 10000;
  for (int i = 0; i < x; i++) {
    if (radius > eccentricity[i])
      radius = eccentricity[i];
  }
  myfile << radius << endl;
  for (int i = 0; i < x; i++) {
    if (radius == eccentricity[i]) {
      myfile << i + 1 << " ";
    }
  }
  myfile << endl;
  myfile.close();
  delete g;
}
