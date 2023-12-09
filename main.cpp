#include <climits>
#include <iomanip>
#include <iostream>
using namespace std;

const int VERTICES = 6; // Number of vertices in the graph

// Function prototypes
int minDistance(int dist[], bool sptSet[]);
void printSolution(int dist[]);
void dijkstra(int graph[VERTICES][VERTICES], int src);

int main() {
  // Example graph represented by an adjacency matrix
  int graph[VERTICES][VERTICES] = 
  {{0, 2, 0, 0, 0, 0}, 
  {2, 0, 4, 1, 0, 0},           
  {0, 4, 0, 7, 3, 0}, 
  {0, 1, 7, 0, 0, 1},
  {0, 0, 3, 0, 0, 5}, 
  {0, 0, 0, 1, 5, 0}};

  dijkstra(graph, 0); // Find the shortest path from vertex 0

  return 0;
}

// Function to find the vertex with the minimum distance value
// from the set of vertices not yet included in the shortest path tree
int minDistance(int dist[], bool sptSet[]) {
  int minDist = INT_MAX, minIndex = -1;

  for (int v = 0; v < VERTICES; ++v) {
    if (!sptSet[v] && dist[v] < minDist) {
      minDist = dist[v];
      minIndex = v;
    }
  }

  return minIndex;
}

// Function to print the constructed distance array
void printSolution(int dist[]) {
  cout << left << setw(10) << "Vertex" << setw(15) << "Distance from Source\n";
  for (int i = 0; i < VERTICES; ++i) {
    cout << setw(10) << i << setw(15) << dist[i] << "\n";
  }
}

// Function that implements Dijkstra's single source shortest path algorithm
void dijkstra(int graph[VERTICES][VERTICES], int src) {
  int dist[VERTICES];    // The output array dist[i] holds the shortest distance
                         // from src to i
  bool sptSet[VERTICES]; // sptSet[i] will be true if vertex i is included in
                         // the shortest path tree or the shortest distance from
                         // src to i is finalized

  for (int i = 0; i < VERTICES; ++i) {
    dist[i] = INT_MAX;
    sptSet[i] = false;
  }

  dist[src] = 0; // Distance from the source vertex to itself is always 0

  for (int count = 0; count < VERTICES - 1; ++count) {
    int u = minDistance(dist, sptSet); // Pick the minimum distance vertex from
                                       // the set of vertices not yet processed
    sptSet[u] = true;                  // Mark the picked vertex as processed

    // Update dist value of the adjacent vertices of the picked vertex
    for (int v = 0; v < VERTICES; ++v) {
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
          dist[u] + graph[u][v] < dist[v])
        dist[v] = dist[u] + graph[u][v];
    }
  }

  // Print the constructed distance array
  printSolution(dist);
}