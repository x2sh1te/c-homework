#include "Graph.h"

// Node 

Node::Node(const string& aname) { name = aname; }
string Node::getName() const { return name; }
node_iterator Node::nb_begin() { return neighbours.begin(); }
node_iterator Node::nb_end() { return neighbours.end(); }
void Node::addNeighbour(Node* neighbour) { neighbours.insert(neighbour); }

Graph::Graph(const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Не удалось открыть файл: " << filename << endl;
        exit(1);
    }
    string src, dest;
    while (file >> src >> dest) {
        Node* s;
        Node* d;
        if (nodeMap.find(src) == nodeMap.end()) {
            s = new Node(src);
            addNode(s);
            nodeMap[src] = s;
        } else s = nodeMap[src];

        if (nodeMap.find(dest) == nodeMap.end()) {
            d = new Node(dest);
            addNode(d);
            nodeMap[dest] = d;
        } else d = nodeMap[dest];

        addEdge(s, d);
    }
    file.close();
}

Graph::~Graph() {
    for (Node* n : nodes)
        delete n;
}

void Graph::addNode(Node* node) { nodes.insert(node); }

void Graph::addEdge(Node* from, Node* to) {
    from->addNeighbour(to);
    to->addNeighbour(from);
}

node_iterator Graph::begin() { return nodes.begin(); }
node_iterator Graph::end() { return nodes.end(); }

// Алгоритм поиска компонент 

vector<Graph> Graph::findComponents() {
    vector<Graph> result;
    set<Node*> visited;

    for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        Node* start = *it;
        if (visited.find(start) != visited.end())
            continue;

        Graph component(""); // Можно пустую строку: граф будем собирать вручную!
        queue<Node*> q;
        q.push(start);

        while (!q.empty()) {
            Node* n = q.front(); q.pop();
            if (visited.find(n) != visited.end()) continue;
            visited.insert(n);
            Node* newNode = new Node(n->getName());
            component.addNode(newNode);
            component.nodeMap[newNode->getName()] = newNode;
            for (node_iterator nb = n->nb_begin(); nb != n->nb_end(); ++nb) {
                if (visited.find(*nb) == visited.end())
                    q.push(*nb);
            }
        }
        // Восстановим рёбра внутри компоненты
        for (node_iterator nit = component.begin(); nit != component.end(); ++nit) {
            string oldName = (*nit)->getName();
            Node* oldNode = nodeMap[oldName];
            for (node_iterator nb = oldNode->nb_begin(); nb != oldNode->nb_end(); ++nb) {
                string nbName = (*nb)->getName();
                if (component.nodeMap.find(nbName) != component.nodeMap.end()) {
                    component.addEdge(component.nodeMap[oldName], component.nodeMap[nbName]);
                }
            }
        }
        result.push_back(component);
    }
    return result;
}

//  Печать рёбер на экран и в файл

void Graph::print() {
    for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        cout << (*it)->getName() << ": ";
        for (node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); ++nb)
            cout << (*nb)->getName() << " ";
        cout << endl;
    }
}

void Graph::print2file(const string& fileName) {
    ofstream file(fileName);
    set<string> printedEdges;
    for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        for (node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); ++nb) {
            string a = (*it)->getName();
            string b = (*nb)->getName();
            string edge = (a < b) ? a + " " + b : b + " " + a;
            if (printedEdges.find(edge) == printedEdges.end()) {
                printedEdges.insert(edge);
                file << edge << endl;
            }
        }
    }
    file.close();
}
