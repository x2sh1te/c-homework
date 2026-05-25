#include "bfs.h"
#include <set>
#include <iostream>

int main() {
    Graph g("1000.csv"); 

    std::set<Node*> unexplored(g.begin(), g.end());
    int component_no = 1;
    while (!unexplored.empty()) {
        Node* start = *(unexplored.begin());
        std::set<Node*> comp;
        bfs_component(start, comp);
        write_component_to_file(comp, component_no);
        std::cout << "Component " << component_no << " size: " << comp.size() << std::endl;
        for (Node* n : comp) unexplored.erase(n);
        ++component_no;
    }
    std::cout << "Total components: " << component_no - 1 << std::endl;
    return 0;
}
