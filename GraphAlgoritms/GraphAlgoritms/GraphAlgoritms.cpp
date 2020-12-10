#include <iostream>
#include "Graph.h"
#include "Iterator.h";

int main()
{
    //int* code = new int[3];
    //for (int i = 0; i < 3; i++) cin >> code[i];
    //code = g.PruferCode();
    //g.PruferDecode(code, 3);
    /*int cur;
    Iterator* g_bft_iterator = g.create_bft_iterator(0);
    while (g_bft_iterator->has_next());*/
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
        for (size_t j = 0; j < Sv[i].get_size(); j++)
        {
            cout << Sv[i].at(j) << " ";
        }
        cout << endl;
        i++;
    }
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
