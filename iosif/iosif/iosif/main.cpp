#include <iostream>
#include <fstream>
#include <ctime>
#include "array.h"
using namespace std;

int josephus(int N, int k)
{
    Array arr(N);
    for (int i = 1; i <= N; i++)
        arr.insert(i);
    int pos = 0;

    while (arr.getSize() > 1)
    {
        pos = (pos + k - 1) % arr.getSize();
        arr.remove(pos);
    }

    return arr[0];
}

int main()
{
    setlocale(LC_ALL, "Russian");

    ofstream file("results.csv");
    file << "N,k,Result,Time(seconds)" << endl;

    int tests[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 2;
    for (int N : tests)
    {
        clock_t start = clock();
        int result = josephus(N, k);
        clock_t end = clock();

        double time = double(end - start) / CLOCKS_PER_SEC;

        file << N << "," << k << "," << result << ","
            << fixed << setprecision(6) << time << endl;

        cout << "N=" << N << "Результат=" << result
            << "Время=" << time << " сек" << endl;
    }
    file.close();

    return 0;
}
