#include "Graph.h"
#include <iostream>
#include <stdlib.h>

void Graph::initGraph() {

}

bool Graph::IfEulerian() {

}

bool Graph::IfBipartite() {

}

bool Graph::IfTree() {
	
}

int* Graph::PruferCode() {

}

void Graph::PruferDecode(int* PrufC) {

}

void Graph::StrongConnected() {

}

int* Graph::Dijkstra(int A, int B) {

}

Iterator* Graph::create_dft_iterator() {
	return new dft_Iterator(G,V);
}

bool Graph::dft_Iterator::has_next() {
    for (size_t i = 0; i < sizeV; i++)
        if (visited[i] == false)
            return true;
    if (!Stack->isEmpty())
        return true;
    else
        return false;
}

int Graph::dft_Iterator::next() {
    if (!has_next()) {
        throw std::out_of_range("No more elements");
    }
    int temp = Icurrent;
    for (size_t i = 0; i < sizeV; i++)
        if ((visited[i] == false)&&(ItrG[Icurrent][i]==1))
        {
            visited[i] = true;
            Icurrent = i;
            Stack->push_back(Icurrent);
            break;
        }
    int backcur;
    while ((temp == Icurrent)&& !Stack->isEmpty())
    {
        backcur=Stack->at(Stack->get_size() - 1);
        Stack->pop_back();
        for (size_t i = 0; i < sizeV; i++)
            if ((visited[i] == false) && (ItrG[backcur][i] == 1))
            {
                visited[i] = true;
                Icurrent = i;
                Stack->push_back(Icurrent);
                break;
            }
    }
    if (temp == Icurrent)
    {
        for (size_t i = 0; i < sizeV; i++)
            if (visited[i] == false)
            {
                visited[i] = true;
                Icurrent = i;
                Stack->push_back(Icurrent);
                break;
            }
    }
    return temp;
}

Iterator* Graph::create_bft_iterator() {
	//return new dft_Iterator(/**/);
}
