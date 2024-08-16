#include <iostream>
#include <map>
#include <set>
#include <queue>
#include "graaf.hpp"

struct Edge {
    int from;
    int to;
    int weight;

    bool operator<(const Edge& other) const {
        return std::tie(weight, from, to) < std::tie(other.weight, other.from, other.to);
    }

    bool operator==(const Edge& other) const {
        return from == other.from && to == other.to && weight == other.weight;
    }
};

void generateDotFile(const std::set<Edge> &edges, const std::string &filename)
{
    std::ofstream file(filename);

    file << "graph G {\n";

    for (const auto &edge : edges)
    {
        file << "    " << edge.from << " -- " << edge.to;
        file << " [label=\"" << edge.weight << "\"];\n";
    }

    file << "}\n";

    file.close();
}

std::set<Edge> prim(GraafMetTakdata<ONGERICHT, int> &graaf) {
    std::set<Edge> mst;  // Minimum Spanning Tree edges
    std::vector<bool> visited(graaf.aantalKnopen(), false);  // To keep track of visited nodes

    auto cmp = [] (const Edge &a, const Edge &b) {
        return a.weight > b.weight;  // Min-heap should have smallest weight on top
    };

    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);  // Min-heap to store the edges

    for (int start = 0; start < graaf.aantalKnopen(); ++start) {
        if (visited[start]) continue;  // Skip if already part of an MST

        // Start with an unvisited node
        //std::cout << "Starting new MST component from node " << start << "\n";
        visited[start] = true;
        for (auto g : graaf[start]) {
            //std::cout << "Pushing edge (" << start << " - " << g.first << ") with weight " << *graaf.geefTakdata(start, g.first) << " into the priority queue.\n";
            pq.push({start, g.first, *graaf.geefTakdata(start, g.first)});
        }

        while (!pq.empty()) {
            Edge e = pq.top();
            pq.pop();

            //std::cout << "Considering edge (" << e.from << " - " << e.to << ") with weight " << e.weight << "\n";

            if (visited[e.to]) {
                //std::cout << "Skipping edge (" << e.from << " - " << e.to << ") as destination node is already visited.\n";
                continue;  // Skip if the destination node is already visited
            }

            // Add the edge to the MST
            //std::cout << "Adding edge (" << e.from << " - " << e.to << ") with weight " << e.weight << " to MST.\n";
            mst.insert(e);
            visited[e.to] = true;

            //std::cout << "Current MST size: " << mst.size() << "\n";

            // Add all edges from the newly visited node to the priority queue
            for (const auto &[neighbor, weight] : graaf[e.to]) {
                if (!visited[neighbor]) {
                    //std::cout << "Pushing edge (" << e.to << " - " << neighbor << ") with weight " << *graaf.geefTakdata(e.to, neighbor) << " into the priority queue.\n";
                    pq.push({e.to, neighbor, *graaf.geefTakdata(e.to, neighbor)});
                }
            }
        }
    }

    std::cout << "Final MST consists of the following edges:\n";
    for (const auto &edge : mst) {
        std::cout << "(" << edge.from << " - " << edge.to << ") with weight " << edge.weight << "\n";
    }

    return mst;
}




int main()
{
    const int numberOfNodes = 10; // Adjust the number of nodes as needed
    const int numberOfEdges = 30; // Adjust the number of edges as needed
    const int maxWeight = 100;    // Maximum weight for an edge

    // Creating a graph with edge data (weights)
    GraafMetTakdata<ONGERICHT, int> graph(numberOfNodes);

    // Seed for random number generation
    std::srand(time(NULL));

    // Set to track existing edges (to avoid duplicates)
    std::set<std::pair<int, int>> existingEdges;

    // Adding random edges with random weights
    for (int i = 0; i < numberOfNodes; ++i)
    {
        int node1 = i;
        int node2 = std::rand() % numberOfNodes;
        int weight = std::rand() % maxWeight + 1; // Weight in the range [1, maxWeight]

        auto edge1 = std::make_pair(node1, node2);
        auto edge2 = std::make_pair(node2, node1);

        // Check for self-loop
        if (node1 != node2 && existingEdges.find(edge1) == existingEdges.end() && existingEdges.find(edge2) == existingEdges.end())
        {
            graph.voegVerbindingToe(node1, node2, weight);
            existingEdges.insert(std::make_pair(node1, node2));
            existingEdges.insert(std::make_pair(node2, node1)); // For undirected graph
        }
    }

    // Adding remaining edges
    for (int i = numberOfNodes; i < numberOfEdges; ++i)
    {
        int node1 = std::rand() % numberOfNodes;
        int node2 = std::rand() % numberOfNodes;
        int weight = std::rand() % maxWeight + 1; // Weight in the range [1, maxWeight]

        auto edge1 = std::make_pair(node1, node2);
        auto edge2 = std::make_pair(node2, node1);

        if (node1 != node2 && existingEdges.find(edge1) == existingEdges.end() && existingEdges.find(edge2) == existingEdges.end())
        {
            graph.voegVerbindingToe(node1, node2, weight);
            existingEdges.insert(std::make_pair(node1, node2));
            existingEdges.insert(std::make_pair(node2, node1)); // For undirected graph
        }
    }

    // Output the graph
    std::cout << "Generated Random Weighted Graph, you can see it in file output_graph.dot..." << std::endl;
    graph.teken("ouput_graph.dot");

    auto edges = prim(graph);
    generateDotFile(edges, "output_prim.dot");

    std::cout << "The result of the prim function can be viewed in file output_prim.dot in the build folder..." << std::endl;

    return 0;
}
