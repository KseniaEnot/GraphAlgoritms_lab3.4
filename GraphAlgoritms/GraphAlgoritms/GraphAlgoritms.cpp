#include <iostream>
#include "Graph.h"
#include "Iterator.h";

int main()
{
    std::cout << "Hello World!\n";
    Graph g;
    cout << g;
    cout << "ok\n";
    cout << endl << g.IfEulerian();
    Iterator* g_dft_iterator = g.create_dft_iterator(0);
    while (g_dft_iterator->has_next() != 0)
    {
        std::cout << "next " << g_dft_iterator->next() << " ";
        cout << "has_next " << g_dft_iterator->has_next() << " ";
        cout << "connect " << g_dft_iterator->newconnection() << "\n";
    }
    std::cout << std::endl;
    Iterator* g_bft_iterator = g.create_bft_iterator(2);
    while (g_bft_iterator->has_next() != 0)
    {
        std::cout << "next " << g_bft_iterator->next() << " ";
        cout << "has_next " << g_bft_iterator->has_next() << " ";
        cout << "connect " << g_bft_iterator->newconnection() << "\n";
    }
    std::cout << std::endl;

}
