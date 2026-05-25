#include "bfs.h"

// ==== Node methods ====
Node::Node(const std::string& aname) : name(aname) {}
const std::string& Node::getName() const { return name; }
auto Node::nb_begin() const { return neighbours.begin(); }
auto Node::nb_end() const { return neighbours.end(); }
void Node::addNeighbour(Node* n) { neighbours.insert(n); }
void Node::removeNeighbour(Node* n) { neighbours.erase(n); }

// ==== Graph methods ====
Graph::Graph(const char* file_name) {
    std::ifstream fin(file_name);
    std::string from, to;
    while (fin >> from >> to) {
        addNode(from); addNode(to);
        addEdge(from, to);
    }
}
Graph::~Graph() {
    for (Node* n : nodes) delete n;
}
void Graph::addNode(const std::string& name) {
    if (name2node.count(name) == 0) {
        Node* n = new Node(name);
        nodes.insert(n);
        name2node[name] = n;
    }
}
void Graph::addEdge(const std::string& from, const std::string& to) {
    Node* n1 = name2node[from];
    Node* n2 = name2node[to];
    n1->addNeighbour(n2);
    n2->addNeighbour(n1);
}
auto Graph::begin() const { return nodes.begin(); }
auto Graph::end() const { return nodes.end(); }
Node* Graph::findNode(const std::string& name) const {
    auto it = name2node.find(name);
    return (it != name2node.end()) ? it->second : nullptr;
}

// ==== BFS ====
BFS::BFS(const Graph& agraph) : graph(agraph) {}
void BFS::component(Node* start, std::set<Node*>& out_nodes) {
    std::queue<Node*> q;
    std::set<Node*> visited;
    q.push(start);
    while (!q.empty()) {
        Node* n = q.front(); q.pop();
        if (visited.count(n)) continue;
        visited.insert(n);
        out_nodes.insert(n);
        for (auto it = n->nb_begin(); it != n->nb_end(); ++it)
            if (!visited.count(*it))
                q.push(*it);
    }
}

// ==== Файл-компонента ====
void write_component_to_file(const std::set<Node*>& comp, int idx) {
    std::ofstream ofs("TestGraph_Component_" + std::to_string(idx) + ".txt");
    std::set<std::pair<std::string, std::string>> edges;
    for (Node* n : comp)
        for (auto it = n->nb_begin(); it != n->nb_end(); ++it)
            if (n->getName() < (*it)->getName() && comp.count(*it))
                edges.insert({ n->getName(), (*it)->getName() });
    for (auto& e : edges)
        ofs << e.first << " " << e.second << "\n";
    ofs.close();
}