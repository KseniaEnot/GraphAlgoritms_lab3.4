#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Iterator.h";

int main()
{
    std::cout << "Hello World!\n";
    Graph g_bft(2, "tests/testBFT1.txt");
    cout << endl;
    Iterator* g_bft_iterator = g_bft.create_bft_iterator(0);
    std::cout << "next " << g_bft_iterator->next() + 1 << " ";
    cout << "has_next " << g_bft_iterator->has_next() << " ";
    cout << "connect " << g_bft_iterator->newconnection() << "\n";
    while (g_bft_iterator->has_next() != 0)
    Graph gIB1(2, "tests//testIfBipartite1.txt");
    cout << gIB1.IfBipartite() << endl;
    Graph gIB2(2, "tests//testIfBipartite2.txt");
    cout << gIB2.IfBipartite() << endl;
    Graph gIB3(2, "tests//testIfBipartite3.txt");
    cout << gIB3.IfBipartite() << endl;
    cout << endl;

    Graph gIE1(2, "tests//testIfEulerian1.txt");
    cout << gIE1.IfEulerian() << endl;
    Graph gIE2(2, "tests//testIfEulerian2.txt");
    cout << gIE2.IfEulerian() << endl;
    Graph gIE3(2, "tests//testIfEulerian3.txt");
    cout << gIE3.IfEulerian() << endl;
    cout << endl;

    Graph gIT1(2, "tests//testIfTree1.txt");
    cout << gIT1.IfTree() << endl;
    Graph gIT2(2, "tests//testIfTree2.txt");
    cout << gIT2.IfTree() << endl;
    Graph gIT3(2, "tests//testIfTree3.txt");
    cout << gIT3.IfTree() << endl;
    cout << endl;

    Graph gPC1(2, "tests//testPruferCode1.txt");
    int* code1 = new int[gPC1.GetSize() - 2];
    code1 = gPC1.PruferCode();
    for (size_t i = 0; i < (gPC1.GetSize()-2); i++)
    {
        cout << code1[i] << " ";
    }
    cout << endl;
    Graph gPC2(2, "tests//testPruferCode2.txt");
    int* code2 = new int[gPC2.GetSize()- 2];
    code2 = gPC2.PruferCode();
    for (size_t i = 0; i < gPC2.GetSize()-2; i++)
    {
        cout << code2[i] << " ";
    }
    cout << endl;
    Graph gPC3(2, "tests//testPruferCode3.txt");
    int* code3 = new int[gPC3.GetSize() - 2];
    code3 = gPC3.PruferCode();
    for (size_t i = 0; i < gPC3.GetSize() - 2; i++)
    {
        cout << code3[i] << " ";
    }
    cout << endl;


    Graph gSC1(2,"tests//testStrongConnected1.txt");
    dualList* Sv = gSC1.StrongConnected();
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
    cout << endl;
    Graph gSC2(2, "tests//testStrongConnected2.txt");
    Sv = gSC2.StrongConnected();
    i = 0;
    while (!Sv[i].isEmpty())
    {
        std::cout << "next " << g_bft_iterator->next() + 1 << " ";
        cout << "has_next " << g_bft_iterator->has_next() << " ";
        cout << "connect " << g_bft_iterator->newconnection() << "\n";
    }

    cout << "NEW TEST\n";
    Graph g_bft2(2, "tests/testBFT2.txt");
    cout << endl;
    Iterator* g_bft_iterator2 = g_bft2.create_bft_iterator(0);
    while (g_bft_iterator2->has_next() != 0)
    {
        std::cout << "next " << g_bft_iterator2->next() << " ";
        cout << "has_next " << g_bft_iterator2->has_next() << " ";
        cout << "connect " << g_bft_iterator2->newconnection() << "\n";
    }

    cout << "NEW TEST\n";
    Graph g_dft(2, "tests/testDFT1.txt");
    cout << endl;
    Iterator* g_dft_iterator = g_dft.create_dft_iterator(0);
    while (g_dft_iterator->has_next() != 0)
    {
        std::cout << "next " << g_dft_iterator->next() << " ";
        cout << "has_next " << g_dft_iterator->has_next() << " ";
        cout << "connect " << g_dft_iterator->newconnection() << "\n";
    }

    cout << "NEW TEST\n";
    Graph g_dft2(2, "tests/testDFT2.txt");
    cout << endl;
    Iterator* g_dft_iterator2 = g_dft2.create_dft_iterator(0);
    while (g_dft_iterator2->has_next() != 0)
    {
        std::cout << "next " << g_dft_iterator2->next() << " ";
        cout << "has_next " << g_dft_iterator2->has_next() << " ";
        cout << "connect " << g_dft_iterator2->newconnection() << "\n";
    }

    cout << "NEW TEST\n";
    Graph g_digkstra1(2, "tests/testDijkstra1.txt");
    int* dij1_arr = new int[g_digkstra1.GetSize()];
    dij1_arr = g_digkstra1.Dijkstra(2);
    for (int j = 0; j < g_digkstra1.GetSize(); j++)
        cout << dij1_arr[j] << " ";
    cout << endl;

    cout << "NEW TEST\n";
    Graph g_digkstra2(2, "tests/testDijkstra2.txt");
    int* dij2_arr = new int[g_digkstra2.GetSize()];
    dij2_arr = g_digkstra2.Dijkstra(3);
    for (int j = 0; j < g_digkstra2.GetSize(); j++)
        cout << dij2_arr[j] << " ";
    cout << endl;

    cout << "NEW TEST\n";
    Graph g1;
    fstream file; int length_Pruf; 
    file.open("tests/testPruferDecode1.txt", ios::in);
    file >> length_Pruf;
    int* Pruf = new int[length_Pruf];
    for (int i = 0; i < length_Pruf; i++)
        file >> Pruf[i];
    g1.PruferDecode(Pruf, length_Pruf);
    cout << g1;
    file.close();

    cout << "NEW TEST\n";
    Graph g2;
    file.open("tests/testPruferDecode2.txt", ios::in);
    file >> length_Pruf;
    int* Pruf2 = new int[length_Pruf];
    for (int i = 0; i < length_Pruf; i++)
        file >> Pruf2[i];
    g2.PruferDecode(Pruf2, length_Pruf);
    cout << g2;

    //Graph ggggg(2);
    //cout << ggggg;

    int* Pruf3 = new int[0];
    g2.PruferDecode(Pruf3, 0);
    cout << g2;
    cout << endl;
    Graph gSC3(2, "tests//testStrongConnected3.txt");
    Sv = gSC3.StrongConnected();
    i = 0;
    while (!Sv[i].isEmpty())
    {
        for (size_t j = 0; j < Sv[i].get_size(); j++)
        {
            cout << Sv[i].at(j) << " ";
        }
        cout << endl;
        i++;
    }
    cout << endl;
    Graph gSC4(2, "tests//testStrongConnected4.txt");
    Sv = gSC4.StrongConnected();
    i = 0;
    while (!Sv[i].isEmpty())
    {
        for (size_t j = 0; j < Sv[i].get_size(); j++)
        {
            cout << Sv[i].at(j) << " ";
        }
        cout << endl;
        i++;
    }
    cout << endl;

}
