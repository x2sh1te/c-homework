#include "bfs.h"
#include <set>

int main() {
    Graph g("TestGraph.txt");
    std::set<Node*> unexplored(g.begin(), g.end());
    int component_no = 1;
    while (!unexplored.empty()) {
        Node* start = *(unexplored.begin());
        std::set<Node*> comp;
        BFS(g).component(start, comp);
        write_component_to_file(comp, component_no);
        for (Node* n : comp) unexplored.erase(n);
        ++component_no;
    }
    return 0;
}