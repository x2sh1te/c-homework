#include "Graph.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string file1 = "C:\Users\nikit\OneDrive\Desktop\дз c++\shape\shape\shape\testgraph.txt";
    Graph graph1(file1.c_str());
    vector<Graph> components1 = graph1.findGraphs();

    cout << "Количество графов в " << file1 << ": " << components1.size() << endl;
    for (int i = 0; i < components1.size(); ++i) {
        cout << "Граф " << i + 1 << " из " << file1 << endl;
        components1[i].print();
        string outFile = "C:\Users\nikit\OneDrive\Desktop\дз c++\shape\shape\shape/testgraph_comp_" +
                         to_string(i + 1) + ".txt";
        components1[i].print2file(outFile);
    }

    string file2 = "C:\Users\nikit\OneDrive\Desktop\дз c++\shape\shape\shape\1000.csv";
    Graph graph2(file2.c_str());
    vector<Graph> components2 = graph2.findGraphs();

    cout << "Количество графов в " << file2 << ": " << components2.size() << endl;
    for (int i = 0; i < components2.size(); ++i) {
        cout << "Граф " << i + 1 << " из " << file2 << endl;
        components2[i].print();
        string outFile = "C:\Users\nikit\OneDrive\Desktop\дз c++\shape\shape\shape/1000_comp_" +
                         to_string(i + 1) + ".txt";
        components2[i].print2file(outFile);
    }

    return 0;
}
