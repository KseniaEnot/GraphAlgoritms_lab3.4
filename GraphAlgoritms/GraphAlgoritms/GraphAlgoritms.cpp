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
    dualList* Sv = g.StrongConnected();
    int i = 0;
    while (!Sv[i].isEmpty())
    {
        for (size_t j = 0; j < Sv[i].get_size(); j++)
        {
            cout << Sv[i].at(j) << " ";
        }
        cout << endl;
        i++;
    }


    /*int i = 0;
    Iterator* g_dft_iterator = g.create_dft_iterator(0);
    while (g_dft_iterator->has_next() != 0)
    {
        std::cout << i << " next: " << g_dft_iterator->next() << endl;
        i++;
    }
    while (g_dft_iterator->has_next() != 0)
    {
        std::cout << "next " << g_dft_iterator->next() << " ";
        cout << "has_next " << g_dft_iterator->has_next() << " ";
        cout << "connect " << g_dft_iterator->newconnection() << "\n";
    }*/    

}
