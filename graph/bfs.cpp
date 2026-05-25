#include "bfs.h"

// ============ Node ============

void Node::addNeighbour(Node* n) {
    neighbours.insert(n);
}
void Node::removeNeighbour(Node* n) {
    neighbours.erase(n);
}

// ============ Graph ============

Graph::Graph(const char* file_name) {
    std::ifstream fin(file_name);
    if (!fin.is_open()) {
        std::cout << "error open file " << file_name << std::endl;
        exit(1);
    }
    std::string from, to;
    while (fin >> from >> to) {
        addNode(from);
        addNode(to);
        addEdge(from, to);
    }
}

Graph::~Graph() {
    for (Node* n : nodes)
        delete n;
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
Node* Graph::findNode(const std::string& name) {
    auto it = name2node.find(name);
    if (it == name2node.end()) return nullptr;
    return it->second;
}

// ============= BFS обход ==============
void bfs_component(Node* start, std::set<Node*>& comp) {
    std::queue<Node*> q;
    std::set<Node*> visited;
    q.push(start);
    while (!q.empty()) {
        Node* n = q.front(); q.pop();
        if (visited.count(n)) continue;
        visited.insert(n);
        comp.insert(n);
        for (auto it = n->nb_begin(); it != n->nb_end(); ++it) {
            if (!visited.count(*it))
                q.push(*it);
        }
    }
}

// ============= Запись компоненты ==============
void write_component_to_file(const std::set<Node*>& comp, int id) {
    std::string fname = "Component_" + std::to_string(id) + ".txt";
    std::ofstream ofs(fname);
    if (!ofs.is_open()) {
        std::cout << "Ошибка открытия файла для записи: " << fname << std::endl;
        return;
    }
    std::set<std::pair<std::string, std::string>> edges;
    for (Node* n : comp) {
        for (auto nb = n->nb_begin(); nb != n->nb_end(); ++nb) {
            if (n->getName() < (*nb)->getName() && comp.count(*nb)) {
                edges.insert({ n->getName(), (*nb)->getName() });
            }
        }
    }
    for (const auto& e : edges) {
        ofs << e.first << " " << e.second << "\n";
    }
    ofs.close();
}
