#include "Graph.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

void Graph::initGraph() {
	int choice;
	fstream f;
	cout << "Hello, choose input method\n 1 - console\n2 - file\n";
	cin >> choice;
	//reading vertices
	if (choice == 1) {
		cout << "Number of vertices: ";
		cin >> V;
	}
	else if (choice == 2) {
		string filename;
		cout << "Input file name: "; cin >> filename;
		f.open(filename, ios::in); //trow error if not opened
		f >> V;
	}
	else { cout << "Wrong input. Try again\n"; initGraph(); return; } //trow error

	//memory
	int** p;
	p = (int**)malloc(sizeof(int*) * V);
	if (!p) {
		throw std::out_of_range("Allocation error");
		return;
	}
	else {
		G = p;
	}

	//reading graph
	if (choice == 1) {
		for (int i = 0; i < V; i++)
		{
			p[i] = (int*)malloc(V * sizeof(int));
			if (!p[i]) { throw std::out_of_range("Allocation error"); return; }
			else G[i] = p[i];
			//reading
			for (int j = 0; j < V; j++)
			{
				int temp; cin >> temp;
				if (temp == 0 || temp == 1) G[i][j] = temp;
				else { throw std::invalid_argument("Input error"); V = 0; } //+clean graph to 0??????????
			}
		}
		cout << "Sucessfully read.\n";
	}
	else if (choice == 2) {
		//f >> noskipws;
		//we believe that people can write input properly i guess
		for (int i = 0; i < V; i++)
		{
			p[i] = (int*)malloc(V * sizeof(int));
			if (!p[i]) { throw std::out_of_range("Allocation error"); return; }
			else G[i] = p[i];
			//reading
			for (int j = 0; j < V; j++)
			{
				if (f.eof()) {
					throw std::invalid_argument("End of file"); //+clean graph to 0
				}
				int temp; f >> temp;
				if (temp == 0 || temp == 1) G[i][j] = temp;
				else { throw std::invalid_argument("Input error"); V = 0; } //+clean graph to 0????????????
			}
		}
		cout << "Sucessfully read." << V << endl;
		f.close();
	}
	return out;
	Directed = DirectedCheck();
}

bool Graph::DirectedCheck() {
	for (size_t i = 0; i < V; i++)
		for (size_t j = i; j < V; j++)
			if (G[i][j] != G[j][i])
				return true;
	return false;
}
bool Graph::IfCycle() {
	Iterator* g_dft_iterator = create_dft_iterator(0);
	bool* visited = new bool[V];
	for (size_t i = 0; i < V; i++)
		visited[i] = false;
	int cur;
	while (g_dft_iterator->has_next())
	{
		cur = g_dft_iterator->next();
		visited[cur] = true;
		for (size_t i = 0; i < V; i++)
			if ((G[cur][i] == 1) && (visited[i] == true))
				return true;
	}
	return false;
}

bool Graph::IfEulerian() {
	return true;
}

bool Graph::IfBipartite() {
	return true;
}

bool Graph::IfTree() {
	return true;
}

int* Graph::PruferCode() {
	return NULL;
}

void Graph::PruferDecode(int* PrufC) {

}

void Graph::StrongConnected() {

}

int* Graph::Dijkstra(int A, int B) {
	return NULL;
}

Iterator* Graph::create_dft_iterator(int start = 0) {
	return new dft_Iterator(G,V,start);
}

std::ostream& operator << (std::ostream& out, const Graph& Gr) {
	cout << "Graph: " << endl;
	for (int i = 0; i < Gr.V; i++) {
		for (int j = 0; j < Gr.V; j++) {
			cout << Gr.G[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}

bool Graph::dft_Iterator::has_next() {
    if (!Stack->isEmpty())
        return true;
    for (size_t i = 0; i < sizeV; i++)
        if (visited[i] == false)
            return true;
    return false;
}

int Graph::dft_Iterator::next() {
    if (!has_next()) {
        throw std::out_of_range("No more elements");
    }
	visited[Icurrent] = true;
    int temp = Icurrent;
    for (size_t i = 0; i < sizeV; i++)
        if ((visited[i] == false)&&(ItrG[Icurrent][i]==1))
        {
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
                Icurrent = i;
                Stack->push_back(Icurrent);
                break;
            }
    }
    return temp;
}

Iterator* Graph::create_bft_iterator(int start = 0) {
    return new bft_Iterator(G, V,start);
}

bool Graph::bft_Iterator::has_next() {
    if (!Queue->isEmpty())
        return true;
    for (size_t i = 0; i < sizeV; i++)
        if (visited[i] == false)
            return true;
    return false;
}

int Graph::bft_Iterator::next() {
    if (!has_next()) {
        throw std::out_of_range("No more elements");
    }
    visited[Icurrent] = true;
    int temp = Icurrent;
    /*На каждом шагу алгоритм берет из начала очереди вершину v и 
    добавляет все непосещенные смежные с v вершины в was и в конец очереди.*/
    for (size_t i = 0; i < sizeV; i++)
		if ((visited[i] == false) && (ItrG[Icurrent][i] == 1)) {
			Queue->push_back(i);
		}
    while (!Queue->isEmpty() && (visited[Icurrent] == true))
    {
        Icurrent = Queue->at(0);
        Queue->pop_front();
    }
    if (Queue->isEmpty() && (visited[Icurrent] == true))
    {
        for (size_t i = 0; i < sizeV; i++)
            if (visited[i] == false)
            {
                Icurrent = i;
				Queue->push_back(Icurrent);
                break;
            }
    }
    return temp;
}

