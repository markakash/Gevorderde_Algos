#include <iostream>
#include <queue>

#include "set"
#include "graaf.hpp"
#include "map"

struct Edge {
    int from;
    int to;
    int weight;

    bool operator<(const Edge &other) const {
        return weight < other.weight;
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

std::set<Edge> kruskal(GraafMetTakdata<ONGERICHT, int> &graaf) {
    std::set<Edge> results;
    std::map<int, std::set<int> *> collection;

    auto cmp = [] (const Edge &a, const Edge &b) {
        return a.weight > b.weight; // Changed to a.weight > b.weight to get the minimum edge
    };

    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);

    // Initialize collections and add edges to the priority queue
    for (int i = 0; i < graaf.aantalKnopen(); i++) {
        collection[i] = new std::set<int>{i}; // Each node starts in its own set
        for (auto c : graaf[i]) {
            if (i < c.first) { // Ensures each edge is added only once
                Edge e = {i, c.first, *graaf.geefTakdata(i, c.first)};
                pq.push(e);
            }
        }
    }

    while (results.size() < graaf.aantalKnopen() - 1 && !pq.empty()) {
        Edge edge = pq.top();
        pq.pop();

        if (collection.at(edge.from) != collection.at(edge.to)) {
            results.insert(edge);

            // Merge the smaller collection into the larger one
            if (collection.at(edge.from)->size() >= collection.at(edge.to)->size()) {
                auto *help = collection.at(edge.to);
                for (auto el : *collection.at(edge.to)) {
                    collection[el] = collection.at(edge.from);
                }
                collection.at(edge.from)->insert(help->begin(), help->end());
                //delete help; // Clean up the old set
            } else {
                auto *help = collection.at(edge.from);
                for (auto el : *collection.at(edge.from)) {
                    collection[el] = collection.at(edge.to);
                }
                collection.at(edge.to)->insert(help->begin(), help->end());
                //delete help; // Clean up the old set
            }
        }
    }

    return results;
}

int main()
{
    /**
    GraafMetTakdata<ONGERICHT, int> graaf(4);
    graaf.voegVerbindingToe(0, 1, 5);
    graaf.voegVerbindingToe(1, 2, 7);

    kruskal(graaf);

    // So ffffffffs fuckers gave dipshit uitleg: So when u make a graph using the .voegverbindingToe method like above, then the following happens:
    // Internally there is vector with maps inside it. The position in that vector comes overeen with the node number. So lets say your adding a connection
    // betweeen node 0 and 1. Then in position 0 and 1, there is a map created. The map is of type <int, int>. The first int says to which node is it connected
    // so, in out example it would be 1. The 2nd int says bbasically the edge number, meaning via which edge is it connected.
    // For example: 0 - 1 - 2. Then in vector on position 1, there are 2 maps. One saying it connected t 0 via edge 0, and one saying its connected to 2 via edge 1.

    for (int a = 1; a < graaf.aantalKnopen(); a++) {
        auto i = graaf[a];
        for (auto b : i) {
            auto meh = b.first;
            auto bbla = b.second;
            std::cout << "First : " << meh << std::endl;
            std::cout << "Second : " << bbla << std::endl;
        }
    }
    **/
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

    auto edges = kruskal(graph);
    generateDotFile(edges, "output_kruskal.dot");

    std::cout << "The result of the kruskal function can be viewed in file output_prim.dot in the build folder..." << std::endl;

    return 0;
}