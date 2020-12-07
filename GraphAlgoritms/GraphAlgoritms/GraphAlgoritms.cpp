#include <iostream>
#include "Graph.h"
#include "Iterator.h";

int main()
{
    std::cout << "Hello World!\n";
    Graph g;
    cout << g;
    cout << "ok";
    std::cout << std::endl;
    int* code = new int[3];
    for (int i = 0; i < 3; i++) cin >> code[i];
    //code = g.PruferCode();
    g.PruferDecode(code, 3);
    cout << g;
    /*int cur;
    Iterator* g_bft_iterator = g.create_bft_iterator(0);
    while (g_bft_iterator->has_next())
    {
        std::cout << "next " << g_bft_iterator->next() << " ";
        cout << "has_next " << g_bft_iterator->has_next() << " ";
        cout << "connect " << g_bft_iterator->newconnection() << "\n";
    }
     std::cout << std::endl;
    std::cout << g.IfBipartite() << std::endl;
    std::cout << std::endl;
    cout << "ok\n";
    cout << endl << g.IfEulerian();
    Iterator* g_dft_iterator = g.create_dft_iterator(0);
    while (g_dft_iterator->has_next() != 0)
    {
        std::cout << "next " << g_dft_iterator->next() << " ";
        cout << "has_next " << g_dft_iterator->has_next() << " ";
        cout << "connect " << g_dft_iterator->newconnection() << "\n";
    }*/    

}
