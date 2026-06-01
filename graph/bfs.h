#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class Node;

typedef set<Node*>::iterator node_iterator;

// Вершина графа
class Node {
    string name;
    set<Node*> neighbours;
    void addNeighbour(Node* neighbour);
public:
    Node(const string& aname);
    string getName() const;
    node_iterator nb_begin();
    node_iterator nb_end();
    friend class Graph;
};

// Граф
class Graph {
    set<Node*> nodes;
    map<string, Node*> nodeMap;
public:
    Graph(const string& fileName);
    ~Graph();
    void addNode(Node* node);
    void addEdge(Node* begin, Node* end);
    node_iterator begin();
    node_iterator end();
    vector<Graph> findComponents(); 
    void print();                   
    void print2file(const string& fileName); /
};

#endif
