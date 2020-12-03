#include <iostream>
#include "Graph.h"
#include "Iterator.h";

int main()
{
    std::cout << "Hello World!\n";
    Graph g;
    cout << g;
    cout << "ok";
    Iterator* g_dft_iterator = g.create_dft_iterator(0);
    while (g_dft_iterator->has_next())
    {
        std::cout << g_dft_iterator->next() << " ";
    }
    std::cout << std::endl;
    Iterator* g_bft_iterator = g.create_bft_iterator(0);
    while (g_bft_iterator->has_next())
    {
        std::cout << g_bft_iterator->next() << " ";
    }
    std::cout << std::endl;

}
