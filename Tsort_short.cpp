#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <iomanip>
#include <algorithm>
#include<limits>

struct Edge {
    int to;
    double distance;
};

struct Node {
    int id;
    double weight;
};

class DestinationPathOptimizer {
    int V;
    std::vector<Node> nodes;
    std::vector<std::vector<Edge>> adj;

    // Topological sorting helper to ensure acyclic order evaluation
    void topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& Stack) {
        visited[v] = true;
        for (const auto& edge : adj[v]) {
            if (!visited[edge.to]) {
                topologicalSortUtil(edge.to, visited, Stack);
            }
        }
        Stack.push(v);
    }

public:
    DestinationPathOptimizer(int V) : V(V), adj(V) {
        for (int i = 0; i < V; ++i) {
            nodes.push_back({i, 0.0});
        }
    }

    void setNodeWeight(int id, double weight) {
        if (id >= 0 && id < V) {
            nodes[id].weight = weight;
        }
    }

    void addEdge(int from, int to, double distance) {
        adj[from].push_back({to, distance});
    }

    void findOptimalSourceToDest(int source, int destination) {
        std::stack<int> Stack;
        std::vector<bool> visited(V, false);

        // Step 1: Linearize the DAG via topological sorting
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        // Step 2: Initialize tracking arrays for path building
        // We initialize with unreachable markers (-1.0 weight / max distance)
        std::vector<double> maxWeight(V, -1.0);
        std::vector<double> minDistance(V, std::numeric_limits<double>::max());
        std::vector<int> parent(V, -1);

        // Base case: Start strictly at the designated source node
        maxWeight[source] = nodes[source].weight;
        minDistance[source] = 0.0;

        // Step 3: Process nodes sequentially from the topological stack
        while (!Stack.empty()) {
            int u = Stack.top();
            Stack.pop();

            // Only propagate paths if the node has been reached from the source
            if (maxWeight[u] != -1.0) {
                for (const auto& edge : adj[u]) {
                    int v = edge.to;
                    
                    double combinedWeight = maxWeight[u] + nodes[v].weight;
                    double combinedDistance = minDistance[u] + edge.distance;

                    // Metric formula maximizing accumulated weight per unit of distance
                    double currentMetric = combinedWeight / (combinedDistance == 0 ? 1 : combinedDistance);
                    double existingMetric = maxWeight[v] / (minDistance[v] == 0 ? 1 : minDistance[v]);

                    // Update if this route provides a better optimization ratio or if v hasn't been reached yet
                    if (minDistance[v] == std::numeric_limits<double>::max() || currentMetric > existingMetric) {
                        maxWeight[v] = combinedWeight;
                        minDistance[v] = combinedDistance;
                        parent[v] = u;
                    }
                }
            }
        }

        // Step 4: Verify destination reachability and extract path sequence
        if (maxWeight[destination] == -1.0) {
            std::cout << "Error: No valid acyclic path exists from Node " << source << " to Node " << destination << ".\n";
            return;
        }

        printTargetedResult(source, destination, parent, maxWeight, minDistance);
    }

    void printTargetedResult(int source, int destination, const std::vector<int>& parent, 
                             const std::vector<double>& maxWeight, const std::vector<double>& minDistance) {
        std::vector<int> path;
        int curr = destination;
        
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        std::reverse(path.begin(), path.end());

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "===============================================\n";
        std::cout << " PATH OPTIMIZATION: NODE " << source << " -> NODE " << destination << "\n";
        std::cout << "===============================================\n";
        std::cout << "Path Traversed     : ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        std::cout << "\nOverall Weight Carried: " << maxWeight[destination] << "\n";
        std::cout << "Total Path Distance   : " << minDistance[destination] << "\n";
        std::cout << "Final Efficiency Ratio: " << (maxWeight[destination] / minDistance[destination]) << " (Weight/Dist)\n";
        std::cout << "-----------------------------------------------\n";
    }
};

int main() {
    int totalVertices = 6;
    DestinationPathOptimizer graph(totalVertices);

    // Set Node Weights (Values added and carried forward)
    graph.setNodeWeight(0, 10.0); // Source
    graph.setNodeWeight(1, 15.0);
    graph.setNodeWeight(2, 30.0);
    graph.setNodeWeight(3, 20.0);
    graph.setNodeWeight(4, 25.0);
    graph.setNodeWeight(5, 40.0); // Destination

    // Add Edges with Distance values
    graph.addEdge(0, 1, 3.0);
    graph.addEdge(0, 2, 6.0);
    graph.addEdge(1, 3, 2.0);
    graph.addEdge(2, 4, 4.0);
    graph.addEdge(3, 5, 5.0);
    graph.addEdge(4, 5, 2.0);
    
    // Alternative shortcut paths to test optimization choices
    graph.addEdge(1, 4, 1.0); 

    // Execute targeting Path from Node 0 to Node 5
    int startNode = 0;
    int endNode = 5;
    graph.findOptimalSourceToDest(startNode, endNode);

    return 0;
}
