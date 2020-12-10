#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Iterator.h";

int main()
{
    std::cout << "Hello World!\n";
    Graph g_test(1);
    cout << g_test;
    //bipatite
    cout << "Bipartite: " << g_test.IfBipartite() << endl;
    //euler
    cout << "Eulerian: " << g_test.IfEulerian() << endl;
    //tree
    cout << "Tree: " << g_test.IfTree() << endl;
    //bft iterator
    cout << endl << "bft Iterator:\n";
    Iterator* g_bft_iterator = g_test.create_bft_iterator(0);
    std::cout << "next " << g_bft_iterator->next() << " ";
    while (g_bft_iterator->has_next() != 0)
    {
        std::cout << "next " << g_bft_iterator->next() << " ";
    }
    //dft iterator
    cout << endl << "dft Iterator:\n";
    Iterator* g_dft_iterator = g_test.create_dft_iterator(0);
    std::cout << "next " << g_dft_iterator->next() << " ";
    while (g_dft_iterator->has_next() != 0)
    {
        std::cout << "next " << g_dft_iterator->next() << " ";
    }
    //Dijkstra
    int* dij1_arr = new int[g_test.GetSize()];
    dij1_arr = g_test.Dijkstra(0);
    cout << "\nShortest path from 0 to\n";
    for (int j = 0; j < g_test.GetSize(); j++)
        cout << j << ": " << dij1_arr[j] << " \n";
    cout << endl;

}
