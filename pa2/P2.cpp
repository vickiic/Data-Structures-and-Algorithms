#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
using namespace std;
#define INF 0x3f3f3f3f

void dijk(int **b, int **parent, int n) {
  vector<int> next[n][n];
  int count[n][n];
  int i, j, k;
  ofstream Write2("pa2_op2_2.txt", ios::out);
  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      next[k][i].push_back(-1);
      if (b[k][i] != INF)
        count[k][i] = 1;
      else
        count[k][i] = 0;
    }
  }
  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        if (b[i][j] > b[i][k] + b[k][j]) {
          b[i][j] = b[i][k] + b[k][j];
          parent[i][j] = parent[k][j];
          next[i][j].clear();
          next[i][j].push_back(k);
          count[i][j] = count[i][k] * count[j][k]; // 1
        } else if ((b[i][j] == b[i][k] + b[k][j]) && k != j && k != i) {
          count[i][j] += count[i][k] * count[j][k]; //+= 1;
          if (b[i][j] != INF)
            next[i][j].push_back(k);
        }
      }
    }
  }
 
  float pathcen[n];
  for (i = 0; i < n; i++)
    pathcen[i] = 0.0;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      for (k = 0; k < next[i][j].size(); k++) {
              if (next[i][j][k]==-1) {
                pathcen[i] += 0.5;
                pathcen[j] += 0;
              }
        pathcen[next[i][j][k]] += (1.0 / count[i][j]);
      }
    }
  }
  //cout << "centrality" << endl;
 // for (i = 0; i < n; i++) {
  //  cout << pathcen[i] << endl;
  //}
  vector<float> nodeBtwn;
  for (i = 0; i < n; i++) {
    nodeBtwn.push_back(pathcen[i]);
  }
  sort(nodeBtwn.begin(), nodeBtwn.end(), greater<float>());
  vector<int> usedIndex;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (pathcen[j] == nodeBtwn[i]) {
        int found = 0;
        for (int k = 0; k < usedIndex.size(); k++) {
          if (j == usedIndex[k]) {
            found = 1;
            break;
          }
        }

        if (!found) {
          Write2 << j + 1 << " " << nodeBtwn[i] << endl;
          usedIndex.push_back(j);
          break;
        }
      }
    }
  }
  Write2.close();
}

int main() {
  ifstream Read("pa2_ip2.txt", ios::in);
  ofstream Write("pa2_op2_1.txt", ios::out);
  int counter = 0;
  int **a;
  if (Read and Write) {
    int n = 1;
    string Line1;
    int l2 = 0;
    int l3 = 0;
    int l4 = 0;
    int counter = 1;
    while (!Read.eof()) //  and n > 0
    {
      getline(Read, Line1);
      stringstream ss;
      ss.str(Line1);

      if (counter == 1) {
        ss >> n;
        a = new int *[n];
        for (int i = 0; i < n; ++i)
          a[i] = new int[3];
      } else {
        ss >> l2;
        ss >> l3;
        ss >> l4;
        a[counter - 2][0] = l2;
        a[counter - 2][1] = l3;
        a[counter - 2][2] = l4;

        l2 = 0;
        l3 = 0;
        l4 = 0;
        if (counter - 1 == n)
          break;
        //	n--;
      }
      counter++;
    }
    int **adj = new int *[n];
    int **parent = new int *[n];
    for (int i = 0; i < n; ++i) {
      adj[i] = new int[n];
      parent[i] = new int[n];
      for (int j = 0; j < n; j++) {
        if (i != j)
          adj[i][j] = INF;
      }
    }
    for (int j = 0; j < n; j++) {
      adj[j][j] = 0;
      parent[j][j] = j;
    }
    for (int j = 0; j < n; j++) {
      adj[a[j][0] - 1][a[j][1] - 1] = a[j][2];
      adj[a[j][1] - 1][a[j][0] - 1] = a[j][2];
      parent[a[j][0] - 1][a[j][1] - 1] = a[j][0] - 1;
      parent[a[j][1] - 1][a[j][0] - 1] = a[j][1] - 1;
    }
    dijk(adj, parent, n);
    int *diff = new int[n];
    for (int j = 0; j < n; j++) {
      diff[j] = 0;
    }

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        Write << i + 1 << " " << j + 1 << " " << adj[i][j] << endl;
      }
    }
  } 
  Read.close();
  Write.close();

}
