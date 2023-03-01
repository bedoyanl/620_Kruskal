// Kruskal's algorithm in C++
// from https://www.programiz.com/dsa/kruskal-algorithm
// and https://www.youtube.com/watch?v=YG4jexlSAjc

#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;
using namespace std::chrono;
#define edge pair<int, int>
class Timer
{
	public:
		Timer()
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}
		~Timer()
		{
			Stop();
		}
		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			auto duration = end-start;
			double ms = duration *0.001;
			std::cout << duration << "us (" << ms << "ms)\n";
			
		}

	private:
		std::chrono::time_point< std::chrono::high_resolution_clock>m_StartTimepoint;

};
class Graph {
   private:
  vector<pair<int, edge> > G;  // graph
  vector<pair<int, edge> > T;  // mst
  int *parent;
  int V;  // number of vertices/nodes in graph
   public:
  Graph(int V);
  void AddWeightedEdge(int u, int v, int w);
  int find_set(int i);
  void union_set(int u, int v);
  void kruskal();
  void print();
};
Graph::Graph(int V) {
  parent = new int[V];

  //i 0 1 2 3 4 5
  //parent[i] 0 1 2 3 4 5
  for (int i = 0; i < V; i++)
    parent[i] = i;

  G.clear();
  T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w) {
  G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
  // If i is the parent of itself
  if (i == parent[i])
    return i;
  else
    // Else if i is not the parent of itself
    // Then i is not the representative of his set,
    // so we recursively call Find on its parent
    return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
  parent[u] = parent[v];
}
void Graph::kruskal() {
  int i, uRep, vRep;
  sort(G.begin(), G.end());  // increasing weight
  for (i = 0; i < G.size(); i++) {
    uRep = find_set(G[i].second.first);
    vRep = find_set(G[i].second.second);
    if (uRep != vRep) {
      T.push_back(G[i]);  // add to tree
      union_set(uRep, vRep);
    }
  }
}
void Graph::print() {
  cout << "Edge :"
     << " Weight" << endl;
  for (int i = 0; i < T.size(); i++) {
    cout << T[i].second.first << " - " << T[i].second.second << " : "
       << T[i].first;
    cout << endl;
  }
}
int main() 
{
    srand(time(NULL)); // Initialize random seed

    for (int n = 10; n <= 1000; n += 10) { // Loop over different graph sizes
        int m = n * (n - 1) / 2; // Calculate maximum number of edges

        // Generate a random graph of size n and m edges
        Graph g(n);
        // ...

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_weight(1, 30);
    uniform_int_distribution<int> dist_vertex(0, n - 1);

    // Generate num_edges random edges with random weights
    for (int i = 0; i < m; i++) {
        int u = dist_vertex(gen);
        int v = dist_vertex(gen);
        int w = dist_weight(gen);
        g.AddWeightedEdge(u, v, w);
    }

        auto start = high_resolution_clock::now(); // Start timer
        // Run Kruskal's algorithm on the generated graph
        g.kruskal();
        // ...
        auto end = high_resolution_clock::now(); // End timer

        auto duration = duration_cast<milliseconds>(end - start); // Compute duration

        cout << "Graph size: " << n << ", time taken: " << duration.count() << " ms" << endl;
    }

    return 0;
}
  
//{
  //	Timer timer;
  	//Graph g(6);
  //g.AddWeightedEdge(0, 1, 4);
  //g.AddWeightedEdge(0, 2, 4);
  //g.AddWeightedEdge(1, 2, 2);
  //g.AddWeightedEdge(1, 0, 4);
  //g.AddWeightedEdge(2, 0, 4);
  //g.AddWeightedEdge(2, 1, 2);
  //g.AddWeightedEdge(2, 3, 3);
  //g.AddWeightedEdge(2, 5, 2);
  //g.AddWeightedEdge(2, 4, 4);
  //g.AddWeightedEdge(3, 2, 3);
  //g.AddWeightedEdge(3, 4, 3);
  //g.AddWeightedEdge(4, 2, 4);
  //g.AddWeightedEdge(4, 3, 3);
  //g.AddWeightedEdge(5, 2, 2);
  //g.AddWeightedEdge(5, 4, 3);

 // g.kruskal();
  //g.print();
//}
