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
    /*int cur;
    Iterator* g_bft_iterator = g.create_bft_iterator(0);
    while (g_bft_iterator->has_next())
    {
        std::cout << "next " << g_bft_iterator->next() << " ";
        cout << "has_next " << g_bft_iterator->has_next() << " ";
        cout << "connect " << g_bft_iterator->newconnection() << "\n";
    }*/
    std::cout << g.IfTree() << std::endl;

}
