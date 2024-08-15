#include <iostream>
#include <map>
#include <set>

#include "graaf.hpp"

void generateDotFile(const Graaf<ONGERICHT> &graph, const std::map<int, int> &colors, std::map<int, std::string> &colorMap, const std::string &filename, std::set<std::pair<int, int>> &edges)
{
    std::ofstream file(filename);

    file << "graph G {\n";
    for (int i = 0; i < graph.aantalKnopen(); ++i)
    {
        file << "    " << i << " [label=\"" << i << "\", color=\"" << colorMap.at(colors.at(i)) << "\"];\n";
    }
    // Write all edges
    for (const auto &edge : edges)
    {
        file << "    " << edge.first << " -- " << edge.second << ";\n";
    }
    file << "}\n";

    file.close();
}

std::map<int, int> coloring_sequence(Graaf<ONGERICHT> graaf) {
    // Basically to know which node has which color
    std::map<int, int> colors;

    for (int i = 0; i < graaf.aantalKnopen(); i++) {
        std::set<int> neighbor_color;

        // Collect all colors used by the neighbour
        for (auto el : graaf[i]) {
            if (colors.contains(el.first)) {
                neighbor_color.insert(colors[el.first]);
            }
        }

        // Find the smallest color not used by neighbour
        int c = 0;
        while (neighbor_color.contains(c)) {
            c++;
        }

        // Assign that color to the current node
        colors[i] = c;
    }

    return colors;
}

int main()
{
    // Number of nodes and edges for the random graph
    int numberOfNodes = 10; // You can change this value
    int numberOfEdges = 15; // You can change this value

    // Creating a graph
    Graaf<ONGERICHT> randomGraph(numberOfNodes);

    // Set to keep track of existing edges
    std::set<std::pair<int, int>> existingEdges;

    // Seed for random number generation
    std::srand(time(nullptr));

    // Adding random edges
    for (int i = 0; i < numberOfEdges; ++i)
    {
        int from = std::rand() % numberOfNodes;
        int to = std::rand() % numberOfNodes;

        // Ensure no self-loops and edge does not already exist
        if (from != to && existingEdges.find(std::make_pair(from, to)) == existingEdges.end() &&
            existingEdges.find(std::make_pair(to, from)) == existingEdges.end())
        {
            randomGraph.voegVerbindingToe(from, to);
            existingEdges.insert(std::make_pair(from, to));
        }
    }

    // Printing the graph
    std::cout << "Generated Random Graph" << std::endl;
    randomGraph.teken("output_graph.dot");

    auto colors = coloring_sequence(randomGraph);

    std::map<int, std::string> colorMap = {
        {0, "red"},
        {1, "blue"},
        {2, "green"},
        {3, "yellow"},
        {4, "orange"},
        {5, "purple"},
        {6, "pink"},
        {7, "brown"},
        {8, "gray"},
        {9, "cyan"}};

    std::set<std::pair<int, int>> uniqueEdges;

    for (int i = 0; i < randomGraph.aantalKnopen(); ++i)
    {
        for (auto el : randomGraph[i])
        {
            if (i < el.first)
            {
                uniqueEdges.insert(std::make_pair(i, el.first));
            }
            else
            {
                uniqueEdges.insert(std::make_pair(el.first, i));
            }
        }
    }

    generateDotFile(randomGraph, colors, colorMap, "seqColor.dot", uniqueEdges);

    std::cout << "To check the result of the sequential coloring, look at the seqColor.dot file in the build folder and use the graphviz extention to visualize." << std::endl;
};
