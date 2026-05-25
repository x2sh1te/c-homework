#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <set>
#include <queue>
#include <fstream>
#include <map>

class Node {
    std::string name;
    std::set<Node*> neighbours;
    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);
public:
    Node(const std::string& aname);
    const std::string& getName() const;
    auto nb_begin() const;
    auto nb_end() const;
    friend class Graph;
};

class Graph {
    std::set<Node*> nodes;
    std::map<std::string, Node*> name2node; // для поиска по имени
public:
    Graph(const char* file_name);
    ~Graph();
    void addNode(const std::string& name);
    void addEdge(const std::string& from, const std::string& to);
    auto begin() const;
    auto end() const;
    Node* findNode(const std::string& name) const;
};

class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph);
    void component(Node* start, std::set<Node*>& out_nodes);
};

void write_component_to_file(const std::set<Node*>& comp, int idx);

#endif // GRAPH_H
