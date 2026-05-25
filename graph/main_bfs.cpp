#include "Graph.h"

int main() {
    // testgraph.txt
    string file1 = "testgraph.txt"; 
    Graph inputGraph(file1);

    // Получаем ВСЕ компоненты как вектор Graph-ов 
    vector<Graph> allComponents = inputGraph.findComponents();

    cout << "Итого компонент для " << file1 << ": " << allComponents.size() << endl;
    for (int i = 0; i < allComponents.size(); ++i) {
        cout << "Компонента " << (i+1) << ":" << endl;
        allComponents[i].print();
        string outFile = "component_" + to_string(i+1) + ".txt";
        allComponents[i].print2file(outFile);
    }

    // 1000.csv 
    string file2 = "1000.csv";
    Graph inputGraph2(file2);
    vector<Graph> components2 = inputGraph2.findComponents();

    cout << "Итого компонент для " << file2 << ": " << components2.size() << endl;
    for (int i = 0; i < components2.size(); ++i) {
        cout << "Компонента " << (i+1) << " (2-й файл):" << endl;
        string outFile = "1000_comp_" + to_string(i+1) + ".txt";
        components2[i].print2file(outFile);
    }

    return 0;
}
