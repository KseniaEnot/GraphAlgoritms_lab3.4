#pragma once
#include "Iterator.h";
#include "dualList.h"
#include "Stack.h"
#include "Queue.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class Graph
{
private:
	int** Graph_Matrix;
	int Vertices;
	bool Directed;
	bool DirectedCheck();
	bool IfCycleNoDir();

public:
	Graph(int** new_graph = NULL, int ver_num = 0) {
		Graph_Matrix = new_graph;
		Vertices = ver_num;
		Directed = DirectedCheck();
	};

	Graph(int choice, string filename = "in.txt"); //choice 1 - cin, 2 - file

	int GetSize();
	bool IfEulerian();
	bool IfBipartite();
	bool IfTree();
	int* PruferCode();
	void TrZam();
	void PruferDecode(int*, int);
	dualList* StrongConnected();
	int* Dijkstra(int);
	friend std::ostream& operator << (std::ostream&, const Graph&);
	friend bool operator == (Graph& left, int right[]) {
		for (int i = 0; i < left.Vertices; i++)
			for (int j = 0; j < left.Vertices; j++)
				if (left.Graph_Matrix[i][j] != right[i * left.Vertices + j]) return false;
		return true;
	}

	Iterator* create_dft_iterator(int); // depth-first traverse iterator
	Iterator* create_bft_iterator(int); // breadth-first traverse iterator

	class dft_Iterator : public Iterator // depth-first traverse
	{
	private:
		bool* visited;
		int** ItrG;
		Stack* stack;
		int Icurrent;
		int sizeV;
		int before;
		bool connection;
	public:
		dft_Iterator(int** Gr, int max, int start = 0) {
			stack = new Stack();
			sizeV = max;
			ItrG = Gr;
			Icurrent = start;
			visited = new bool[max];
			stack->push(Icurrent);
			for (size_t i = 0; i < max; i++)
				visited[i] = false;
			visited[Icurrent] = true;
			before = -1;
			connection = true;
		};
		int next();
		bool has_next();
		bool newconnection();
		int beforecur();
		~dft_Iterator() {
			delete visited;
			delete* ItrG;
		}
	};

	class bft_Iterator : public Iterator // depth-first traverse
	{
	private:
		bool* visited;
		int** ItrG;
		Queue* queue;
		int Icurrent;
		int sizeV;
		int before = -1;
		bool connection;
	public:
		bft_Iterator(int** Gr, int max, int start = 0) {
			queue = new Queue();
			sizeV = max;
			ItrG = Gr;
			Icurrent = start;
			visited = new bool[max];
			queue->push(Icurrent);
			for (size_t i = 0; i < max; i++)
				visited[i] = false;
			visited[Icurrent] = true;
			connection = true;
		};
		int next();
		bool has_next();
		bool newconnection();
		int beforecur();
		~bft_Iterator() {
			delete visited;
			delete* ItrG;
		}
	};

	~Graph() {
		for (size_t i = 0; i < Vertices; i++)
			free(Graph_Matrix[i]);
		free(Graph_Matrix);
	}
};
