#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <queue>
#include <fstream>
#include <map>
#include <string>

class Node;

class Graph {
    std::set<Node*> nodes;
    std::map<std::string, Node*> name2node;

public:
    Graph(const char* file_name);
    ~Graph();
    Node* findNode(const std::string& name);
    void addNode(const std::string& name);
    void addEdge(const std::string& from, const std::string& to);
    auto begin() const { return nodes.begin(); }
    auto end() const { return nodes.end(); }
};

class Node {
    std::string name;
    std::set<Node*> neighbours;

    void addNeighbour(Node* n);
    void removeNeighbour(Node* n);

public:
    Node(const std::string& n) : name(n) {}
    const std::string& getName() const { return name; }
    auto nb_begin() const { return neighbours.begin(); }
    auto nb_end() const { return neighbours.end(); }

    friend class Graph;
};

// BFS для выделения компоненты связности
void bfs_component(Node* start, std::set<Node*>& comp);

void write_component_to_file(const std::set<Node*>& comp, int id);

#endif // GRAPH_H
