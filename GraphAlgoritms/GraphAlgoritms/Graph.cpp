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
				if (i == j) G[i][j] = 0;
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
				if (i == j) G[i][j] = 0;
			}
		}
		cout << "Sucessfully read." << V << endl;
		f.close();
	}
	Directed = DirectedCheck();
}

void Graph::QuickSort(int L, int R, int* arr)
{
	int x = arr[(R + L) / 2]; //choose the middle element as a pivot
	int swapbuf;
	int i = L, j = R;
	do
	{
		while (arr[i] < x)//looking for an element smaller than the pivot
			i++;
		while (arr[j] > x)//looking for an element bigger than the pivot
			j--;
		if (i <= j) // swap
		{
			swapbuf = arr[i];
			arr[i] = arr[j];
			arr[j] = swapbuf;
			i++;
			j--;
		}
	} while (i < j);
	if (i < R) //if they did not go beyond the bounds of the array
		QuickSort(i, R, arr);
	if (j > L)
		QuickSort(L, j, arr);
}

bool Graph::DirectedCheck() {
	for (size_t i = 0; i < V; i++)
		for (size_t j = i; j < V; j++)
			if (G[i][j] != G[j][i])
				return true;
	return false;
}

bool Graph::IfCycle() {
	if (Directed) {
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
	else {
		Iterator* g_dft_iterator = create_dft_iterator(0);
		bool* visited = new bool[V];
		for (size_t i = 0; i < V; i++)
			visited[i] = false;
		int cur,bef;
		while (g_dft_iterator->has_next())
		{
			bef = g_dft_iterator->beforecur();
			cur = g_dft_iterator->next();
			visited[cur] = true;
			for (size_t i = 0; i < V; i++)
				if ((G[cur][i] == 1) && (visited[i] == true) && (i != bef))
					return true;
		}
		return false;
	}
	
}

bool Graph::IfEulerian() {
	//check for connections
	Iterator* g_dft_iterator = create_dft_iterator(0);
	int max_connect = 0, cur_connect = 0;
	while (g_dft_iterator->has_next())
	{
		std::cout << g_dft_iterator->next() << " ";
		if (!g_dft_iterator->newconnection()) cur_connect++;
		else {
			if (max_connect > 1) { if (cur_connect > 1) return false; }
			if (cur_connect > max_connect) max_connect = cur_connect;
			cur_connect = 0;
		}
	}
	cout << cur_connect << " " << max_connect << endl;
	if (cur_connect > 1 && max_connect > 1) return false;

	//count
	int* count_rows, *count_col;
	count_rows = new int[V];
	count_col = new int[V];
	for (int j = 0; j < V; j++) count_col[j] = 0;
	for (int i = 0; i < V; i++) {
		count_rows[i] = 0;
		for (int j = 0; j < V; j++) {
			if (G[i][j] == 1) { count_rows[i]++; count_col[j]++; }
		}
	}

	for (int i = 0; i < V; i++)
		if (!Directed && (count_col[i] + count_rows[i]) % 2 != 0) return false;
		else if (Directed && (count_col[i] != count_rows[i])) return false;
	return true;
}

bool Graph::IfBipartite() {
	int* color = new int[V];
	for (size_t i = 0; i < V; i++)
		color[i] = 2; //1-black,0-white,2-grey
	Iterator* g_bft_iterator = create_bft_iterator(0);
	int cur;
	while (g_bft_iterator->has_next())
	{
		if (g_bft_iterator->newconnection())
		{
			cur = g_bft_iterator->next();
			color[cur] = 1;
		}
		else
			cur = g_bft_iterator->next();
		for (size_t i = 0; i < V; i++)
			if (G[cur][i] == 1)
			{
				switch (color[i])
				{
				case 2:
					if (color[cur] == 1)
						color[i] = 0;
					else color[i] = 1;
					break;
				default:
					if (color[i] == color[cur])
					{
						return false;
					}
					break;
				}
			}
	}
	return true;
}

bool Graph::IfTree() {
	if (IfCycle()) return false;
	Iterator* g_dft_iterator = create_dft_iterator(0);
	if (Directed)
	{
		int countDeg;
		int count = 0;
		for (size_t i = 0; i < V; i++)
		{
			countDeg = 0;
			for (size_t j = 0; j < V; j++)
				countDeg += G[j][i];
			if (countDeg>1)
			{
				return false;
			}
			else if (countDeg==0)
			{
				count++;
				if (count > 1)
					return false;
			}
		}
	}
	else {
		while (g_dft_iterator->has_next())
		{
			g_dft_iterator->next();
			if (g_dft_iterator->newconnection()) return false;
		}
	}
	return true;
}

int* Graph::PruferCode() {
	return NULL;
}

void Graph::PruferDecode(int* PrufC) {

}

void Graph::StrongConnected() {
	/*
	1.Инвертируем дуги исходного ориентированного графа.
	2.Запускаем поиск в глубину на этом обращённом графе, запоминая, в каком порядке выходили из вершин.
	3.Запускаем поиск в глубину на исходном графе, в очередной раз выбирая не посещённую вершину с
	максимальным номером в векторе, полученном в п.2.
	4.Полученные из п.3 деревья и являются сильно связными компонентами.*/
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
		if ((visited[i] == false) && (ItrG[Icurrent][i] == 1))
		{
			before = Icurrent;
			Icurrent = i;
			Stack->push_back(Icurrent);
			connection = false;
			break;
		}
	int backcur;
	while ((temp == Icurrent) && !Stack->isEmpty())
	{
		backcur = Stack->at(Stack->get_size() - 1);
		Stack->pop_back();
		for (size_t i = 0; i < sizeV; i++)
			if ((visited[i] == false) && (ItrG[backcur][i] == 1))
			{
				before = backcur;
				Icurrent = i;
				Stack->push_back(Icurrent);
				connection = false;
				break;
			}
	}
	if (temp == Icurrent)
	{
		for (size_t i = 0; i < sizeV; i++)
			if (visited[i] == false)
			{
				before = -1;
				Icurrent = i;
				Stack->push_back(Icurrent);
				connection = true;
				break;
			}
	}
	return temp;
}

int  Graph::dft_Iterator::beforecur() {
	return before;
}

bool  Graph::dft_Iterator::newconnection() {
	return connection;
}

Iterator* Graph::create_bft_iterator(int start = 0) {
	return new bft_Iterator(G, V, start);
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
	for (size_t i = 0; i < sizeV; i++)
		if ((visited[i] == false) && (ItrG[Icurrent][i] == 1)) {
			Queue->push_back(i);
		}
	while (!Queue->isEmpty() && (visited[Icurrent] == true))
	{
		Icurrent = Queue->at(0);
		connection = false;
		Queue->pop_front();
	}
	if (Queue->isEmpty() && (visited[Icurrent] == true))
	{
		for (size_t i = 0; i < sizeV; i++)
			if (visited[i] == false)
			{
				Icurrent = i;
				Queue->push_back(Icurrent);
				connection = true;
				break;
			}
	}
	return temp;
}

int  Graph::bft_Iterator::beforecur() {
	return before;
}

bool  Graph::bft_Iterator::newconnection() {
	return connection;
}

